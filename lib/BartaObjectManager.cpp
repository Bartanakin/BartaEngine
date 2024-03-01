#include <pch.h>
#include <BartaObjectManager.h>

Barta::BartaObjectManager::BartaObjectManager() noexcept
:   objectList({}),
    collidableList({}),
    dynamicsList({})
{}

Barta::BartaObjectManager::~BartaObjectManager() {
    auto i = this->objectList.begin();
	while( i != this->objectList.end() ){
		auto objectPtr = ( *i );
		delete objectPtr;

		i++;
	}
}

void Barta::BartaObjectManager::addNewObject( BartaObjectInterface* const newObject ){
    for (auto it = this->objectList.begin(); it != this->objectList.end(); it++) {
        if ((*it)->getZIndex() >= newObject->getZIndex()) {
            this->objectList.insert(it, newObject);

            return;
        }
    }

	this->objectList.push_back( newObject );
}

void Barta::BartaObjectManager::addCollidableObject(CollisionAwareInterface* const collidableObject) {
	this->collidableList.push_back(collidableObject);
}

const Barta::CollisionAwareInterface::CollidableList& Barta::BartaObjectManager::getCollidableList() const noexcept {
	return this->collidableList;
}

void Barta::BartaObjectManager::addDynamicsObject(DynamicsAwareInterface* const dynamicsObject) {
	this->dynamicsList.push_back(dynamicsObject);
}

Barta::DynamicsAwareInterface::DynamicsAwareList& Barta::BartaObjectManager::getDynamicsList() noexcept {
	return this->dynamicsList;
}

void Barta::BartaObjectManager::reduceDeleted(){
	this->collidableList.reduce();
	this->dynamicsList.reduce();

	auto newList = ObjectList();
	auto i = this->objectList.begin();
	while( i != this->objectList.end() ){
		if( ( *i )->isToBeDeleted() ){
			auto objectPtr = ( *i );
			delete objectPtr;
		}
		else{
			newList.push_back( *i );
		}
	
		i++;
	}

	this->objectList = newList;
}

Barta::ObjectManagerInterface::ObjectList Barta::BartaObjectManager::getList() noexcept {
	return this->objectList;
}
