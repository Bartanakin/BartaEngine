#pragma once
#include "HitboxInterface.h"
#include "../Geometrics/TransformableInterface.h"

namespace Barta{

	class CircleHitbox final : public HitboxInterface{
	public:
		CircleHitbox( const Circle& circle );
		~CircleHitbox() = default;

		bool isWithin( const Vector2f& position ) const override;

		CollisionTestResult intersects(
			const HitboxInterface& secondHitbox,
			const CollisionDetectionStrategyInterface& collisionDetector,
			const DynamicsDTO& dynamicsDifference
		) const override;

		std::unique_ptr<const HitboxInterface> getTransformedHitbox( const TransformableInterface& transformable ) const override;

		CollisionTestResult intersectsWithCircle(
			const Circle& secondCircle,
			const CollisionDetectionStrategyInterface& collisionDetector,
			const DynamicsDTO& dynamicsDifference
		) const override;

		CollisionTestResult intersectsWithAABB(
			const AABB& secondAABB,
			const CollisionDetectionStrategyInterface& collisionDetector,
			const DynamicsDTO& dynamicsDifference
		) const override;
	
	private:
		const Circle& getCircle() const;

		Circle circle;
	};

}
