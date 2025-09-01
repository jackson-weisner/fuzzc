# Description
`fuzzc` is a simple C library for fuzzy strings.
It was mainly used as an exploration of how fuzzy matching works.

# Building
To build the library, run:
```bash
source build.sh
```
After running, a `build` directory will be created containing the compiled static and dynamic library, along with the `tests` executable.




## Distance functions
### Levenshtein distance
Use the `fuzzc_levenshtein_distance` function to calculate the Levenshtein distance between two strings.
Levenshtein distance is the minimum number of single-character edits (insertions, deletions and substitutions) required to change one string into the other.

### Damerau-Levenshtein distance
Use `fuzzc_damerau_levenshtein_distance` to calculate the Damerau-Levenshtein distance between two strings.
Damerau-Levenshtein distance is similar to Levenshtein distance but also considers transpositions of two adjacent characters as a single edit.

### Hamming distance
Use `fuzzc_hamming_distance` to calculate the Hamming distance between two strings of equal length.
Hamming distance is the number of positions at which the corresponding characters are different.



# Usage

## Calculating similarity
Pass two strings and a distance function to `fuzzc_calculate_similarity` to get a similarity score between 0 and 1.
```c
#include "api.h"

int main() {
    double similarity = fuzzc_calculate_similarity("string1", "string2", fuzzc_levenshtein_distance);
    return 0;
}
```



## Top match
Pass a string and an array of choices to `fuzzc_top_match` to get the closest match based on a specified distance function.
```c
#include "api.h"

int main() {
    char *choices[] = {"apple", "banana", "orange"};
    char *result = fuzzc_top_match("teststring", choices, 3, fuzzc_levenshtein_distance);
    return 0;
}
```



## Matches in threshold
Pass a string and an array of choices to `fuzzc_matches_in_threshold` to get all choices that are within a certain similarity threshold (between 0 and 1).

```c
#include "api.h"

int main() {
    char *choices[] = {"apple", "banana", "orange"};
    matches *result = fuzzc_matches_in_threshold("teststring", choices, 3, 0.5, fuzzc_levenshtein_distance);
    
    for (size_t i = 0; i < result->count; i++) {
        printf("Match: %s, Similarity: %f\n", result->match_array[i].data, result->match_array[i].similarity);
    }
    
    fuzzc_free_matches(result);
    
    return 0;
}
```



## Longest common subsequence
Pass two strings to `fuzzc_longest_common_subsequence` to get their longest common subsequence.

```c
#include "api.h"

int main() {
    char *result = fuzzc_longest_common_subsequence("AGGTAB", "GXTXAYB");
    return 0;
}
```