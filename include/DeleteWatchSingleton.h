#pragma once
#include "pch.h"

namespace Barta {
    class DeleteWatchSingleton {
    private:
        static DeleteWatchSingleton* instance;

        explicit DeleteWatchSingleton() noexcept = default;
    public:
        DeleteWatchSingleton(const DeleteWatchSingleton&) noexcept = delete;
        DeleteWatchSingleton(DeleteWatchSingleton&&) noexcept = delete;
        DeleteWatchSingleton& operator=(const DeleteWatchSingleton&) noexcept = delete;
        DeleteWatchSingleton& operator=(DeleteWatchSingleton&&) noexcept = delete;

        static DeleteWatchSingleton& getInstance();

        bool isToBeDeleted(size_t id);

        void setToBeDeleted(size_t id, bool value);
    private:
        std::vector<bool> watches;
    };
}
