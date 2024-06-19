from typing import Callable

from tabulate import tabulate
from timeit import timeit
import numpy as np
import torch as pt
import tensorflow as tf

from numpy.typing import ArrayLike
from tensorflow import Tensor as TFTensor
from torch import Tensor as PTTensor

Array = ArrayLike | PTTensor | TFTensor


def get_gflops(ops: float, seconds: float) -> float:
    """Return the GigaFLOPS of a given operation and time in seconds.
    """
    return (ops/seconds)/1e9


def make_table(t_values: dict) -> None:
    """Print a table with the given values."""
    print(tabulate(t_values, headers=("lib", "gflop/s",
          "secs", "relative throughput", "Size")))


def measure_expr(A: Array,
                 B: Array,
                 sin: Callable[[Array], Array],
                 cos: Callable[[Array], Array],
                 matmul: Callable[[Array, Array], Array],
                 t_number: int = 3) -> float:
    return timeit(lambda: 2 + matmul(A, B) + A * B * matmul(sin(A), cos(A) + B) + 3., number=t_number)/t_number


if __name__ == "__main__":
    table = []
    M, N, K = 256, 256, 256
    nsec: int = 230162833 * 1e-9  # 49758236*1e-9  # 38_283_092_347

    floating_ops: int = 4*M*N*K + 5*M*N  # 2 * M*N*K
    lm_gflops: int = get_gflops(floating_ops, nsec)
    table.append(("lazy_mat", lm_gflops, nsec, '---', f'{M}x{N}x{K}'))

    np_A = np.random.rand(M, N)
    np_B = np.random.rand(M, K)
    np_sec = measure_expr(np_A, np_B, np.sin, np.cos, np.matmul)
    np_gflops = get_gflops(floating_ops, np_sec)
    table.append(("numpy", np_gflops,
                 np_sec, f'{lm_gflops/np_gflops: .4f}x', f'{M}x{N}x{K}'))

    pt_A = pt.tensor(np_A)
    pt_B = pt.tensor(np_B)
    pt_sec = measure_expr(pt_A, pt_B, pt.sin, pt.cos, pt.matmul)
    pt_gflops = get_gflops(floating_ops, pt_sec)
    table.append(("pytorch", pt_gflops, pt_sec,
                 f'{lm_gflops/pt_gflops: .4f}x', f'{M}x{N}x{K}'))

    tf_A = tf.convert_to_tensor(np_A)
    tf_B = tf.convert_to_tensor(np_B)
    tf_sec = measure_expr(tf_A, tf_B, tf.sin, tf.cos, tf.matmul)
    tf_gflops = get_gflops(floating_ops, tf_sec)
    table.append(("tensorflow", tf_gflops, tf_sec,
                 f'{lm_gflops/tf_gflops: .4f}x', f'{M}x{N}x{K}'))

    make_table(table)
