#include "../../misc/EXTERN.hpp"
#include "../Scaling.hpp"

// Linear scaling (no transformation)
class LinearScaling : public Scaling {
public:
    float scale(float value, float, float) const override {
        return value;
    }
    
    float unscale(float scaledValue, float, float) const override {
        return scaledValue;
    }
};

EXTERN(LinearScaling, (), ())
