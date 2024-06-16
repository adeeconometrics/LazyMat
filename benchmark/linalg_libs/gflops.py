from tabulate import tabulate
from timeit import timeit
import numpy as np
import torch as pt
import tensorflow as tf


def get_gflops(ops: float, seconds: float) -> float:
    """Return the GigaFLOPS of a given operation and time in seconds.
    """
    return (ops/seconds)/1e9


def make_table(t_values: dict) -> None:
    """Print a table with the given values."""
    print(tabulate(t_values, headers=("lib", "gflop/s",
          "secs", "relative throughput", "Size")))


if __name__ == "__main__":
    table = []
    M, N, K = 8192, 8192, 8192
    nsec: int = 102409764 * 1e-9  # 49758236*1e-9  # 38_283_092_347

    floating_ops: int = 2 * M*N*K  # 4*M*N*K + 5*M*N
    lm_gflops: int = get_gflops(floating_ops, nsec)
    table.append(("lazy_mat", lm_gflops, nsec, '---', f'{M}x{N}x{K}'))

    np_A = np.random.rand(M, N)
    np_B = np.random.rand(M, K)
    np_sec = timeit(lambda: np_A@np_B, number=3)/3
    np_gflops = get_gflops(floating_ops, np_sec)
    table.append(("numpy", np_gflops,
                 np_sec, f'{lm_gflops/np_gflops: .4f}x', f'{M}x{N}x{K}'))

    pt_A = pt.tensor(np_A)
    pt_B = pt.tensor(np_B)
    pt_sec = timeit(lambda: pt.matmul(pt_A, pt_B), number=3)/3
    pt_gflops = get_gflops(floating_ops, pt_sec)
    table.append(("pytorch", pt_gflops, pt_sec,
                 f'{lm_gflops/pt_gflops: .4f}x', f'{M}x{N}x{K}'))

    tf_A = tf.convert_to_tensor(np_A)
    tf_B = tf.convert_to_tensor(np_B)
    tf_sec = timeit(lambda: tf.matmul(tf_A, tf_B), number=3)/3
    tf_gflops = get_gflops(floating_ops, tf_sec)
    table.append(("tensorflow", tf_gflops, tf_sec,
                 f'{lm_gflops/tf_gflops: .4f}x', f'{M}x{N}x{K}'))

    make_table(table)
