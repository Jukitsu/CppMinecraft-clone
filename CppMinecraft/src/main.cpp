#pragma once
#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <memory>

#include "app/app.h"


inline void setCtrReport()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
}


#ifdef DEBUG
long long heap_allocation;
void* operator new(size_t size)
{
    heap_allocation += size;
    void* ptr = malloc(size);
    if (!ptr)
        throw std::bad_alloc();
    std::cout << "Current usage of the heap: "
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
    setCtrReport();
    {
        /* Pretty straightforward stuff */
        Application::App app(852, 480, false); 
        app.init(); 
        app.run(); 
    }
    _CrtDumpMemoryLeaks(); // Memory leak detection
    std::cin.get();
    return 0;
}