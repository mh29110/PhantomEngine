#pragma once
#include "Curve.h"
namespace Phantom{ namespace maths{

	template<typename Tval, typename Tparam>
	class Linear :public CurveBase, public Curve<Tval, Tparam>
	{
	public:
		Linear() : CurveBase(CurveType::kLinear) {}
		Linear(const Tval* knots, const size_t count) : Linear() {
			for (size_t i = 0; i < count; i++)
			{
				Curve<Tval, Tparam>::m_Knots.push_back(knots[i]);
			}
		}
	};



}}