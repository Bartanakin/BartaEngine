#pragma once
#include "../pch.h"
#include "../Dynamics/DynamicsAwareInterface.h"
#include "../Hitbox/HitboxAwareInterface.h"
#include "../ReduceableList.h"

namespace Barta {

	class CollisionAwareInterface:
        public virtual HitboxAware,
        public virtual DynamicsAwareInterface
    {
		public:
		inline CollisionAwareInterface() = default;
		inline virtual ~CollisionAwareInterface() = default;
	};

}
