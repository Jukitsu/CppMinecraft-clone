#pragma once
#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "app/app.h"

#define sensitivity 0.004

#define DEBUG
#ifdef DEBUG
long long heap_allocation;
void* operator new(size_t size)
{
    heap_allocation += size;
    std::cout << "Current usage of the heap: "
        << heap_allocation << " bytes\n";
    return malloc(size);
}
void operator delete(void* _Block, size_t size)
{
    heap_allocation -= size;
    std::cout << "Current usage of the heap: "
        << heap_allocation << " bytes\n";
    free(_Block);
}
#endif 

int main(void)
{
    Application::App app(852, 480, true);
    app.init();
    app.run();
    return 0;
}