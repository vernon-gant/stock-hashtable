#ifndef STOCK_UI_H
#define STOCK_UI_H

#include <string>
#include "stock.h"

// A class representing the user interface for the stock management system
class UI {
public:
    // Prints the menu of available options to the console
    static void printMenu();

    // Scans the user's choice from the console and returns it
    static int scanChoice();

    // Scans the user input for a stock and returns a shared pointer to it
    static std::shared_ptr<Stock> scanStock();

    // Scans the user input for a file path and returns it as a string
    static std::string scanFilePath();

    // Scans the user input for a search keyword and returns it as a pair
    // The first element of the pair is the keyword, the second element indicates
    // whether to search by name (true) or shorthand (false)
    static std::pair<std::string,bool> scanKeyword();
};



#endif //STOCK_UI_H
