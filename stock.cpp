#include "stock.h"

PriceData::PriceData() {
    date = "";
    open = 0;
    high = 0;
    low = 0;
    close = 0;
    adjClose = 0;
}

std::ostream& operator<<(std::ostream &os, const PriceData &priceData) {
    os << priceData.date << ","
       << priceData.open << ","
       << priceData.high << ","
       << priceData.low << ","
       << priceData.close << ","
       << priceData.adjClose << "\n";
    return os;
}


std::istream& operator>>(std::istream &is, PriceData &priceData) {
    std::string date;
    double open, high, low, close, adjClose;
    char delimiter;

    std::getline(is, date, ',');
    is >> open >> delimiter
       >> high >> delimiter
       >> low >> delimiter
       >> close >> delimiter
       >> adjClose;

    priceData.setDate(date);
    priceData.setOpen(open);
    priceData.setHigh(high);
    priceData.setLow(low);
    priceData.setClose(close);
    priceData.setAdjClose(adjClose);

    return is;
}

void PriceData::print() const {
    std::cout << "Date: " << date << std::endl;
    std::cout << "Open: " << open << std::endl;
    std::cout << "High: " << high << std::endl;
    std::cout << "Low: " << low << std::endl;
    std::cout << "Close: " << close << std::endl;
    std::cout << "Adj Close: " << adjClose << std::endl << std::endl;

}

void PriceData::setDate(const std::string &date) {
    PriceData::date = date;
}

void PriceData::setOpen(double open) {
    PriceData::open = open;
}

void PriceData::setHigh(double high) {
    PriceData::high = high;
}

void PriceData::setLow(double low) {
    PriceData::low = low;
}

void PriceData::setClose(double close) {
    PriceData::close = close;
}

void PriceData::setAdjClose(double adjClose) {
    PriceData::adjClose = adjClose;
}

Stock::Stock() {
    name = "";
    shorthand = "";
    id = "";
    prices = std::vector<PriceData>();
}

void Stock::importPrices(const std::string &path) {
    std::ifstream ss(path);
    if (!ss.is_open()) {
        throw std::runtime_error("Failed to open file " + path);
    }

    std::string line;

    // Skip header
    std::getline(ss, line);

    // Parse each row
    while (std::getline(ss, line)) {
        std::istringstream rowStream(line);
        std::string dateStr, openStr, highStr, lowStr, closeStr, adjCloseStr, volumeStr;

        // Parse columns
        std::getline(rowStream, dateStr, ',');
        std::getline(rowStream, openStr, ',');
        std::getline(rowStream, highStr, ',');
        std::getline(rowStream, lowStr, ',');
        std::getline(rowStream, closeStr, ',');
        std::getline(rowStream, adjCloseStr, ',');
        std::getline(rowStream, volumeStr);

        // Convert string values to doubles
        double open = std::stod(openStr);
        double high = std::stod(highStr);
        double low = std::stod(lowStr);
        double close = std::stod(closeStr);
        double adjClose = std::stod(adjCloseStr);

        // Create and add PriceData object
        PriceData price(dateStr, open, high, low, close, adjClose);
        prices.push_back(price);
    }
}

bool Stock::operator==(const Stock &other) const {
    return name == other.name || shorthand == other.shorthand;
}

void Stock::printPrice() const {
    if (prices.empty()) {
        std::cout << "No price data available for " << this->signature() << std::endl;
        return;
    } else {
        std::cout << "Price data for " << this->signature() << std::endl;
        std::cout << "============================" << std::endl;
        prices.back().print();
    }
}

std::string Stock::signature() const {
    return "(" + name + "|" + shorthand + "|" + id + ")";
}

std::ostream &operator<<(std::ostream &os, const Stock &stock) {
    os << "(" << stock.name << "|" << stock.shorthand << "|" << stock.id << ")" << std::endl;
    if (stock.prices.empty()) {
        os << "No price data available" << std::endl;
    } else {
        for (const auto &price : stock.prices) {
            os << price;
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, Stock &stock) {
    std::string line;
    std::string name, shorthand, id;
    std::vector<PriceData> prices;

    std::getline(is, name, '|');
    std::getline(is, shorthand, '|');
    std::getline(is, id, ')');

    stock.setName(name.substr(1));
    stock.setShorthand(shorthand);
    stock.setId(id);

    // Read the newline character
    std::getline(is, line);

    while (is.peek() != EOF && is.peek() != '(') {
        std::getline(is, line);

        if (line == "No price data available") {
            break;
        } else {
            std::istringstream ss(line);
            PriceData priceData;
            ss >> priceData;
            stock.addPriceData(priceData);
        }
    }
    return is;
}

void Stock::setName(const std::string &name) {
    Stock::name = name;
}

void Stock::setShorthand(const std::string &shorthand) {
    Stock::shorthand = shorthand;
}

void Stock::setId(const std::string &id) {
    Stock::id = id;
}

void Stock::savePrices() const {
    std::ofstream ss("current_stock.csv");
    if (!ss.is_open()) {
        throw std::runtime_error("Failed to save prices...");
    }

    ss << "Date,Open,High,Low,Close,Adj Close\n";
    for (const auto &price : prices) {
        ss << price;
    }
}

void Stock::plotPrice() const {
    if (prices.empty()) {
        std::cout << "No price data available for " << this->signature() << std::endl;
        return;
    }
    this->savePrices();
    const std::string pythonInterpreterPath = R"(.\venv\Scripts\python.exe)";
    // Run the Python script and redirect its output to the console
    std::system((std::string(pythonInterpreterPath + " plot.py")).c_str());
}



