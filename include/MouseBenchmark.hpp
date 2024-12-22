#pragma once

#include "Config.hpp"
#include "Utils.hpp"
#include "Metrics.hpp"
#include <memory>

class MouseBenchmark {
public:
    MouseBenchmark();
    void run();

private:
    enum class TestState {
        MENU,
        COMBINED_TEST,
        LATENCY_TEST,
        POLLING_RATE_TEST,
        MOVEMENT_TEST
    };

    // Core components
    sf::RenderWindow window;
    TestState currentState;
    bool vsyncEnabled;
    
    // Utilities
    Utils::HighResolutionTimer timer;
    MetricsCollector metrics;
    
    // UI Elements
    sf::Font font;
    sf::Text menuText;
    sf::Text statsText;
    std::vector<sf::RectangleShape> clickTargets;

    // Initialization
    void initializeWindow();
    void initializeUI();
    void generateClickTargets();

    // Main loop functions
    void handleEvents();
    void update();
    void render();

    // Event handlers
    void handleKeyPress(const sf::Event::KeyEvent& key);
    void handleMouseClick(const sf::Event::MouseButtonEvent& mouse);
    void handleMouseMove(const sf::Event::MouseMoveEvent& mouse);

    // Rendering functions
    void drawMenu();
    void drawCombinedTest();
    void drawLatencyTest();
    void drawPollingRateTest();
    void drawMovementTest();

    // UI helper functions
    void updateStatsText(const std::string& title);
    void drawMetricsGraph(const std::vector<float>& data, 
                         const sf::Vector2f& position,
                         float max,
                         const sf::Color& color);
};
