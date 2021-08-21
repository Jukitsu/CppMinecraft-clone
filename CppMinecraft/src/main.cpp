#pragma once
#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "app/app.h"

#define sensitivity 0.004


int main(void)
{
    Application::App app(852, 480, true);
    app.init();
    app.run();
    return 0;
}