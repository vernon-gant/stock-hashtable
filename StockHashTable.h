#ifndef STOCK_STOCKHASHTABLE_H
#define STOCK_STOCKHASHTABLE_H

#include "stock.h"

class StockHashTable {
private:
    // The default size of the hash table
    static const int DEFAULT_SIZE = 10;

    // The array of StockEntry pointers, used to store the stocks
    StockEntry * stocksByName[DEFAULT_SIZE];
    StockEntry * stocksByShorthand[DEFAULT_SIZE];

    // The number of stocks in the hash table
    int size;

private:
    // The hash function used to compute the index of a stock in the hash table
    [[nodiscard]] int hash(const std::string &key) const;

    // The function used to search for a stock by its shorthand in the hash table
    [[nodiscard]] int searchByShorthand(const std::string &shorthand) const;

    // The function used to search for a stock by its name in the hash table
    [[nodiscard]] int searchByName(const std::string &name) const;

    // The function used to delete all the stocks in the hash table
    void deleteAll();

public:
    // The constructor of the hash table
    StockHashTable();

    // The destructor of the hash table
    ~StockHashTable();

    // The function used to add a stock to the hash table
    void add(const std::shared_ptr<Stock>& stock);

    // The function used to search for a stock in the hash table
    Stock& search(const std::pair<std::string, bool> &key);

    // The function used to remove a stock from the hash table
    void remove(const std::pair<std::string, bool>& key);

    // The function used to save the contents of the hash table to a file
    void save(const std::string &path) const;

    // The function used to load the contents of the hash table from a file
    void load(const std::string &path);
};

#endif //STOCK_STOCKHASHTABLE_H

