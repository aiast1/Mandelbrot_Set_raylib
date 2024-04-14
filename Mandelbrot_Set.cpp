#include "raylib.h"
#include <complex>

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "Mandelbrot Set");

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    BeginTextureMode(target);
    ClearBackground(BLACK);

    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            double a = (x - screenWidth / 1.5) * 4.0 / screenWidth;
            double b = (y - screenHeight / 2.0) * 4.0 / screenHeight;

            std::complex<double> c(a, b);
            std::complex<double> z(0, 0);
            int it = 0;

            while (std::abs(z) < 2.0 && it < 100) {
                z = z * z + c;
                it++;
            }

            float brightness = (float)it / 100;
            Color color = Color{ (unsigned char)(9 * (1 - brightness) * brightness * brightness * brightness * 255),
                                (unsigned char)(15 * (1 - brightness) * brightness * brightness * 255),
                                (unsigned char)(8.5 * (1 - brightness) * brightness * 255),      255 };

            DrawPixel(x, y, color);
        }
    }

    EndTextureMode();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(target.texture, 0, 0, WHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}