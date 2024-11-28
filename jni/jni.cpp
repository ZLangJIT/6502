#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <dlfcn.h>

#include <jni.h>
#include <android/hardware_buffer.h>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#define log(...) __android_log_print(ANDROID_LOG_DEBUG, "gles-renderer", __VA_ARGS__)
#define loge(...) __android_log_print(ANDROID_LOG_ERROR, "gles-renderer", __VA_ARGS__)

// Stands to HAL_PIXEL_FORMAT_BGRA_8888
#define AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM 5

static int eglCheckError(int line) {
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

static const char* eglErrorLabel(int code) {
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

static void checkGlError(int line) {
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

static const char vertex_shader[] =
    "attribute vec4 position;\n"
    "attribute vec2 texCoords;"
    "varying vec2 outTexCoords;\n"
    "void main(void) {\n"
    "   outTexCoords = texCoords;\n"
    "   gl_Position = position;\n"
    "}\n";

#define FRAGMENT_SHADER(texture) \
    "precision mediump float;\n" \
    "varying vec2 outTexCoords;\n" \
    "uniform sampler2D texture;\n" \
    "void main(void) {\n" \
    "   gl_FragColor = texture2D(texture, outTexCoords)" texture ";\n" \
    "}\n"

static const char fragment_shader[] = FRAGMENT_SHADER();
static const char fragment_shader_bgra[] = FRAGMENT_SHADER(".bgra");

static GLuint load_shader(GLenum shaderType, const char* pSource) {
    GLint compiled = 0;
    GLuint shader = glCreateShader(shaderType); checkGlError();
    if (shader) {
        glShaderSource(shader, 1, &pSource, nullptr); checkGlError();
        glCompileShader(shader); checkGlError();
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); checkGlError();
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen); checkGlError();
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, nullptr, buf); checkGlError();
                    log("Xlorie: Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader); checkGlError();
                shader = 0;
            }
        }
    }
    return shader;
}

static GLuint create_program(const char* p_vertex_source, const char* p_fragment_source) {
    GLuint program, vertexShader, pixelShader;
    GLint linkStatus = GL_FALSE;
    vertexShader = load_shader(GL_VERTEX_SHADER, p_vertex_source);
    pixelShader = load_shader(GL_FRAGMENT_SHADER, p_fragment_source);
    if (!pixelShader || !vertexShader) {
        return 0;
    }

    program = glCreateProgram(); checkGlError();
    if (program) {
        glAttachShader(program, vertexShader); checkGlError();
        glAttachShader(program, pixelShader); checkGlError();
        glLinkProgram(program); checkGlError();
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus); checkGlError();
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength); checkGlError();
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, nullptr, buf); checkGlError();
                    log("Xlorie: Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program); checkGlError();
            program = 0;
        }
    }
    return program;
}

static EGLDisplay egl_display = EGL_NO_DISPLAY;
static EGLContext ctx = EGL_NO_CONTEXT;
static EGLSurface sfc = EGL_NO_SURFACE;
static EGLConfig cfg = 0;
static EGLNativeWindowType win = 0;
static AHardwareBuffer *buffer = nullptr;
static EGLImageKHR image = nullptr;
static int renderedFrames = 0;

static struct {
    GLuint id;
    float width, height;
} display;

static struct {
    GLuint id;
    float x, y, width, height, xhot, yhot;
} cursor;

GLuint g_texture_program = 0, gv_pos = 0, gv_coords = 0;
GLuint g_texture_program_bgra = 0, gv_pos_bgra = 0, gv_coords_bgra = 0;

#define USAGE (AHARDWAREBUFFER_USAGE_CPU_WRITE_OFTEN | AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN)

static int renderer_init(bool* legacy_drawing, uint8_t* flip) {
    EGLint major, minor;
    EGLint numConfigs;
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

    if (ctx)
        return 1;

    egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (egl_display == EGL_NO_DISPLAY) {
        log("Xlorie: Got no EGL display.\n");
        eglCheckError(__LINE__);
        return 0;
    }

    if (eglInitialize(egl_display, &major, &minor) != EGL_TRUE) {
        log("Xlorie: Unable to initialize EGL\n");
        eglCheckError(__LINE__);
        return 0;
    }
    log("Xlorie: Initialized EGL version %d.%d\n", major, minor);
    eglBindAPI(EGL_OPENGL_ES_API);

    if (eglChooseConfig(egl_display, configAttribs, &cfg, 1, &numConfigs) != EGL_TRUE &&
            eglChooseConfig(egl_display, configAttribs2, &cfg, 1, &numConfigs) != EGL_TRUE) {
        log("Xlorie: eglChooseConfig failed.\n");
        eglCheckError(__LINE__);
        return 0;
    }

    ctx = eglCreateContext(egl_display, cfg, nullptr, ctxattribs);
    if (ctx == EGL_NO_CONTEXT) {
        log("Xlorie: eglCreateContext failed.\n");
        eglCheckError(__LINE__);
        return 0;
    }

    if (eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) != EGL_TRUE) {
        log("Xlorie: eglMakeCurrent failed.\n");
        eglCheckError(__LINE__);
        return 0;
    }

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
                .format = AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM,
                .usage = AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE | USAGE
        };

        status = AHardwareBuffer_allocate(&d0, &new_);
        if (status != 0 || new_ == nullptr) {
            loge("Failed to allocate native buffer (%p, error %d)", new_, status);
            loge("Forcing legacy drawing");
            *legacy_drawing = 1;
            return 1;
        }

        uint32_t *pixels;
        if (AHardwareBuffer_lock(new_, USAGE, -1, nullptr, (void **) &pixels) == 0) {
            pixels[0] = 0xAABBCCDD;
            AHardwareBuffer_unlock(new_, nullptr);
        } else {
            loge("Failed to lock native buffer (%p, error %d)", new_, status);
            loge("Forcing legacy drawing");
            *legacy_drawing = 1;
            return 1;
        }

        clientBuffer = eglGetNativeClientBufferANDROID(new_);
        if (!clientBuffer) {
            eglCheckError(__LINE__);
            loge("Failed to obtain EGLClientBuffer from AHardwareBuffer");
            loge("Forcing legacy drawing");
            *legacy_drawing = 1;
            return 1;
        }

        if (!(img = eglCreateImageKHR(egl_display, EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_ANDROID, clientBuffer, imageAttributes))) {
            if (eglGetError() == EGL_BAD_PARAMETER) {
                loge("Sampling from HAL_PIXEL_FORMAT_BGRA_8888 is not supported, forcing AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM");
                *flip = 1;
            } else {
                loge("Failed to obtain EGLImageKHR from EGLClientBuffer");
                loge("Forcing legacy drawing");
                *legacy_drawing = 1;
            }
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
            if (eglChooseConfig(egl_display, configAttributes, &checkcfg, 1, &numConfigs) != EGL_TRUE) {
                log("Xlorie: check eglChooseConfig failed.\n");
                eglCheckError(__LINE__);
                return 0;
            }

            EGLContext testctx = eglCreateContext(egl_display, checkcfg, nullptr, ctxattribs);
            if (testctx == EGL_NO_CONTEXT) {
                log("Xlorie: check eglCreateContext failed.\n");
                eglCheckError(__LINE__);
                return 0;
            }

            const EGLint pbufferAttributes[] = {
                    EGL_WIDTH, 64,
                    EGL_HEIGHT, 64,
                    EGL_NONE,
            };
            EGLSurface checksfc = eglCreatePbufferSurface(egl_display, checkcfg, pbufferAttributes);

            if (eglMakeCurrent(egl_display, checksfc, checksfc, testctx) != EGL_TRUE) {
                log("Xlorie: check eglMakeCurrent failed.\n");
                eglCheckError(__LINE__);
                return 0;
            }

            glActiveTexture(GL_TEXTURE0); checkGlError();
            glGenTextures(1, &texture); checkGlError();
            glBindTexture(GL_TEXTURE_2D, texture); checkGlError();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); checkGlError();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); checkGlError();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); checkGlError();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); checkGlError();
            glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, img); checkGlError();
            glGenFramebuffers(1, &fbo); checkGlError();
            glBindFramebuffer(GL_FRAMEBUFFER, fbo); checkGlError();
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0); checkGlError();
            uint32_t pixel[64*64];
            glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel); checkGlError();
            if (pixel[0] == 0xAABBCCDD) {
                log("Xlorie: GLES draws pixels unchanged, probably system does not support AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM. Forcing bgra.\n");
                *flip = 1;
            } else if (pixel[0] != 0xAADDCCBB) {
                log("Xlorie: GLES receives broken pixels. Forcing legacy drawing. 0x%X\n", pixel[0]);
                *legacy_drawing = 1;
            }
            eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        }
    }

    return 1;
}

static void renderer_unset_buffer(void) {
    if (eglGetCurrentContext() == EGL_NO_CONTEXT) {
        loge("There is no current context, `renderer_set_buffer` call is cancelled");
        return;
    }

    log("renderer_set_buffer0");
    if (image)
        eglDestroyImageKHR(egl_display, image);
    if (buffer)
        AHardwareBuffer_release(buffer);

    buffer = nullptr;
}

static int renderer_redraw(uint8_t flip);

static void renderer_set_buffer(AHardwareBuffer* buf) {
    const EGLint imageAttributes[] = {EGL_IMAGE_PRESERVED_KHR, EGL_TRUE, EGL_NONE};
    EGLClientBuffer clientBuffer;
    AHardwareBuffer_Desc desc = {0};
    uint8_t flip = 0;

    if (eglGetCurrentContext() == EGL_NO_CONTEXT) {
        loge("There is no current context, `renderer_set_buffer` call is cancelled");
        return;
    }

    renderer_unset_buffer();

    buffer = buf;

    glBindTexture(GL_TEXTURE_2D, display.id); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); checkGlError();
    if (buffer) {
        AHardwareBuffer_acquire(buffer);
        AHardwareBuffer_describe(buffer, &desc);

        display.width = (float) desc.width;
        display.height = (float) desc.height;

        clientBuffer = eglGetNativeClientBufferANDROID(buffer);
        if (!clientBuffer) {
            eglCheckError(__LINE__);
            loge("Failed to obtain EGLClientBuffer from AHardwareBuffer");
        }
        image = clientBuffer ? eglCreateImageKHR(egl_display, EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_ANDROID, clientBuffer, imageAttributes) : nullptr;
        if (image != nullptr) {
            glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, image);
            flip = desc.format != AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM;
        } else {
            if (clientBuffer) {
                eglCheckError(__LINE__);
                loge("Binding AHardwareBuffer to an EGLImage failed.");
            }

            display.width = 1;
            display.height = 1;
            uint32_t data = {0};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
            checkGlError();
        }
        checkGlError();
    } else {
        display.width = 1;
        display.height = 1;
        uint32_t data = {0};
        loge("There is no AHardwareBuffer, nothing to be bound.");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data); checkGlError();
    }

    renderer_redraw(flip);

    log("renderer_set_buffer %p %d %d", buffer, desc.width, desc.height);
}

static void renderer_set_window(ANativeWindow * window, AHardwareBuffer* new_buffer) {
    int width = window ? ANativeWindow_getWidth(window) : 0;
    int height = window ? ANativeWindow_getHeight(window) : 0;
    log("renderer_set_window %p %d %d", window, width, height);
    if (window && win == window)
        return;

    if (sfc != EGL_NO_SURFACE) {
        if (eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) != EGL_TRUE) {
            log("Xlorie: eglMakeCurrent (EGL_NO_SURFACE) failed.\n");
            eglCheckError(__LINE__);
            return;
        }
        if (eglDestroySurface(egl_display, sfc) != EGL_TRUE) {
            log("Xlorie: eglDestoySurface failed.\n");
            eglCheckError(__LINE__);
            return;
        }
    }
    sfc = EGL_NO_SURFACE;

    if (window && (width <= 0 || height <= 0)) {
        log("Xlorie: We've got invalid surface. Probably it became invalid before we started working with it.\n");
    }

    win = window;

    if (!win)
        return;
        
    sfc = eglCreateWindowSurface(egl_display, cfg, win, nullptr);
    if (sfc == EGL_NO_SURFACE) {
        log("Xlorie: eglCreateWindowSurface failed.\n");
        eglCheckError(__LINE__);
        return;
    }

    if (eglMakeCurrent(egl_display, sfc, sfc, ctx) != EGL_TRUE) {
        log("Xlorie: eglMakeCurrent failed.\n");
        eglCheckError(__LINE__);
        return;
    }

    if (!g_texture_program) {
        g_texture_program = create_program(vertex_shader, fragment_shader);
        if (!g_texture_program) {
            log("Xlorie: GLESv2: Unable to create shader program.\n");
            eglCheckError(__LINE__);
            return;
        }

        g_texture_program_bgra = create_program(vertex_shader, fragment_shader_bgra);
        if (!g_texture_program_bgra) {
            log("Xlorie: GLESv2: Unable to create bgra shader program.\n");
            eglCheckError(__LINE__);
            return;
        }

        gv_pos = (GLuint) glGetAttribLocation(g_texture_program, "position"); checkGlError();
        gv_coords = (GLuint) glGetAttribLocation(g_texture_program, "texCoords"); checkGlError();

        gv_pos_bgra = (GLuint) glGetAttribLocation(g_texture_program_bgra, "position"); checkGlError();
        gv_coords_bgra = (GLuint) glGetAttribLocation(g_texture_program_bgra, "texCoords"); checkGlError();

        glActiveTexture(GL_TEXTURE0); checkGlError();
        glGenTextures(1, &display.id); checkGlError();
        glGenTextures(1, &cursor.id); checkGlError();
    }

    eglSwapInterval(egl_display, 0);

    if (win && ctx && ANativeWindow_getWidth(win) > 0 && ANativeWindow_getHeight(win) > 0)
        glViewport(0, 0, ANativeWindow_getWidth(win), ANativeWindow_getHeight(win)); checkGlError();

    log("Xlorie: new surface applied: %p\n", sfc);

    if (!new_buffer) {
        glClearColor(0.f, 0.f, 0.f, 0.0f); checkGlError();
        glClear(GL_COLOR_BUFFER_BIT); checkGlError();
    } else renderer_set_buffer(new_buffer);
}

static void renderer_update_root(int w, int h, void* data, uint8_t flip) {
    if (eglGetCurrentContext() == EGL_NO_CONTEXT || !w || !h)
        return;

    if (display.width != (float) w || display.height != (float) h) {
        display.width = (float) w;
        display.height = (float) h;

        glBindTexture(GL_TEXTURE_2D, display.id); checkGlError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); checkGlError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); checkGlError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); checkGlError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); checkGlError();
        glTexImage2D(GL_TEXTURE_2D, 0, flip ? GL_RGBA : GL_BGRA_EXT, w, h, 0, flip ? GL_RGBA : GL_BGRA_EXT, GL_UNSIGNED_BYTE, data); checkGlError();
    } else {
        glBindTexture(GL_TEXTURE_2D, display.id); checkGlError();

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, flip ? GL_RGBA : GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
        checkGlError();
    }
}

static void renderer_update_cursor(int w, int h, int xhot, int yhot, void* data) {
    log("Xlorie: updating cursor\n");
    cursor.width = (float) w;
    cursor.height = (float) h;
    cursor.xhot = (float) xhot;
    cursor.yhot = (float) yhot;

    if (eglGetCurrentContext() == EGL_NO_CONTEXT || !cursor.width || !cursor.height)
        return;

    glBindTexture(GL_TEXTURE_2D, cursor.id); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); checkGlError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); checkGlError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); checkGlError();
}

static void renderer_set_cursor_coordinates(int x, int y) {
    cursor.x = (float) x;
    cursor.y = (float) y;
}

static void draw(GLuint id, float x0, float y0, float x1, float y1, uint8_t flip) {
    float coords[20] = {
        x0, -y0, 0.f, 0.f, 0.f,
        x1, -y0, 0.f, 1.f, 0.f,
        x0, -y1, 0.f, 0.f, 1.f,
        x1, -y1, 0.f, 1.f, 1.f,
    };

    GLuint p = flip ? gv_pos_bgra : gv_pos, c = flip ? gv_coords_bgra : gv_coords;

    glActiveTexture(GL_TEXTURE0); checkGlError();
    glUseProgram(flip ? g_texture_program_bgra : g_texture_program); checkGlError();
    glBindTexture(GL_TEXTURE_2D, id); checkGlError();

    glVertexAttribPointer(p, 3, GL_FLOAT, GL_FALSE, 20, coords); checkGlError();
    glVertexAttribPointer(c, 2, GL_FLOAT, GL_FALSE, 20, &coords[3]); checkGlError();
    glEnableVertexAttribArray(p); checkGlError();
    glEnableVertexAttribArray(c); checkGlError();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); checkGlError();
}

static void draw_cursor(void) {
    float x, y, w, h;

    if (!cursor.width || !cursor.height)
        return;

    x = 2.f * (cursor.x - cursor.xhot) / display.width - 1.f;
    y = 2.f * (cursor.y - cursor.yhot) / display.height - 1.f;
    w = 2.f * cursor.width / display.width;
    h = 2.f * cursor.height / display.height;
    glEnable(GL_BLEND); checkGlError();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); checkGlError();
    draw(cursor.id, x, y, x + w, y + h, false);
    glDisable(GL_BLEND); checkGlError();
}

float ia = 0;

static int renderer_should_redraw(void) {
    return sfc != EGL_NO_SURFACE && eglGetCurrentContext() != EGL_NO_CONTEXT;
}

static int renderer_redraw(uint8_t flip) {
    int err = EGL_SUCCESS;

    if (!sfc || eglGetCurrentContext() == EGL_NO_CONTEXT)
        return false;

    draw(display.id,  -1.f, -1.f, 1.f, 1.f, flip);
    draw_cursor();
    if (eglSwapBuffers(egl_display, sfc) != EGL_TRUE) {
        err = eglGetError();
        eglCheckError(__LINE__);
        if (err == EGL_BAD_NATIVE_WINDOW || err == EGL_BAD_SURFACE) {
            log("We've got %s so window is to be destroyed. "
                "Native window disconnected/abandoned, probably activity is destroyed or in background",
                eglErrorLabel(err));
            renderer_set_window(nullptr, nullptr);
            return false;
        }
    }

    renderedFrames++;
    return true;
}

void renderer_print_fps(float millis) {
    if (renderedFrames)
        log("%d frames in %.1f seconds = %.1f FPS",
                                renderedFrames, millis / 1000, (float) renderedFrames *  1000 / millis);
    renderedFrames = 0;
}

struct {
    AHardwareBuffer* buffer;
    bool locked;
    bool legacyDrawing;
    uint8_t flip;
    uint32_t width, height;
} root;

// void updateBuffer() {
//     AHardwareBuffer_Desc d0 = {}, d1 = {};
//     AHardwareBuffer *new = NULL, *old = pvfb->root.buffer;
//     int status, wasLocked = pvfb->root.locked;
//     void *data0 = NULL, *data1 = NULL;

//     if (pvfb->root.legacyDrawing) {
//         PixmapPtr pixmap = (PixmapPtr) pScreenPtr->devPrivate;
//         DrawablePtr draw = &pixmap->drawable;
//         data0 = malloc(pScreenPtr->width * pScreenPtr->height * 4);
//         data1 = (draw->width && draw->height) ? pixmap->devPrivate.ptr : NULL;
//         if (data1)
//             pixman_blt(data1, data0, draw->width, pScreenPtr->width, 32, 32, 0, 0, 0, 0,
//                       min(draw->width, pScreenPtr->width), min(draw->height, pScreenPtr->height));
//         pScreenPtr->ModifyPixmapHeader(pScreenPtr->devPrivate, pScreenPtr->width, pScreenPtr->height, 32, 32, pScreenPtr->width * 4, data0);
//         free(data1);
//         return;
//     }

//     if (pScreenPtr->devPrivate) {
//         d0.width = pScreenPtr->width;
//         d0.height = pScreenPtr->height;
//         d0.layers = 1;
//         d0.usage = USAGE | AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE;
//         d0.format = pvfb->root.flip
//                 ? AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM
//                 : AHARDWAREBUFFER_FORMAT_B8G8R8A8_UNORM;

//         /* I could use this, but in this case I must swap colours in the shader. */
//         // desc.format = AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM;

//         status = AHardwareBuffer_allocate(&d0, &new);
//         if (status != 0)
//             FatalError("Failed to allocate root window pixmap (error %d)", status);

//         AHardwareBuffer_describe(new, &d0);
//         status = AHardwareBuffer_lock(new, USAGE, -1, NULL, &data0);
//         if (status != 0)
//             FatalError("Failed to lock root window pixmap (error %d)", status);

//         pvfb->root.buffer = new;
//         pvfb->root.locked = true;

//         pScreenPtr->ModifyPixmapHeader(pScreenPtr->devPrivate, d0.width, d0.height, 32, 32, d0.stride * 4, data0);

//         renderer_set_buffer(new);
//     }

//     if (old) {
//         if (wasLocked)
//             AHardwareBuffer_unlock(old, NULL);

//         if (new && pvfb->root.locked) {
//             /*
//             * It is pretty easy. If there is old pixmap we should copy it's contents to new pixmap.
//             * If it is impossible we should simply request root window exposure.
//             */
//             AHardwareBuffer_describe(old, &d1);
//             status = AHardwareBuffer_lock(old, USAGE, -1, NULL, &data1);
//             if (status == 0) {
//                 pixman_blt(data1, data0, d1.stride, d0.stride,
//                           32, 32, 0, 0, 0, 0,
//                           min(d1.width, d0.width), min(d1.height, d0.height));
//                 AHardwareBuffer_unlock(old, NULL);
//             } else {
//                 RegionRec reg;
//                 BoxRec box = {.x1 = 0, .y1 = 0, .x2 = d0.width, .y2 = d0.height};
//                 RegionInit(&reg, &box, 1);
//                 pScreenPtr->WindowExposures(pScreenPtr->root, &reg);
//                 RegionUninit(&reg);
//                 AHardwareBuffer_release(old);
//                 return;
//             }
//         }
//         AHardwareBuffer_release(old);
//     }
// }

static inline void renderer_unlock() {
    if (root.legacyDrawing)
        return; //renderer_update_root(pixmap->drawable.width, pixmap->drawable.height, pixmap->devPrivate.ptr, pvfb->root.flip);

    if (root.locked)
        AHardwareBuffer_unlock(root.buffer, NULL);

    root.locked = false;
    //pixmap->drawable.pScreen->ModifyPixmapHeader(pixmap, -1, -1, -1, -1, -1, NULL);
}

static inline bool renderer_lock() {
    AHardwareBuffer_Desc desc = {};
    void *data;
    int status;

    if (root.legacyDrawing)
        return true;

    if (!root.buffer) {
        root.locked = false;
        return false;
    }

    AHardwareBuffer_describe(root.buffer, &desc);
    status = AHardwareBuffer_lock(root.buffer, USAGE, -1, NULL, &data);
    root.locked = status == 0;
    if (root.locked) {
        //pixmap->drawable.pScreen->ModifyPixmapHeader(pixmap, desc.width, desc.height, -1, -1, desc.stride * 4, data);
    } else {
        loge("Failed to lock surface: %d", status);
    }

    return root.locked;
}

extern "C" {

bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

#include <game-activity/native_app_glue/android_native_app_glue.c>

    void handle_cmd(android_app *pApp, int32_t cmd) {
      int ret = 0;
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            pApp->userData = ((void*)0x1);
            ret = renderer_init(&root.legacyDrawing, &root.flip);
            log("renderer_init returned %d", ret);
            renderer_set_window(pApp->window, root.buffer);
            //updateBuffer();
            break;
        case APP_CMD_TERM_WINDOW:
            if (pApp->userData == ((void*)0x1)) {
                renderer_set_window(nullptr, nullptr);
                pApp->userData = 0x0;
            }
            break;
        default:
            break;
    }
}

void android_main(struct android_app *pApp) {
    log("Welcome to android_main");
    
    

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
                    loge("ALooper_pollOnce returned an error");
                    break;
                case ALOOPER_POLL_CALLBACK:
                    break;
                default:
                    if (pSource) {
                        pSource->process(pApp, pSource);
                    }
            }
        }

        if (pApp->userData == ((void*)0x1)) {
          // AHardwareBuffer_sendHandleToUnixSocket
          // AHardwareBuffer_recvHandleFromUnixSocket
          if (renderer_should_redraw()) {
            renderer_unlock();
            int redrawn = renderer_redraw(root.flip);
            renderer_lock();
          }
        }
    } while (!pApp->destroyRequested);
}
}
