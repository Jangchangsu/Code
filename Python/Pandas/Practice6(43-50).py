import pandas as pd

weather_index = pd.read_csv('./csvdata/weather.csv', index_col = 0, encoding='CP949')
weather_no_index = pd.read_csv('./csvdata/weather.csv', encoding='CP949')

weather_index.fillna(weather_index['평균 풍속(m/s)'].mean(), inplace = True)
