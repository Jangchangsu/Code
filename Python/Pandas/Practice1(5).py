import pandas as pd

# DataFrame basic method()

dataframe = {'A':[1,2,3,4,5,None,7],
             'B':[1,4,3,2,5,None,None],
             'C':['foo','bar','oh','bar','foo','bar','foo']}
df = pd.DataFrame(dataframe)

print('Mean Operation')
mean_A = df['A'].mean()
print(mean_A)

print('Measuring correlation')
corr_AB = df['A'].corr(df['B'])
print(corr_AB)

print('Counting Not null')
count_A = df['A'].count()
print(count_A)

print('Sorting list')
sort_B = df['B'].sort_values()
print(sort_B)

print('groupby')
groupedby_CB = df.groupby('C')['B'].mean()  
print(groupedby_CB)