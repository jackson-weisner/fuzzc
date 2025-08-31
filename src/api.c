//
// Created by jacks on 8/9/2025.
//
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/api.h"

// Function to calculate similarity based on a distance function
// Returns a value between 0.0 (completely different) and 1.0 (identical)
// Returns -1.0 if the distance function is not defined for the input strings
double fuzzc_calculate_similarity(const char *s1, const char *s2, int (*distance_func)(const char *, const char *)) {
    const int distance = distance_func(s1, s2);
    if (distance == UNDEFINED_DISTANCE) return UNDEFINED_DISTANCE;

    const int max_len = (strlen(s1) > strlen(s2)) ? (int)strlen(s1) : (int)strlen(s2);
    return 1.0 - (double)distance / max_len;
}

// Function to find the most similar string from an array based on a distance function.
char *fuzzc_top_match(const char *s1, char **s2, const int size, int (*distance_func)(const char *, const char *)) {
    double max_similarity = 0;
    char *most_similar = NULL;

    for (int i = 0; i < size; i++) {
        const double similarity = fuzzc_calculate_similarity(s1, s2[i], distance_func);
        if (similarity > max_similarity) {
            max_similarity = similarity;
            most_similar = s2[i];
        }
    }

    return most_similar;
}

// Function to find all strings from an array that exceed a similarity threshold based on a distance function.
matches *fuzzc_matches_in_threshold(const char *s1, char **s2, const int size, const double threshold, int (*distance_func)(const char *, const char *)) {
    char **m = malloc(size * sizeof(char *));
    if (m == NULL) return NULL;

    int count = 0;
    for (int i = 0; i < size; i++) {
        const double similarity = fuzzc_calculate_similarity(s1, s2[i], distance_func);
        if (similarity > threshold) {
            m[count] = s2[i];
            count++;
        }
    }

    if (count == 0) goto cleanup;

    char **temp = realloc(m, count * sizeof(char *));
    if (temp == NULL) goto cleanup;

    matches *result = malloc(count * sizeof(matches));
    if (result == NULL) goto cleanup;

    result->matches = temp;
    result->count = count;

    return result;
cleanup:
    free(m);
    return NULL;
}