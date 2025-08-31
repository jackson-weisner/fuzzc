//
// Created by jacks on 8/31/2025.
//


#include <assert.h>

#include "../include/distance.h"
#include "../include/macros.h"
#include "tests.h"

static void test_fuzzc_levenshtein_distance() {
    assert(fuzzc_levenshtein_distance("kitten", "sitting") == 3);
    assert(fuzzc_levenshtein_distance("flaw", "lawn") == 2);
    assert(fuzzc_levenshtein_distance("intention", "execution") == 5);
    assert(fuzzc_levenshtein_distance("", "") == 0);
    assert(fuzzc_levenshtein_distance("a", "") == 1);
    assert(fuzzc_levenshtein_distance("", "a") == 1);
    assert(fuzzc_levenshtein_distance("abc", "abc") == 0);
}

static void test_fuzzc_hamming_distance() {
    assert(fuzzc_hamming_distance("karolin", "kathrin") == 3);
    assert(fuzzc_hamming_distance("karolin", "kerstin") == 3);
    assert(fuzzc_hamming_distance("1011101", "1001001") == 2);
    assert(fuzzc_hamming_distance("2173896", "2233796") == 3);
    assert(fuzzc_hamming_distance("", "") == 0);
    assert(fuzzc_hamming_distance("a", "a") == 0);
    assert(fuzzc_hamming_distance("a", "b") == 1);
    assert(fuzzc_hamming_distance("abc", "a") == UNDEFINED_DISTANCE);
}

static void test_fuzzc_damerau_levenshtein_distance() {
    assert(fuzzc_damerau_levenshtein_distance("ca", "abc") == 3);
    assert(fuzzc_damerau_levenshtein_distance("abc", "ac") == 1);
    assert(fuzzc_damerau_levenshtein_distance("abcdef", "abcfde") == 2);
    assert(fuzzc_damerau_levenshtein_distance("", "") == 0);
    assert(fuzzc_damerau_levenshtein_distance("a", "") == 1);
    assert(fuzzc_damerau_levenshtein_distance("", "a") == 1);
    assert(fuzzc_damerau_levenshtein_distance("abc", "abc") == 0);
}

void test_fuzzc_distance_functions() {
    test_fuzzc_levenshtein_distance();
    test_fuzzc_hamming_distance();
    test_fuzzc_damerau_levenshtein_distance();
}