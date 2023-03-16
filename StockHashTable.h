#ifndef STOCK_STOCKHASHTABLE_H
#define STOCK_STOCKHASHTABLE_H


#include "stock.h"

class StockHashTable {
private:
    // static const int DEFAULT_SIZE = 2019;
    static const int DEFAULT_SIZE = 10;

    StockEntry * stocksByName[DEFAULT_SIZE];
    StockEntry * stocksByShorthand[DEFAULT_SIZE];
    int size;

private:

    [[nodiscard]] int hash(const std::string &key) const;

    [[nodiscard]] int searchByShorthand(const std::string &shorthand) const;

    [[nodiscard]] int searchByName(const std::string &name) const;

    void deleteAll();

public:

    StockHashTable();

    ~StockHashTable();

    void add(const std::shared_ptr<Stock>& stock);

    Stock& search(const std::pair<std::string, bool> &key);

    void remove(const std::pair<std::string, bool>& key);

    void save(const std::string &path) const;

    void load(const std::string &path);
};


#endif //STOCK_STOCKHASHTABLE_H
