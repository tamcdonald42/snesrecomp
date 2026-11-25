#pragma once
#include "display_aspect.h"

/* The shared desktop OpenGL presenter (desktop/opengl.c). util.h declares
 * OpenGLRenderer_Create itself; this header carries only the presentation
 * policy a host may need to override. */

#ifdef __cplusplus
extern "C" {

/* Bezel layer for the GL presenter. The game uploads its art once and
 * then tells the presenter, per frame, whether to draw it and how much of
 * the frame width each margin takes (0.1667 = 64 of 384). Both are NULL
 * until a GL presenter exists, so a caller can test them to find out
 * whether the fast path is available at all. */
extern void (*SnesOpenGLBezelImage)(const unsigned char *left,
                                    int left_w, int left_h,
                                    const unsigned char *right,
                                    int right_w, int right_h);
extern void (*SnesOpenGLBezelFrame)(int visible, float margin_fraction);

#endif

/* Force the swap interval instead of deriving it from config.
 *
 * Call BEFORE the renderer is created. A host that paces presentation on its
 * own clock (an FPS cap, or a split simulation/presentation rate) passes 0,
 * so SDL_GL_SwapWindow does not block on the display as well and fight that
 * pacing. Left unset, the presenter vsyncs unless config's DisableFrameDelay
 * is on. */
/* Swap interval for the GL presenter: 0 immediate, 1 wait for the panel,
 * -1 late-swap-tearing ("Adaptive"). Call before OpenGLRenderer_Create. */
void snesrecomp_opengl_set_vsync(int interval);
void snesrecomp_opengl_set_viewport(void (*compute)(int, int, int, int,
                                                   SnesDisplayViewport *));

/* Capture the next fully composited OpenGL frame to screenshots/*.bmp. */
void OpenGLRenderer_RequestScreenshot(void);

#ifdef __cplusplus
}
#endif
