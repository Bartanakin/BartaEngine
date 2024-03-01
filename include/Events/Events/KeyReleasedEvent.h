#pragma once
#include "../../pch.h"
#include "../BartaKeyMap.h"
#include "../TemplateEventSubscriber.h"

namespace Barta{

	class KeyReleasedEvent {
	public:
		inline KeyReleasedEvent(BartaKeyMap key) noexcept : key(key) {};

		BartaKeyMap key;
	};

	template<>
	class EventSubscriber<KeyReleasedEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(KeyReleasedEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<KeyReleasedEvent> KeyReleasedSubscriberInterface;
}

