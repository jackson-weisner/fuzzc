#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/api.h"

#include <stdio.h>

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

    for (size_t i = 0; i < size; i++) {
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
    if (size <= 0 || threshold < 0.0 || threshold > 1.0 || s2 == NULL) return NULL;

    char **m = malloc(size * sizeof(char *));
    if (m == NULL) return NULL;

    int count = 0;
    for (size_t i = 0; i < size; i++) {
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

    result->data = temp;
    result->count = count;

    return result;
cleanup:
    free(m);
    return NULL;
}


// Function to find the longest common subsequence between two strings.
char *fuzzc_longest_common_subsequence(const char *s1, const char *s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);

    int dp[len1+1][len2+1];
    if (memset(dp, 0, sizeof(dp)) == NULL) return NULL;

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }

    int index = dp[len1][len2];
    char *result = malloc((index + 1) * sizeof(char));
    if (result == NULL) return NULL;
    result[index] = '\0';

    size_t i = len1, j = len2;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            result[--index] = s1[i-1];
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    return result;
}