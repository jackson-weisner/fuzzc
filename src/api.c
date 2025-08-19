//
// Created by jacks on 8/9/2025.
//
#include <string.h>

#include "../include/macros.h"

// Function to calculate similarity based on a distance function
// Returns a value between 0.0 (completely different) and 1.0 (identical)
// Returns -1.0 if the distance function is not defined for the input strings
double calculate_similarity(const char *s1, const char *s2, int (*distance_func)(const char *, const char *)) {
    const int distance = distance_func(s1, s2);
    if (distance == UNDEFINED_DISTANCE) return distance;

    const int max_len = (strlen(s1) > strlen(s2)) ? (int)strlen(s1) : (int)strlen(s2);
    return 1.0 - (double)distance / max_len;
}
