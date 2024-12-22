#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

struct LatencyData {
    double timestamp;
    double latency;
};

struct PollingData {
    double timestamp;
    double interval;
    sf::Vector2f position;
};

struct MovementData {
    double timestamp;
    sf::Vector2f position;
    float velocity;
};

class MetricsCollector {
public:
    void addLatencyMeasurement(double timestamp, double latency);
    void addPollingMeasurement(double timestamp, double interval, const sf::Vector2f& position);
    void addMovementMeasurement(double timestamp, const sf::Vector2f& position, float velocity);
    
    void clear();
    void update();

    // Getters
    double getCurrentLatency() const { return currentLatency; }
    double getAverageLatency() const { return averageLatency; }
    double getMinLatency() const { return minLatency; }
    double getMaxLatency() const { return maxLatency; }
    
    double getCurrentPollingRate() const { return currentPollingRate; }
    double getAveragePollingRate() const { return averagePollingRate; }
    
    float getCurrentMovementSpeed() const { return currentMovementSpeed; }
    float getAverageMovementSpeed() const { return averageMovementSpeed; }

    const std::deque<LatencyData>& getLatencyData() const { return latencyMeasurements; }
    const std::deque<PollingData>& getPollingData() const { return pollingMeasurements; }
    const std::deque<MovementData>& getMovementData() const { return movementMeasurements; }

private:
    std::deque<LatencyData> latencyMeasurements;
    std::deque<PollingData> pollingMeasurements;
    std::deque<MovementData> movementMeasurements;

    double currentLatency{0.0};
    double averageLatency{0.0};
    double minLatency{999999.0};
    double maxLatency{0.0};
    
    double currentPollingRate{0.0};
    double averagePollingRate{0.0};
    
    float currentMovementSpeed{0.0};
    float averageMovementSpeed{0.0};

    void updateLatencyStats();
    void updatePollingStats();
    void updateMovementStats();
};
