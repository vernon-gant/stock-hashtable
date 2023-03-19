#ifndef STOCK_UI_H
#define STOCK_UI_H


#include <string>
#include "stock.h"

class UI {
public:
    static void printMenu();
    static int scanChoice();
    static std::shared_ptr<Stock> scanStock();
    static std::string scanFileName();
    static std::pair<std::string,bool> scanKeyword();
};


#endif //STOCK_UI_H
