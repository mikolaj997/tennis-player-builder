#include "TaskManager.h"

#include <iostream>
#include <limits>
#include <string>

void showMenu() {
    std::cout << "\n=== TASK MANAGER ===\n";
    std::cout << "1. Add task\n";
    std::cout << "2. Show tasks\n";
    std::cout << "3. Complete task\n";
    std::cout << "4. Remove task\n";
    std::cout << "5. Search task\n";
    std::cout << "6. Statistics\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    TaskManager manager;

    int choice;

    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Invalid input.\n";
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            std::string name;

            std::cout << "Task name: ";
            std::getline(std::cin, name);

            manager.addTask(name);
        }
        else if (choice == 2) {
            manager.showTasks();
        }
        else if (choice == 3) {
            int id;

            std::cout << "Task ID: ";
            std::cin >> id;

            manager.completeTask(id);
        }
        else if (choice == 4) {
            int id;

            std::cout << "Task ID: ";
            std::cin >> id;

            manager.removeTask(id);
        }
        else if (choice == 5) {
            std::string phrase;

            std::cout << "Search phrase: ";
            std::getline(std::cin, phrase);

            manager.searchTask(phrase);
        }
        else if (choice == 6) {
            manager.showStatistics();
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    std::cout << "Goodbye!\n";

    return 0;
}