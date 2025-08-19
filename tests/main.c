//
// Created by jacks on 8/18/2025.
//

#include <stdio.h>

#include "../include/api.h"
#include "../include/distance.h"

int main() {
    printf("%f\n", calculate_similarity("testone", "testtwo", levenstein_distance));
    return 0;
}