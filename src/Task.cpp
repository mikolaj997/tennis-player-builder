#include "Task.h"

Task::Task(int id, const std::string& name)
    : id(id), name(name), completed(false) {
}