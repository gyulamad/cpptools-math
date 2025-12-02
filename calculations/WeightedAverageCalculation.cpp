#include <string>                 // for operator==, string
#include <vector>                 // for vector
#include "../Calc.hpp"            // for Calc
#include "../Calculation.hpp"     // for Calculation
#include "../../misc/EXTERN.hpp"          // for EXTERN

class WeightedAverageCalculation: public Calculation<float> {
public:
    WeightedAverageCalculation() {}
    virtual ~WeightedAverageCalculation() {}
    
    void onLoad() override {
        // TODO ...
    }

    void onReload() override {
        this->params = inifile;
    }

    void start() override {
        count = 0;
        negative = false;
        values.clear();
    }

    void process(const string& key, float value) override {
        float weighted = value * params.get<float>(key);
        if (weighted < 0) negative = true;
        values.push_back(weighted);
        count++;
    }

    float result() override {
        float sum = Calc<float>::sum(values);
        float result = sum / count;
        if (negative && result > 0) result = -result;
        return result;
    }

protected:
    IniFile params;
    bool negative = false;
    int count = 0;
    vector<float> values;
};

EXTERN(WeightedAverageCalculation)
