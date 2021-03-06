/* Positive double hill_climb function */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

struct config {

    double candidate;
    int num_parallel_tweaks;
    double (*eval)(double);
    double max_seconds;
    double max_change;
    double max_quality;
    int ignore_max_quality; // 1 is true
    int sign; // 0 both, 1 is only true, -1 is only negative
    int verbose; // 1 prints candidate value and quality each iteration

};

double mutate(double candidate, double max_change, int sign) {

    double change = fmod(rand(), (candidate * (1 - max_change)));

    (sign > 0) ? change * 1 : change * -1;
    candidate = (rand() % 2 == 1) ? (candidate -= change) : (candidate += change);
    (sign > 0) ? candidate * 1 : candidate * -1;

    return candidate;
}

double climb(struct config local_config) {
    srand((unsigned) time(NULL));

    double candidate = local_config.candidate;
    double quality = local_config.eval(candidate);
    double new_candidate;
    double new_quality;

    time_t start_seconds = time(NULL);

    if (local_config.verbose) {
            printf("current_candidate: %f\nquality: %f\n", candidate, quality);
    }

    while (time(NULL) - start_seconds <= local_config.max_seconds) {

        for (int i = 0; i < local_config.num_parallel_tweaks; i++) {
            new_candidate = mutate(candidate, local_config.max_change, local_config.sign); 
            new_quality = local_config.eval(new_candidate);

            if (new_quality > quality) {
                candidate = new_candidate;
                quality = new_quality;
            }
        }

        if (local_config.ignore_max_quality == 0  && new_quality >= local_config.max_quality) {
            break;
        }

        if (local_config.verbose) {
            printf("current_candidate: %f\nquality: %f\n", candidate, quality);
        }
    }

    return candidate;

}
