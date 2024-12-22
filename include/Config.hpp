#pragma once
#include <SFML/Graphics.hpp>

namespace Config {
    // Window settings
    constexpr int WINDOW_WIDTH = 1920;
    constexpr int WINDOW_HEIGHT = 1080;
    constexpr const char* WINDOW_TITLE = "Advanced Mouse Benchmark Tool";

    // Test settings
    constexpr size_t MAX_MEASUREMENTS = 1000;
    constexpr size_t DISPLAY_POINTS = 100;
    constexpr size_t NUM_CLICK_TARGETS = 5;
    constexpr float TARGET_SIZE = 50.f;

    // Colors
    const sf::Color LATENCY_COLOR = sf::Color::Red;
    const sf::Color POLLING_COLOR = sf::Color::Green;
    const sf::Color MOVEMENT_COLOR = sf::Color::Blue;
    const sf::Color TEXT_COLOR = sf::Color::White;
    const sf::Color BACKGROUND_COLOR = sf::Color(30, 30, 30);

    // Graph settings
    constexpr float GRAPH_WIDTH = WINDOW_WIDTH / 2.5f;
    constexpr float GRAPH_HEIGHT = WINDOW_HEIGHT / 3.0f;
    constexpr float GRAPH_MARGIN = 50.f;

    // Text settings
    constexpr unsigned int MENU_TEXT_SIZE = 24;
    constexpr unsigned int STATS_TEXT_SIZE = 20;
}
