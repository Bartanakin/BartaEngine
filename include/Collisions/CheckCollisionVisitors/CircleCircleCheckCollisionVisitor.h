#pragma once
#include "../../pch.h"
#include"../CheckCollisionVisitorInterface.h"
#include"../../Geometrics/BartaShapes/Circle.h"
#include"../../Dynamics/DynamicsDTO.h"

namespace Barta{
	class CircleCircleCheckCollisionVisitor : public CheckCollisionVisitorInterface{
	public:
		CircleCircleCheckCollisionVisitor(
			const Circle& circle1,
			const Circle& circle2,
			const DynamicsDTO& dynamicsDifference
		);
		virtual ~CircleCircleCheckCollisionVisitor();

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
		const Circle circle1;
		const Circle circle2;
		const DynamicsDTO dynamicsDifference;

		Vector2f getNormalVector() const;
	};
}

