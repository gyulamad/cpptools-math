#pragma once

// Abstract base class for scaling strategies
class Scaling {
public:
    virtual ~Scaling() = default;
    virtual float scale(float value, float lowerBound, float upperBound) const = 0;
    virtual float unscale(float scaledValue, float lowerBound, float upperBound) const = 0;
};
