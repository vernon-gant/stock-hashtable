#include "../includes/App.h"

void App::run() {
    int command;
    do {
        UI::printMenu();
        command = UI::scanChoice();
        switch (command) {
            case 1: {
                try {
                    std::cout << "| ADD STOCK |" << std::endl << std::endl;
                    auto stock = UI::scanStock();
                    stockHashTable.add(stock);
                    std::cout << stock->signature() << " was added successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "| REMOVE STOCK |" << std::endl << std::endl;
                auto keyword = UI::scanKeyword();
                try {
                    stockHashTable.remove(keyword);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 3:
                std::cout << "| IMPORT STOCK |" << std::endl << std::endl;
                try {
                    auto keyword = UI::scanKeyword();
                    Stock &stock = stockHashTable.search(keyword);
                    std::string path = UI::scanFileName();
                    stock.importPrices(path);
                    std::cout << "Price for " << stock.signature() << " was imported successfully!" << std::endl;
                } catch (std::runtime_error &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 4: {
                try {
                    std::cout << "| SEARCH STOCK |" << std::endl << std::endl;
                    std::pair<std::string, bool> keyword = UI::scanKeyword();
                    Stock &stock = stockHashTable.search(keyword);
                    stock.printPrice();
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 5:
                std::cout << "| PLOT PRICES |" << std::endl << std::endl;
                try {
                    auto keyword = UI::scanKeyword();
                    Stock &stock = stockHashTable.search(keyword);
                    stock.plotPrice();
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 6: {
                std::cout << "| SAVE STOCKS |" << std::endl << std::endl;
                std::string path = UI::scanFileName();
                stockHashTable.save(path);
                break;
            }
            case 7:
                std::cout << "| LOAD STOCKS |" << std::endl << std::endl;
                try {
                    std::string path = UI::scanFileName();
                    this->stockHashTable.load(path);
                } catch (std::runtime_error &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 8:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                break;
        }
    } while (command != 8);

}


