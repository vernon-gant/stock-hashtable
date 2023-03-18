#ifndef STOCK_APP_H
#define STOCK_APP_H

#include "UI.h"
#include "StockHashTable.h"

class App {
public:

    void run();

private:
   
    StockHashTable stockHashTable;
};


#endif //STOCK_APP_H
