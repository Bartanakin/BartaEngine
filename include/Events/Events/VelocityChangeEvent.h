#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"
#include "../../Dynamics/DynamicsAwareInterface.h"

namespace Barta {

	class DynamicsChangeEvent {
		public:
		DynamicsChangeEvent(
            DynamicsAwareInterface* dynamicsAware,
            Vector2f velocityChange
        ) noexcept:
			dynamicsAware(dynamicsAware),
            velocityChange(velocityChange)
        {}

		DynamicsAwareInterface* dynamicsAware;
		Vector2f velocityChange;
	};

	template<>
	class EventSubscriber<DynamicsChangeEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(DynamicsChangeEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<DynamicsChangeEvent> DynamicsChangeSubscriberInterface;
}

