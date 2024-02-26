import csv

# Read csv file

file = open('./csvdata/weather.csv')
data = csv.reader(file)
header = next(data) #Delete Scheme

# Print all
"""
for row in data:
    print(row)
"""


# Print Extracted
"""
for row in data:
    print(row[3], end=',')
"""

# Seraching Maximum value
"""
max_wind = 0.0

for row in data:
    if row[3] == '':
        wind = 0
    else:
        wind = float(row[3])
    if max_wind < wind:
        max_wind = wind
print('Maximum wind speed is', max_wind, 'm/s','over the past 10 years')
"""
# plot graph

import matplotlib.pyplot as plt

monthly_wind = [ 0 for x in range(12)]
days_counted = [ 0 for x in range(12)]

for row in data:
    month = int(row[0][5:7])

    if row[3] != '':
        wind = float(row[3])
        monthly_wind[month-1] += wind
        days_counted[month-1] += 1

for i in range(12):
    monthly_wind[i] /= days_counted[i]

# define x axis
months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
x = range(0, 12)

plt.plot(monthly_wind, 'blue')

# Cover the x value
plt.xticks(x, months)

plt.show()


file.close()