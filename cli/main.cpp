#include <stdio.h>

#include <vector>

#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#if ANDROID
#include <android/native_window_jni.h>
#include <android/log.h>
#include <android/hardware_buffer.h>
#endif

#include <stdarg.h>
#include <cassert>
#include <cstring>
#include <string>

#ifdef __ANDROID__
#include <android/log.h>
#endif

int LOG_INFO(const char* format, ... ) {
    assert(format != nullptr);
#ifdef __ANDROID__
    va_list args2;
    va_start(args2, format);
    __android_log_vprint(ANDROID_LOG_INFO, "GLIS", format, args2);
    va_end(args2);
#endif
    // set color to green
    fprintf(stdout, "\033[0;32m");
    va_list args;
    va_start(args, format);
    int len = vfprintf(stdout, format, args);
    va_end(args);
    // clear color
    fprintf(stdout, "\033[0m");
    len += fprintf(stdout, "\n");
    fflush(stdout);
    return len;
}

int LOG_ERROR(const char* format, ... ) {
    assert(format != nullptr);
#ifdef __ANDROID__
    va_list args2;
    va_start(args2, format);
    __android_log_vprint(ANDROID_LOG_ERROR, "GLIS", format, args2);
    va_end(args2);
#endif
    // set color to red
    fprintf(stderr, "\033[0;31m");
    va_list args;
    va_start(args, format);
    int len = vfprintf(stderr, format, args);
    va_end(args);
    // clear color
    fprintf(stderr, "\033[0m");
    len += fprintf(stderr, "\n");
    fflush(stderr);
    return len;
}

void LOG_ALWAYS_FATAL(const char* format, ... ) {
    assert(format != nullptr);
#ifdef __ANDROID__
    va_list args2;
    va_start(args2, format);
    __android_log_vprint(ANDROID_LOG_ERROR, "GLIS", format, args2);
    va_end(args2);
#endif
    // set color to red
    fprintf(stderr, "\033[0;31m");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    // clear color
    fprintf(stderr, "\033[0m");
    fprintf(stderr, "\n");
    fflush(stderr);
    abort();
}

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
    os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING(LOG_ERROR, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING, false)

#define os_gl_ERROR_SWITCH_CASE(name, const) \
    os_gl_ERROR_SWITCH_CASE_CUSTOM_STRING(name, const, #const, "%s", "%s generated error: %s")

#define os_gl_ERROR_SWITCH_CASE_DEFAULT(name, err) \
    os_gl_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(LOG_ERROR, default, name, err, err, "Unknown error: %d", "Unknown error", "%s generated an unknown error: %d", "%s generated an unknown error", true, false)

#define os_gl_boolean_to_string(val, TRUE_VALUE) val == TRUE_VALUE ? "true" : "false"

const char * os_gl_INTERNAL_MESSAGE_PREFIX = "";
bool os_gl_LOG_PRINT_NON_ERRORS = true;

EGLint os_egl_error = EGL_SUCCESS;
GLint os_gl_error = GL_NO_ERROR;

#define os_gl_error_to_string_GL(name, err) \
    os_gl_INTERNAL_MESSAGE_PREFIX = "OpenGL:          "; \
    os_gl_error = err; \
    switch (os_gl_error) { \
        os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(LOG_INFO, name, \
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
    switch (os_egl_error) { \
        os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING_DONT_PRINT_ERROR(LOG_INFO, name, \
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

#define eglCheckError(code) code; os_gl_error_to_string_EGL(#code, eglGetError());
#define glCheckError(code) code; os_gl_error_to_string_GL(#code, glGetError());

#define eglCheckErrorIf(code, block_true) if ((code) == EGL_TRUE) { os_gl_error_to_string_EGL(#code, eglGetError()); block_true; } else { os_gl_error_to_string_EGL(#code, eglGetError()); };
#define glCheckErrorIf(code, block_true) if ((code) == GL_TRUE) { os_gl_error_to_string_GL(#code, glGetError()); block_true; } else { os_gl_error_to_string_EGL(#code, glGetError()); };

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

#define component_action(start, action, end, x)   LOG_INFO("[component " #start "] - " #x); x.action(); LOG_INFO("[component " #end "] - " #x "\n")

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
        LOG_INFO("EGL driver name: %s", getDisplayDriverName(d));
     }
  #endif
  
     LOG_INFO(d == EGL_NO_DISPLAY ? "EGL client extensions string:" : "EGL extensions string:");
  
     return PrintExtensions(extensions);
  }

  int maj, min;
  EGLDisplay egl_display = EGL_NO_DISPLAY;

  bool
  doOneDisplay(EGLDisplay d, const char *name)
  {
  
    LOG_INFO("%s:", name);
    eglCheckErrorIf(!eglInitialize(d, &maj, &min), {
      return false;
    })
    LOG_INFO("EGL API version: %d.%d", maj, min);
    LOG_INFO("EGL vendor string: %s", eglQueryString(d, EGL_VENDOR));
    LOG_INFO("EGL version string: %s", eglQueryString(d, EGL_VERSION));
  #ifdef EGL_VERSION_1_2
    LOG_INFO("EGL client APIs: %s", eglQueryString(d, EGL_CLIENT_APIS));
  #endif

    PrintDisplayExtensions(d);
     
    //PrintConfigs(d);
    printf("\n");
    egl_display = d;
    return true;
  }

  void onBuild() override {
    int ret = 0;
    const char *clientext;

    clientext = PrintDisplayExtensions(EGL_NO_DISPLAY);
    printf("\n");

    if (strstr(clientext, "EGL_EXT_platform_base")) {
      PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay = (PFNEGLGETPLATFORMDISPLAYEXTPROC) eglGetProcAddress("eglGetPlatformDisplayEXT");
      if (strstr(clientext, "EGL_KHR_platform_android"))
        if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_ANDROID_KHR, EGL_DEFAULT_DISPLAY, NULL), "Android platform"))
          return;
      if (strstr(clientext, "EGL_MESA_platform_gbm") || strstr(clientext, "EGL_KHR_platform_gbm"))
        if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_GBM_MESA, EGL_DEFAULT_DISPLAY, NULL), "GBM platform"))
          return;
      if (strstr(clientext, "EGL_EXT_platform_wayland") || strstr(clientext, "EGL_KHR_platform_wayland"))
        if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT, EGL_DEFAULT_DISPLAY, NULL), "Wayland platform"))
          return;
      if (strstr(clientext, "EGL_EXT_platform_x11") || strstr(clientext, "EGL_KHR_platform_x11"))
        if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_X11_EXT, EGL_DEFAULT_DISPLAY, NULL), "X11 platform"))
          return;
      if (strstr(clientext, "EGL_MESA_platform_surfaceless"))
        if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA, EGL_DEFAULT_DISPLAY, NULL), "Surfaceless platform"))
          return;
    } else {
      if (doOneDisplay(eglGetDisplay(EGL_DEFAULT_DISPLAY), "Default display"))
        return;
    }
  }
  void onDestroy() override {
    if (egl_display != EGL_NO_DISPLAY) {
      eglCheckError(eglTerminate(egl_display));
      egl_display = EGL_NO_DISPLAY;
      min = 0;
      maj = 0;
    }
  }
};

struct egl_context : public dep {
  egl_display display;
  EGLint major, minor;
  void onBuild() override {
    component_build(display);
    eglCheckError(eglMakeCurrent(display.egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
  }
  void onDestroy() override {
    eglCheckError(eglMakeCurrent(display.egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
    component_destroy(display);
  }
};

int main(int argc, char* argv[]) {
  egl_context context;
  component_build(context);
  component_destroy(context);
  //component_rebuild(context);
  return 0;
}
