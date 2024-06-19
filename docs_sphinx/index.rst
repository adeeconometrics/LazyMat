.. LazyMat documentation master file, created by
   sphinx-quickstart on Fri Jun  7 22:30:37 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to LazyMat's documentation!
===================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


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

Benchmark on Apple M2 8C MacOS 14.5 Release mode -- compiled on `arm64` build for Matmul.

```console
(venv) ➜  benchmark git:(dev-etparser) ✗ python linalg_libs/gflops.py
lib           gflop/s         secs  relative throughput    Size
----------  ---------  -----------  ---------------------  --------------
lazy_mat    2356.53    0.000911291  ---                    1024x1024x1024
numpy         67.4947  0.0318171    34.9143x               1024x1024x1024
pytorch       86.5684  0.0248068    27.2216x               1024x1024x1024
tensorflow    94.7282  0.02267      24.8767x               1024x1024x1024
(venv) ➜  benchmark git:(dev-etparser) ✗ python linalg_libs/gflops.py
lib           gflop/s       secs  relative throughput    Size
----------  ---------  ---------  ---------------------  --------------
lazy_mat    7470.82    0.0022996  ---                    2048x2048x2048
numpy         96.7968  0.177484   77.1804x               2048x2048x2048
pytorch      172.91    0.0993571  43.2063x               2048x2048x2048
tensorflow   156.748   0.109602   47.6613x               2048x2048x2048
(venv) ➜  benchmark git:(dev-etparser) ✗ python linalg_libs/gflops.py
lib           gflop/s      secs  relative throughput    Size
----------  ---------  --------  ---------------------  --------------
lazy_mat     6614.64   0.020778  ---                    4096x4096x4096
numpy         146.621  0.937376  45.1139x               4096x4096x4096
pytorch       277.298  0.495636  23.8539x               4096x4096x4096
tensorflow    158.817  0.865391  41.6494x               4096x4096x4096
```

---

Build for Debug:

```bash
$ mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug ../ && make
```

Build for Release:

```bash
$ mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug ../ && make
```

Running tests

```bash
$ ./bin/unittest
```

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
