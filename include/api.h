//
// Created by jacks on 8/9/2025.
//

#ifndef API_H
#define API_H

#include "../include/match.h"

double fuzzc_calculate_similarity(const char *s1, const char *s2, int (*distance_func)(const char *, const char *));
char *fuzzc_top_match(const char *s1, char **s2, int size, int (*distance_func)(const char *, const char *));
matches *fuzzc_matches_in_threshold(const char *s1, char **s2, int size, double threshold, int (*distance_func)(const char *, const char *));

#endif //API_H
