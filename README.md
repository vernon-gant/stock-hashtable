# Stock Market Management System

This is a C++ program that manages stock prices. It stores the stocks in a hash table to enable quick searching of a particular stock. 
Each stock has a name, a security identification number (WKN), and an abbreviation (a string). 
Additionally, the program manages the stock prices for the previous 30 days with the following information: (Date, Open, High, Low, Close, Volume, Adj Close).

## Headers

### PriceData

This class represents a single data point of stock prices for a particular day. It has the following attributes:

- date: a string that represents the date of the data point.
- open: a double that represents the opening price of the stock for that day.
- high: a double that represents the highest price of the stock for that day.
- low: a double that represents the lowest price of the stock for that day.
- close: a double that represents the closing price of the stock for that day.
- adjClose: a double that represents the adjusted closing price of the stock for that day.

This class also has several methods to set and get the attributes of the data point, as well as to print the data point to the console.

### Stock

This class represents a stock with a name, a shorthand, and an ID. It also has a vector of `PriceData` objects that represent the stock prices for the previous 30 days. It has the following attributes:

- name: a string that represents the name of the stock.
- shorthand: a string that represents the shorthand of the stock.
- id: a string that represents the ID of the stock.
- prices: a vector of `PriceData` objects that represent the stock prices for the previous 30 days.

This class also has several methods to set and get the attributes of the stock, as well as to add new `PriceData` objects to the `prices` vector. It also has methods to import stock prices from a CSV file, print the stock prices to the console, and plot the closing prices of the last 30 days of the stock as an ASCII graph.

### StockEntry

This class represents an entry in the hash table of stocks. It has a `shared_ptr` to a `Stock` object, as well as a boolean flag that indicates whether the entry has been deleted. It has the following attributes:

- stock: a `shared_ptr` to a `Stock` object.
- deleted: a boolean flag that indicates whether the entry has been deleted.

This class also has methods to get and set the `Stock` object, as well as to check whether the entry has been deleted.

### StockHashTable

This class represents the hash table of stocks. It has two arrays of `StockEntry` objects, one indexed by the stock's name and one indexed by the stock's shorthand. It also has a `size` attribute that represents the size of the hash table. It has the following attributes:

- stocksByName: an array of `StockEntry` objects, indexed by the stock's name.
- stocksByShorthand: an array of `StockEntry` objects, indexed by the stock's shorthand.
- size: an integer that represents the size of the hash table.

This class also has methods to add, search, and remove stocks from the hash table. It also has methods to save and load the hash table from a file.

### App

This class represents the main application. It has a `StockHashTable` object that represents the hash table of stocks. It has the following attributes:

- stockHashTable: a `StockHashTable` object that represents the hash table of stocks.

This class also has a `run()` method that displays the menu and executes the user's choices.

### UI

This class represents the user interface of the program. It has several static methods to display the menu, scan the user's choice, scan a Stock object, scan a file name, and scan a keyword for searching or deleting a stock from the hash table.

### Python for plotting

The program uses a Python script for plotting the closing prices of the last 30 days of a stock. The plotPrice() method in the Stock class invokes the Python script to read the data from the prices vector, create a CSV file, and plot the graph using the pandas and matplotlib libraries.

The Python script reads the CSV file, converts the 'Date' column to datetime objects, calculates the average stock price per day, and gets the last 30 days of data from the CSV file. Then, it plots the data using matplotlib and displays the graph to the user.

Note: The Python script deletes the CSV file after plotting the graph. The CSV file should be saved in the ./resources/ directory with a unique name. Make sure to install pandas and matplotlib libraries in Python 3 before running the program.

### How to use the program

Firstly create a venv in project root direcotry and install dependencies from plotting/requirements.txt 
Then compile the source code and run the executable file. The program will display a menu with the available options. Follow the on-screen instructions to perform the desired actions.

Note: Before importing stock prices, make sure to download the CSV file and save it in the project directory with a unique name.

### Requirements

This program requires a C++ compiler that supports C++11 or higher, as well as Python 3.

### Authors

This project was created by me and Vural Zeliha.
