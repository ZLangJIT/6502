#include <MultiTouch/MultiTouch.h>
#include <jni.h>
#include <string>
#include <time.h>

#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define NVG_LOG(...) os_log_error(__VA_ARGS__)
#define NANOVG_GLES3_IMPLEMENTATION
#define NANOVG_SW_IMPLEMENTATION
#define NVGSWU_GLES3

#include <nanovg.h>
#include <nanovg_vtex.h>
#include <nanovg_gl_utils.h>
#include <nanovg_sw.h>
#include <nanovg_sw_utils.h>

#define FONTSTASH_IMPLEMENTATION
#include <fontstash.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

MultiTouch multiTouch;

class JVM_MANAGER {
public:
    JavaVM * jvm;
    JNIEnv* jenv;
    JavaVMAttachArgs jvmArgs;
    bool needsToDetach;

    JVM_MANAGER();
    bool getJVM(JNIEnv * env);
    bool attachJVM();
    void detachJVM();

    template <typename J, typename O> O globalRef(J j, O o) {
        return reinterpret_cast<O>(j->NewGlobalRef(o));
    }
};

JVM_MANAGER::JVM_MANAGER() {
    jvm = nullptr;
    jenv = nullptr;
    needsToDetach = false;
    jvmArgs.version = JNI_VERSION_1_6;
}

bool JVM_MANAGER::getJVM(JNIEnv *env) {
    return env->GetJavaVM(&jvm) == JNI_OK;
}

bool JVM_MANAGER::attachJVM() {
    // checks if current env needs attaching or it is already attached
    jint res = jvm->GetEnv((void**)&jenv, JNI_VERSION_1_6);
    if (res == JNI_EDETACHED) {
        // Supported but not attached yet, needs to call AttachCurrentThread
        res = jvm->AttachCurrentThread(&jenv, &jvmArgs);
        if (res == JNI_OK) {
            needsToDetach = true;
        } else {
            // Failed to attach, cancel
            return false;
        }
    } else if (JNI_OK == res) {
        // Current thread already attached, do not attach 'again' (just to save the attachedHere flag)
        // We make sure to keep attached = 0
        needsToDetach = false;
    } else {
        // JNI_EVERSION, specified version is not supported cancel this..
        return false;
    }
    return true;
}

void JVM_MANAGER::detachJVM() {
    if (needsToDetach) {
        jvm->DetachCurrentThread();
    }
}

class AppInstance {
public:
    JVM_MANAGER jvmManager;
    jobject jObject;
    jclass jClass;
    jmethodID jSwapBuffers;
    int w;
    int h;
    NVGcontext* vg;
    NVGcontext* vgsw;
    NVGSWUblitter* vgsw_blitter;
    uint8_t* vgsw_blitter_fb;

    void swapBuffers();

    void onEglSetup(JNIEnv *jenv, jobject classInstance, jstring name, jstring signature, jboolean was_destroyed);
    void onEglTearDown(jboolean was_destroyed);

    void surfaceChanged(int w, int h);
    void onDraw();
    bool onTouchEvent(MultiTouch & touchEvent);
};

void AppInstance::onEglSetup (
  JNIEnv * jenv, jobject classInstance, jstring name, jstring signature, jboolean was_destroyed
) {
    if (!jvmManager.getJVM(jenv)) {
        os_log_error("failed to get JavaVM");
        return;
    }
    if (!jvmManager.attachJVM()) {
        os_log_error("failed to attach JVM");
        return;
    }
    jObject = jvmManager.globalRef(jenv, classInstance);
    jClass = jvmManager.globalRef(jenv, jenv->GetObjectClass(jObject));
    jboolean isCopy1, isCopy2;

    if (name == nullptr) {
        os_log_error("cannot use a null name (0x0)");
        return;
    }

    if (signature == nullptr) {
        os_log_error("cannot use a null signature (0x0)");
        return;
    }

    const char * n = jvmManager.jenv->GetStringUTFChars(name, &isCopy1);
    if (n == nullptr) {
        os_log_error("cannot get UTF chars from name");
        return;
    }

    const char * s = jvmManager.jenv->GetStringUTFChars(signature, &isCopy2);
    if (s == nullptr) {
        os_log_error("cannot get UTF chars from signature");
        jvmManager.jenv->ReleaseStringUTFChars(name, n);
        return;
    }

    jSwapBuffers = jvmManager.jenv->GetMethodID(jClass, n, s);

    if (jSwapBuffers == nullptr) {
        os_log_error(
                "cannot find method with name '%s', and signature '%s'", n, s
        );
    }

    jvmManager.jenv->ReleaseStringUTFChars(name, n);
    jvmManager.jenv->ReleaseStringUTFChars(name, s);

    if (was_destroyed) {
      //ImGui_ImplAndroid_Init(pApp->window);
      w = 0;
      h = 0;
      vg = nvglCreate(NVGL_DEBUG);
      vgsw = nvgswCreate(NVG_NO_FONTSTASH|NVG_SDF_TEXT);
      vgsw_blitter = nvgswuCreateBlitter();
      vgsw_blitter_fb = nullptr;
    }
}

void AppInstance::surfaceChanged (int w, int h) {
    this->w = w;
    this->h = h;
    if (vgsw_blitter_fb != nullptr) {
      delete[] vgsw_blitter_fb;
      vgsw_blitter_fb = new uint8_t[w*h*4];
    } else {
      vgsw_blitter_fb = new uint8_t[w*h*4];
    }
    memset(vgsw_blitter_fb, 0x3F, w*h*4);
    nvgswSetFramebuffer(vgsw, vgsw_blitter_fb, w, h, 0, 8, 16, 24);
}

void AppInstance::onEglTearDown (jboolean was_destroyed)
{
  if (was_destroyed) {
    nvgswDelete(vgsw);
    nvglDelete(vg);
    delete[] vgsw_blitter_fb;
    nvgswuDeleteBlitter(vgsw_blitter);
    h = 0;
    w = 0;
  }
  jvmManager.jenv->DeleteGlobalRef(jClass);
  jvmManager.jenv->DeleteGlobalRef(jObject);
  jvmManager.detachJVM();
  jSwapBuffers = nullptr;
}

void AppInstance::swapBuffers ()
{
    if (jSwapBuffers != nullptr) {
        jvmManager.jenv->CallVoidMethod(jObject, jSwapBuffers);
    }
}

void AppInstance::onDraw () {
    // we use an existing EGL context
    // Setup time step
    struct timespec current_timespec;
    clock_gettime(CLOCK_MONOTONIC, &current_timespec);
    double current_time = (double)(current_timespec.tv_sec) + (current_timespec.tv_nsec / 1000000000.0);
    //ImGuiIO& io = ImGui::GetIO();
    //io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
    //g_Time = current_time;
    NVGLUframebuffer* nvgFB = nvgluCreateFramebuffer(vg, 0, 0, NVGLU_NO_NVG_IMAGE);
    int prevFBO = nvgluBindFramebuffer(nvgFB);
    nvgluSetFramebufferSize(nvgFB, w, h, 0);
    nvgluSetViewport(0, 0, w, h);
    nvgluClear(nvgRGBAf(0.3f, 0.3f, 0.32f, 1.0f));
    nvgBeginFrame(vg, w, h, 1.0f);
    nvgEndFrame(vg);
    // blit to prev FBO and rebind it
    nvgluBlitFramebuffer(nvgFB, prevFBO);
    swapBuffers();
}

bool AppInstance::onTouchEvent(MultiTouch & touchEvent) {
    auto t = touchEvent.getTouchAt(touchEvent.getTouchIndex());
    if (t.state == MultiTouch::TOUCH_DOWN) {
      //f = 1.0f;
    } else if (t.state == MultiTouch::TOUCH_UP || t.state == MultiTouch::TOUCH_CANCELLED) {
      //f = 0.0f;
    }
    return true;
}

#define APP(jlong) reinterpret_cast<AppInstance*>(jlong)
#define JLONG(ptr) reinterpret_cast<jlong>(ptr)

static void GlDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam) {
  (void) length;
  (void) userParam;

  if (id == 131185) {
    // Buffer creation.
    return;
  }

  const char* strSource = "";
  switch (source)
  {
  case GL_DEBUG_SOURCE_API_KHR: strSource = "API"; break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR: strSource = "window system"; break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER_KHR: strSource = "shader compiler"; break;
  case GL_DEBUG_SOURCE_THIRD_PARTY_KHR: strSource = "third party"; break;
  case GL_DEBUG_SOURCE_APPLICATION_KHR: strSource = "application"; break;
  case GL_DEBUG_SOURCE_OTHER_KHR: strSource = "other"; break;
  }

  const char* strType = "";
  switch (type) {
  case GL_DEBUG_TYPE_ERROR_KHR: strType = "error"; break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR: strType = "deprecated behavior"; break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR: strType = "undefined behavior"; break;
  case GL_DEBUG_TYPE_PORTABILITY_KHR: strType = "portability"; break;
  case GL_DEBUG_TYPE_PERFORMANCE_KHR: strType = "performance"; break;
  case GL_DEBUG_TYPE_MARKER_KHR: strType = "marker"; break;
  case GL_DEBUG_TYPE_PUSH_GROUP_KHR: strType = "push group"; break;
  case GL_DEBUG_TYPE_POP_GROUP_KHR: strType = "pop group"; break;
  case GL_DEBUG_TYPE_OTHER_KHR: strType = "other"; break;
  }

  const char* strSeverity = "";
  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH_KHR: strSeverity = "HIGH"; break;
  case GL_DEBUG_SEVERITY_MEDIUM_KHR: strSeverity = "MEDIUM"; break;
  case GL_DEBUG_SEVERITY_LOW_KHR: strSeverity = "LOW"; break;
  case GL_DEBUG_SEVERITY_NOTIFICATION_KHR: strSeverity = "notification"; break;
  }

  switch (type)
  {
      case GL_DEBUG_TYPE_ERROR_KHR:
      case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR:
        os_log_fatal("[OpenGL]\n  source: %s\n  type: %s\n  severity: %s\n  message:\n%s", strSource, strSeverity, strType, message); break;
      case GL_DEBUG_TYPE_PORTABILITY_KHR:
        os_log_error("[OpenGL]\n  source: %s\n  type: %s\n  severity: %s\n  message:\n%s", strSource, strSeverity, strType, message); break;
      case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR:
      case GL_DEBUG_TYPE_PERFORMANCE_KHR:
      case GL_DEBUG_TYPE_MARKER_KHR:
      case GL_DEBUG_TYPE_PUSH_GROUP_KHR:
      case GL_DEBUG_TYPE_POP_GROUP_KHR:
      case GL_DEBUG_TYPE_OTHER_KHR:
      default:
        os_log_info("[OpenGL]\n  source: %s\n  type: %s\n  severity: %s\n  message:\n%s", strSource, strSeverity, strType, message); break;
  }
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_nativeOnContextCreated (
        JNIEnv * env, jobject thiz
)
{}

extern "C" JNIEXPORT jlong JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_createNativeInstance (
        JNIEnv * env, jobject thiz
)
{
    multiTouch.setMaxSupportedTouches(10);
    os_log_info("CREATE APP");
    return JLONG(new AppInstance());
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_destroyNativeInstance (
        JNIEnv * env, jobject thiz, jlong instance
)
{
    os_log_info("DESTROY APP");
    delete APP(instance);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_onEglSetup (
        JNIEnv * env, jobject thiz, jlong instance, jobject class_instance, jstring name,
        jstring signature, jboolean was_destroyed
)
{
    if (was_destroyed) {
        os_log_info("OpenGL ES Platform info:");
        os_log_info("Version: %s", glGetString(GL_VERSION));
        os_log_info("Vendor: %s", glGetString(GL_VENDOR));
        os_log_info("Renderer: %s", glGetString(GL_RENDERER));
        os_log_info("Shading language version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        
        #ifndef EGL_CONTEXT_FLAGS
        #  define EGL_CONTEXT_FLAGS                 0x821E
        #endif
        #ifndef EGL_CONTEXT_FLAGS_KHR
        #  define EGL_CONTEXT_FLAGS_KHR             0x30FC
        #endif
      
        GLint context_flags;
        glGetIntegerv(EGL_CONTEXT_FLAGS, &context_flags);
        if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT_KHR) {
          os_log_info("GL Context has debug flag, hooking up callback");
          glEnable(GL_DEBUG_OUTPUT_KHR);
          glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR);
          glDebugMessageCallbackKHR(GlDebugOutput, nullptr);
          glDebugMessageControlKHR(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }
    os_log_info("EGL SETUP [was_destroyed = %s]", was_destroyed ? "true" : "false");
    APP(instance)->onEglSetup(env, class_instance, name, signature, was_destroyed);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_surfaceChanged (
        JNIEnv * env, jobject thiz, jlong instance, jint w, jint h
)
{
    os_log_info("EGL SURFACE CHANGE");
    APP(instance)->surfaceChanged(w, h);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_addTouch__JFF(
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y
)
{
    multiTouch.addTouch(identifier, x, y);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_addTouch__JFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size
)
{
    multiTouch.addTouch(identifier, x, y, size);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_addTouch__JFFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size, jfloat pressure
)
{
    multiTouch.addTouch(identifier, x, y, size, pressure);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_moveTouch__JFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y
)
{
    multiTouch.moveTouch(identifier, x, y);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_moveTouch__JFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size
)
{
    multiTouch.moveTouch(identifier, x, y, size);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_moveTouch__JFFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size, jfloat pressure
)
{
    multiTouch.moveTouch(identifier, x, y, size, pressure);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_removeTouch__JFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y
)
{
    multiTouch.removeTouch(identifier, x, y);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_removeTouch__JFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size
)
{
    multiTouch.removeTouch(identifier, x, y, size);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_removeTouch__JFFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size, jfloat pressure
)
{
    multiTouch.removeTouch(identifier, x, y, size, pressure);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_cancelTouch__JFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y
)
{
    multiTouch.cancelTouch(identifier, x, y);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_cancelTouch__JFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size
)
{
    multiTouch.cancelTouch(identifier, x, y, size);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_cancelTouch__JFFFF (
        JNIEnv * env, jobject thiz,
        jlong identifier, jfloat x, jfloat y, jfloat size, jfloat pressure
)
{
    multiTouch.cancelTouch(identifier, x, y, size, pressure);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_onTouchEvent (
        JNIEnv * env, jobject thiz, jlong instance
)
{
    return APP(instance)->onTouchEvent(multiTouch);
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_onDraw (
        JNIEnv * env, jobject thiz, jlong instance
)
{
    APP(instance)->onDraw();
}

extern "C" JNIEXPORT void JNICALL
Java_smallville7123_graphical_tool_kit_DiligentEngineView_00024DiligentEngineRenderer_onEglTearDown (
        JNIEnv * env, jobject thiz, jlong instance, jboolean was_destroyed
)
{
    os_log_info("EGL TEAR DOWN [was_destroyed = %s]", was_destroyed ? "true" : "false");
    APP(instance)->onEglTearDown(was_destroyed);
}
