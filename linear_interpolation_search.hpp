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

#ifdef TEST

// Helper struct for testing
struct test_linear_interpolation_search_TestData {
    int key;
    int value;
};

TEST(test_linear_interpolation_search_empty_vector) {
    bool threw = false;
    vector<test_linear_interpolation_search_TestData> data;
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    try {
        linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 1, getter);
    } catch (exception &e) {
        threw = true;
    }
    assert(threw && "Empty vector should throw");
}

TEST(test_linear_interpolation_search_single_element_found) {
    vector<test_linear_interpolation_search_TestData> data = {{5, 10}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    size_t result = linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 5, getter);
    assert(result == 0 && "Single element match should return index 0");
}

TEST(test_linear_interpolation_search_single_element_not_found) {
    bool threw = false;
    vector<test_linear_interpolation_search_TestData> data = {{5, 10}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    try {
        linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 6, getter, false);
    } catch (...) {
        threw = true;
    }
    assert(threw && "Single element non-match should throw");
}

TEST(test_linear_interpolation_search_multiple_elements_found_middle) {
    vector<test_linear_interpolation_search_TestData> data = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    size_t result = linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 3, getter) == 2;
    assert(result && "Target in middle should return correct index");
}

TEST(test_linear_interpolation_search_multiple_elements_found_first) {
    vector<test_linear_interpolation_search_TestData> data = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    size_t result = linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 1, getter);
    assert(result == 0 && "Target at start should return index 0");
}

TEST(test_linear_interpolation_search_multiple_elements_found_last) {
    vector<test_linear_interpolation_search_TestData> data = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    size_t result = linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 5, getter);
    assert(result == 4 && "Target at end should return index 4");
}

TEST(test_linear_interpolation_search_target_not_found_below_range) {
    bool threw = false;
    vector<test_linear_interpolation_search_TestData> data = {{10, 100}, {20, 200}, {30, 300}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    try {
        linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 5, getter);
    } catch (...) {
        threw = true;
    }
    assert(threw && "Target below range should throw");
}

TEST(test_linear_interpolation_search_target_not_found_above_range) {
    bool threw = false;
    vector<test_linear_interpolation_search_TestData> data = {{10, 100}, {20, 200}, {30, 300}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    try {
        linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 40, getter);
    } catch (...) {
        threw = true;
    }
    assert(threw && "Target above range should throw");
}

TEST(test_linear_interpolation_search_target_not_found_in_gap) {
    bool threw = false;
    vector<test_linear_interpolation_search_TestData> data = {{10, 100}, {20, 200}, {30, 300}};
    auto getter = [](const test_linear_interpolation_search_TestData& d) { return d.key; };
    try {
        linear_interpolation_search<test_linear_interpolation_search_TestData, int>(data, 15, getter);
    } catch (...) {
        threw = true;
    }
    assert(threw && "Target in gap should throw");
}

#endif