cmake_minimum_required(VERSION 3.24)
project(stock)

set(CMAKE_CXX_STANDARD 17)

add_executable(stock src/main.cpp src/stock.cpp src/UI.cpp src/App.cpp src/StockHashTable.cpp)
