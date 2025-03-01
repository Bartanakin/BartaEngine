#pragma once
#include <ListManagerConcept.h>
#include <pch.h>

namespace Barta {

template<DeleteSettable T, DeleteSettable... Ts>
class StaticObjectManager: public StaticObjectManager<T>, public StaticObjectManager<Ts...> {
public:
    StaticObjectManager():
        StaticObjectManager<T>(),
        StaticObjectManager<Ts...>() {}

    ~StaticObjectManager() {}

    using StaticObjectManager<T>::reduceDeleted;
    using StaticObjectManager<Ts...>::reduceDeleted;
    using StaticObjectManager<T>::addObject;
    using StaticObjectManager<Ts...>::addObject;
    using StaticObjectManager<T>::getList;
    using StaticObjectManager<Ts...>::getList;
};

template<DeleteSettable T>
class StaticObjectManager<T> {
public:
    StaticObjectManager() noexcept:
        objects(ListType<T>()) {}

    ~StaticObjectManager() = default;

    void addObject(
        T* object
    ) {
        this->objects.push_back(object);
    }

    void reduceDeleted() { this->objects.reduce(); }

    ListType<T>& getList(
        T* = nullptr
    ) {
        return this->objects;
    }

private:
    ListType<T> objects;
};

static_assert(ListManagerConcept<StaticObjectManager<BartaObjectInterface>, BartaObjectInterface>);
}
