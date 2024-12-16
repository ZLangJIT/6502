#include <stdio.h>
#include <vector>

#if __ANDROID__
#include <android/log.h>
#include <android/native_window_jni.h>
#include <android/hardware_buffer.h>
#endif

#include <nanovg.h>
#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#define NANOVG_GLES3_IMPLEMENTATION
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

#include <dlfcn.h>

#include <jni.h>
#include <android/hardware_buffer.h>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

int os_log_info(const char* format, ... ) {
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

int os_log_error(const char* format, ... ) {
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

void os_log_fatal(const char* format, ... ) {
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
    os_gl_SWITCH_CASE_CUSTOM_LOGGER_CUSTOM_STRING(os_log_error, name, const, constSTRING, UNNAMED_STRING, NAMED_STRING, false)

#define os_gl_ERROR_SWITCH_CASE(name, const) \
    os_gl_ERROR_SWITCH_CASE_CUSTOM_STRING(name, const, #const, "%s", "%s generated error: %s")

#define os_gl_ERROR_SWITCH_CASE_DEFAULT(name, err) \
    os_gl_SWITCH_CASE_CUSTOM_CASE_CUSTOM_LOGGER_CUSTOM_STRING_CAN_I_PRINT_ERROR(os_log_error, default, name, err, err, "Unknown error: %d", "Unknown error", "%s generated an unknown error: %d", "%s generated an unknown error", true, false)

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
      os_log_info("EGL driver name: %s", getDisplayDriverName(d));
   }
#endif

   os_log_info(d == EGL_NO_DISPLAY ? "EGL client extensions string:" : "EGL extensions string:");

   return PrintExtensions(extensions);
}

int maj, min;
EGLDisplay egl_display = EGL_NO_DISPLAY;

bool
doOneDisplay(EGLDisplay d, const char *name)
{
  os_log_info("%s:", name);
  os_egl_check_errorIf(!eglInitialize(d, &maj, &min), {
    os_log_error("");
    return false;
  })
  os_log_info("EGL API version: %d.%d", maj, min);
  os_log_info("EGL vendor string: %s", eglQueryString(d, EGL_VENDOR));
  os_log_info("EGL version string: %s", eglQueryString(d, EGL_VERSION));
#ifdef EGL_VERSION_1_2
  os_log_info("EGL client APIs: %s", eglQueryString(d, EGL_CLIENT_APIS));
#endif

  PrintDisplayExtensions(d);
   
  //PrintConfigs(d);
  os_log_info("");
  egl_display = d;
  return true;
}

bool init_egl() {
  int ret = 0;
  const char *clientext;

  clientext = PrintDisplayExtensions(EGL_NO_DISPLAY);
  printf("\n");

  if (strstr(clientext, "EGL_EXT_platform_base")) {
    PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay = (PFNEGLGETPLATFORMDISPLAYEXTPROC) eglGetProcAddress("eglGetPlatformDisplayEXT");
    if (strstr(clientext, "EGL_KHR_platform_android"))
      if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_ANDROID_KHR, EGL_DEFAULT_DISPLAY, NULL), "Android platform"))
        return true;
    if (strstr(clientext, "EGL_MESA_platform_gbm") || strstr(clientext, "EGL_KHR_platform_gbm"))
      if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_GBM_MESA, EGL_DEFAULT_DISPLAY, NULL), "GBM platform"))
        return true;
    if (strstr(clientext, "EGL_EXT_platform_wayland") || strstr(clientext, "EGL_KHR_platform_wayland"))
      if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT, EGL_DEFAULT_DISPLAY, NULL), "Wayland platform"))
        return true;
    if (strstr(clientext, "EGL_EXT_platform_x11") || strstr(clientext, "EGL_KHR_platform_x11"))
      if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_X11_EXT, EGL_DEFAULT_DISPLAY, NULL), "X11 platform"))
        return true;
    if (strstr(clientext, "EGL_MESA_platform_surfaceless"))
      if (doOneDisplay(getPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA, EGL_DEFAULT_DISPLAY, NULL), "Surfaceless platform"))
        return true;
  } else {
    if (doOneDisplay(eglGetDisplay(EGL_DEFAULT_DISPLAY), "Default display"))
      return true;
  }
  return false;
}

bool deinit_egl() {
  if (egl_display != EGL_NO_DISPLAY) {
    os_egl_check_errorIf(!eglTerminate(egl_display), {
      os_log_error("");
      return false;
    });
    egl_display = EGL_NO_DISPLAY;
    min = 0;
    maj = 0;
  }
  return true;
};

EGLint numConfigs;
EGLConfig cfg = 0;
EGLContext ctx = EGL_NO_CONTEXT;
EGLSurface sfc = EGL_NO_SURFACE;

EGLSurface swap_surface_egl(EGLSurface sfc) {
  os_egl_check_errorIf_(eglSwapBuffers(egl_display, sfc), ==, EGL_FALSE, {
    if (os_egl_last_error == EGL_BAD_NATIVE_WINDOW || os_egl_last_error == EGL_BAD_SURFACE) {
      return EGL_NO_SURFACE;
    }
  });
  return sfc;
}

void destroy_surface_egl(EGLSurface & sfc) {
  if (ctx != EGL_NO_CONTEXT) {
    os_egl_check_error(eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
    if (sfc != EGL_NO_SURFACE) {
      os_egl_check_error(eglDestroySurface(egl_display, sfc));
      sfc = EGL_NO_SURFACE;
    }
  }
}

EGLSurface create_pixelbuffer_surface_egl(EGLint w, EGLint h) {
  EGLSurface sfc = EGL_NO_SURFACE;
  const EGLint pbufferAttributes[] = {
          EGL_WIDTH, w,
          EGL_HEIGHT, h,
          EGL_NONE,
  };
  os_egl_check_errorIf_((sfc = eglCreatePbufferSurface(egl_display, cfg, pbufferAttributes)), ==, 0, {
    	os_log_error("Could not create a pixel buffer surface");
  });
  return sfc;
}

EGLNativeWindowType win;
EGLSurface create_window_surface_egl(ANativeWindow * window, int & width, int & height) {
  EGLSurface sfc = EGL_NO_SURFACE;
  width = window ? ANativeWindow_getWidth(window) : 0;
  height = window ? ANativeWindow_getHeight(window) : 0;
  os_log_info("window %p dimensions %dx%d", window, width, height);

    if (window && (width <= 0 || height <= 0)) {
        os_log_error("We've got invalid surface. Probably it became invalid before we started working with it.");
        return sfc;
    }

    if (!window) return sfc;
  os_egl_check_errorIf_((sfc = eglCreateWindowSurface(egl_display, cfg, window, nullptr)), ==, 0, {
    	os_log_error("Could not create a window surface");
      return sfc;
  });
  return sfc;
}

bool set_no_surface_current() {
  os_egl_check_errorIf(!eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT), {
    	os_log_error("Could not unbind context");
      return false;
  });
  return true;
}

bool set_surface_current(EGLSurface sfc) {
  os_egl_check_errorIf(!eglMakeCurrent(egl_display, sfc, sfc, ctx), {
    	os_log_error("Could not bind context");
      return false;
  });
  return true;
}

void destroy_context_egl() {
  if (ctx != EGL_NO_CONTEXT) {
    os_egl_check_error(eglDestroyContext(egl_display, ctx));
    ctx = EGL_NO_CONTEXT;
  }
}

bool create_context_egl() {
  eglBindAPI(EGL_OPENGL_ES_API);
  
  const EGLint configAttribs[] = {
          EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
          EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
          EGL_RED_SIZE, 8,
          EGL_GREEN_SIZE, 8,
          EGL_BLUE_SIZE, 8,
          EGL_ALPHA_SIZE, 0,
          EGL_NONE
  };
  const EGLint configAttribs2[] = {
          EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
          EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
          EGL_RED_SIZE, 8,
          EGL_GREEN_SIZE, 8,
          EGL_BLUE_SIZE, 8,
          EGL_ALPHA_SIZE, 8,
          EGL_NONE
  };
  const EGLint ctxattribs[] = {
          EGL_CONTEXT_CLIENT_VERSION,2, EGL_NONE
  };
  
  os_egl_check_errorIf(!eglChooseConfig(egl_display, configAttribs, &cfg, 1, &numConfigs), {
    os_egl_check_errorIf(!eglChooseConfig(egl_display, configAttribs2, &cfg, 1, &numConfigs), {
    	os_log_error("Could not find a compatible configuration");
      return false;
    })
  });
  
  os_egl_check_errorIf_((ctx = eglCreateContext(egl_display, cfg, nullptr, ctxattribs)), ==, EGL_NO_CONTEXT, {
    	os_log_error("Could not create a context");
      return false;
  });
  os_egl_check_errorIf(!eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT), {
    	os_log_error("Could not make context current");
    	destroy_context_egl();
      return false;
  });
  #if __ANDROID__
	  os_log_info("Checking texture compatibility...");
    {
        // Some devices do not support sampling from HAL_PIXEL_FORMAT_BGRA_8888, here we are checking it.
        const EGLint imageAttributes[] = {EGL_IMAGE_PRESERVED_KHR, EGL_TRUE, EGL_NONE};
        EGLClientBuffer clientBuffer;
        EGLImageKHR img;
        AHardwareBuffer *new_ = nullptr;
        int status;
        AHardwareBuffer_Desc d0 = {
                .width = 64,
                .height = 64,
                .layers = 1,
                  // Stands to HAL_PIXEL_FORMAT_BGRA_8888
                  // #define AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM 5
                .format = 5,
                .usage = AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE | (AHARDWAREBUFFER_USAGE_CPU_WRITE_OFTEN | AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN)
        };

        status = AHardwareBuffer_allocate(&d0, &new_);
        if (status != 0 || new_ == nullptr) {
            os_log_error("Failed to allocate native buffer (%p, error %d)", new_, status);
            os_log_error("Forcing legacy drawing");
            goto DONE;
        }

        uint32_t *pixels;
        if (AHardwareBuffer_lock(new_, (AHARDWAREBUFFER_USAGE_CPU_WRITE_OFTEN | AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN), -1, nullptr, (void **) &pixels) == 0) {
            pixels[0] = 0xAABBCCDD;
            AHardwareBuffer_unlock(new_, nullptr);
        } else {
            os_log_error("Failed to lock native buffer (%p, error %d)", new_, status);
            os_log_error("Forcing legacy drawing");
            AHardwareBuffer_release(new_);
            goto DONE;
        }

        os_egl_check_errorIf_(!(clientBuffer = eglGetNativeClientBufferANDROID(new_)), ==, true, {
            os_log_error("Failed to obtain EGLClientBuffer from AHardwareBuffer");
            os_log_error("Forcing legacy drawing");
            AHardwareBuffer_release(new_);
            goto DONE;
        });

        os_egl_check_error((img = eglCreateImageKHR(egl_display, EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_ANDROID, clientBuffer, imageAttributes)));
        if (!img) {
            if (os_egl_last_error == EGL_BAD_PARAMETER) {
                os_log_error("Sampling from HAL_PIXEL_FORMAT_BGRA_8888 is not supported, forcing AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM");
                // *flip = 1;
                AHardwareBuffer_release(new_);
                goto DONE;
            } else {
                os_log_error("Failed to obtain EGLImageKHR from EGLClientBuffer");
                os_log_error("Forcing legacy drawing");
                AHardwareBuffer_release(new_);
                goto DONE;
            }
            AHardwareBuffer_release(new_);
            goto DONE;
        } else {
            // For some reason all devices I checked had no GL_EXT_texture_format_BGRA8888 support, but some of them still provided BGRA extension.
            // EGL does not provide functions to query texture format in runtime.
            // Workarounds are less performant but at least they let us use Termux:X11 on devices with missing BGRA support.
            // We handle two cases.
            // If resulting texture has BGRA format but still drawing RGBA we should flip format to RGBA and flip pixels manually in shader.
            // In the case if for some reason we can not use HAL_PIXEL_FORMAT_BGRA_8888 we should fallback to legacy drawing method (uploading pixels via glTexImage2D).
            const EGLint configAttributes[] = {
                    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_NONE
            };
            EGLConfig checkcfg = 0;
            GLuint fbo = 0, texture = 0;
            os_egl_check_errorIf(!eglChooseConfig(egl_display, configAttributes, &checkcfg, 1, &numConfigs), {
                os_log_error("EGL: check eglChooseConfig failed.");
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            });

            EGLContext testctx;
            os_egl_check_errorIf_((testctx = eglCreateContext(egl_display, checkcfg, nullptr, ctxattribs)), ==, EGL_NO_CONTEXT, {
                os_log_error("EGL: check eglCreateContext failed.");
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            });

            const EGLint pbufferAttributes[] = {
                    EGL_WIDTH, 64,
                    EGL_HEIGHT, 64,
                    EGL_NONE,
            };
            EGLSurface checksfc;
            os_egl_check_errorIf_((checksfc = eglCreatePbufferSurface(egl_display, checkcfg, pbufferAttributes)), ==, 0, {
                os_log_error("EGL: check eglCreatePbufferSurface failed.");
                os_egl_check_error(eglDestroyContext(egl_display, testctx));
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            });

            os_egl_check_errorIf(!eglMakeCurrent(egl_display, checksfc, checksfc, testctx), {
                os_log_error("EGL: check eglMakeCurrent failed.");
                os_egl_check_error(eglDestroySurface(egl_display, checksfc));
                os_egl_check_error(eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
                os_egl_check_error(eglDestroyContext(egl_display, testctx));
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            });

            os_gl_check_error(glActiveTexture(GL_TEXTURE0));
            os_gl_check_error(glGenTextures(1, &texture));
            os_gl_check_error(glBindTexture(GL_TEXTURE_2D, texture));
            os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            os_gl_check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
            os_gl_check_error(glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, img));
            os_gl_check_error(glGenFramebuffers(1, &fbo));
            os_gl_check_error(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
            os_gl_check_error(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0));
            uint32_t pixel[64*64];
            os_gl_check_error(glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel));
            if (pixel[0] == 0xAABBCCDD) {
                os_log_error("GLES: GLES draws pixels unchanged, probably system does not support AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM. Forcing bgra.");
                // *flip = 1;
                os_egl_check_error(eglDestroySurface(egl_display, checksfc));
                os_egl_check_error(eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
                os_egl_check_error(eglDestroyContext(egl_display, testctx));
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            } else if (pixel[0] != 0xAADDCCBB) {
                os_log_error("Xlorie: GLES receives broken pixels. Forcing legacy drawing. 0x%X", pixel[0]);
                os_egl_check_error(eglDestroySurface(egl_display, checksfc));
                os_egl_check_error(eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
                os_egl_check_error(eglDestroyContext(egl_display, testctx));
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            }
            os_egl_check_error(eglDestroySurface(egl_display, checksfc));
            os_egl_check_error(eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
            os_egl_check_error(eglDestroyContext(egl_display, testctx));
            os_egl_check_error(eglDestroyImageKHR(egl_display, img));
            AHardwareBuffer_release(new_);
        }
    }
  #endif

  DONE:
  #if __ANDROID__
	os_log_info("Checked texture compatibility");
	#endif
	return true;
}

extern "C" {

bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

struct GLData {
  EGLSurface sfc = EGL_NO_SURFACE;
  int w = 0;
  int h = 0;
  NVGcontext* vg = nullptr;
};

#include <game-activity/native_app_glue/android_native_app_glue.c>

    void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            pApp->userData = 0x0;
            if (init_egl()) {
              if (!create_context_egl()) {
                deinit_egl();
              } else {
                int w, h;
                EGLSurface sfc = create_window_surface_egl(pApp->window, w, h);
                if (sfc == EGL_NO_SURFACE) {
                  destroy_context_egl();
                  deinit_egl();
                } else {
                  if (set_surface_current(sfc)) {
                  	NVGcontext* vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
                  	if (vg == NULL) {
                  		os_log_error("Could not init nanovg.");
                      destroy_surface_egl(sfc);
                      destroy_context_egl();
                      deinit_egl();
                  	} else {
                      GLData * p = new GLData;
                      p->sfc = sfc;
                      p->w = w;
                      p->h = h;
                      p->vg = vg;
                      pApp->userData = p;
                  	}
                  } else {
                    destroy_surface_egl(sfc);
                    destroy_context_egl();
                    deinit_egl();
                  }
                }
              }
            }
            break;
        case APP_CMD_TERM_WINDOW:
            set_no_surface_current();
            if (pApp->userData) {
              GLData * p = reinterpret_cast<GLData*>(pApp->userData);
            	nvgDeleteGLES3(p->vg);
              destroy_surface_egl(p->sfc);
              pApp->userData = 0x0;
              delete p;
            }
            destroy_context_egl();
            deinit_egl();
            break;
        default:
            break;
    }
}

void android_main(struct android_app *pApp) {
    os_log_info("Welcome to android_main");

    pApp->onAppCmd = handle_cmd;

    android_app_set_motion_event_filter(pApp, motion_event_filter_func);

    do {
        bool done = false;
        while (!done) {
            int timeout = 0;
            int events;
            android_poll_source *pSource;
            int result = ALooper_pollOnce(timeout, nullptr, &events, reinterpret_cast<void**>(&pSource));
            switch (result) {
                case ALOOPER_POLL_TIMEOUT:
                    [[clang::fallthrough]];
                case ALOOPER_POLL_WAKE:
                    done = true;
                    break;
                case ALOOPER_EVENT_ERROR:
                    os_log_error("ALooper_pollOnce returned an error");
                    break;
                case ALOOPER_POLL_CALLBACK:
                    break;
                default:
                    if (pSource) {
                        pSource->process(pApp, pSource);
                    }
            }
        }

        if (pApp->userData) {
          GLData * p = reinterpret_cast<GLData*>(pApp->userData);

          // AHardwareBuffer_sendHandleToUnixSocket
          // AHardwareBuffer_recvHandleFromUnixSocket
          if (p->sfc != EGL_NO_SURFACE && eglGetCurrentContext() != EGL_NO_CONTEXT) {
        		float pxRatio = (float)p->w / (float)p->w;
        
        		// Update and render
        		glViewport(0, 0, p->w, p->h);
        		glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
        		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
        
        		glEnable(GL_BLEND);
        		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        		glEnable(GL_CULL_FACE);
        		glDisable(GL_DEPTH_TEST);
        
        		nvgBeginFrame(p->vg, p->w, p->h, pxRatio);
        		
        		// https://github.com/mgood7123/mps
        		// https://github.com/mgood7123/ManagedObject
        		// https://github.com/mgood7123/ManagedObject/blob/main/include/managed_object_obj.h
        		// https://github.com/styluslabs/nanovgXC
        		// https://github.com/wjakob/nanogui/blob/master/src/glcanvas.cpp
        		// https://github.com/yushroom/FishGUI
        		// https://github.com/kublasean/RecyclerViewQt/tree/main/recycler
        		// https://github.com/ridiculousfish/libdivide
        		// https://github.com/ocornut/imgui/tree/master/backends
        		// https://github.com/Trilloxa/Glass-UI
        		
        		// prebuilt for android
        		// https://github.com/MJx0/KittyMemory/blob/master/KittyMemory/Deps/Keystone
        		
        		// Android-like C++ ui
        		// https://github.com/houstudio/cdroid

            // auto& io = ImGui::GetIO();
            // ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

        		nvgEndFrame(p->vg);
        		
        		if (swap_surface_egl(p->sfc) == EGL_NO_SURFACE) {
              set_no_surface_current();
              destroy_surface_egl(p->sfc);
        		}
          }
        }
    } while (!pApp->destroyRequested);
}
}
