#pragma once

using namespace std;

template<typename T>
class Calc {
public:

    // Calculate sum
    static T sum(const vector<T>& values) {
        T sum = 0;
        for (const T& v : values) sum += v;
        if (isnan(sum))
            throw ERROR("Invalid: Calculate sum");
        return sum;
    }
    
    // Calculate mean
    static T mean(const vector<T>& values) {
        if (values.empty())
            throw ERROR("Not values to calculate mean"); 
        T mean = sum(values) / values.size();
        if (isnan(mean))
            throw ERROR("Invalid: Calculate mean");       
        return mean;
    }

    // Calculate sum of Squared difference
    static T sqrdsum(const vector<T>& values, T mean = NAN, T exponent = 2) {
        if (exponent <= 0)
            throw ERROR("Invalid exponent (power) given: " + to_string(exponent));
        T sum = 0;
        T avg = isnan(mean) ? Calc::mean(values) : mean; // TODO: bouble up
        for (const T& v : values) sum += pow(v - avg, exponent);
        if (isnan(sum))
            throw ERROR("Invalid: Calculate sum of Squared difference");
        return sum;
    }
    
    // Calculate variance (correction_factor: exponent (power) = 2 by default - sample variance, 1 - mean absolute deviation, 0.5 - root mean square (RMS) etc...)
    static T variance(const vector<T>& values, T mean = NAN, T correction_factor = 2) {      
        if (values.size() < 2)
            throw ERROR("Not enough values to calculate variance");        
        T variance = sqrdsum(values, mean, correction_factor) / (values.size() - 1);
        if (isnan(variance))
            throw ERROR("Invalid: Calculate variance");
        return variance;
    }
    
    // Calculate standard deviation
    static T stdev(const vector<T>& values, T mean = NAN, T correction_factor = 2) {
        T stdev = sqrt(abs(variance(values, mean, correction_factor)));
        if (isnan(stdev))
            throw ERROR("Invalid: Calculate standard deviation");
        return stdev;
    }
    
    // Calculate Sharpe ratio
    static T sharpe(const vector<T>& returns, T risk_free_rate, T correction_factor = 2) {
        size_t returns_size = returns.size();
        if (returns_size < 1)
            throw ERROR("No returns in context");

        // Calculate excess returns
        vector<T> excess_returns;
        for (T ret : returns) {
            excess_returns.push_back(ret - risk_free_rate);
        }

        // Calculate mean of returns
        T mean = Calc::mean(excess_returns);

        // Calculate standard deviation of returns
        T stdev = Calc::stdev(excess_returns, mean, correction_factor);
        if (abs(stdev) < 1e-9)
            throw ERROR("Invalid: zero standard deviation"); 

        // Calculate Sharpe ratio
        T sharpe = mean / stdev;
        if (isnan(sharpe))
            throw ERROR("Invalid: Calculate sharpe"); 
        return sharpe;
    }

    static T rescale_linear(T y, T x, T x_new)
    {
        if (x == 0)
            throw ERROR("Invalid: Linear rescaling can not be done from zero");
        T y_new = y * (x_new / x); // calculate y_new
        if (isnan(y_new))
            throw ERROR("Invalid: Calculate rescale_linear"); 
        return y_new;
    }

    static T rescale_compound(T y, T x, T x_new)
    {
        if (x == 0)
            throw ERROR("Invalid: Compound rescaling can not be done from zero");
        T y_new = pow(1 + y * x, 1 / x_new) - 1; // calculate y_new
        if (isnan(y_new))
            throw ERROR("Invalid: Calculate rescale_compound"); 
        return y_new;
    }

    // Calculate mean absolute deviation between actual and ideal series
    static T mean_absolute_deviation(const vector<T>& actual, const vector<T>& ideal) {
        if (actual.empty() || ideal.empty())
            throw ERROR("Empty series provided for mean absolute deviation calculation");
        
        if (actual.size() != ideal.size())
            throw ERROR("Series size mismatch for mean absolute deviation calculation");
        
        T sum_deviations = static_cast<T>(0);
        for (size_t i = 0; i < actual.size(); ++i) {
            sum_deviations += abs(actual[i] - ideal[i]);
        }
        
        T mad = sum_deviations / actual.size();
        if (isnan(mad))
            throw ERROR("Invalid: Calculate mean absolute deviation");
        return mad;
    }

    static T sigmoid(T x) {
        return 1.0 / (1.0 + exp(-x));
    }

    static T inc_pc(T initial, T current) {
        if (initial == 0)
            return (current == 0) ? 0.0 : (current > 0 ? INFINITY : -INFINITY);
        return (current - initial) / initial;
    }
    
    static T dec_pc(T initial, T current) {
        if (initial == 0)
            return (current == 0) ? 0.0 : (current > 0 ? INFINITY : -INFINITY);
        return (initial - current) / initial;
    }

};
