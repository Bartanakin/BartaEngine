#pragma once
#include "../../pch.h"
#include "CollisionTestResult.h"
#include "../StaticCollisionAware.h"

namespace Barta {

    template<StaticCollisionAware T1, StaticCollisionAware T2>
	struct SExtendedCollisionResult {
        CollisionTestResult collisionTestResult;
        T1* object1;
        T2* object2;
	
        SExtendedCollisionResult() noexcept :
            collisionTestResult({}),
            object1(nullptr),
            object2(nullptr)
        {}
		
        // shallow copy
        SExtendedCollisionResult(const SExtendedCollisionResult& second) noexcept :
            collisionTestResult(second.collisionTestResult),
            object1(second.object1),
            object2(second.object2)
		{}
		
        SExtendedCollisionResult(
            CollisionTestResult collisionTestResult,
            T1* object1,
            T2* object2
		) noexcept :
            collisionTestResult(collisionTestResult),
            object1(object1),
            object2(object2)
		{}

        SExtendedCollisionResult& operator=(const SExtendedCollisionResult& second) noexcept {
            this->collisionTestResult = second.collisionTestResult;
            this->object1 = second.object1;
            this->object2 = second.object2;

            return *this;
        }

        bool operator==(const SExtendedCollisionResult& second) const noexcept {
            return this->collisionTestResult == second.collisionTestResult
                && (
                    (
                            static_cast<void*>(this->object1) == static_cast<void*>(second.object1) 
                        && 
                            static_cast<void*>(this->object2) == static_cast<void*>(second.object2)
                    )
                    ||
                    (
                            static_cast<void*>(this->object2) == static_cast<void*>(second.object1)
                        &&
                            static_cast<void*>(this->object1) == static_cast<void*>(second.object2)
                    )
                );
        }
	};

}