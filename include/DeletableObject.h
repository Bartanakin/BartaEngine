#pragma once

namespace Barta{

	class DeletableObject{
        static const bool TRUE_DELETE;
	public:
        DeletableObject(bool* deleteWatch = nullptr) noexcept : toBeDeleted(deleteWatch) {}

		bool isToBeDeleted() const {
            if (this->toBeDeleted == nullptr) {
                return false;
            }

            return *this->toBeDeleted;
        }
        void setDeleteWatch(const bool* watch) { this->toBeDeleted = watch; }
		void markToBeDeleted() { this->toBeDeleted = &DeletableObject::TRUE_DELETE; }
    protected:
        ~DeletableObject() = default;

        const bool* toBeDeleted;
	};
}
