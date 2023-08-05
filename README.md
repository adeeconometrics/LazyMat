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
Compilation:
```bash
$ mkdir build && cd build && cmake ../ && make
```

Executing: 
```bash
$ ../bin/LazyMat.o
```
