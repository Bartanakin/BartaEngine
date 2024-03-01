#pragma once
#include "Geometrics/TransformableInterface.h"
#include "Graphics/BartaSprite.h"

namespace Barta{

	class BartaObjectInterface {
	public:
        virtual ~BartaObjectInterface() noexcept = default;

		virtual bool isToBeDeleted() const = 0;

		virtual const TransformableInterface& getTransformable() const = 0;

		virtual const BartaSprite* getResource() noexcept = 0;

        virtual int getZIndex() const = 0;
	};
}
