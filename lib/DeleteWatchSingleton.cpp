//
// Created by barta on 26/12/2023.
//

#include <DeleteWatchSingleton.h>

Barta::DeleteWatchSingleton* Barta::DeleteWatchSingleton::instance = nullptr;

Barta::DeleteWatchSingleton &Barta::DeleteWatchSingleton::getInstance() {
    if (instance == nullptr) {
        DeleteWatchSingleton::instance = new DeleteWatchSingleton();
    }

    return *DeleteWatchSingleton::instance;
}
bool Barta::DeleteWatchSingleton::isToBeDeleted(size_t id) {
    if (this->watches.size() <= id) {
        this->watches.insert(this->watches.end(), id - this->watches.size(), false);
    }

    return this->watches[id];
}
void Barta::DeleteWatchSingleton::setToBeDeleted(size_t id, bool value) {
    if (this->watches.size() <= id) {
        this->watches.insert(this->watches.end(), id - this->watches.size(), false);
    }

    this->watches[id] = value;
}
