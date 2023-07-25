#!/bin/bash

g++ -std=c++17 -Wall -Wextra -pedantic ./include/utils.hpp -O0 -pg ./src/lazy2.cpp -o ./profile/lazy/lazy2.o

./profile/lazy/lazy2.o && mv gmon.out ./profile/lazy/

gprof ./profile/lazy/lazy2.o ./profile/lazy/gmon.out | gprof2dot -s -w | dot -Gdpi=200 -Tpng -o ./profile/lazy/lazy_profile.png 


g++ -std=c++17 -Wall -Wextra -pedantic ./include/utils.hpp -O0 -pg ./src/eager.cpp -o ./profile/eager/eager.o

./profile/eager/eager.o && mv gmon.out ./profile/eager/

gprof ./profile/eager/eager.o ./profile/eager/gmon.out | gprof2dot -s -w | dot -Gdpi=200 -Tpng -o ./profile/eager/eager_profile.png 