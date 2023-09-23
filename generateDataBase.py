import pandas as pd
import random


def generate_almost_sorted(data_final_amount: int):
    data_final_amount = 1000000
    final_data = []

    amount = int((95/100) * data_final_amount)

    for i in range(0, amount-1):
        final_data.append(i)

    for j in range(1, data_final_amount-amount):
        final_data.append(random.randint(0, data_final_amount-1))

    df = pd.DataFrame(final_data)
    df.to_csv(f"{data_final_amount}qo.csv")


def generate_inverse(data_final_amount: int):
    final_data = []

    for i in reversed(range(0, data_final_amount-1)):
        final_data.append(i)
    

    df = pd.DataFrame(final_data)
    df.to_csv(f"{data_final_amount}i.csv")


def generate_data(data_final_amount: int):
    final_data = []

    for i in range(0, data_final_amount-1):
        final_data.append(i)
    

    df = pd.DataFrame(final_data)
    df.to_csv(f"{data_final_amount}.csv")


# example of usage

generate_data(1000)
generate_inverse(1000)
generate_almost_sorted(1000)
