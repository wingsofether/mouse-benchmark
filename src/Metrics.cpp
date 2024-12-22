#include "Metrics.hpp"
#include "Config.hpp"
#include <numeric>
#include <algorithm>

void MetricsCollector::addLatencyMeasurement(double timestamp, double latency) {
    if (latency <= 0 || latency >= 1000) return; // Filter unrealistic values
    
    LatencyData data{timestamp, latency};
    latencyMeasurements.push_back(data);
    
    if (latencyMeasurements.size() > Config::MAX_MEASUREMENTS) {
        latencyMeasurements.pop_front();
    }
    
    currentLatency = latency;
    minLatency = std::min(minLatency, latency);
    maxLatency = std::max(maxLatency, latency);
}

void MetricsCollector::addPollingMeasurement(double timestamp, double interval, const sf::Vector2f& position) {
    if (interval <= 0) return;
    
    PollingData data{timestamp, interval, position};
    pollingMeasurements.push_back(data);
    
    if (pollingMeasurements.size() > Config::MAX_MEASUREMENTS) {
        pollingMeasurements.pop_front();
    }
    
    currentPollingRate = 1000.0 / interval;
}

void MetricsCollector::addMovementMeasurement(double timestamp, const sf::Vector2f& position, float velocity) {
    MovementData data{timestamp, position, velocity};
    movementMeasurements.push_back(data);
    
    if (movementMeasurements.size() > Config::MAX_MEASUREMENTS) {
        movementMeasurements.pop_front();
    }
    
    currentMovementSpeed = velocity;
}

void MetricsCollector::clear() {
    latencyMeasurements.clear();
    pollingMeasurements.clear();
    movementMeasurements.clear();
    
    currentLatency = averageLatency = 0.0;
    minLatency = 999999.0;
    maxLatency = 0.0;
    currentPollingRate = averagePollingRate = 0.0;
    currentMovementSpeed = averageMovementSpeed = 0.0;
}

void MetricsCollector::update() {
    updateLatencyStats();
    updatePollingStats();
    updateMovementStats();
}

void MetricsCollector::updateLatencyStats() {
    if (latencyMeasurements.empty()) return;
    
    double sum = std::accumulate(latencyMeasurements.begin(), latencyMeasurements.end(), 0.0,
        [](double acc, const LatencyData& data) { return acc + data.latency; });
    averageLatency = sum / latencyMeasurements.size();
}

void MetricsCollector::updatePollingStats() {
    if (pollingMeasurements.empty()) return;
    
    double sum = 0.0;
    size_t validCount = 0;
    
    for (const auto& data : pollingMeasurements) {
        if (data.interval > 0) {
            sum += 1000.0 / data.interval;
            validCount++;
        }
    }
    
    averagePollingRate = validCount > 0 ? sum / validCount : 0.0;
}

void MetricsCollector::updateMovementStats() {
    if (movementMeasurements.empty()) return;
    
    float sum = std::accumulate(movementMeasurements.begin(), movementMeasurements.end(), 0.0f,
        [](float acc, const MovementData& data) { return acc + data.velocity; });
    averageMovementSpeed = sum / movementMeasurements.size();
}
