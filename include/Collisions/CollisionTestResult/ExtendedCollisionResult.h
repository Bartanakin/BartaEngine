#pragma once
#include "../../pch.h"
#include "CollisionTestResult.h"
#include "../CollisionAware.h"

namespace Barta {

    template<CollisionAware T1, CollisionAware T2>
	struct ExtendedCollisionResult {
        CollisionTestResult collisionTestResult;
        T1* object1;
        T2* object2;
	
        ExtendedCollisionResult() noexcept :
            collisionTestResult({}),
            object1(nullptr),
            object2(nullptr)
        {}
		
        // shallow copy
        ExtendedCollisionResult(const ExtendedCollisionResult& second) noexcept :
            collisionTestResult(second.collisionTestResult),
            object1(second.object1),
            object2(second.object2)
		{}
		
        ExtendedCollisionResult(
            CollisionTestResult collisionTestResult,
            T1* object1,
            T2* object2
		) noexcept :
            collisionTestResult(collisionTestResult),
            object1(object1),
            object2(object2)
		{}

        ExtendedCollisionResult& operator=(const ExtendedCollisionResult& second) noexcept {
            this->collisionTestResult = second.collisionTestResult;
            this->object1 = second.object1;
            this->object2 = second.object2;

            return *this;
        }

        bool operator==(const ExtendedCollisionResult& second) const noexcept {
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