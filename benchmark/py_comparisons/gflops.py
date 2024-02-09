from tabulate import tabulate
from timeit import timeit
import numpy as np
import torch as pt
import tensorflow as tf
import mxnet as mx

from enum import Enum

class Libraries(Enum):
    MXNET = "mxnet"
    NUMPY = "numpy"
    TORCH = "pytorch"
    TF = "tensorflow"

def get_gflops(ops:float, seconds:float) -> float:
    return (ops/seconds)/1e9

def make_table(t_values:dict) -> None:
    print(tabulate(t_values))

if __name__ == "__main__":
    M,N,K = 256,256,256
    np_A = 