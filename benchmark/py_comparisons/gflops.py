from tabulate import tabulate
from timeit import timeit
import numpy as np
import torch as pt
import tensorflow as tf

def get_gflops(ops:float, seconds:float) -> float:
    return (ops/seconds)/1e9

def make_table(t_values:dict) -> None:
    print(tabulate(t_values, headers=("lib", "gflop/s")))

if __name__ == "__main__":
    table = []
    equation = lambda A,B:  A * B + B / A * B * B - A
    M,N,K = 256,256,256
    nsec = 11173225
    
    table.append(("lazy_mat", get_gflops(N*M*6, nsec*1e-9)))

    np_A = np.random.rand(M,N)
    np_B = np.random.rand(M,K)
    np_sec = timeit(lambda: equation(np_A,np_B), number=2)/2
    table.append(("numpy",get_gflops(N*M*6, np_sec)))

    pt_A = pt.tensor(np_A)
    pt_B = pt.tensor(np_B)
    pt_sec = timeit(lambda: equation(pt_A,pt_B), number=2)/2
    table.append(("pytorch",get_gflops(N*M*6, pt_sec)))


    tf_A = tf.convert_to_tensor(np_A)
    tf_B = tf.convert_to_tensor(np_B)
    tf_sec = timeit(lambda: equation(tf_A,tf_B), number=2)/2
    table.append(("tensorflow",get_gflops(N*M*6, tf_sec)))

    make_table(table)
