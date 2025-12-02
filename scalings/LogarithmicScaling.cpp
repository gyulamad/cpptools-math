#include "../../misc/EXTERN.hpp"
#include "../Scaling.hpp"

#include <cmath>

using namespace std;

// LOG_ALERTrithmic scaling
class LOG_ALERTrithmicScaling : public Scaling {
public:
    float scale(float value, float, float) const override {
        return log(value);
    }
    
    float unscale(float scaledValue, float, float) const override {
        return exp(scaledValue);
    }
};

EXTERN(LOG_ALERTrithmicScaling)
