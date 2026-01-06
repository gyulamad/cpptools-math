#include <string> 
#include "../Calculation.hpp"
#include "../Calc.hpp"

class WeightedAverageCalculation: public Calculation {
public:
    using Calculation::Calculation;
    virtual ~WeightedAverageCalculation() {}
    
    void onLoad() override {
        // TODO ...
    }

    void onReload() override {
        // this->params = inifile;
    }

    void start() override {
        count = 0;
        negative = false;
        values.clear();
    }

    void process(const string& key, float value) override {
        float weighted = value * get<float>(key, "weights");
        if (weighted < 0) negative = true;
        values.push_back(weighted);
        count++;
    }

    float result() override {
        float sum = Calc<float>::sum(values, true);
        float result = sum / count;
        if (negative && result > 0) result = -result;
        return result;
    }

protected:
    // IniFile params;
    bool negative = false;
    int count = 0;
    vector<float> values;
};

EXTERN_CALCULATION(WeightedAverageCalculation)
