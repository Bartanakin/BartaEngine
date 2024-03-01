#pragma once
#include "../../pch.h"
#include "../BartaKeyMap.h"
#include "../TemplateEventSubscriber.h"

namespace Barta{

	class KeyPressedEvent {
	public:
		inline KeyPressedEvent(BartaKeyMap key) noexcept : key(key) {};

		BartaKeyMap key;
	};

	template<>
	class EventSubscriber<KeyPressedEvent> {
		public:
        virtual ~EventSubscriber() noexcept = default;

		virtual bool handle(KeyPressedEvent& event) = 0;

		virtual bool isValid() const noexcept = 0;
	};

	typedef EventSubscriber<KeyPressedEvent> KeyPressedSubscriberInterface;
}

