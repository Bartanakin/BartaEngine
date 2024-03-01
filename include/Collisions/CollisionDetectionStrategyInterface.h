#pragma once
#include "../pch.h"
#include"../Geometrics/BartaShapes/Circle.h"
#include "CheckCollisionVisitorInterface.h"

namespace Barta{
	class CollisionDetectionStrategyInterface{
	public:
		CollisionDetectionStrategyInterface() = default;
		virtual ~CollisionDetectionStrategyInterface() = default;

		virtual CollisionTestResult acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const = 0;
	};
}

