//
// Created by jacks on 8/9/2025.
//
#include "../include/distance.h"
#include "../include/macros.h"
#include <stdio.h>
#include <string.h>

int levenstein_distance(const char *s1, const char *s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = (int)j; // Deletion
            } else if (j == 0) {
                dp[i][j] = (int)i; // Insertion
            } else {
                const int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
                dp[i][j] = MIN(MIN(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);
            }
        }
    }
    return dp[len1][len2];
}

int damerau_levenshtein_distance(const char *s1, const char *s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = (int)j; // Deletion
            } else if (j == 0) {
                dp[i][j] = (int)i; // Insertion
            } else {
                const int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
                dp[i][j] = MIN(MIN(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);
                if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                    dp[i][j] = MIN(dp[i][j], dp[i - 2][j - 2] + cost);
                }
            }
        }
    }
    return dp[len1][len2];
}

int hamming_distance(const char *s1, const char *s2) {
    if (strlen(s1) != strlen(s2)) {
        return UNDEFINED_DISTANCE; // Hamming distance is only defined for strings of equal length
    }
    int distance = 0;
    for (size_t i = 0; i < strlen(s1); i++) {
        if (s1[i] != s2[i]) {
            distance++;
        }
    }
    return distance;
}
