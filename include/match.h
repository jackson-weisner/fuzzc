//
// Created by jacks on 8/30/2025.
//

#ifndef FUZZC_MATCH_H
#define FUZZC_MATCH_H

typedef struct matches {
    char **matches;
    int count;
} matches;

void fuzzc_free_matches(matches *m);

#endif //FUZZC_MATCH_H