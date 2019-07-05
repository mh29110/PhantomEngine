#pragma once
#include <functional>
//数值法 （牛顿法） 解多项式

namespace Phantom {namespace maths {

	template<typename Tval,typename Tparam>
	struct NewtonRapson
	{
		typedef std::function <Tval(Tparam)> nr_f;
		typedef std::function <Tval(Tparam)> nr_fprime;

		static inline Tparam Solve(Tparam x0, nr_f f, nr_fprime fprime)
		{
			Tparam x, x1 = x0;
			do {
				x = x1;
				Tval fx = f(x);
				Tval fx1 = fprime(x);
				x1 = x - (fx / fx1);
			} while (static_cast<Tval>(abs(x1 - x)) >= static_cast<Tval>(10E-6));

			return x1;
		}
	};
}}