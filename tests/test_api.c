#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/distance.h"
#include "../include/api.h"
#include "tests.h"
#include "../include/match.h"
#include "../include/macros.h"

static void test_fuzzc_calculate_similarity() {
    double sim = fuzzc_calculate_similarity("kitten", "sitting", fuzzc_levenshtein_distance);
    assert(sim > 0.5 && sim < 0.6);

    sim = fuzzc_calculate_similarity("flaw", "lawn", fuzzc_levenshtein_distance);
    assert(sim > 0.4 && sim < 0.6);

    sim = fuzzc_calculate_similarity("karolin", "kathrin", fuzzc_hamming_distance);
    assert(sim > 0.5 && sim < 0.6);

    sim = fuzzc_calculate_similarity("karolin", "kerstin", fuzzc_hamming_distance);
    assert(sim > 0.5 && sim < 0.6);

    sim = fuzzc_calculate_similarity("arolin", "kerstin", fuzzc_hamming_distance);
    assert(UNDEFINED_DISTANCE == sim);

    sim = fuzzc_calculate_similarity("ca", "abc", fuzzc_damerau_levenshtein_distance);
    assert(sim == 0.0);

    sim = fuzzc_calculate_similarity("abc", "ac", fuzzc_damerau_levenshtein_distance);
    assert(sim > 0.6 && sim < 0.8);
}

static void test_fuzzc_top_match() {
    char *arr[] = {"sitting", "flitting", "biting", "kitchen"};

    char *top = fuzzc_top_match("kitten", arr, 4, fuzzc_levenshtein_distance);
    assert(strcmp(top, "kitchen") == 0);

    top = fuzzc_top_match("lawn", arr, 4, fuzzc_levenshtein_distance);
    assert(strcmp(top, "flitting") == 0);

    char *arr2[] = {"kathrin", "kerstin", "kathrine", "kathrinn"};
    top = fuzzc_top_match("karolin", arr2, 4, fuzzc_hamming_distance);
    assert(strcmp(top, "kathrin") == 0);

    char *arr3[] = {"abc", "ac", "a", "ab"};
    top = fuzzc_top_match("bc", arr3, 4, fuzzc_damerau_levenshtein_distance);
    assert(strcmp(top, "abc") == 0);
}

static void test_fuzzc_matches_in_threshold() {
    char *words[] = {"sitting", "flitting", "biting", "kitchen", "kitten", "kittin"};
    matches *m = fuzzc_matches_in_threshold("kitten", words, 4, 0.5, fuzzc_levenshtein_distance);
    assert(m->count == 2);
    fuzzc_free_matches(m);

    m = fuzzc_matches_in_threshold("", words, 4, 0.3, fuzzc_levenshtein_distance);
    assert(m == NULL);

    m = fuzzc_matches_in_threshold("test", NULL, 4, 0.3, fuzzc_levenshtein_distance);
    assert(m == NULL);
}

static void test_fuzzc_longest_common_subsequence() {
    char *lcs = fuzzc_longest_common_subsequence("AGGTAB", "GXTXAYB");
    assert(strcmp(lcs, "GTAB") == 0);
    free(lcs);

    lcs = fuzzc_longest_common_subsequence("ABCBDAB", "BDCAB");
    assert(strcmp(lcs, "BDAB") == 0);
    free(lcs);

    lcs = fuzzc_longest_common_subsequence("AAAA", "AA");
    assert(strcmp(lcs, "AA") == 0);
    free(lcs);

    lcs = fuzzc_longest_common_subsequence("ABC", "DEF");
    assert(strcmp(lcs, "") == 0);
    free(lcs);
}

void test_fuzzc_api_functions() {
    test_fuzzc_calculate_similarity();
    test_fuzzc_top_match();
    test_fuzzc_matches_in_threshold();
    test_fuzzc_longest_common_subsequence();
}