from typing import List

def convert(input_list: List[List[int]]) -> str:
    formatted_list = ['{' + ','.join(map(str, sublist)) + '}' for sublist in input_list]
    result = ', \n'.join(formatted_list)
    return "{" + result + "}"


if __name__ == '__main__':
    import numpy as np
    A = np.array([[  774252441,   293375679,    83645520, -1440015269],
                    [ 1989508433,   833720247, -1181399795,  -316612276],
                    [ 1804760737,   451723847,  2084893522,   969428760],
                    [   54893165,  -445213092,  2093245104,  -746545411]])
    print(np.log(A)*A+A)