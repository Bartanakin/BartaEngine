#pragma once
#include "../../pch.h"
#include "../../Geometrics/Vector2f.h"
#include "../TemplateEventSubscriber.h"

namespace Barta{

	class LeftClickEvent {
	public:
		inline LeftClickEvent(Vector2f position) noexcept : position(position) {};

		inline Vector2f getPosition() const noexcept { return this->position; };

	private:
		Vector2f position;
	};

	template<>
	class EventSubscriber<LeftClickEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(LeftClickEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<LeftClickEvent> LeftClickEventSubscriberInterface;
}

