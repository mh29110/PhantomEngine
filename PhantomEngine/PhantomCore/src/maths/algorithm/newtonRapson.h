#pragma once
#include <functional>
//数值法 （牛顿法） 解多项式

namespace Phantom {namespace maths {

	template<typename T>
	struct NewtonRapson
	{
		typedef std::function <T(T)> nr_f;
		typedef std::function <T(T)> nr_fprime;

		static inline T Solve(T x0, nr_f f, nr_fprime fprime)
		{
			T x, x1 = x0;
			do {
				x = x1;
				T fx = f(x);
				T fx1 = fprime(x);
				x1 = x - (fx / fx1);
			} while (std::abs(x1 - x) >= 10E-6);
			return x1;
		}
	};
}}