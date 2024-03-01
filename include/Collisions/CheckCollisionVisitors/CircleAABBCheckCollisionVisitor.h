#pragma once
#include "../../pch.h"
#include "../CheckCollisionVisitorInterface.h"
#include "../../Geometrics/BartaShapes/AABB.h"
#include "../../Geometrics/BartaShapes/Circle.h"
#include "../../Dynamics/DynamicsDTO.h"

namespace Barta{

	class CircleAABBCheckCollisionVisitor : public CheckCollisionVisitorInterface{
	public:
		CircleAABBCheckCollisionVisitor(
			const Circle& circle,
			const AABB& aabb,
			const DynamicsDTO& dynamicsDifference
		);
		virtual ~CircleAABBCheckCollisionVisitor();

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
		const Circle circle;
		const AABB aabb;
		const DynamicsDTO dynamicsDifference;
		const AABB expandedAABB;

		Vector2f matchCornerCenter(AABB::VoronoiRegion regionMask, const AABB& aabb) const;
		Vector2f calculateNormVector(const float delta_time) const;
	};
}

