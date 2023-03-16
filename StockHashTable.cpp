#include <cstdint>
#include "StockHashTable.h"
#include "stock.h"

int StockHashTable::hash(const std::string &key) const {
    uint32_t hash = 0;
    for (size_t i = 1; i <= key.length(); i++) {
        hash += key[i] * i;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % DEFAULT_SIZE;
}

void StockHashTable::add(const std::shared_ptr<Stock>& stock) {
    int indexByName = hash(stock->getName());
    int indexByShorthand = hash(stock->getShorthand());
    while (!stocksByName[indexByName]->isEmpty()) {
        if (stocksByName[indexByName]->getStock() == *stock) {
            throw std::invalid_argument(
                    "Stock already exists: " + stocksByName[indexByName]->getStock().getName() + " (" + stocksByName[indexByName]->getStock().getShorthand() + ")");
        }
        indexByName = (indexByName + 1) % DEFAULT_SIZE;
    }
    while (!stocksByShorthand[indexByShorthand]->isEmpty()) {
        if (stocksByShorthand[indexByShorthand]->getStock() == *stock) {
            throw std::invalid_argument(
                    "Stock already exists: " + stocksByShorthand[indexByShorthand]->getStock().getName() + " (" + stocksByShorthand[indexByShorthand]->getStock().getShorthand() + ")");
        }
        indexByShorthand = (indexByShorthand + 1) % DEFAULT_SIZE;
    }
    stocksByName[indexByName]->setStock(stock);
    if (stocksByName[indexByName]->isDeleted()) {
        stocksByName[indexByName]->restore();
    }
    stocksByShorthand[indexByShorthand]->setStock(stock);
    if (stocksByShorthand[indexByShorthand]->isDeleted()) {
        stocksByShorthand[indexByShorthand]->restore();
    }
    size++;
}

int StockHashTable::searchByShorthand(const std::string &shorthand) const {
    int shortHandIdx = hash(shorthand);
    int i = 0;
    while (!stocksByShorthand[shortHandIdx]->isEmpty() ||
            stocksByShorthand[shortHandIdx]->isDeleted()) {
        if (!stocksByShorthand[shortHandIdx]->isEmpty() && stocksByShorthand[shortHandIdx]->getStock().getShorthand() == shorthand) {
            break;
        }
        i++;
        shortHandIdx = (shortHandIdx + i * i) % DEFAULT_SIZE;
    }
    if (!stocksByShorthand[shortHandIdx]->isEmpty() && stocksByShorthand[shortHandIdx]->getStock().getShorthand() == shorthand) {
        return shortHandIdx;
    } else {
        throw std::invalid_argument("Stock not found: " + shorthand);
    }
}

int StockHashTable::searchByName(const std::string &name) const {
    int nameIdx = hash(name);
    int i = 0;
    while (!stocksByName[nameIdx]->isEmpty() ||
           stocksByName[nameIdx]->isDeleted()){
        if (!stocksByName[nameIdx]->isEmpty() && stocksByName[nameIdx]->getStock().getName() == name) {
            break;
        }
        i++;
        nameIdx = (nameIdx + i * i) % DEFAULT_SIZE;
    }
    if (!stocksByName[nameIdx]->isEmpty() && stocksByName[nameIdx]->getStock().getName() == name) {
        return nameIdx;
    } else {
        throw std::invalid_argument("Stock not found: " + name);
    }
}

void StockHashTable::remove(const std::pair<std::string, bool>& key) {
    int shortHandIdx, nameIdx;
    if (key.second) {
        nameIdx = searchByName(key.first);
        shortHandIdx = searchByShorthand(stocksByName[nameIdx]->getStock().getShorthand());
    } else {
        shortHandIdx = searchByShorthand(key.first);
        nameIdx = searchByName(stocksByShorthand[shortHandIdx]->getStock().getName());
    }
    Stock stock = stocksByName[nameIdx]->getStock();
    stocksByName[nameIdx]->reset(true);
    stocksByShorthand[shortHandIdx]->reset(true);
    std::cout << "Stock deleted: " << stock.signature() << std::endl;
}

Stock &StockHashTable::search(const std::pair<std::string, bool> &key) {
    if (key.second) {
        return stocksByName[searchByName(key.first)]->getStock();
    } else {
        return stocksByShorthand[searchByShorthand(key.first)]->getStock();
    }
}

StockHashTable::~StockHashTable() {
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        delete stocksByName[i];
        delete stocksByShorthand[i];
    }
}

StockHashTable::StockHashTable() {
    size = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        stocksByName[i] = new StockEntry();
        stocksByShorthand[i] = new StockEntry();
    }
}

void StockHashTable::save(const std::string &path) const {
    std::ofstream ostream(path);
    for (auto i : stocksByName) {
        if (i->isEmpty() || i->isDeleted()) {
            continue;
        } else {
            ostream << i->getStock();
        }
    }
    ostream.close();
    std::cout << "Saved " << size << " stocks to " << path << std::endl;
}

void StockHashTable::deleteAll() {
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        stocksByName[i]->reset();
        stocksByShorthand[i]->reset();
    }
    size = 0;
}

void StockHashTable::load(const std::string &path) {
    this->deleteAll();
    std::ifstream inFile(path);
    while (inFile.peek() != EOF) {
        Stock stock;
        inFile >> stock;
        this->add(std::make_shared<Stock>(stock));
    }
    std::cout << "Loaded " << size << " stocks from " << path << std::endl;
    inFile.close();
}
