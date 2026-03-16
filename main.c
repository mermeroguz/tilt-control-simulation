#include "raylib.h"
#include <math.h>

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Aircraft Style HUD Simulation");
    SetTargetFPS(60);

    float pitch = 0.0f;
    float roll = 0.0f;

    float altitude = 1500.0f;

    float pitchVelocity = 0.0f;
    float gravity = -0.01f;
    float damping = 0.985f;

    float scale = 8.0f;

    while (!WindowShouldClose())
    {
        // --- Input ---
        float input = 0.05f;

        float normalizedRoll = fmodf(roll, 360.0f);
        if (normalizedRoll < 0) normalizedRoll += 360.0f;

        // inverted flight
        if (normalizedRoll > 90 && normalizedRoll < 270)
        {
        if (IsKeyDown(KEY_W)) pitchVelocity -= input;
        if (IsKeyDown(KEY_S)) pitchVelocity += input;
        }
        else
        {
        if (IsKeyDown(KEY_W)) pitchVelocity += input;
        if (IsKeyDown(KEY_S)) pitchVelocity -= input;
        }
        if (IsKeyDown(KEY_D)) roll -= 0.6f;
        if (IsKeyDown(KEY_A)) roll += 0.6f;

        // --- Physics ---
       pitchVelocity += gravity;
       pitch += pitchVelocity;

       pitchVelocity *= damping;
       altitude += pitch * 0.5f;

       if (pitch > 180) pitch -= 360;
       if (pitch < -180) pitch += 360;
       if (altitude < 0) altitude = 0;

        // Limits
       if (pitch > 180) pitch -= 360;
       if (pitch < -180) pitch += 360;

        if (roll > 360) roll -= 360;
        if (roll < -360) roll += 360;

        // --- Drawing ---
        BeginDrawing();
        ClearBackground(BLACK);

        int centerX = screenWidth / 2;
        int centerY = screenHeight / 2;

        DrawText("AIRCARFT STYLE HUD SIMULATION", 290, 20, 24, GREEN);
        DrawText(TextFormat("Pitch: %.1f", pitch), 20, 20, 20, GREEN);
        DrawText(TextFormat("Roll: %.0f deg", roll), 20, 80, 20, GREEN);
        DrawText(TextFormat("Roll: %.1f", roll), 20, 50, 20, GREEN);
        DrawText("W/S Pitch   A/D Roll   ESC Quit", 20, 565, 20, GREEN);

        // --- Artificial Horizon ---
        float angle = roll * DEG2RAD;
        float horizonY = centerY + pitch * scale;
        float lineLength = 1200.0f;

        Vector2 leftPoint = {
            centerX - cosf(angle) * lineLength,
            horizonY - sinf(angle) * lineLength
        };

        Vector2 rightPoint = {
            centerX + cosf(angle) * lineLength,
            horizonY + sinf(angle) * lineLength
        };

        DrawLineV(leftPoint, rightPoint, GREEN);

        // --- Pitch Ladder ---
        for (int ladderPitch = -180; ladderPitch <= 180; ladderPitch += 5)
        {
            float yOffset = (pitch - ladderPitch) * scale;

            Vector2 ladderLeft = { centerX - 40, centerY + yOffset };
            Vector2 ladderRight = { centerX + 40, centerY + yOffset };

            // Rotate ladder around screen center
            Vector2 relLeft = { ladderLeft.x - centerX, ladderLeft.y - centerY };
            Vector2 relRight = { ladderRight.x - centerX, ladderRight.y - centerY };

            Vector2 rotLeft = {
                relLeft.x * cosf(angle) - relLeft.y * sinf(angle),
                relLeft.x * sinf(angle) + relLeft.y * cosf(angle)
            };

            Vector2 rotRight = {
                relRight.x * cosf(angle) - relRight.y * sinf(angle),
                relRight.x * sinf(angle) + relRight.y * cosf(angle)
            };

            Vector2 finalLeft = { centerX + rotLeft.x, centerY + rotLeft.y };
            Vector2 finalRight = { centerX + rotRight.x, centerY + rotRight.y };

            if (finalLeft.y > 0 && finalLeft.y < screenHeight &&
                finalRight.y > 0 && finalRight.y < screenHeight)
            {
                DrawLineV(finalLeft, finalRight, GREEN);
                DrawText(TextFormat("%d", ladderPitch), (int)finalRight.x + 10, (int)finalRight.y - 10, 18, GREEN);
            }
        }

        // --- Flight Path Marker / Center Symbol ---
        DrawCircleLines(centerX, centerY, 10, GREEN);
        DrawLine(centerX - 20, centerY, centerX + 20, centerY, GREEN);
        DrawLine(centerX, centerY - 20, centerX, centerY + 20, GREEN);

        // Small aircraft-style wings
        DrawLine(centerX - 35, centerY + 15, centerX - 10, centerY + 15, GREEN);
        DrawLine(centerX + 10, centerY + 15, centerX + 35, centerY + 15, GREEN);

        // --- Side Scales (simple HUD info feel) ---
        DrawText(TextFormat("ALT %.0f", altitude), 60, 120, 20, GREEN);
       for (int i = -2; i <= 2; i++)
{
    int altMark = (int)(altitude / 100) * 100 + i * 100;

    int y = centerY + i * 60;

    DrawLine(90, y, 115, y, GREEN);
    DrawText(TextFormat("%d", altMark), 40, y - 10, 18, GREEN);
}

        DrawText("SPD (SOON)", 760, 120, 20, GREEN);
        for (int i = 0; i < 5; i++)
        {
            int y = 170 + i * 60;
            DrawLine(785, y, 810, y, GREEN);
            DrawText(TextFormat("%.1f", 1.0f - i * 0.2f), 820, y - 10, 18, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}