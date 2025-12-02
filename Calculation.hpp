#pragma once

#include "../misc/Initializable.hpp"

template<typename T>
class Calculation: public Initializable {
public:
    Calculation(): Initializable() {}
    virtual ~Calculation() {}
    virtual void start() = 0;
    virtual void process(const string& key, T value) = 0;
    virtual T result() = 0;
};
