#include "../include/match.h"

#include <stdlib.h>

void fuzzc_free_matches(matches *m) {
    if (m != NULL) {
        if (m->matches != NULL) free(m->matches);
        free(m);
    }
}
