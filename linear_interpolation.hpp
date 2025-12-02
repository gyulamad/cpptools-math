#pragma once

// Helper function for linear interpolation to estimate position
template<typename T>
int linear_interpolation(T target, T low, T high, int l, int h) {
    if (l == h)
        return l;
    // Interpolation formula: pos = low + (high - low) * (target - low) / (high - low)
    double ratio = (double)(target - low) / (high - low);
    int pos = l + (int)((h - l) * ratio);
    
    // Ensure pos is within bounds, fallback to binary search midpoint if out of bounds
    if (pos < l || pos > h)
        pos = l + (h - l) / 2;
    return pos;
}
