// #include <stdio.h>

// #include <vector>

// #define EGL_EGLEXT_PROTOTYPES
// #define GL_GLEXT_PROTOTYPES

// #include <EGL/egl.h>
// #include <EGL/eglext.h>
// #include <GLES2/gl2.h>
// #include <GLES2/gl2ext.h>
// #if ANDROID
// #include <android/native_window_jni.h>
// #include <android/log.h>
// #include <android/hardware_buffer.h>

// #define log(...) __android_log_print(ANDROID_LOG_DEBUG, "gles-renderer", __VA_ARGS__)
// #define loge(...) __android_log_print(ANDROID_LOG_ERROR, "gles-renderer", __VA_ARGS__)

// #else

// #define log(...) printf(__VA_ARGS__)
// #define loge(...) printf(__VA_ARGS__)

// #endif

// int eglCheckError(int line) {
//     char* desc;
//     int err = eglGetError();
//     switch(err) {
// #define E(code, text) case code: desc = (char*) text; break
//         case EGL_SUCCESS: desc = nullptr; // "No error"
//         E(EGL_NOT_INITIALIZED, "EGL not initialized or failed to initialize");
//         E(EGL_BAD_ACCESS, "Resource inaccessible");
//         E(EGL_BAD_ALLOC, "Cannot allocate resources");
//         E(EGL_BAD_ATTRIBUTE, "Unrecognized attribute or attribute value");
//         E(EGL_BAD_CONTEXT, "Invalid EGL context");
//         E(EGL_BAD_CONFIG, "Invalid EGL frame buffer configuration");
//         E(EGL_BAD_CURRENT_SURFACE, "Current surface is no longer valid");
//         E(EGL_BAD_DISPLAY, "Invalid EGL display");
//         E(EGL_BAD_SURFACE, "Invalid surface");
//         E(EGL_BAD_MATCH, "Inconsistent arguments");
//         E(EGL_BAD_PARAMETER, "Invalid argument");
//         E(EGL_BAD_NATIVE_PIXMAP, "Invalid native pixmap");
//         E(EGL_BAD_NATIVE_WINDOW, "Invalid native window");
//         E(EGL_CONTEXT_LOST, "Context lost");
// #undef E
//         default: desc = (char*) "Unknown error";
//     }

//     if (desc)
//         log("Xlorie: egl error on line %d: %s\n", line, desc);

//     return err;
// }

// const char* eglErrorLabel(int code) {
//     switch(code) {
//         case EGL_SUCCESS: return nullptr; // "No error"
// #define E(code) case code: return #code; break
//         E(EGL_NOT_INITIALIZED);
//         E(EGL_BAD_ACCESS);
//         E(EGL_BAD_ALLOC);
//         E(EGL_BAD_ATTRIBUTE);
//         E(EGL_BAD_CONTEXT);
//         E(EGL_BAD_CONFIG);
//         E(EGL_BAD_CURRENT_SURFACE);
//         E(EGL_BAD_DISPLAY);
//         E(EGL_BAD_SURFACE);
//         E(EGL_BAD_MATCH);
//         E(EGL_BAD_PARAMETER);
//         E(EGL_BAD_NATIVE_PIXMAP);
//         E(EGL_BAD_NATIVE_WINDOW);
//         E(EGL_CONTEXT_LOST);
// #undef E
//         default: return "EGL_UNKNOWN_ERROR";
//     }

// }

// #define eglCheckError() eglCheckError(__LINE__)

// // void checkGlError(int line) {
// //     GLenum error;
// //     char *desc = nullptr;
// //     for (error = glGetError(); error; error = glGetError()) {
// //         switch (error) {
// // #define E(code) case code: desc = (char*)#code; break
// //             E(GL_INVALID_ENUM);
// //             E(GL_INVALID_VALUE);
// //             E(GL_INVALID_OPERATION);
// //             E(GL_STACK_OVERFLOW_KHR);
// //             E(GL_STACK_UNDERFLOW_KHR);
// //             E(GL_OUT_OF_MEMORY);
// //             E(GL_INVALID_FRAMEBUFFER_OPERATION);
// //             E(GL_CONTEXT_LOST_KHR);
// //             default:
// //                 continue;
// // #undef E
// //         }
// //         log("Xlorie: GLES %d ERROR: %s.\n", line, desc);
// //         return;
// //     }
// // }

// // #define checkGlError() checkGlError(__LINE__)

// class dep {
//   std::vector<dep*> deps;
//   bool destroyed = true;
//   public:
//   void add(dep * x) {
//     deps.emplace_back(x);
//   }
//   virtual void onBuild() {}
//   virtual void onRebuild() { destroy(); build(); }
//   virtual void onDestroy() {}
//   void build() {
//     if (destroyed) {
//       onBuild();
//       for (dep * x : deps) x->build();
//       destroyed = false;
//     }
//   }
//   void rebuild() { onRebuild(); }
//   void destroy() {
//     if (!destroyed) {
//       for (size_t i = deps.size(); i > 0; i--) deps[i-1]->destroy();
//       onDestroy();
//       destroyed = true;
//     }
//   }
//   virtual ~dep() { destroy(); }
// };

// #define component_action(start, action, end, x)   puts("[component " #start "] - " #x); x.action(); puts("[component " #end "] - " #x "\n")

// #define component_build(x)   component_action(building, build, built, x)
// #define component_rebuild(x)   component_action(rebuilding, rebuild, rebuilt, x)
// #define component_destroy(x)   component_action(destroying, destroy, destroyed, x)

// struct egl_display : public dep {
//   EGLDisplay egl_display = EGL_NO_DISPLAY;
//   void onBuild() override {
//     egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
//     if (egl_display == EGL_NO_DISPLAY) {
//       log("EGL: Got no EGL display.\n");
//       eglCheckError();
//     }
//   }
//   void onDestroy() override {
//     egl_display = EGL_NO_DISPLAY;
//   }
// };

// struct egl_initialize : public dep {
//   egl_display display;
//   EGLint major, minor;
//   void onBuild() override {
//     component_build(display);
//     if (eglInitialize(display.egl_display, &major, &minor) != EGL_TRUE) {
//         log("EGL: Unable to initialize EGL\n");
//         eglCheckError();
//     }
//   }
//   void onDestroy() override {
//     major = 0;
//     minor = 0;
//     component_destroy(display);
//   }
// };

// int main(int argc, char* argv[]) {
//   egl_display display;
//   egl_initialize initialize;
//   component_rebuild(display);
//   component_rebuild(initialize);
//   return 0;
// }

/*
 * eglinfo - like glxinfo but for EGL
 *
 * Brian Paul
 * 11 March 2005
 *
 * Copyright (C) 2005  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define EGL_EGLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONFIGS 1000
#define MAX_MODES 1000
#define MAX_SCREENS 10

/* These are X visual types, so if you're running eglinfo under
 * something not X, they probably don't make sense. */
static const char *vnames[] = { "SG", "GS", "SC", "PC", "TC", "DC" };

/**
 * Print table of all available configurations.
 */
static void
PrintConfigs(EGLDisplay d)
{
   EGLConfig configs[MAX_CONFIGS];
   EGLint numConfigs, i;

   eglGetConfigs(d, configs, MAX_CONFIGS, &numConfigs);

   printf("Configurations:\n");
   printf("     bf lv colorbuffer dp st  ms    vis   cav bi  renderable  supported\n");
   printf("  id sz  l  r  g  b  a th cl ns b    id   eat nd gl es es2 vg surfaces \n");
   /*        ^  ^   ^  ^  ^  ^  ^ ^  ^  ^  ^    ^    ^   ^  ^  ^  ^   ^  ^
    *        |  |   |  |  |  |  | |  |  |  |    |    |   |  |  |  |   |  |
    *        |  |   |  |  |  |  | |  |  |  |    |    |   |  |  |  |   |  EGL_SURFACE_TYPE
    *        |  |   |  |  |  |  | |  |  |  |    |    |   |  EGL_RENDERABLE_TYPE
    *        |  |   |  |  |  |  | |  |  |  |    |    |   EGL_BIND_TO_TEXTURE_RGB/EGL_BIND_TO_TEXTURE_RGBA
    *        |  |   |  |  |  |  | |  |  |  |    |    EGL_CONFIG_CAVEAT
    *        |  |   |  |  |  |  | |  |  |  |    EGL_NATIVE_VISUAL_ID/EGL_NATIVE_VISUAL_TYPE
    *        |  |   |  |  |  |  | |  |  |  EGL_SAMPLE_BUFFERS
    *        |  |   |  |  |  |  | |  |  EGL_SAMPLES
    *        |  |   |  |  |  |  | |  EGL_STENCIL_SIZE
    *        |  |   |  |  |  |  | EGL_DEPTH_SIZE
    *        |  |   |  |  |  |  EGL_ALPHA_SIZE
    *        |  |   |  |  |  EGL_BLUE_SIZE
    *        |  |   |  |  EGL_GREEN_SIZE
    *        |  |   |  EGL_RED_SIZE
    *        |  |   EGL_LEVEL
    *        |  EGL_BUFFER_SIZE
    *        EGL_CONFIG_ID
    */
   printf("---------------------------------------------------------------------\n");
   for (i = 0; i < numConfigs; i++) {
      EGLint id, size, level;
      EGLint red, green, blue, alpha;
      EGLint depth, stencil;
      EGLint renderable, surfaces;
      EGLint vid, vtype, caveat, bindRgb, bindRgba;
      EGLint samples, sampleBuffers;
      char surfString[100] = "";

      eglGetConfigAttrib(d, configs[i], EGL_CONFIG_ID, &id);
      eglGetConfigAttrib(d, configs[i], EGL_BUFFER_SIZE, &size);
      eglGetConfigAttrib(d, configs[i], EGL_LEVEL, &level);

      eglGetConfigAttrib(d, configs[i], EGL_RED_SIZE, &red);
      eglGetConfigAttrib(d, configs[i], EGL_GREEN_SIZE, &green);
      eglGetConfigAttrib(d, configs[i], EGL_BLUE_SIZE, &blue);
      eglGetConfigAttrib(d, configs[i], EGL_ALPHA_SIZE, &alpha);
      eglGetConfigAttrib(d, configs[i], EGL_DEPTH_SIZE, &depth);
      eglGetConfigAttrib(d, configs[i], EGL_STENCIL_SIZE, &stencil);
      eglGetConfigAttrib(d, configs[i], EGL_NATIVE_VISUAL_ID, &vid);
      eglGetConfigAttrib(d, configs[i], EGL_NATIVE_VISUAL_TYPE, &vtype);

      eglGetConfigAttrib(d, configs[i], EGL_CONFIG_CAVEAT, &caveat);
      eglGetConfigAttrib(d, configs[i], EGL_BIND_TO_TEXTURE_RGB, &bindRgb);
      eglGetConfigAttrib(d, configs[i], EGL_BIND_TO_TEXTURE_RGBA, &bindRgba);
      eglGetConfigAttrib(d, configs[i], EGL_RENDERABLE_TYPE, &renderable);
      eglGetConfigAttrib(d, configs[i], EGL_SURFACE_TYPE, &surfaces);

      eglGetConfigAttrib(d, configs[i], EGL_SAMPLES, &samples);
      eglGetConfigAttrib(d, configs[i], EGL_SAMPLE_BUFFERS, &sampleBuffers);

      if (surfaces & EGL_WINDOW_BIT)
         strcat(surfString, "win,");
      if (surfaces & EGL_PBUFFER_BIT)
         strcat(surfString, "pb,");
      if (surfaces & EGL_PIXMAP_BIT)
         strcat(surfString, "pix,");
      if (surfaces & EGL_STREAM_BIT_KHR)
         strcat(surfString, "str,");
      if (strlen(surfString) > 0)
         surfString[strlen(surfString) - 1] = 0;

      printf("0x%02x %2d %2d %2d %2d %2d %2d %2d %2d %2d%2d 0x%02x%s ",
             id, size, level,
             red, green, blue, alpha,
             depth, stencil,
             samples, sampleBuffers, vid, vtype < 6 ? vnames[vtype] : "--");
      printf("  %c  %c  %c  %c  %c   %c %s\n",
             (caveat != EGL_NONE) ? 'y' : ' ',
             (bindRgba) ? 'a' : (bindRgb) ? 'y' : ' ',
             (renderable & EGL_OPENGL_BIT) ? 'y' : ' ',
             (renderable & EGL_OPENGL_ES_BIT) ? 'y' : ' ',
             (renderable & EGL_OPENGL_ES2_BIT) ? 'y' : ' ',
             (renderable & EGL_OPENVG_BIT) ? 'y' : ' ',
             surfString);
   }
}


static const char *
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


static const char *
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


static const char *
PrintDeviceExtensions(EGLDeviceEXT d)
{
   PFNEGLQUERYDEVICESTRINGEXTPROC queryDeviceString =
     (PFNEGLQUERYDEVICESTRINGEXTPROC)
     eglGetProcAddress("eglQueryDeviceStringEXT");
   const char *extensions;

   puts("EGL device extensions string:");

   extensions = queryDeviceString(d, EGL_EXTENSIONS);
   if (!extensions)
      return NULL;

   return PrintExtensions(extensions);
}


static int
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

   PrintConfigs(d);
   eglTerminate(d);
   printf("\n");
   return 0;
}


static int
doOneDevice(EGLDeviceEXT d, int i)
{
   PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay =
     (PFNEGLGETPLATFORMDISPLAYEXTPROC)
     eglGetProcAddress("eglGetPlatformDisplayEXT");

   printf("Device #%d:\n\n", i);

   PrintDeviceExtensions(d);

   return doOneDisplay(getPlatformDisplay(EGL_PLATFORM_DEVICE_EXT, d, NULL),
                       "Platform Device");
}


static int
doDevices(const char *name)
{
   PFNEGLQUERYDEVICESEXTPROC queryDevices =
     (PFNEGLQUERYDEVICESEXTPROC) eglGetProcAddress("eglQueryDevicesEXT");
   EGLDeviceEXT *devices;
   EGLint max_devices, num_devices;
   EGLint i;
   int ret = 0;

   printf("%s:\n", name);

   if (!queryDevices(0, NULL, &max_devices))
      return 1;
   devices = reinterpret_cast<EGLDeviceEXT *>(calloc(sizeof(EGLDeviceEXT), max_devices));
   if (!devices)
      return 1;
   if (!queryDevices(max_devices, devices, &num_devices))
     num_devices = 0;

   for (i = 0; i < num_devices; ++i) {
       ret += doOneDevice(devices[i], i);
   }

   free(devices);

   return ret;
}


int
main(int argc, char *argv[])
{
   int ret = 0;
   const char *clientext;

   clientext = PrintDisplayExtensions(EGL_NO_DISPLAY);
   printf("\n");

   if (strstr(clientext, "EGL_EXT_platform_base") || strstr(clientext, "EGL_ANGLE_platform_angle")) {
       PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay =
           (PFNEGLGETPLATFORMDISPLAYEXTPROC)
           eglGetProcAddress("eglGetPlatformDisplayEXT");
       if (strstr(clientext, "EGL_KHR_platform_android"))
           ret += doOneDisplay(getPlatformDisplay(EGL_PLATFORM_ANDROID_KHR,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "Android platform");
       if (strstr(clientext, "EGL_MESA_platform_gbm") ||
           strstr(clientext, "EGL_KHR_platform_gbm"))
           ret += doOneDisplay(getPlatformDisplay(EGL_PLATFORM_GBM_MESA,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "GBM platform");
       if (strstr(clientext, "EGL_EXT_platform_wayland") ||
           strstr(clientext, "EGL_KHR_platform_wayland"))
           ret += doOneDisplay(getPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "Wayland platform");
       if (strstr(clientext, "EGL_EXT_platform_x11") ||
           strstr(clientext, "EGL_KHR_platform_x11"))
           ret += doOneDisplay(getPlatformDisplay(EGL_PLATFORM_X11_EXT,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "X11 platform");
       if (strstr(clientext, "EGL_MESA_platform_surfaceless"))
           ret += doOneDisplay(getPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA,
                                                  EGL_DEFAULT_DISPLAY,
                                                  NULL), "Surfaceless platform");
       if (strstr(clientext, "EGL_EXT_device_enumeration") &&
           strstr(clientext, "EGL_EXT_platform_device"))
           ret += doDevices("Device platform");
   }
   else {
      ret = doOneDisplay(eglGetDisplay(EGL_DEFAULT_DISPLAY), "Default display");
   }

   return ret;
}
