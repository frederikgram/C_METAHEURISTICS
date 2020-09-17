#include "steepest_ascent_hill.c"

double my_test_eval(double candidate) {
    return fabs(candidate - 1337);
}

void main(){

    struct config MyConfig;

    MyConfig.candidate = 42;
    MyConfig.eval = my_test_eval;
    MyConfig.ignore_max_quality = 1;
    MyConfig.max_change = 0.1;
    MyConfig.max_quality = -1;
    MyConfig.max_seconds = 4;
    MyConfig.num_parallel_tweaks = 5;
    MyConfig.sign = 1;
    MyConfig.verbose = 1;

    climb(MyConfig);

}