#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include "../../Collisions/CollcionTestResult/SExtendedCollisionResult.h"

namespace Barta {

    template<typename T1, typename T2>
	class SCollisionEvent 
	{
		public:
		SCollisionEvent(const SExtendedCollisionResult<T1, T2> collisionResuslt, float delta_t) noexcept:
			collisionResuslt(std::move(collisionResuslt)), delta_t(delta_t) {}
        SCollisionEvent(const SCollisionEvent&) = delete;
        SCollisionEvent(SCollisionEvent&&) noexcept = default;
        SCollisionEvent& operator=(const SCollisionEvent&) = delete;
        ~SCollisionEvent() noexcept = default;

		inline const SExtendedCollisionResult<T1, T2> getTestResult() const noexcept {
			return this->collisionResuslt;
		}

		inline float getDelta_t() const noexcept {
			return this->delta_t;
		}

		private:
		const SExtendedCollisionResult<T1, T2> collisionResuslt;
		const float delta_t;
	};
}
