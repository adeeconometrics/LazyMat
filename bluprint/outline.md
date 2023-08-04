# Outline

Contains API outline to be implemented

### Unary Expr

Trigonometric

- [x] sin
- [x] cos
- [x] tan
- [x] asin
- [x] acos
- [x] atan
- [ ] hypot
- [x] to_deg
- [x] to_rad

Hyperbolic

- [x] sinh
- [x] cosh
- [x] tanh
- [x] asinh
- [x] acosh
- [x] atanh

Rounding

- [ ] round
- [x] floor
- [x] ceil
- [ ] trunc

Sum, and Prod

- [ ] sum
- [ ] cumsum
- [ ] prod
- [ ] cumprod

Num Theory

- [x] mod
- [ ] lcm
- [ ] gcd

Exponents

- [x] exp
- [x] exp2
- [x] log
- [x] log2
- [x] log10

### Binary

- [ ] pow

Features to work on:

- [ ] support vectorized operations
- [ ] matrix types and template specialization
- [ ] support for large array objects (beyond 256x256)
  - [ ] resolve stack and heap overflow
