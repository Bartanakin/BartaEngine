#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include <Collisions/CollisionTestResult/ExtendedCollisionResult.h>

namespace Barta {

    template<typename T1, typename T2>
	class CollisionEvent
	{
		public:
		CollisionEvent(const ExtendedCollisionResult<T1, T2> collisionResult, float delta_t) noexcept:
            collisionResult(std::move(collisionResult)), delta_t(delta_t) {}
        CollisionEvent(const CollisionEvent&) = delete;
        CollisionEvent(CollisionEvent&&) noexcept = default;
        CollisionEvent& operator=(const CollisionEvent&) = delete;
        ~CollisionEvent() noexcept = default;

		inline const ExtendedCollisionResult<T1, T2> getTestResult() const noexcept {
			return this->collisionResult;
		}

		inline float getDelta_t() const noexcept {
			return this->delta_t;
		}

		private:
		const ExtendedCollisionResult<T1, T2> collisionResult;
		const float delta_t;
	};
}
