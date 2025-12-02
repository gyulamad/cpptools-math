#include "../../misc/EXTERN.hpp"
#include "../Scaling.hpp"

// Normalized scaling to [0,1]
class NormalizedScaling : public Scaling {
public:
    float scale(float value, float lowerBound, float upperBound) const override {
        if (upperBound == lowerBound) return float(0);
        return (value - lowerBound) / (upperBound - lowerBound);
    }
    
    float unscale(float scaledValue, float lowerBound, float upperBound) const override {
        return lowerBound + scaledValue * (upperBound - lowerBound);
    }
};

EXTERN(NormalizedScaling)
