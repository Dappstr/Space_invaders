#include <iostream>
#include <raylib.h>
#include <string>
#include "game.hpp"
#include "obstacle.hpp"


namespace globals {
    constexpr size_t window_width{ 750 };
    constexpr size_t window_height{ 700 };
    constexpr size_t offset{ 50 };
}

std::string format_with_leading_zeros(const size_t score, const int width) {
    std::string score_text = std::to_string(score);
    size_t leading_zeros = width - score_text.length();
    return score_text = std::string(leading_zeros, '0') + score_text;
}

int main()
{
    InitWindow(globals::window_width + globals::offset, globals::window_height + 2 * globals::offset, "Space Invaders");
    InitAudioDevice();
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceship_image = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    constexpr Color grey{ 29, 29, 27, 255 };
    constexpr Color yellow = { 243, 216, 63, 255 };

    Game game;

    while (!WindowShouldClose()) {
        UpdateMusicStream(game.m_music);
        game.handle_input();
        game.update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({ 10, 10, 780, 780 }, 0.18f, 20, 2, yellow);
        DrawLineEx({ 25, 730 }, { 775, 730 }, 3, yellow);
        if (game.m_run) {
            DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, yellow);
        }
        else {
            DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, yellow);
        }

        float x = 50.0;
        for (size_t i = 0; i < game.m_lives; ++i) {
            DrawTextureV(spaceship_image, { x, 745}, RAYWHITE);
            x += 50;
        }
        DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, yellow);
        std::string score_text{ format_with_leading_zeros(game.m_score, 5) };
        DrawTextEx(font, score_text.c_str(), { 50, 40 }, 34, 2, yellow);

        DrawTextEx(font, "HIGH SCORE", { 570, 15 }, 34, 2, yellow);
        std::string high_score_text = format_with_leading_zeros(game.m_high_score, 5);
        DrawTextEx(font, high_score_text.c_str(), { 655, 40 }, 34, 2, yellow);

        game.draw();
        EndDrawing();
    }
    
    CloseWindow();
    CloseAudioDevice();

    return EXIT_SUCCESS;
}