import pandas as pd

# Compare with Series and DataFrame

listdata = [1,2,3,4]
dictdata = {'a':[1,2,3,4], 'b':[4,3,2,1]}

series = pd.Series(listdata)
print('In this case of a Series and list')
print(series)
print('Shape : ', series.shape, '\n')

dataframe = pd.DataFrame(listdata)
print('In this case of a DataFrame and list')
print(dataframe)
print('Shape: ', dataframe.shape, '\n')

series2 = pd.Series(dictdata)
print('In this case of a Series and dictionary')
print(series2)
print('Shape : ', series2.shape, '\n')

dataframe2 = pd.DataFrame(dictdata)
print('In this case of a DataFrame and dictionary')
print(dataframe2)
print('Shape: ', dataframe2.shape, '\n')
