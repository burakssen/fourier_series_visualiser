#pragma once

#include <string>
#include <vector>

#include <raylib.h>

class App
{
    App();

public:
    ~App();
    static App &GetInstance();

    void Run();

private:
    void HandleInput();
    void Update();
    void Draw();

private:
    float m_width = 1024;
    float m_height = 768;

    std::string m_title = "Fourier Series Visualisation";

    float m_time = 0.0f;
    std::vector<float> m_wave;

    int m_resolution = 3;

    int m_reverse = 1;
};