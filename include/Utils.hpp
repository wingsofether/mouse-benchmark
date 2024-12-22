#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>

namespace Utils {
    // Time measurement utilities
    class HighResolutionTimer {
    public:
        HighResolutionTimer() {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&lastTime);
        }

        double getDeltaTime() {
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);
            double delta = static_cast<double>(currentTime.QuadPart - lastTime.QuadPart) / 
                          static_cast<double>(frequency.QuadPart);
            lastTime = currentTime;
            return delta;
        }

        double getTime() {
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);
            return static_cast<double>(currentTime.QuadPart) / static_cast<double>(frequency.QuadPart);
        }

    private:
        LARGE_INTEGER frequency;
        LARGE_INTEGER lastTime;
    };

    // Graphics utilities
    void drawGraph(sf::RenderWindow& window, 
                  const sf::Vector2f& position, 
                  const sf::Vector2f& size,
                  const std::vector<float>& data, 
                  float min, 
                  float max, 
                  const sf::Color& color) {
        if (data.empty()) return;

        std::vector<sf::Vertex> vertices(data.size() * 2);
        float xStep = size.x / (data.size() - 1);
        
        for (size_t i = 0; i < data.size(); ++i) {
            float x = position.x + i * xStep;
            float normalizedY = (data[i] - min) / (max - min);
            float y = position.y + size.y - (normalizedY * size.y);
            
            vertices[i * 2] = sf::Vertex(sf::Vector2f(x, y), color);
            vertices[i * 2 + 1] = sf::Vertex(sf::Vector2f(x, position.y + size.y), color);
        }
        
        window.draw(vertices.data(), vertices.size(), sf::Lines);
    }

    // Math utilities
    template<typename T>
    T clamp(T value, T min, T max) {
        return std::min(std::max(value, min), max);
    }

    float calculateDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
        return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
    }
}
