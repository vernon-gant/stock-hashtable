#ifndef STOCK_STOCK_H
#define STOCK_STOCK_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

class PriceData {
private:
    std::string date;
public:
    void setDate(const std::string &date);

    void setOpen(double open);

    void setHigh(double high);

    void setLow(double low);

    void setClose(double close);

    void setAdjClose(double adjClose);

private:
    double open, high, low, close, adjClose;
public:
    PriceData();

    PriceData(std::string date, double open, double high, double low, double close, double adjClose) : date(std::move(
            date)), open(open), high(high), low(low), close(close), adjClose(adjClose) {}

    void print() const;

    friend std::ostream& operator<<(std::ostream &os, const PriceData &priceData);

    friend std::istream& operator>>(std::istream &is, PriceData &priceData);
};

class Stock {
private:
    std::string name, shorthand, id;
    std::vector<PriceData> prices;

    void savePrices() const;
public:
    Stock();

    ~Stock() {
        prices.clear();
    }

    Stock(std::string name, std::string shorthand, std::string id) : name(std::move(name)), shorthand(std::move(
            shorthand)), id(std::move(id)) {}

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    [[nodiscard]] const std::string &getShorthand() const {
        return shorthand;
    }

    void setName(const std::string &name);

    void setShorthand(const std::string &shorthand);

    void setId(const std::string &id);

    void addPriceData(const PriceData& priceData) {
        prices.push_back(priceData);
    }

    void importPrices(const std::string &fileName);

    void printPrice() const;

    void plotPrice() const;

    [[nodiscard]] std::string signature() const;

    bool operator==(const Stock &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Stock &stock);

    friend std::istream &operator>>(std::istream &is, Stock &stock);
};

class StockEntry {
private:
    std::shared_ptr<Stock> stock;
    bool deleted;
public:
    StockEntry() {
        stock = nullptr;
        deleted = false;
    }

    [[nodiscard]] Stock &getStock() const {
        return *stock;
    }

    [[nodiscard]] bool isDeleted() const {
        return deleted;
    }

    [[nodiscard]] bool isEmpty() const {
        return this->stock == nullptr;
    }

    void reset(bool wasDeleted = false) {
        stock.reset();
        deleted = wasDeleted;
    }

    void setStock(std::shared_ptr<Stock> newStock) {
        this->stock = std::move(newStock);
    }

    void restore() {
        deleted = false;
    }
};

#endif //STOCK_STOCK_H
