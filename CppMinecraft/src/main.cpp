#pragma once
#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <memory>

#include "app/app.h"

#define sensitivity 0.004

#define DEBUG
#ifdef DEBUG
long long heap_allocation;
void* operator new(size_t size)
{
    heap_allocation += size;
    void* ptr = malloc(size);
    if (!ptr)
        throw std::bad_alloc();
    std::cout << "Allocated " << size << " bytes on the heap\n"
    << "Current usage of the heap: "
    << heap_allocation << " bytes\n";
    return ptr;
}
void operator delete(void* _Block, size_t size)
{
    heap_allocation -= size;
    std::cout << "Freeing " << size << " bytes on the heap\n"
        << "Current usage of the heap: "
        << heap_allocation << " bytes\n";
    free(_Block);
}
#endif 

int main(void)
{
    {
        Application::App app(852, 480, true);
        app.init();
        app.run();
    }
    std::cin.get();
    return 0;
}