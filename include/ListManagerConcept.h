#pragma once
#include <ReduceableList.h>
#include <pch.h>

namespace Barta {

template<typename T>
using ListType = ReducibleList<std::vector<T*>>;

template<typename T>
concept DeleteSettable = requires(T t) {
    { t.isToBeDeleted() } -> std::same_as<bool>;
};

template<typename ListManager, typename T>
concept ListManagerConcept = DeleteSettable<T> && requires(ListManager listManager, T object) {
    { listManager.getList(static_cast<T*>(nullptr)) } -> std::same_as<ListType<T>&>;
    { listManager.addObject(&object) };
};
}
