#pragma once
#include "../../pch.h"

namespace Barta{

	class EquationInterface{
	public:

		enum class Method{
			DEFAULT = 0
		};

		enum class State{
			UNSOLVED = 0,
			NO_SOLUTIONS,
			FINITE_NO_SOLTIONS,
			INFINITE_NO_SOLUTIONS
		};

		EquationInterface() noexcept = default;
		EquationInterface( const EquationInterface& ) noexcept = default;
		EquationInterface( EquationInterface&& ) noexcept = default;
		EquationInterface& operator=( EquationInterface&& ) noexcept = default;
		virtual ~EquationInterface() noexcept = default;

		virtual void solve( const Method& method = Method::DEFAULT ) = 0;

		virtual State getState() const noexcept = 0;

		virtual std::vector<float> getSolutions() const = 0;
	};
}