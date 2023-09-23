import pandas as pd
from datetime import datetime

def selectionSort(itemsList):
    n = len( itemsList )
    for i in range( n - 1 ): 
        minValueIndex = i

        for j in range( i + 1, n ):
            if itemsList[j] < itemsList[minValueIndex] :
                minValueIndex = j

        if minValueIndex != i :
            temp = itemsList[i]
            itemsList[i] = itemsList[minValueIndex]
            itemsList[minValueIndex] = temp

    return itemsList

df = pd.read_csv("./cenarios/100000qo.csv")

a = df["0"].to_list()
 
start = datetime.now()
selectionSort(a)
end = datetime.now()
delta = end - start
print(int(delta.total_seconds() * 1000))
