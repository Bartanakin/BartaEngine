#pragma once
#include "../../pch.h"
#include"../CollisionDetectionStrategyInterface.h"
#include"../../Dynamics/TimerInterface.h"
#include "../../Geometrics/Math/MathLibraryInterface.h"

namespace Barta{
	class DynamicCollisionDetectionStrategy : public CollisionDetectionStrategyInterface{
	public:
		DynamicCollisionDetectionStrategy(std::unique_ptr<MathLibraryInterface> mathLibrary, const TimerInterface& timer);
		virtual ~DynamicCollisionDetectionStrategy() noexcept = default;

		virtual CollisionTestResult acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const override;
	private:
		const TimerInterface& timer;

		std::unique_ptr<MathLibraryInterface> mathLibrary;
	};
}

