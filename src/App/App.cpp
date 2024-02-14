#include "App.h"

App::App()
{
    InitWindow(this->m_width, this->m_height, this->m_title.c_str());
    SetTargetFPS(60);
}

App::~App()
{
    CloseWindow();
}

App &App::GetInstance()
{
    static App instance;
    return instance;
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        this->HandleInput();
        this->Update();
        this->Draw();
    }
}

void App::HandleInput()
{
    if (IsKeyPressed(KEY_UP))
    {
        this->m_resolution++;
        if (this->m_resolution > 100)
            this->m_resolution = 100;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        this->m_resolution--;
        if (this->m_resolution < 1)
            this->m_resolution = 1;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        this->m_reverse *= -1;
    }
}

void App::Update()
{
    this->m_time += GetFrameTime() * PI * 0.5f * this->m_reverse;
}

void App::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Fourier Series Visualisation", 10, 10, 20, WHITE);
    DrawText(TextFormat("Resolution: %d", this->m_resolution), 10, 40, 20, WHITE);
    float x = GetScreenWidth() / 4;
    float y = GetScreenHeight() / 2;

    DrawLine(x, y, this->m_width, this->m_height / 2, GRAY);

    for (int i = 0; i < this->m_resolution; i++)
    {
        float prevX = x;
        float prevY = y;

        float n = i * 2 + 1;
        float radius = 100 * (4 / (n * PI));
        x += radius * cos(n * this->m_time);
        y += radius * sin(n * this->m_time);

        Color color = ColorFromHSV((int)(360 * (i / (float)this->m_resolution)), 0.8f, 0.8f);

        DrawCircleLinesV(Vector2{prevX, prevY}, radius, color);
        DrawLine(prevX, prevY, x, y, WHITE);
    }

    this->m_wave.insert(this->m_wave.begin(), y);
    if (this->m_wave.size() > 500)
    {
        this->m_wave.pop_back();
    }

    DrawLine(x, y, 500, this->m_wave[0], WHITE);
    for (int i = 0; i < this->m_wave.size(); i++)
    {
        Color color = ColorFromHSV((int)(360 * (i / (float)this->m_wave.size())), 0.8f, 0.8f);
        DrawLineEx({(float)200 + i + 300, this->m_wave[i]}, {(float)200 + i + 300, this->m_wave[i + 1]}, 2, color);
    }

    EndDrawing();
}
