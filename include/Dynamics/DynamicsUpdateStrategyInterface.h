#pragma once
#include "../pch.h"
#include "DynamicsAwareInterface.h"

namespace Barta{

	class DynamicsUpdateStrategyInterface{
	public:
		DynamicsUpdateStrategyInterface() = default;
		virtual ~DynamicsUpdateStrategyInterface() = default;

		virtual void update(DynamicsAwareInterface::DynamicsAwareList&, const float) = 0;
	};
}