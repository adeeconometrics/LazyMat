<!-- ![Logo](img/LazyMatLogo.png -->

# LazyMat

Experimenting with Generic Lazy Matrix implementation in Cpp

<p align="center">
  <img src="img/LazyMatLogo.png" alt="Image">
</p>

## Motivation, Goals, and Disclaimers

This is a personal project that aims to explore ideas of deferred execution and ought to
investigate how it can improve performance for vectorized expressions. I wrote this
project to educate myself on the subtle techniques of expression templates, and locality of reference.

The project aims to support vector and matrix operations. There is no long-term initiative
to maintain and continuously develop this code. You are welcome to submit an issue or suggest improvements.
The robustness of this codebase is only limited to its test coverage.
This is not recommended to be used in a production environment.

---

### Performance

Benchmark on Apple M2 8C MacOS 14.5 Release mode -- compiled on `arm64` build.

```
(venv) ➜  benchmark git:(dev-etparser) ✗ python linalg_libs/gflops.py
lib           gflop/s      secs  relative throughput    Size
----------  ---------  --------  ---------------------  --------------
lazy_mat      299.266  0.459254  ---                    4096x4096x4096
numpy         169.974  0.808587  1.7607x                4096x4096x4096
pytorch       286.947  0.47897   1.0429x                4096x4096x4096
tensorflow    179.51   0.765636  1.6671x                4096x4096x4096
(venv) ➜  benchmark git:(dev-etparser) ✗ python linalg_libs/gflops.py
lib           gflop/s       secs  relative throughput    Size
----------  ---------  ---------  ---------------------  --------------
lazy_mat      386.895  0.0444045  ---                    2048x2048x2048
numpy         110.947  0.154847   3.4872x                2048x2048x2048
pytorch       172.165  0.0997873  2.2472x                2048x2048x2048
tensorflow    144.056  0.119259   2.6857x                2048x2048x2048
(venv) ➜  benchmark git:(dev-etparser) ✗ python linalg_libs/gflops.py
lib           gflop/s       secs  relative throughput    Size
----------  ---------  ---------  ---------------------  --------------
lazy_mat      141.186  0.0152103  ---                    1024x1024x1024
numpy         106.926  0.0200839  1.3204x                1024x1024x1024
pytorch       121.461  0.0176804  1.1624x                1024x1024x1024
tensorflow     65.359  0.0328568  2.1602x                1024x1024x1024
```

---

Compilation:

```bash
$ mkdir build && cd build && cmake ../ && make
```

Executing:

```bash
$ ../bin/LazyMat.o
```
