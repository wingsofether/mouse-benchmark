cmake_minimum_required(VERSION 3.15)
project(MouseBenchmark VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(MouseBenchmark 
    src/main.cpp
    src/MouseBenchmark.cpp
    src/LatencyTester.cpp
    src/PollingRateTester.cpp
    src/MovementAnalyzer.cpp
)

# Include directories
target_include_directories(MouseBenchmark PRIVATE include)

# Link libraries
target_link_libraries(MouseBenchmark PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
)
