#pragma once
#include <Dynamics/UpdateStrategy/UpdateStrategyConcept.h>
#include <Dynamics/UpdateStrategy/UpdateStrategyManagerConcept.h>
#include <ListManagerConcept.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {

template<typename UpdateStrategy, typename ObjectType, typename... Rest>
class UpdateStrategyManager: public UpdateStrategyManager<UpdateStrategy, ObjectType>, public UpdateStrategyManager<Rest...> {
public:
    template<typename UpdateStrategyForConstructor, typename... RestForConstructor>
        requires UpdateStrategyConcept<UpdateStrategyForConstructor, ObjectType> explicit UpdateStrategyManager(
        UpdateStrategyForConstructor updateStrategyForConstructor,
        RestForConstructor... restForConstructor
    ) noexcept:
        UpdateStrategyManager<UpdateStrategy, ObjectType>(std::forward<UpdateStrategyForConstructor>(updateStrategyForConstructor)),
        UpdateStrategyManager<Rest...>(std::forward<RestForConstructor...>(restForConstructor...)) {}

    template<typename ListManager>
    void prepare(
        ListManager listManager,
        float time
    ) {
        UpdateStrategyManager<UpdateStrategy, ObjectType>::template prepare(listManager, time);
        UpdateStrategyManager<Rest...>::template prepare(listManager, time);
    }

    template<typename ListManager>
    void update(
        ListManager listManager,
        bool doForward
    ) {
        UpdateStrategyManager<UpdateStrategy, ObjectType>::template update(listManager, doForward);
        UpdateStrategyManager<Rest...>::template update(listManager, doForward);
    }
};

template<typename UpdateStrategy, DynamicsAwareConcept ObjectType>
    requires UpdateStrategyConcept<UpdateStrategy, ObjectType> class UpdateStrategyManager<UpdateStrategy, ObjectType> {
public:
    explicit UpdateStrategyManager(
        UpdateStrategy updateStrategy
    ) noexcept:
        updateStrategy(std::move(updateStrategy)) {}

    template<typename ListManager>
        requires ListManagerConcept<ListManager, ObjectType> void prepare(
        ListManager listManager,
        float time
    ) {
        for (auto object: listManager.getList(static_cast<ObjectType*>(nullptr))) {
            this->updateStrategy.prepare(*object, time);
        }
    }

    template<typename ListManager>
        requires ListManagerConcept<ListManager, ObjectType> void update(
        ListManager listManager,
        bool doForward
    ) {
        for (auto object: listManager.getList(static_cast<ObjectType*>(nullptr))) {
            this->updateStrategy.update(*object, doForward);
        }
    }

private:
    UpdateStrategy updateStrategy;
};

}
