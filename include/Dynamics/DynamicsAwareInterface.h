#pragma once
#include "../pch.h"
#include "../Geometrics/Vector2f.h"
#include "DynamicsDTO.h"
#include "../ReduceableList.h"

namespace Barta{

	class DynamicsAwareInterface{
	public:
		DynamicsAwareInterface() = default;
		virtual ~DynamicsAwareInterface() = default;

		using DynamicsAwareList = ReducibleList<std::list<DynamicsAwareInterface*>>;

		virtual void move( const Vector2f& shift ) = 0;

		virtual void rotate(float, Vector2f) = 0;

		virtual const DynamicsDTO& getDynamicsDTO() const = 0;

		virtual void setDynamicsDTO( const DynamicsDTO& ) = 0;

		virtual bool isToBeDeleted() const = 0;
	};
}