import pandas as pd
import matplotlib.pyplot as plt

countries_df = pd.read_csv('./csvdata/countries.csv', index_col = 0)
sorted = countries_df.sort_values('population')
print(sorted)