#pragma once
#include "../pch.h"
#include "DynamicsUpdateStrategyInterface.h"

namespace Barta{

	class ConstVelocityDynamicsUpdateStrategy : public DynamicsUpdateStrategyInterface{
	public:
		ConstVelocityDynamicsUpdateStrategy() noexcept = default;

		virtual ~ConstVelocityDynamicsUpdateStrategy() noexcept = default;
		
		virtual void update(DynamicsAwareInterface::DynamicsAwareList& objectList, const float deltaTime) override;

	};
}