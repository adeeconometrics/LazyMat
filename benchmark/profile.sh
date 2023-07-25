#!/bin/bash

cc_flags=$(g++ -std=c++17 -Wall -Wextra -pedantic -O0 -pg)
lazy_dir=./profile/lazy
eager_dir=./profile/eager

$cc_flags ./include/utils.hpp ./src/lazy2.cpp -o $lazy_dir/lazy2.o

./profile/lazy/lazy2.o && mv gmon.out ./profile/lazy/

gprof ./profile/lazy/lazy2.o ./profile/lazy/gmon.out | gprof2dot -s -w | dot -Gdpi=200 -Tpng -o ./profile/lazy/lazy_profile.png 

$cc_flags ./include/utils.hpp ./src/eager.cpp -o $eager_dir/eager.o

$eager_dir/eager.o && mv gmon.out $eager_dir/

gprof $eager_dir/eager.o $eager_dir/gmon.out | gprof2dot -s -w | dot -Gdpi=200 -Tpng -o $eager_dir/eager_profile.png 