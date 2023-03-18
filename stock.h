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
    // Default constructor
    PriceData();

    // Parameterized constructor
    PriceData(std::string date, double open, double high, double low, double close, double adjClose) : date(std::move(
            date)), open(open), high(high), low(low), close(close), adjClose(adjClose) {}

    // Print price data to console
    void print() const;

    // Overloaded output stream operator
    friend std::ostream& operator<<(std::ostream &os, const PriceData &priceData);

    // Overloaded input stream operator
    friend std::istream& operator>>(std::istream &is, PriceData &priceData);
};

class Stock {
private:
    std::string name, shorthand, id;
    std::vector<PriceData> prices;

    // Save prices to file
    void savePrices() const;
public:
    // Default constructor
    Stock();

    // Parameterized constructor
    Stock(std::string name, std::string shorthand, std::string id) : name(std::move(name)), shorthand(std::move(
            shorthand)), id(std::move(id)) {}

    // Getter functions
    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    [[nodiscard]] const std::string &getShorthand() const {
        return shorthand;
    }

    // Setter functions
    void setName(const std::string &name);

    void setShorthand(const std::string &shorthand);

    void setId(const std::string &id);

    // Add price data to stock
    void addPriceData(const PriceData& priceData) {
        prices.push_back(priceData);
    }

    // Import prices from file
    void importPrices(const std::string &path);

    // Print stock prices to console
    void printPrice() const;

    // Plot stock prices using matplotlib
    void plotPrice() const;

    // Calculate stock signature
    [[nodiscard]] std::string signature() const;

    // Overloaded equality operator
    bool operator==(const Stock &other) const;

    // Overloaded output stream operator
    friend std::ostream &operator<<(std::ostream &os, const Stock &stock);

    // Overloaded input stream operator
    friend std::istream &operator>>(std::istream &is, Stock &stock);
};

class StockEntry {
private:
    std::shared_ptr<Stock> stock;
    bool deleted;
public:
    // Default constructor
    StockEntry() {
        stock = nullptr;
        deleted = false;
    }

    // Getter functions
    [[nodiscard]] Stock &getStock() const {
        return *stock;
    }

    [[nodiscard]] bool isDeleted() const {
        return deleted;
    }

    [[nodiscard]] bool isEmpty() const {
        return this->stock == nullptr;
    }

    // Reset stock entry
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
