import pandas as pd
from datetime import datetime


def quick_sort(arr):
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]

    return quick_sort(left) + middle + quick_sort(right)

# Example usage:
if __name__ == "__main__":
    for i in range(0, 3):
        df = pd.read_csv("./cenarios/1000i.csv")
        data = df["0"].to_list()
        my_list = data
        start = datetime.now()
        quick_sort(my_list)
        end = datetime.now()
        delta = end - start
        print(int(delta.total_seconds() * 1000))