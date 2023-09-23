import pandas as pd
import random


end = 1000000
list_ = []

amount = int((95/100) * end)

for i in range(0, amount-1):
    list_.append(i)

for j in range(1, end-amount):
    list_.append(random.randint(1, end))

df = pd.DataFrame(list_)
df.to_csv("1000000qo.csv")