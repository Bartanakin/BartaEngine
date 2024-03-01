#pragma once
#include "../pch.h"
#include "../Dynamics/DynamicsAwareInterface.h"
#include "../Hitbox/HitboxAwareInterface.h"
#include "../ReduceableList.h"

namespace Barta {

	class CollisionAwareInterface:public HitboxAware, public DynamicsAwareInterface {
		public:
		inline CollisionAwareInterface() = default;
		inline virtual ~CollisionAwareInterface() = default;

		using CollidableList = ReducibleList<std::list<CollisionAwareInterface*>>;

	};

}
