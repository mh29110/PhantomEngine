#pragma once

#include <map>
#include "Curve.h"
#include "maths/algorithm/newtonRapson.h"

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

			virtual Tparam Reserve(Tval t, size_t& idx) const final {
				//1. find the section 
				Tval t0 = 0, t1 = 0;
				if (Curve<Tval, Tparam> ::m_Knots.size() < 2) //assert
				{
					return 0;
				}
				if (t <= Curve<Tval, Tparam>::m_Knots.front()) //before the start point.
				{
					idx = 0;
					return 0;
				}
				if (t >= Curve<Tval, Tparam>::m_Knots.back())// after the end point.
				{
					idx = Curve<Tval, Tparam>::m_Knots.size();
					return 1;
				}
				for (size_t i = 1; i < Curve<Tval, Tparam>::m_Knots.size(); i++)
				{
					if (t >= Curve<Tval, Tparam>::m_Knots[i])
						continue;
					t0 = m_Knots[i - 1];
					t1 = m_Knots[i];
					idx = i;
					break;
				}
				//2. solve the proportion in the section
				Tval c0, c1; //control points in the section

				//sequence of points : t0 --- c0 (outgoing)  --- c1 (incoming) ---- t1;
				c0 = m_OutgoingCtrlPoints.find(t0)->second;
				c1 = m_IncomingCtrlPoints.find(t1)->second;

				typename maths::NewtonRapson<Tval, Tparam>::nr_f f= [t1, t0, c1, c0, t](Tparam s) {
					return (t1 - 3.0f * c1 + 3.0f * c0 - t0) * pow(s, 3.0f)
						+ 3.0f * (c1 - 2.0f * c0 + t0) * pow(s, 2.0f)
						+ 3.0f * (c0 - t0) * s
						+ t0 - t;
				};
				typename NewtonRapson<Tval, Tparam>::nr_fprime fprime = [t1, t0, c1, c0](Tparam s) {
					return 3.0f * (t1 - 3.0f * c1 + 3.0f * c0 - t0) * pow(s, 2.0f)
						+ 6.0f * (c1 - 2.0f * c0 + t0) * s
						+ 3.0f * (c0 - t0);
				};


				return NewtonRapson<Tval, Tparam>::Solve(0.5f, f, fprime);
			}
		
			virtual Tval Interpolate(Tparam s, const size_t index) const final
			{
				if (Curve<Tval, Tparam>::m_Knots.size() == 0)
					return 0;
				else if (Curve<Tval, Tparam>::m_Knots.size() == 1)
					return Curve<Tval, Tparam>::m_Knots[0];
				else if (Curve<Tval, Tparam>::m_Knots.size() < index + 1)
					return Curve<Tval, Tparam>::m_Knots.back();
				else if (index == 0)
					return Curve<Tval, Tparam>::m_Knots.front();
				else
				{
					auto t1 = Curve<Tval, Tparam>::m_Knots[index - 1];
					auto t2 = Curve<Tval, Tparam>::m_Knots[index];

					Tval c1, c2;
					c1 = m_OutgoingCtrlPoints.find(t1)->second;
					c2 = m_IncomingCtrlPoints.find(t2)->second;

					return (t2 - 3.0f * c2 + 3.0f * c1 - t1) * pow(s, 3.0f)
						+ 3.0f * (c2 - 2.0f * c1 + t1) * pow(s, 2.0f)
						+ 3.0f * (c1 - t1) * s
						+ t1;
				}
			}
		private:
			std::map <Tval, Tval> m_IncomingCtrlPoints;
			std::map <Tval, Tval> m_OutgoingCtrlPoints;
		};
	}
}