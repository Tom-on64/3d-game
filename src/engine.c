#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "engine.h"

void update(float dt) {
    if (dt <= 0.032f) printf("\x1b[32m"); // Good - green
    else printf("\x1b[31m"); // Bad - red

    printf("[DBG] ∆t = %.3f\n", dt);
}

void render() {
    // Clear screen
    clearpixels(screen, 0);

    // Draw random colors
    for (size_t i = 0; i < 0xffff; i++) {
        int x = random() % screen->width;
        int y = random() % screen->height;
        int r = random() % 255;
        int g = random() % 255;
        int b = random() % 255;

        uint32_t color = r | (g << 8) | (b << 16);

        putpixel(screen, x, y, color);
    }

    drawframe(screen);
}

