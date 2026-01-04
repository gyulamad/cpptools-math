#pragma once

#include "../misc/Initializable.hpp"

#define EXTERN_CALCULATION(clazz) EXTERN_INITIALIZABLE(clazz)

template<typename T = float>
class CalculationT: public Initializable {
public:
    // CalculationT(
    //     bool createIfNotExists,
    //     bool throwsIfNotExists,
    //     bool warnsIfNotExists,
    //     bool verbose
    // ):
    //     Initializable(
    //         createIfNotExists,
    //         throwsIfNotExists,
    //         warnsIfNotExists,
    //         verbose
    //     )
    // {}

    CalculationT(
        const string& inifname, 
        bool load, // = false, 
        bool createIfNotExists,
        bool throwsIfNotExists,
        bool warnsIfNotExists,
        bool verbose
    ):
        Initializable(
            inifname,
            load,
            createIfNotExists,
            throwsIfNotExists,
            warnsIfNotExists,
            verbose
        )
    {}

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