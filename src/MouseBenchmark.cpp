#include "MouseBenchmark.hpp"
#include <sstream>
#include <iomanip>

MouseBenchmark::MouseBenchmark() : currentState(TestState::MENU), vsyncEnabled(false) {
    initializeWindow();
    initializeUI();
    generateClickTargets();
}

void MouseBenchmark::initializeWindow() {
    sf::VideoMode mode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    window.create(mode, Config::WINDOW_TITLE, sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(false);
    window.setMouseCursorVisible(true);
    window.setKeyRepeatEnabled(false);
}

void MouseBenchmark::initializeUI() {
    if (!font.loadFromFile("resources/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    menuText.setFont(font);
    menuText.setCharacterSize(Config::MENU_TEXT_SIZE);
    menuText.setFillColor(Config::TEXT_COLOR);
    menuText.setPosition(20, 20);

    statsText.setFont(font);
    statsText.setCharacterSize(Config::STATS_TEXT_SIZE);
    statsText.setFillColor(Config::TEXT_COLOR);
    statsText.setPosition(20, Config::WINDOW_HEIGHT - 150);
}

void MouseBenchmark::generateClickTargets() {
    clickTargets.clear();
    for (size_t i = 0; i < Config::NUM_CLICK_TARGETS; ++i) {
        sf::RectangleShape target(sf::Vector2f(Config::TARGET_SIZE, Config::TARGET_SIZE));
        target.setFillColor(Config::LATENCY_COLOR);
        target.setPosition(
            static_cast<float>(rand() % (Config::WINDOW_WIDTH - static_cast<int>(Config::TARGET_SIZE))),
            static_cast<float>(rand() % (Config::WINDOW_HEIGHT - static_cast<int>(Config::TARGET_SIZE)))
        );
        clickTargets.push_back(target);
    }
}

void MouseBenchmark::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void MouseBenchmark::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handleKeyPress(event.key);
                break;
            case sf::Event::MouseButtonPressed:
                handleMouseClick(event.mouseButton);
                break;
            case sf::Event::MouseMoved:
                handleMouseMove(event.mouseMove);
                break;
            default:
                break;
        }
    }
}

void MouseBenchmark::handleKeyPress(const sf::Event::KeyEvent& key) {
    switch (key.code) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        case sf::Keyboard::Num1:
            currentState = TestState::LATENCY_TEST;
            break;
        case sf::Keyboard::Num2:
            currentState = TestState::POLLING_RATE_TEST;
            break;
        case sf::Keyboard::Num3:
            currentState = TestState::MOVEMENT_TEST;
            break;
        case sf::Keyboard::Num4:
            currentState = TestState::COMBINED_TEST;
            break;
        case sf::Keyboard::V:
            vsyncEnabled = !vsyncEnabled;
            window.setVerticalSyncEnabled(vsyncEnabled);
            break;
        default:
            break;
    }
}

void MouseBenchmark::handleMouseClick(const sf::Event::MouseButtonEvent& mouse) {
    double timestamp = timer.getTime();
    double latency = timer.getDeltaTime() * 1000.0; // Convert to milliseconds
    metrics.addLatencyMeasurement(timestamp, latency);
}

void MouseBenchmark::handleMouseMove(const sf::Event::MouseMoveEvent& mouse) {
    double timestamp = timer.getTime();
    double interval = timer.getDeltaTime() * 1000.0; // Convert to milliseconds
    sf::Vector2f currentPos(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
    
    metrics.addPollingMeasurement(timestamp, interval, currentPos);
    
    const auto& movementData = metrics.getMovementData();
    if (!movementData.empty()) {
        float velocity = Utils::calculateDistance(movementData.back().position, currentPos) / interval;
        metrics.addMovementMeasurement(timestamp, currentPos, velocity);
    }
}

void MouseBenchmark::update() {
    metrics.update();
}

void MouseBenchmark::render() {
    window.clear(Config::BACKGROUND_COLOR);

    switch (currentState) {
        case TestState::MENU:
            drawMenu();
            break;
        case TestState::COMBINED_TEST:
            drawCombinedTest();
            break;
        case TestState::LATENCY_TEST:
            drawLatencyTest();
            break;
        case TestState::POLLING_RATE_TEST:
            drawPollingRateTest();
            break;
        case TestState::MOVEMENT_TEST:
            drawMovementTest();
            break;
    }

    window.display();
}

void MouseBenchmark::drawMenu() {
    std::stringstream ss;
    ss << "Advanced Mouse Benchmark Tool\n\n"
       << "1: Latency Test\n"
       << "2: Polling Rate Test\n"
       << "3: Movement Test\n"
       << "4: Combined Test (All Metrics)\n"
       << "V: Toggle VSync (Currently: " << (vsyncEnabled ? "ON" : "OFF") << ")\n"
       << "ESC: Exit\n\n"
       << "Current Performance:\n"
       << "FPS: " << static_cast<int>(1.0f / timer.getDeltaTime());
    
    menuText.setString(ss.str());
    window.draw(menuText);
}

void MouseBenchmark::drawMetricsGraph(const std::vector<float>& data,
                                    const sf::Vector2f& position,
                                    float max,
                                    const sf::Color& color) {
    Utils::drawGraph(window, position, 
                    sf::Vector2f(Config::GRAPH_WIDTH, Config::GRAPH_HEIGHT),
                    data, 0, max, color);
}

void MouseBenchmark::updateStatsText(const std::string& title) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2)
       << title << " (Press ESC to exit)\n\n"
       << "Latency:\n"
       << "  Current: " << metrics.getCurrentLatency() << " ms\n"
       << "  Average: " << metrics.getAverageLatency() << " ms\n"
       << "  Min: " << metrics.getMinLatency() << " ms\n"
       << "  Max: " << metrics.getMaxLatency() << " ms\n\n"
       << "Polling Rate:\n"
       << "  Current: " << metrics.getCurrentPollingRate() << " Hz\n"
       << "  Average: " << metrics.getAveragePollingRate() << " Hz\n\n"
       << "Movement:\n"
       << "  Current Speed: " << metrics.getCurrentMovementSpeed() << " px/ms\n"
       << "  Average Speed: " << metrics.getAverageMovementSpeed() << " px/ms\n"
       << "\nFPS: " << static_cast<int>(1.0f / timer.getDeltaTime());
    
    statsText.setString(ss.str());
}

void MouseBenchmark::drawCombinedTest() {
    // Convert measurement data to graph format
    std::vector<float> latencyData;
    for (const auto& data : metrics.getLatencyData()) {
        latencyData.push_back(static_cast<float>(data.latency));
    }
    
    std::vector<float> pollingData;
    for (const auto& data : metrics.getPollingData()) {
        pollingData.push_back(static_cast<float>(1000.0 / data.interval));
    }
    
    std::vector<float> speedData;
    for (const auto& data : metrics.getMovementData()) {
        speedData.push_back(data.velocity);
    }

    // Draw graphs
    drawMetricsGraph(latencyData, 
                    sf::Vector2f(Config::GRAPH_MARGIN, Config::GRAPH_MARGIN),
                    static_cast<float>(metrics.getMaxLatency()),
                    Config::LATENCY_COLOR);
    
    drawMetricsGraph(pollingData,
                    sf::Vector2f(Config::GRAPH_WIDTH + Config::GRAPH_MARGIN * 2, Config::GRAPH_MARGIN),
                    1000.0f,
                    Config::POLLING_COLOR);
    
    drawMetricsGraph(speedData,
                    sf::Vector2f(Config::GRAPH_MARGIN, Config::GRAPH_HEIGHT + Config::GRAPH_MARGIN * 2),
                    1000.0f,
                    Config::MOVEMENT_COLOR);

    updateStatsText("Combined Test");
    statsText.setPosition(Config::GRAPH_WIDTH + Config::GRAPH_MARGIN * 2, 
                         Config::GRAPH_HEIGHT + Config::GRAPH_MARGIN * 2);
    window.draw(statsText);
}

void MouseBenchmark::drawLatencyTest() {
    for (const auto& target : clickTargets) {
        window.draw(target);
    }
    
    std::vector<float> data;
    for (const auto& measurement : metrics.getLatencyData()) {
        data.push_back(static_cast<float>(measurement.latency));
    }
    
    drawMetricsGraph(data,
                    sf::Vector2f(Config::WINDOW_WIDTH - Config::GRAPH_WIDTH - 20, 50),
                    static_cast<float>(metrics.getMaxLatency()),
                    Config::LATENCY_COLOR);
    
    updateStatsText("Click Latency Test");
    window.draw(statsText);
}

void MouseBenchmark::drawPollingRateTest() {
    std::vector<float> data;
    for (const auto& measurement : metrics.getPollingData()) {
        data.push_back(static_cast<float>(1000.0 / measurement.interval));
    }
    
    drawMetricsGraph(data,
                    sf::Vector2f(Config::WINDOW_WIDTH - Config::GRAPH_WIDTH - 20, 50),
                    1000.0f,
                    Config::POLLING_COLOR);
    
    updateStatsText("Polling Rate Test");
    window.draw(statsText);
}

void MouseBenchmark::drawMovementTest() {
    const auto& movementData = metrics.getMovementData();
    if (movementData.size() > 1) {
        std::vector<sf::Vertex> trail(movementData.size());
        for (size_t i = 0; i < movementData.size(); ++i) {
            float alpha = static_cast<float>(i) / movementData.size();
            trail[i] = sf::Vertex(
                movementData[i].position,
                sf::Color(Config::MOVEMENT_COLOR.r,
                         Config::MOVEMENT_COLOR.g,
                         Config::MOVEMENT_COLOR.b,
                         static_cast<sf::Uint8>(255 * alpha))
            );
        }
        window.draw(trail.data(), trail.size(), sf::LineStrip);
    }
    
    updateStatsText("Movement Test");
    window.draw(statsText);
}
