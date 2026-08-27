#include "TaskManager.h"

#include <algorithm>
#include <iostream>

TaskManager::TaskManager()
    : nextId(1) {
}

void TaskManager::addTask(const std::string& name) {
    tasks.emplace_back(nextId, name);
    ++nextId;

    std::cout << "Task added!\n";
}

void TaskManager::showTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks.\n";
        return;
    }

    for (const Task& task : tasks) {
        std::cout << task.id << ". "
                  << task.name
                  << " [" << (task.completed ? "DONE" : "TODO") << "]\n";
    }
}

void TaskManager::completeTask(int id) {
    for (Task& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            std::cout << "Task completed!\n";
            return;
        }
    }

    std::cout << "Task not found.\n";
}

void TaskManager::removeTask(int id) {
    auto oldSize = tasks.size();

    tasks.erase(
        std::remove_if(
            tasks.begin(),
            tasks.end(),
            [id](const Task& task) {
                return task.id == id;
            }
        ),
        tasks.end()
    );

    if (tasks.size() < oldSize) {
        std::cout << "Task removed!\n";
    } else {
        std::cout << "Task not found.\n";
    }
}

void TaskManager::searchTask(const std::string& phrase) const {
    bool found = false;

    for (const Task& task : tasks) {
        if (task.name.find(phrase) != std::string::npos) {
            std::cout << task.id << ". "
                      << task.name
                      << " [" << (task.completed ? "DONE" : "TODO") << "]\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching tasks.\n";
    }
}

void TaskManager::showStatistics() const {
    int completed = 0;

    for (const Task& task : tasks) {
        if (task.completed) {
            ++completed;
        }
    }

    std::cout << "Total tasks: " << tasks.size() << '\n';
    std::cout << "Completed: " << completed << '\n';
    std::cout << "Remaining: " << tasks.size() - completed << '\n';
}