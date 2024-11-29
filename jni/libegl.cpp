#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/native_window_jni.h>
#include <android/log.h>

#include <android/hardware_buffer.h>

#define log(...) __android_log_print(ANDROID_LOG_DEBUG, "gles-renderer", __VA_ARGS__)
#define loge(...) __android_log_print(ANDROID_LOG_ERROR, "gles-renderer", __VA_ARGS__)

int eglCheckError(int line) {
    char* desc;
    int err = eglGetError();
    switch(err) {
#define E(code, text) case code: desc = (char*) text; break
        case EGL_SUCCESS: desc = nullptr; // "No error"
        E(EGL_NOT_INITIALIZED, "EGL not initialized or failed to initialize");
        E(EGL_BAD_ACCESS, "Resource inaccessible");
        E(EGL_BAD_ALLOC, "Cannot allocate resources");
        E(EGL_BAD_ATTRIBUTE, "Unrecognized attribute or attribute value");
        E(EGL_BAD_CONTEXT, "Invalid EGL context");
        E(EGL_BAD_CONFIG, "Invalid EGL frame buffer configuration");
        E(EGL_BAD_CURRENT_SURFACE, "Current surface is no longer valid");
        E(EGL_BAD_DISPLAY, "Invalid EGL display");
        E(EGL_BAD_SURFACE, "Invalid surface");
        E(EGL_BAD_MATCH, "Inconsistent arguments");
        E(EGL_BAD_PARAMETER, "Invalid argument");
        E(EGL_BAD_NATIVE_PIXMAP, "Invalid native pixmap");
        E(EGL_BAD_NATIVE_WINDOW, "Invalid native window");
        E(EGL_CONTEXT_LOST, "Context lost");
#undef E
        default: desc = (char*) "Unknown error";
    }

    if (desc)
        log("Xlorie: egl error on line %d: %s\n", line, desc);

    return err;
}

const char* eglErrorLabel(int code) {
    switch(code) {
        case EGL_SUCCESS: return nullptr; // "No error"
#define E(code) case code: return #code; break
        E(EGL_NOT_INITIALIZED);
        E(EGL_BAD_ACCESS);
        E(EGL_BAD_ALLOC);
        E(EGL_BAD_ATTRIBUTE);
        E(EGL_BAD_CONTEXT);
        E(EGL_BAD_CONFIG);
        E(EGL_BAD_CURRENT_SURFACE);
        E(EGL_BAD_DISPLAY);
        E(EGL_BAD_SURFACE);
        E(EGL_BAD_MATCH);
        E(EGL_BAD_PARAMETER);
        E(EGL_BAD_NATIVE_PIXMAP);
        E(EGL_BAD_NATIVE_WINDOW);
        E(EGL_CONTEXT_LOST);
#undef E
        default: return "EGL_UNKNOWN_ERROR";
    }

}

void checkGlError(int line) {
    GLenum error;
    char *desc = nullptr;
    for (error = glGetError(); error; error = glGetError()) {
        switch (error) {
#define E(code) case code: desc = (char*)#code; break
            E(GL_INVALID_ENUM);
            E(GL_INVALID_VALUE);
            E(GL_INVALID_OPERATION);
            E(GL_STACK_OVERFLOW_KHR);
            E(GL_STACK_UNDERFLOW_KHR);
            E(GL_OUT_OF_MEMORY);
            E(GL_INVALID_FRAMEBUFFER_OPERATION);
            E(GL_CONTEXT_LOST_KHR);
            default:
                continue;
#undef E
        }
        log("Xlorie: GLES %d ERROR: %s.\n", line, desc);
        return;
    }
}

#define checkGlError() checkGlError(__LINE__)
#define eglCheckError() eglCheckError(__LINE__)

#include <vector>

class dep {
  std::vector<dep*> deps;
  bool destroyed = true;
  public:
  void add(dep * x) {
    deps.emplace_back(x);
  }
  virtual void onBuild() {}
  virtual void onRebuild() { destroy(); build(); }
  virtual void onDestroy() {}
  void build() {
    if (destroyed) {
      onBuild();
      for (dep * x : deps) x->build();
      destroyed = false;
    }
  }
  void rebuild() { onRebuild(); }
  void destroy() {
    if (!destroyed) {
      for (size_t i = deps.size(); i > 0; i--) deps[i-1]->destroy();
      onDestroy();
      destroyed = true;
    }
  }
  virtual ~dep() { destroy(); }
};

#define component_action(start, action, end, x)   puts("[component " #start "] - " #x); x.action(); puts("[component " #end "] - " #x "\n")

#define component_build(x)   component_action(building, build, built, x)
#define component_rebuild(x)   component_action(rebuilding, rebuild, rebuilt, x)
#define component_destroy(x)   component_action(destroying, destroy, destroyed, x)

struct egl_display : public dep {
  EGLDisplay egl_display = EGL_NO_DISPLAY;
  void onBuild() override {
    egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (egl_display == EGL_NO_DISPLAY) {
      log("EGL: Got no EGL display.\n");
      eglCheckError();
    }
    log("EGL: Got a valid EGL display.\n");
  }
  void onDestroy() override {
    egl_display = EGL_NO_DISPLAY;
  }
};
