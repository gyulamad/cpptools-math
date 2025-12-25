#pragma once

#include "../misc/Initializable.hpp"

template<typename T = float>
class CalculationT: public Initializable {
public:
    CalculationT(): Initializable() {}
    virtual ~CalculationT() {}
    virtual void start() = 0;
    virtual void process(const string& key, T value) = 0;
    virtual T result() = 0;
};

class Calculation: public CalculationT<float> {
public:
    using CalculationT::CalculationT;
    virtual ~Calculation() {}
};