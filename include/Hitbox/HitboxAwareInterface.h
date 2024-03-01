#pragma once
#include "../pch.h"
#include "HitboxInterface.h"
#include "../Geometrics/TransformableInterface.h"

namespace Barta{

	class HitboxAware{
	public:
		HitboxAware() = default;
		virtual ~HitboxAware() = default;

		virtual std::unique_ptr<const HitboxInterface> getHitbox() const = 0;
	};
}

