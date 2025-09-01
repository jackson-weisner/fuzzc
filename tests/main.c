#include <stdio.h>

#include "tests.h"

int main() {
    test_fuzzc_distance_functions();
    test_fuzzc_api_functions();

    printf("all tests passed\n");

    return 0;
}