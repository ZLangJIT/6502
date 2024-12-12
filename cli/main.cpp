#include <stdio.h>
#include <vector>

#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#if __ANDROID__
#include <android/log.h>
#include <android/native_window_jni.h>
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
    os_egl_last_error = os_egl_error; \
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
  os_egl_check_errorIf(!eglInitialize(d, &maj, &min), {
    LOG_ERROR("");
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
  LOG_INFO("");
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
      LOG_ERROR("");
      return false;
    });
    egl_display = EGL_NO_DISPLAY;
    min = 0;
    maj = 0;
  }
  return true;
};

int main(int argc, char* argv[]) {
  if (!init_egl()) return 0;
  eglBindAPI(EGL_OPENGL_ES_API);
  
  EGLint numConfigs;
  EGLConfig cfg = 0;
  EGLContext ctx = EGL_NO_CONTEXT;
  EGLSurface sfc = EGL_NO_SURFACE;

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
      deinit_egl();
      return 0;
    })
  });
  
  os_egl_check_errorIf_((ctx = eglCreateContext(egl_display, cfg, nullptr, ctxattribs)), !=, EGL_NO_CONTEXT, {
      deinit_egl();
      return 0;
  });
  os_egl_check_errorIf(!eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT), {
      os_egl_check_error(eglDestroyContext(egl_display, ctx));
      deinit_egl();
      return 0;
  });
  #if __ANDROID__
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
            LOG_ERROR("Failed to allocate native buffer (%p, error %d)", new_, status);
            LOG_ERROR("Forcing legacy drawing");
            goto DONE;
        }

        uint32_t *pixels;
        if (AHardwareBuffer_lock(new_, (AHARDWAREBUFFER_USAGE_CPU_WRITE_OFTEN | AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN), -1, nullptr, (void **) &pixels) == 0) {
            pixels[0] = 0xAABBCCDD;
            AHardwareBuffer_unlock(new_, nullptr);
        } else {
            LOG_ERROR("Failed to lock native buffer (%p, error %d)", new_, status);
            LOG_ERROR("Forcing legacy drawing");
            AHardwareBuffer_release(new_);
            goto DONE;
        }

        os_egl_check_errorIf_(!(clientBuffer = eglGetNativeClientBufferANDROID(new_)), ==, true, {
            LOG_ERROR("Failed to obtain EGLClientBuffer from AHardwareBuffer");
            LOG_ERROR("Forcing legacy drawing");
            AHardwareBuffer_release(new_);
            goto DONE;
        });

        os_egl_check_error((img = eglCreateImageKHR(egl_display, EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_ANDROID, clientBuffer, imageAttributes));
        if (!image) {
            if (os_egl_last_error == EGL_BAD_PARAMETER) {
                LOG_ERROR("Sampling from HAL_PIXEL_FORMAT_BGRA_8888 is not supported, forcing AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM");
                // *flip = 1;
                AHardwareBuffer_release(new_);
                goto DONE;
            } else {
                LOG_ERROR("Failed to obtain EGLImageKHR from EGLClientBuffer");
                LOG_ERROR("Forcing legacy drawing");
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
                LOG_ERROR("EGL: check eglChooseConfig failed.\n");
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            });

            EGLContext testctx;
            os_egl_check_errorIf_((testctx = eglCreateContext(egl_display, checkcfg, nullptr, ctxattribs)), ==, EGL_NO_CONTEXT, {
                LOG_ERROR("EGL: check eglCreateContext failed.\n");
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
            os_egl_check_errorIf_((checksfc = eglCreatePbufferSurface(egl_display, checkcfg, pbufferAttributes))), ==, 0, {
                LOG_ERROR("EGL: check eglCreatePbufferSurface failed.\n");
                os_egl_check_error(eglDestroyContext(egl_display, testctx));
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            });

            os_egl_check_errorIf(!eglMakeCurrent(egl_display, checksfc, checksfc, testctx), {
                LOG_ERROR("EGL: check eglMakeCurrent failed.\n");
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
                LOG_ERROR("GLES: GLES draws pixels unchanged, probably system does not support AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM. Forcing bgra.\n");
                //*flip = 1;
                os_egl_check_error(eglDestroySurface(egl_display, checksfc));
                os_egl_check_error(eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
                os_egl_check_error(eglDestroyContext(egl_display, testctx));
                os_egl_check_error(eglDestroyImageKHR(egl_display, img));
                AHardwareBuffer_release(new_);
                goto DONE;
            } else if (pixel[0] != 0xAADDCCBB) {
                LOG_ERROR("Xlorie: GLES receives broken pixels. Forcing legacy drawing. 0x%X\n", pixel[0]);
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
    DONE:
    }
  #endif
  deinit_egl();
  return 0;
}
