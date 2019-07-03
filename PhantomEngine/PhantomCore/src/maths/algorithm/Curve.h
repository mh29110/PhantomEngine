#pragma once
#include "common/Portable.h"


namespace Phantom {
	ENUM(CurveType) {
		kLinear = "LINE"_i32,
			kBezier = "BEZI"_i32
	};

	class CurveBase
	{
	private:
		const CurveType m_kCurveType;

	public:
		CurveBase() = delete;
		CurveBase(CurveType type) :m_kCurveType(type) {}
		virtual ~CurveBase() = default;
		CurveType GetCurveType() const { return m_kCurveType; }
	};

	template <typename Tval,typename Tparam>
	class Curve {
	protected:
		std::vector<Tval> m_Knots;
	public:
		void AddKnot(const Tval knot) {
			m_Knots.push_back(knot);
		}
	};
	
}