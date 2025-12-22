#pragma once

#include <functional>
#include "../misc/ERROR.hpp"
#include "linear_interpolation.hpp"

using namespace std;

// Template function for linear interpolation search
template<typename T, typename TKey>
size_t linear_interpolation_search(
    const vector<T>& data, TKey target, function<TKey(const T&)> getter, 
    bool getClosestIfNotFound = false
) {
    if (data.empty())
        throw ERROR("Attempt to linear interpolation search on an empty vector");

    size_t l = 0;
    size_t h = data.size() - 1;
    size_t pos = 0;

    if (getClosestIfNotFound) {
        target = max(target, getter(data[l]));
        target = min(target, getter(data[h]));
    }

    while (l <= h && target >= getter(data[l]) && target <= getter(data[h])) {
        // Avoid division by zero
        if (l == h) {
            if (getter(data[l]) == target || getClosestIfNotFound) return l;
            throw ERROR("Linear interpolation search target is not found.");
        }

        // Use interpolation helper to estimate position
        pos = linear_interpolation(target, getter(data[l]), getter(data[h]), l, h);

        // Compare the key at the estimated position
        TKey actual = getter(data[pos]);
        if (actual == target) return pos; // Found the target

        // Adjust the search range
        if (actual < target)
            l = pos + 1;
        else
            h = pos - 1;
    }

    if (getClosestIfNotFound) return pos;
    throw ERROR("Linear interpolation search target is not found."); // Target not found
}
