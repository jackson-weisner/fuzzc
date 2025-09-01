#include "../include/match.h"

#include <stdlib.h>

void fuzzc_free_matches(matches *m) {
    if (m != NULL) {
        if (m->match_array != NULL) free(m->match_array);
        free(m);
    }
}
