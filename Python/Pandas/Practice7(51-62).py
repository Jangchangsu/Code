import pandas as pd

df_1 = pd.DataFrame({'item':['ring0','ring0','ring1','ring1'],
                     'type':['Gold', 'Silver', 'Gold', 'Bronze'],
                     'price':[20000, 10000, 50000, 30000]})
df_2 = df_1.pivot(index='item', columns='type', values='price')

df_3 = pd.DataFrame({'A':['a10','a11','a12'],
                     'B':['b10','b11','b12'],
                     'C':['c10','c11','c12']}, index= ['1','2','3'])
df_4 = pd.DataFrame({'B':['b23','b24','b25'],
                     'C':['c23','c24','c25'],
                     'D':['d23', 'd24','b25']}, index= ['3','4','5'])

# concatenate
"""
df_5 = pd.concat([df_3, df_4], axis = 0, join='outer') #default
df_6 = pd.concat([df_3, df_4], axis = 0, join='inner')
df_7 = pd.concat([df_3, df_4], axis = 1, join='outer')
df_8 = pd.concat([df_3, df_4], axis = 1, join='inner')
print(df_1)
print(df_2)
print(df_5)
print(df_6)
print(df_7)
print(df_8)
"""

#merge
"""
df_9 = df_3.merge(df_4, how='outer', on='B')
df_10 = df_3.merge(df_4, how='outer', left_index = True, right_index = True)
print(df_9)
print(df_10)
"""

df_11 = df_3.merge(df_4, how='left', on='B')
df_12 = df_3.merge(df_4, how='right', on='B')
df_13 = df_3.merge(df_4, how='outer', on='B')
df_14 = df_3.merge(df_4, how='inner', on='B')
print('left outer\n',df_11)
print('right outer\n',df_12)
print('full outer\n',df_13)
print('inner\n',df_14)