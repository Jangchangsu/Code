import numpy as np
import pandas as pd

#Translate Series to Dictionary

name_series = pd.Series(['Suan','Sujeong','Dongyun','Ean','Jiahn'])
age_series = pd.Series([19,23,22,19,16])
sex_series = pd.Series(['female','female','male','female','male'])
grade_series = pd.Series([4.35, 4.23, 4.25, 4.37, 4.25])

dataframe = pd.DataFrame({'name': name_series, 'age': age_series, 'sex': sex_series, 'grade': grade_series})

print(dataframe)