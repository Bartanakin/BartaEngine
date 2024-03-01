#pragma once
#include "../Events/VelocityChangeEvent.h"

namespace Barta {

	class DynamicsChangeSubscriber: public DynamicsChangeSubscriberInterface {
		public:

		DynamicsChangeSubscriber() = default;
		~DynamicsChangeSubscriber() = default;

		bool handle(DynamicsChangeEvent& event) override;

		bool isValid() const noexcept override;

		private:
	};

}