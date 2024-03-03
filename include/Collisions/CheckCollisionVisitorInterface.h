#pragma once
#include "../pch.h"
#include "../Dynamics/TimerInterface.h"
#include "../Geometrics/Math/MathLibraryInterface.h"
#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>

namespace Barta{
	class CheckCollisionVisitorInterface{
	public:
		CheckCollisionVisitorInterface() = default;
		virtual ~CheckCollisionVisitorInterface() = default;

		virtual CollisionTestResult checkStaticCollision(
			const MathLibraryInterface& mathLib,
			CollisionTestResultBuilder& collisionTestResultBuilder
		) const = 0;

		virtual CollisionTestResult checkDynamicCollision(
			const MathLibraryInterface& mathLib,
			const float delta_time,
			CollisionTestResultBuilder& collisionTestResultBuilder
		) const = 0;
	};
}
