#pragma once

#include <map>
#include "Curve.h"

namespace Phantom {
	namespace maths {
		template<typename Tval, typename Tparam>
		class Bezier :public CurveBase, public Curve<Tval, Tparam>
		{
		public:
			Bezier() : CurveBase(CurveType::kBezier) {}
			Bezier(const Tval* knots, const Tval* in_cp, const Tval* out_cp, const size_t count) :Bezier()
			{
				for (size_t i = 0; i < count; i++)
				{
					Curve<Tval, Tparam>::m_Knots.push_back(knots[i]);
					AddCtrlPoints(knots[i], in_cp[i], out_cp[i]);
				}
			}

			void AddCtrlPoints(const Tval knot, const Tval incoming_cp, const Tval outgoing_cp)
			{
				m_IncomingCtrlPoints.insert({ knot,incoming_cp });
				m_OutgoingCtrlPoints.insert({ knot,outgoing_cp });
			}
		
		private:
			std::map <Tval, Tval> m_IncomingCtrlPoints;
			std::map <Tval, Tval> m_OutgoingCtrlPoints;
		};
	}
}