# Advanced Mouse Benchmark Tool

high-precision mouse benchmarking application designed to measure and analyze mouse performance metrics in real-time. This tool provides accurate measurements of latency, polling rate, and movement precision with microsecond accuracy.

## Features

### Real-time Performance Metrics
- **Click Latency Testing**
  - Microsecond-precision measurement
  - Multiple click targets for accurate testing
  - Min/Max/Average latency tracking
  - Real-time graphical visualization

- **Polling Rate Analysis**
  - High-precision rate measurement
  - Real-time rate calculation
  - Historical data tracking
  - Graphical representation of polling consistency

- **Movement Precision Testing**
  - Velocity and acceleration tracking
  - Movement path visualization
  - Precision analysis
  - Speed measurements

### Advanced Features
- **Combined Testing Mode**
  - Simultaneous measurement of all metrics
  - Multi-graph display
  - Real-time updates
  - Comprehensive statistics

- **Performance Optimization**
  - Windows high-precision timers
  - Elevated process priority
  - VSync control
  - DPI scaling awareness


## System Requirements

### Minimum Requirements
- Windows 10/11
- CPU: Dual-core processor
- RAM: 4GB
- GPU: DirectX 11 compatible
- Display: 1080p resolution

### Recommended
- CPU: Quad-core processor
- RAM: 8GB
- GPU: Dedicated graphics card
- Display: 144Hz or higher refresh rate

## Building from Source

### Prerequisites
```bash
# Required packages
- CMake 3.15 or higher
- SFML 2.5 or higher
- C++20 compatible compiler (MSVC recommended)
```

### Build Steps
1. Clone the repository:
```bash
git clone https://github.com/wingsofether/mouse-benchmark.git
cd mouse-benchmark
```

2. Create build directory:
```bash
mkdir build
cd build
```

3. Generate build files:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build . --config Release
```

## Usage Guide

### Controls
- `1`: Latency Test Mode
- `2`: Polling Rate Test Mode
- `3`: Movement Test Mode
- `4`: Combined Test Mode (All Metrics)
- `V`: Toggle VSync
- `ESC`: Exit Application

### Test Modes

#### Latency Test
1. Click the red squares as they appear
2. Watch real-time latency measurements
3. Monitor min/max/average values
4. View the latency graph for consistency

#### Polling Rate Test
1. Move your mouse around the screen
2. Observe the real-time polling rate
3. Check for rate consistency
4. Monitor for rate drops or spikes

#### Movement Test
1. Move your mouse to create trails
2. Analyze movement precision
3. Check velocity measurements
4. Observe acceleration patterns

#### Combined Test
1. Access all metrics simultaneously
2. Monitor comprehensive statistics
3. Compare different metrics in real-time
4. View multiple performance graphs

## Technical Details

### Measurement Precision
- Latency: Microsecond accuracy using Windows High-Resolution Performance Counter
- Polling Rate: Real-time calculation with timestamp precision
- Movement: Sub-pixel tracking with velocity calculation

### Performance Optimizations
- Direct hardware timing access
- Minimal overhead measurement code
- Efficient data structures
- Memory-optimized storage

### Data Collection
- Circular buffer implementation
- Automatic outlier filtering
- Rolling average calculations
- Real-time statistical analysis

## Contributing

We welcome contributions! Please follow these steps:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

### Coding Standards
- Follow modern C++ practices
- Maintain const correctness
- Use RAII principles
- Document public interfaces

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- SFML team for the graphics library
- Windows Performance Counter API
