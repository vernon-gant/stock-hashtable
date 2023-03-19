import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import os
import warnings

# Suppress warnings
warnings.filterwarnings("ignore")

# Read the CSV data
csv_path = './resources/current_stock.csv'
data = pd.read_csv(csv_path)

# Convert the 'Date' column to datetime objects
data['Date'] = pd.to_datetime(data['Date'], format='%Y-%m-%d')

# Calculate the average stock price per day
data['Average'] = (data['High'] + data['Low']) / 2

# Get the last 30 days of data from the CSV file
filtered_data = data.tail(30)

# Plot the data
fig, ax = plt.subplots()
ax.plot(filtered_data['Date'], filtered_data['Average'], label='Average Stock Price')
ax.set(xlabel='Date', ylabel='Price', title='Stock Price - Last 30 Days')
ax.legend()

ax.xaxis.set_major_locator(mdates.DayLocator(interval=3))
ax.xaxis.set_major_formatter(mdates.DateFormatter('%d/%m/%Y'))
plt.xticks(rotation=45)
plt.show()

# Delete the CSV file
os.remove(csv_path)
