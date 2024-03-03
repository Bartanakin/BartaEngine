#pragma once

#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>
#include "../../pch.h"
#include "../CheckCollisionVisitorInterface.h"
#include "../../Geometrics/BartaShapes/AABB.h"
#include "../../Dynamics/DynamicsDTO.h"

namespace Barta{

	class AABB_AABBCheckCollisionVisitor : public CheckCollisionVisitorInterface{
	public:
		AABB_AABBCheckCollisionVisitor(
			const AABB& aabb1,
			const AABB& aabb2,
			const DynamicsDTO& dynamicsDifference
		) noexcept;

		virtual CollisionTestResult checkStaticCollision(
			const MathLibraryInterface& mathLib,
			CollisionTestResultBuilder& collisionTestResultBuilder
		) const override;

		virtual CollisionTestResult checkDynamicCollision(
			const MathLibraryInterface& mathLib,
			const float delta_time,
			CollisionTestResultBuilder& collisionTestResultBuilder
		) const override;

	private:
		const AABB aabb1;
		const AABB aabb2;
		const DynamicsDTO dynamicsDifference;
	};
}

