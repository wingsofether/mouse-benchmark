#include "MouseBenchmark.hpp"
#include <iostream>
#include <windows.h>

int main() {
    // Set high priority for more accurate measurements
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    
    // Disable Windows DPI scaling
    SetProcessDPIAware();
    
    try {
        MouseBenchmark benchmark;
        benchmark.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
