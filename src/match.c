#include "../include/match.h"

#include <stdlib.h>

void fuzzc_free_matches(matches *m) {
    if (m != NULL) {
        if (m->data != NULL) free(m->data);
        free(m);
    }
}
