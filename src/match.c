#include "../include/match.h"

#include <stdlib.h>

void fuzzc_free_matches(matches *m) {
    if (m != NULL) {
        if (m->similarities != NULL) free(m->similarities);
        free(m);
    }
}
