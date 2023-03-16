cmake_minimum_required(VERSION 3.24)
project(stock)

set(CMAKE_CXX_STANDARD 17)

add_executable(stock main.cpp stock.cpp stock.h UI.cpp UI.h App.cpp App.h StockHashTable.cpp StockHashTable.h)
