#include <MultiTouch/MultiTouch.h>
#include <jni.h>
#include <string>

#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"

#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define os_gl_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOGGING_FUNCTION, CASE_NAME, name, const, constSTRING, UNNAMED_STRING_CAN_PRINT_ERROR, UNNAMED_STRING_CANNOT_PRINT_ERROR, NAMED_STRING_CAN_PRINT_ERROR, NAMED_STRING_CANNOT_PRINT_ERROR, PRINT, IS_AN_ERROR) CASE_NAME: { \
    if(name == nullptr || name == nullptr || name == 0) { \
        if (PRINT) { \
            if ((UNNAMED_STRING_CAN_PRINT_ERROR) != nullptr) { \
                std::string msg = os_gl_INTERNAL_MESSAGE_PREFIX; \
                msg += UNNAMED_STRING_CAN_PRINT_ERROR; \
                LOGGING_FUNCTION(msg.c_str(), constSTRING); \
            } \
        } \
        else { \
            if ((UNNAMED_STRING_CANNOT_PRINT_ERROR) != nullptr) { \
                std::string msg = os_gl_INTERNAL_MESSAGE_PREFIX; \
                msg += UNNAMED_STRING_CANNOT_PRINT_ERROR; \
                LOGGING_FUNCTION("%s", msg.c_str()); \
            } \
        } \
    } \
    else { \
        if (PRINT) { \
            if ((NAMED_STRING_CAN_PRINT_ERROR) != nullptr) { \
                std::string msg = os_gl_INTERNAL_MESSAGE_PREFIX; \
                msg += NAMED_STRING_CAN_PRINT_ERROR; \
                LOGGING_FUNCTION(msg.c_str(), name, constSTRING); \
            } \
        } \
        else { \
            if ((NAMED_STRING_CANNOT_PRINT_ERROR) != nullptr) { \
                std::string msg = os_gl_INTERNAL_MESSAGE_PREFIX; \
                msg += NAMED_STRING_CANNOT_PRINT_ERROR; \
                LOGGING_FUNCTION(msg.c_str(), name); \
            } \
        } \
    } \
    if (IS_AN_ERROR) abort(); \
    break; \
}

#define os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(LOGGER, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING) \
    os_gl_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOGGER, case const, name, const, constSTRING, nullptr, UNNAMED_STRING, nullptr, NAMED_STRING, false, false)

#define os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING(LOGGER, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING, IS_AN_ERROR) \
    os_gl_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOGGER, case const, name, const, constSTRING, UNNAMED_STRING, nullptr, NAMED_STRING, nullptr, true, IS_AN_ERROR)

#define os_gl_ERROR_SWITCH_CASE_CUSTOM_STRING(name, const, constSTRING, UNNAMED_STRING, NAMED_STRING) \
    os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING(os_log_fatal, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING, false)

#define os_gl_ERROR_SWITCH_CASE(name, const) \
    os_gl_ERROR_SWITCH_CASE_CUSTOM_STRING(name, const, #const, "%s", "%s generated error: %s")

#define os_gl_ERROR_SWITCH_CASE_DEFAULT(name, err) \
    os_gl_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(os_log_fatal, default, name, err, err, "Unknown error: %d", "Unknown error", "%s generated an unknown error: %d", "%s generated an unknown error", true, false)

#define os_gl_boolean_to_string(val, TRUE_VALUE) val == TRUE_VALUE ? "true" : "false"

const char * os_gl_INTERNAL_MESSAGE_PREFIX = "";
bool os_gl_LOG_PRINT_NON_ERRORS = false;

EGLint os_egl_error = EGL_SUCCESS;
GLint os_gl_error = GL_NO_ERROR;

EGLint os_egl_last_error = EGL_SUCCESS;
GLint os_gl_last_error = GL_NO_ERROR;

#define os_gl_error_to_string_GL(name, err) \
    os_gl_INTERNAL_MESSAGE_PREFIX = "OpenGL:          "; \
    os_gl_error = err; \
    os_gl_last_error = os_gl_error; \
    switch (os_gl_error) { \
        os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(os_log_info, name, \
                                                                      GL_NO_ERROR, \
                                                                      "GL_NO_ERROR", \
                                                                      os_gl_LOG_PRINT_NON_ERRORS \
                                                                      ? "no error was generated" \
                                                                      : nullptr, \
                                                                      os_gl_LOG_PRINT_NON_ERRORS \
                                                                      ? "%s did not generate an error" \
                                                                      : nullptr) \
        os_gl_ERROR_SWITCH_CASE(name, GL_INVALID_ENUM) \
        os_gl_ERROR_SWITCH_CASE(name, GL_INVALID_VALUE) \
        os_gl_ERROR_SWITCH_CASE(name, GL_INVALID_OPERATION) \
        os_gl_ERROR_SWITCH_CASE(name, GL_INVALID_FRAMEBUFFER_OPERATION) \
        os_gl_ERROR_SWITCH_CASE(name, GL_OUT_OF_MEMORY) \
        os_gl_ERROR_SWITCH_CASE_DEFAULT(name, err) \
    } \
    os_gl_INTERNAL_MESSAGE_PREFIX = ""; \
    os_gl_error = GL_NO_ERROR;

#define os_gl_error_to_string_EGL(name, err) \
    os_gl_INTERNAL_MESSAGE_PREFIX = "OpenGL ES (EGL): "; \
    os_egl_error = err; \
    os_egl_last_error = os_egl_error; \
    switch (os_egl_error) { \
        os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(os_log_info, name, \
                                                                      EGL_SUCCESS, \
                                                                      "EGL_SUCCESS", \
                                                                      os_gl_LOG_PRINT_NON_ERRORS \
                                                                      ? "no error was generated" \
                                                                      : nullptr, \
                                                                      os_gl_LOG_PRINT_NON_ERRORS \
                                                                      ? "%s did not generate an error" \
                                                                      : nullptr) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_NOT_INITIALIZED) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_ACCESS) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_ALLOC) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_ATTRIBUTE) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_CONTEXT) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_CONFIG) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_CURRENT_SURFACE) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_DISPLAY) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_SURFACE) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_MATCH) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_PARAMETER) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_NATIVE_PIXMAP) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_BAD_NATIVE_WINDOW) \
        os_gl_ERROR_SWITCH_CASE(name, EGL_CONTEXT_LOST) \
        os_gl_ERROR_SWITCH_CASE_DEFAULT(name, err) \
    } \
    os_gl_INTERNAL_MESSAGE_PREFIX = ""; \
    os_egl_error = EGL_SUCCESS;

#define os_egl_check_error(code) code; os_gl_error_to_string_EGL(#code, eglGetError());
#define os_gl_check_error(code) code; os_gl_error_to_string_GL(#code, glGetError());

#define os_egl_check_errorIf_(code, eq, val, block_true) if ((code) eq val) { os_gl_error_to_string_EGL(#code, eglGetError()); block_true; } else { os_gl_error_to_string_EGL(#code, eglGetError()); };
#define os_egl_check_errorIf(code, block_true) if ((code) == EGL_TRUE) { os_gl_error_to_string_EGL(#code, eglGetError()); block_true; } else { os_gl_error_to_string_EGL(#code, eglGetError()); };
#define os_gl_check_errorIf(code, block_true) if ((code) == GL_TRUE) { os_gl_error_to_string_GL(#code, glGetError()); block_true; } else { os_gl_error_to_string_EGL(#code, glGetError()); };

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

#include <time.h>

class AppInstance {
public:
    float f;
    size_t frames;
    double g_Time;
    JVM_MANAGER jvmManager;
    jobject jObject;
    jclass jClass;
    jmethodID jSwapBuffers;
    int w;
    int h;

    void swapBuffers();

    void onEglSetup(JNIEnv *jenv, jobject classInstance, jstring name, jstring signature, jboolean was_destroyed);
    void onEglTearDown(jboolean was_destroyed);

    void surfaceChanged(int w, int h);
    void onDraw();
    bool onTouchEvent(MultiTouch & touchEvent);
    void destroyResources();
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
      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGui::StyleColorsDark();
      //ImGui_ImplAndroid_Init(pApp->window);
      g_Time = 0.0;
      ImGuiIO& io = ImGui::GetIO();
      io.BackendPlatformName = "imgui_impl_android";
      ImGui_ImplOpenGL3_Init("#version 300 es");
      ImFontConfig font_cfg;
      font_cfg.SizePixels = 22.0f;
      io.Fonts->AddFontDefault(&font_cfg);
      ImGui::GetStyle().ScaleAllSizes(3.0f);
      frames = 0;
      f = 0.0;
      w = 0;
      h = 0;
    }
}

void AppInstance::onEglTearDown (jboolean was_destroyed)
{
  if (was_destroyed) {
    destroyResources();
    ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplAndroid_Shutdown();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendPlatformName = nullptr;
    ImGui::DestroyContext();
    frames = 0;
    f = 0.0;
    w = 0;
    h = 0;
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

void AppInstance::surfaceChanged (int w, int h) {
    this->w = 0;
    this->h = 0;
    glViewport(0, 0, w, h);
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)w, (float)h);
    if (w > 0 && h > 0)
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
//io.DisplayFramebufferScale = ImVec2((float)display_width / window_width, (float)display_height / window_height);
}

void AppInstance::onDraw () {
    // we use an existing EGL context
    
    //ImGui_ImplAndroid_NewFrame();
    
    // Setup time step
    struct timespec current_timespec;
    clock_gettime(CLOCK_MONOTONIC, &current_timespec);
    double current_time = (double)(current_timespec.tv_sec) + (current_timespec.tv_nsec / 1000000000.0);
    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
    g_Time = current_time;
    //static bool use_work_area = true;
    //static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground;

    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
    // Based on your use case you may want one of the other.
    //const ImGuiViewport* viewport = ImGui::GetMainViewport();
    //ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    //ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    //ImGui::Begin("Example: Fullscreen window", nullptr, flags);
    GLuint FramebufferID = 0;
    GLuint renderedTextureID = 0;
    GLuint depthrenderbufferID = 0;
    os_gl_check_error(glGenFramebuffers(1, &FramebufferID));
    os_gl_check_error(glBindFramebuffer(GL_FRAMEBUFFER, FramebufferID));
    os_gl_check_error(glGenTextures(1, &renderedTextureID));
    os_gl_check_error(glBindTexture(GL_TEXTURE_2D, renderedTextureID));
    os_gl_check_error(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 400, 400));
    os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    os_gl_check_error(glGenRenderbuffers(1, &depthrenderbufferID));
    os_gl_check_error(glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbufferID));
    os_gl_check_error(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 400, 400));
    os_gl_check_error(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbufferID));
    os_gl_check_error(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTextureID, 0));
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    os_gl_check_error(glDrawBuffers(1, DrawBuffers)); // "1" is the size of DrawBuffers

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {

// -------------------- Incomplete FBO error codes ---------------
#ifndef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
#   define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#endif

#ifndef GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
#   define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#endif

#ifndef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
#   define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#endif

        const char* StatusString = "Unknown";
        switch (Status)
        {
            // clang-format off
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         StatusString = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";         break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: StatusString = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        StatusString = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";        break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        StatusString = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";        break;
            case GL_FRAMEBUFFER_UNSUPPORTED:                   StatusString = "GL_FRAMEBUFFER_UNSUPPORTED";                   break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        StatusString = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";        break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      StatusString = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";      break;
                // clang-format on
        }
        os_log_fatal("Framebuffer is incomplete. FB status: %s", StatusString);
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos({0, 0}); ImGui::SetNextWindowSize({400, 400});
    ImGui::Begin("offscreen window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings
      //| ImGuiWindowFlags_NoBackground
    );
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Frames Rendered: %zu", frames);
    ImGui::End();
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
    ImGui_ImplOpenGL3_RenderDrawData(draw_data);
    
    os_gl_check_error(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    ImGui_ImplOpenGL3_NewFrame();
    os_gl_check_error(glClearColor(0.0f, f, 1.0f, 1.0f));
    os_gl_check_error(glClear(GL_COLOR_BUFFER_BIT));
    ImGui::NewFrame();
    //ImGui::Begin("Example: Fullscreen window", nullptr, flags);
    ImGui::SetNextWindowPos({0, 0}); ImGui::SetNextWindowSize({500, 500});
    ImGui::Begin("OpenGL Texture Text");
    ImGui::Text("texture id = %u", renderedTextureID);
    ImGui::Text("size = %d x %d", 400, 400);
    ImGui::Image((ImTextureID)(intptr_t)renderedTextureID, ImVec2(400, 400));
    ImGui::End();
    ImGui::Render();
    ImDrawData* draw_data2 = ImGui::GetDrawData();
    ImGui_ImplOpenGL3_RenderDrawData(draw_data2);
    swapBuffers();
    frames++;
    os_gl_check_error(glDeleteRenderbuffers(1, &depthrenderbufferID));
    os_gl_check_error(glDeleteTextures(1, &renderedTextureID));
    os_gl_check_error(glDeleteFramebuffers(1, &FramebufferID));
}

bool AppInstance::onTouchEvent(MultiTouch & touchEvent) {
    auto t = touchEvent.getTouchAt(touchEvent.getTouchIndex());
    if (t.state == MultiTouch::TOUCH_DOWN) {
      f = 1.0f;
    } else if (t.state == MultiTouch::TOUCH_UP || t.state == MultiTouch::TOUCH_CANCELLED) {
      f = 0.0f;
    }
    return true;
}

void AppInstance::destroyResources () {
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
        os_gl_check_error(glGetIntegerv(EGL_CONTEXT_FLAGS, &context_flags));
        if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT_KHR) {
          os_log_info("GL Context has debug flag, hooking up callback");
          os_gl_check_error(glEnable(GL_DEBUG_OUTPUT_KHR));
          os_gl_check_error(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR));
          os_gl_check_error(glDebugMessageCallbackKHR(GlDebugOutput, nullptr));
          os_gl_check_error(glDebugMessageControlKHR(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
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
