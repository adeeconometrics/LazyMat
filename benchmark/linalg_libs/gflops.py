from tabulate import tabulate
from timeit import timeit
import numpy as np
import torch as pt
import tensorflow as tf

def get_gflops(ops:float, seconds:float) -> float:
    return (ops/seconds)/1e9

def make_table(t_values:dict) -> None:
    print(tabulate(t_values, headers=("lib", "gflop/s", "secs", "relative throughput")))

if __name__ == "__main__":
    table = []
    equation = lambda A,B:  A * B + B / A * B * B - A
    M,N,K = 2048,2048,2048
    nsec = 41*1e-9
    
    lm_gflops = get_gflops(N*M*6, nsec)
    table.append(("lazy_mat", lm_gflops, nsec, '---'))

    np_A = np.random.rand(M,N)
    np_B = np.random.rand(M,K)
    np_sec = timeit(lambda: equation(np_A,np_B), number=2)/2
    np_gflops = get_gflops(N*M*6, np_sec)
    table.append(("numpy",get_gflops(N*M*6, np_gflops),np_sec, f'{lm_gflops/np_gflops : .4f}x'))

    pt_A = pt.tensor(np_A)
    pt_B = pt.tensor(np_B)
    pt_sec = timeit(lambda: equation(pt_A,pt_B), number=2)/2
    pt_gflops = get_gflops(N*M*6, pt_sec)
    table.append(("pytorch",pt_gflops, pt_sec, f'{lm_gflops/pt_gflops : .4f}x'))


    tf_A = tf.convert_to_tensor(np_A)
    tf_B = tf.convert_to_tensor(np_B)
    tf_sec = timeit(lambda: equation(tf_A,tf_B), number=2)/2
    tf_gflops = get_gflops(N*M*6, tf_sec)
    table.append(("tensorflow",tf_gflops, tf_sec, f'{lm_gflops/tf_gflops : .4f}x'))

    make_table(table)
