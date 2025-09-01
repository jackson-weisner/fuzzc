#ifndef DISTANCE_H
#define DISTANCE_H

int fuzzc_levenshtein_distance(const char *s1, const char *s2);
int fuzzc_damerau_levenshtein_distance(const char *s1, const char *s2);
int fuzzc_hamming_distance(const char *s1, const char *s2);

#endif //DISTANCE_H

