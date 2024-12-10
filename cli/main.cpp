#include <stdio.h>

#include <vector>

#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <cstring>
#if ANDROID
#include <android/native_window_jni.h>
#include <android/log.h>
#include <android/hardware_buffer.h>

#define log(...) __android_log_print(ANDROID_LOG_DEBUG, "gles-renderer", __VA_ARGS__)
#define loge(...) __android_log_print(ANDROID_LOG_ERROR, "gles-renderer", __VA_ARGS__)

#else

#define log(...) printf(__VA_ARGS__)
#define loge(...) printf(__VA_ARGS__)

#endif

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

#define eglCheckError() eglCheckError(__LINE__)

// void checkGlError(int line) {
//     GLenum error;
//     char *desc = nullptr;
//     for (error = glGetError(); error; error = glGetError()) {
//         switch (error) {
// #define E(code) case code: desc = (char*)#code; break
//             E(GL_INVALID_ENUM);
//             E(GL_INVALID_VALUE);
//             E(GL_INVALID_OPERATION);
//             E(GL_STACK_OVERFLOW_KHR);
//             E(GL_STACK_UNDERFLOW_KHR);
//             E(GL_OUT_OF_MEMORY);
//             E(GL_INVALID_FRAMEBUFFER_OPERATION);
//             E(GL_CONTEXT_LOST_KHR);
//             default:
//                 continue;
// #undef E
//         }
//         log("Xlorie: GLES %d ERROR: %s.\n", line, desc);
//         return;
//     }
// }

// #define checkGlError() checkGlError(__LINE__)

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
  const char *
  PrintExtensions(const char *extensions)
  {
     const char *p, *end, *next;
     int column;
  
     column = 0;
     end = extensions + strlen(extensions);
  
     for (p = extensions; p < end; p = next + 1) {
        next = strchr(p, ' ');
        if (next == NULL)
           next = end;
  
        if (column > 0 && column + next - p + 1 > 70) {
  	 printf("\n");
  	 column = 0;
        }
        if (column == 0)
  	 printf("    ");
        else
  	 printf(" ");
        column += next - p + 1;
  
        printf("%.*s", (int) (next - p), p);
  
        p = next + 1;
     }
  
     if (column > 0)
        printf("\n");
  
     return extensions;
  }
  
  
  const char *
  PrintDisplayExtensions(EGLDisplay d)
  {
     const char *extensions;
  
     extensions = eglQueryString(d, EGL_EXTENSIONS);
     if (!extensions)
        return NULL;
  
  #ifdef EGL_MESA_query_driver
     if (strstr(extensions, "EGL_MESA_query_driver")) {
        PFNEGLGETDISPLAYDRIVERNAMEPROC getDisplayDriverName =
           (PFNEGLGETDISPLAYDRIVERNAMEPROC)
              eglGetProcAddress("eglGetDisplayDriverName");
        printf("EGL driver name: %s\n", getDisplayDriverName(d));
     }
  #endif
  
     puts(d == EGL_NO_DISPLAY ? "EGL client extensions string:" :
                                "EGL extensions string:");
  
     return PrintExtensions(extensions);
  }

  EGLDisplay egl_display = EGL_NO_DISPLAY;

  int
  doOneDisplay(EGLDisplay d, const char *name)
  {
     int maj, min;
  
     printf("%s:\n", name);
     if (!eglInitialize(d, &maj, &min)) {
        printf("eglinfo: eglInitialize failed\n\n");
        return 1;
     }
  
     printf("EGL API version: %d.%d\n", maj, min);
     printf("EGL vendor string: %s\n", eglQueryString(d, EGL_VENDOR));
     printf("EGL version string: %s\n", eglQueryString(d, EGL_VERSION));
  #ifdef EGL_VERSION_1_2
     printf("EGL client APIs: %s\n", eglQueryString(d, EGL_CLIENT_APIS));
  #endif
  
     PrintDisplayExtensions(d);
     
     //PrintConfigs(d);
     printf("\n");
     egl_display = d;
     return 0;
  }

  void onBuild() override {
   int ret = 0;
   const char *clientext;

   clientext = PrintDisplayExtensions(EGL_NO_DISPLAY);
   printf("\n");

   if (strstr(clientext, "EGL_EXT_platform_base")) {
       PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay =
           (PFNEGLGETPLATFORMDISPLAYEXTPROC)
           eglGetProcAddress("eglGetPlatformDisplayEXT");
       if (strstr(clientext, "EGL_KHR_platform_android"))
           if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_ANDROID_KHR,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "Android platform")) return;
       if (strstr(clientext, "EGL_MESA_platform_gbm") ||
           strstr(clientext, "EGL_KHR_platform_gbm"))
           if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_GBM_MESA,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "GBM platform")) return;
       if (strstr(clientext, "EGL_EXT_platform_wayland") ||
           strstr(clientext, "EGL_KHR_platform_wayland"))
           if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "Wayland platform")) return;
       if (strstr(clientext, "EGL_EXT_platform_x11") ||
           strstr(clientext, "EGL_KHR_platform_x11"))
           if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_X11_EXT,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "X11 platform")) return;
       if (strstr(clientext, "EGL_MESA_platform_surfaceless"))
           if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "Surfaceless platform")) return;
   }
   else {
      if (doOneDisplay(eglGetDisplay(EGL_DEFAULT_DISPLAY), "Default display")) return;
   }
  }
  void onDestroy() override {
    if (egl_display != EGL_NO_DISPLAY) eglTerminate(egl_display);
    egl_display = EGL_NO_DISPLAY;
  }
};

struct egl_initialize : public dep {
  egl_display display;
  EGLint major, minor;
  void onBuild() override {
    component_build(display);
    if (eglInitialize(display.egl_display, &major, &minor) != EGL_TRUE) {
        log("EGL: Unable to initialize EGL\n");
        eglCheckError();
    }
  }
  void onDestroy() override {
    major = 0;
    minor = 0;
    component_destroy(display);
  }
};

int main(int argc, char* argv[]) {
  egl_display display;
  egl_initialize initialize;
  component_rebuild(display);
  component_rebuild(initialize);
  return 0;
}
