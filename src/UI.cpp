#include <limits>
#include "../includes/UI.h"

void UI::printMenu() {
    std::cout << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "MENU" << std::endl << std::endl;
    std::cout << "1. ADD" << std::endl;
    std::cout << "2. REMOVE" << std::endl;
    std::cout << "3. IMPORT" << std::endl;
    std::cout << "4. SEARCH" << std::endl;
    std::cout << "5. PLOT" << std::endl;
    std::cout << "6. SAVE" << std::endl;
    std::cout << "7. LOAD" << std::endl;
    std::cout << "8. QUIT" << std::endl;
    std::cout << "-----------" << std::endl << std::endl;
}

int UI::scanChoice() {
    std::cout << "Enter your choice: ";
    int choice = -1;
    while (true) {
        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 8) {
                std::cout << std::endl;
                return choice;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter again: " << std::endl;
    }
}

std::shared_ptr<Stock> UI::scanStock() {
    std::string name;
    std::string shorthand;
    std::string id;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter shorthand: ";
    std::cin >> shorthand;
    std::cout << "Enter id: ";
    std::cin >> id;
    std::cout << std::endl;
    return std::make_shared<Stock>(name, shorthand, id);
}

std::string UI::scanFileName() {
    std::string path;
    std::cout << "Enter file name: ";
    std::cin >> path;
    std::cout << std::endl;
    return path;
}

std::pair<std::string,bool> UI::scanKeyword() {
    std::string keyType;
    std::cout << "Search by name or shorthand? (name/shorthand): ";
    std::cin >> keyType;
    std::string keyword;
    std::cout << "Enter keyword: ";
    std::cin >> keyword;
    std::cout << std::endl;
    return std::make_pair(keyword, keyType == "name");
}
