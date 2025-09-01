#ifndef FUZZC_MATCH_H
#define FUZZC_MATCH_H

#include <stddef.h>

typedef struct {
    char **data;
    size_t count;
} matches;

void fuzzc_free_matches(matches *m);

#endif //FUZZC_MATCH_H