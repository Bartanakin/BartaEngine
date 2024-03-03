#pragma once

#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include "../../pch.h"
#include"../CollisionDetectionStrategyInterface.h"
#include "../../Geometrics/Math/MathLibraryInterface.h"

namespace Barta{
	class StaticCollisionDetectionStrategy : public CollisionDetectionStrategyInterface{

	public:
		StaticCollisionDetectionStrategy(std::unique_ptr<MathLibraryInterface>);
		virtual ~StaticCollisionDetectionStrategy() noexcept = default;

		virtual CollisionTestResult acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const override;

	private:
		std::unique_ptr<MathLibraryInterface> mathLibrary;
	};
}

