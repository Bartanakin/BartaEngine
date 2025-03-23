#include <BartaObjectManager.h>

Barta::BartaObjectManager::BartaObjectManager() noexcept:
    objectList({}),
    dynamicsList({}),
    graphicsList({}) {}

Barta::BartaObjectManager::~BartaObjectManager() {
    auto i = this->objectList.begin();
    while (i != this->objectList.end()) {
        auto objectPtr = (*i);
        delete objectPtr;

        i++;
    }
}

void Barta::BartaObjectManager::addNewObject(
    BartaObjectInterface* newObject
) {
    this->objectList.push_back(newObject);
}

void Barta::BartaObjectManager::addDynamicsObject(
    DynamicsAwareInterface* dynamicsObject
) {
    this->dynamicsList.push_back(dynamicsObject);
}

Barta::DynamicsAwareInterface::DynamicsAwareList& Barta::BartaObjectManager::getDynamicsList() noexcept {
    return this->dynamicsList;
}

void Barta::BartaObjectManager::addGraphicsObject(
    GraphicsDataAwareInterface* newGraphicsObject
) {
    for (auto it = this->graphicsList.begin(); it != this->graphicsList.end(); it++) {
        // if ((*it)->getGraphicsData().z_index >= newGraphicsObject->getGraphicsData().z_index) {
        this->graphicsList.insert(it, newGraphicsObject);

        return;
        // }
    } // TODO

    this->graphicsList.push_back(newGraphicsObject);
}

Barta::GraphicsDataAwareInterface::GraphicsDataAwareList& Barta::BartaObjectManager::getGraphicsList() noexcept {
    return this->graphicsList;
}

void Barta::BartaObjectManager::reduceDeleted() {
    this->dynamicsList.reduce();
    this->graphicsList.reduce();

    auto newList = ObjectList();
    auto i = this->objectList.begin();
    while (i != this->objectList.end()) {
        if ((*i)->isToBeDeleted()) {
            auto objectPtr = (*i);
            delete objectPtr;
        } else {
            newList.push_back(*i);
        }

        i++;
    }

    this->objectList = newList;
}

Barta::ObjectManagerInterface::ObjectList Barta::BartaObjectManager::getList() noexcept {
    return this->objectList;
}
