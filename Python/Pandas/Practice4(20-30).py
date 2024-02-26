import pandas as pd
# Read csv file through pandas

df_my_index= pd.read_csv('./csvdata/countries.csv', index_col = 0) # delete col (Null)
df_no_index= pd.read_csv('./csvdata/countries.csv')
df_weather_index = pd.read_csv('./csvdata/weather.csv', index_col = 0, encoding='CP949') # CP949 To read korean

#print one column

print(df_my_index['population'])
print(df_no_index['population'])


#print more column ([,,,,] packaging to one list)
"""
print(df_my_index[['area','population']])
print(df_no_index[['area','population']])
"""
import matplotlib.pyplot as plt

#visualize the data (1)
"""
df_my_index['population'].plot(kind='bar', color=('b', 'darkorange', 'g','r','m'))
df_my_index['population'].plot(kind='pie')
plt.show()
"""
#visualize the data (2)
"""
df_weather_index['ave_wind'].plot(kind='hist', bins=33) #bins = 33 devide 33 sections
plt.show()
"""
#Read the data and apply slicing
"""
head = df_my_index.head() #read from the first row to the fifth row
tail = df_my_index.tail() #read from the last row to the fifth row fron the end
slicing = df_my_index[:3]

print(head)
print(tail)
print(slicing)
"""
#Read the filtered data
"""
fil_data1 = df_my_index.loc['KR']
fil_data2 = df_my_index['country'][:2]
fil_data3 = df_my_index.loc['KR','capital']
fil_data4 = df_my_index['capital'].loc['KR']

print(fil_data1)
print(fil_data2)
print(fil_data3)
print(fil_data4)
"""
#append the column
"""
df_my_index['density'] = df_my_index['population'] / df_my_index['area']
print(df_my_index)
"""