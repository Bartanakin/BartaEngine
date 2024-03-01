#pragma once
#include "../../pch.h"
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"

namespace Barta{

	class MouseMoveEvent {
	public:
		inline MouseMoveEvent(Vector2f position) noexcept : position(position) {};

		inline Vector2f getPosition() const noexcept { return this->position; };

	private:
		Vector2f position;
	};
}

SUBSCRIBER_INTERFACE_DEFINITION(Barta::MouseMoveEvent);

namespace Barta{
    typedef EventSubscriber<MouseMoveEvent> MouseMoveSubscriberInterface;
}

