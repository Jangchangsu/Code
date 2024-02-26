import pandas as pd

weather_index = pd.read_csv('./csvdata/weather.csv', index_col = 0, encoding='CP949')
weather_no_index = pd.read_csv('./csvdata/weather.csv', encoding='CP949')

# basic operation
"""
stand_deviation = weather.describe()
num_count = weather.count()
mean_data = weather.mean()
"""
import matplotlib.pyplot as plt
import datetime as dt

# plot graph (compare with csv method)
"""
monthly = [None for x in range(12)]
monthly_ave_wind = [0 for x in range(12)]

weather_no_index['date'] = pd.to_datetime(weather_no_index['date']) # when occure the can't convert value error, It is solution
weather_no_index['month'] = pd.DatetimeIndex(weather_no_index['date']).month

for i in range(12):
    monthly[i] = weather_no_index[weather_no_index['month'] == i + 1]
    monthly_ave_wind[i] = monthly[i].mean()['ave_wind']

plt.plot(monthly_ave_wind, 'red')
plt.show()
"""

# plot graph through Utilize groupby() method
"""
weather_no_index['date'] = pd.to_datetime(weather_no_index['date'])
weather_no_index['month'] = pd.DatetimeIndex(weather_no_index['date']).month
means = weather_no_index.groupby('month').mean()
means['ave_wind'].plot(kind = 'bar')
plt.show()
"""





