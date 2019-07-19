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

		//寻找time的落点区间
		virtual Tparam Reverse(Tval t, size_t& idx) const final
		{
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

			for (size_t i = 1;i<Curve<Tval,Tparam>::m_Knots.size();i++)
			{
				if (t >= Curve<Tval, Tparam>::m_Knots[i])
					continue;
				t0 = Curve<Tval, Tparam>::m_Knots[i - 1];
				t1 = Curve<Tval, Tparam>::m_Knots[i];
				idx = i;
				break;
			}
			return Tparam((t - t0) / (t1 - t0));
		}

		virtual Tval Interpolate(Tparam s, const size_t index) const final
		{
			return 0;
		}
	};

	template<>
	class Linear<mat4x4, float> : public CurveBase, public Curve<mat4x4, float>
	{
	public:
		Linear() : CurveBase(CurveType::kLinear) {}
		Linear(const std::vector<mat4x4> knots)
			: Linear()
		{
			Curve<mat4x4, float>::m_Knots = knots;
		}

		Linear(const mat4x4* knots, const size_t count)
			: Linear()
		{
			for (size_t i = 0; i < count; i++)
			{
				Curve<mat4x4, float>::m_Knots.push_back(knots[i]);
			}
		}

		virtual float Reverse(mat4x4 v, size_t& index) const final
		{
			float result = 0.0f;
			assert(0);

			return result;
		}

		virtual mat4x4 Interpolate(float s, const size_t index) const final
		{
			mat4x4 result(1.0f);
			if (Curve<mat4x4, float>::m_Knots.size() == 0)
				return result;
			else if (Curve<mat4x4, float>::m_Knots.size() == 1)
				return Curve<mat4x4, float>::m_Knots[0];
			else if (Curve<mat4x4, float>::m_Knots.size() < index + 1)
				return Curve<mat4x4, float>::m_Knots.back();
			else if (index == 0)
				return Curve<mat4x4, float>::m_Knots.front();
			else
			{
				auto v1 = Curve<mat4x4, float>::m_Knots[index - 1];
				auto v2 = Curve<mat4x4, float>::m_Knots[index];

				vec3 translation1, translation2;
				vec3 scalar1, scalar2;
				vec3 rotation1, rotation2;

				Matrix4X4fDecompose(v1, rotation1, scalar1, translation1);
				Matrix4X4fDecompose(v2, rotation2, scalar2, translation2);

				// Interpolate tranlation
				vec3 translation =  translation1 * (1.0f - s)+  translation2*s;
				// Interpolate scalar 
				vec3 scalar =   scalar1 *(1.0f - s) +  scalar2*s;
				// Interpolate rotation
				vec3 rotation =  rotation1 * (1.0f - s) +   rotation2 * s;

				// compose the interpolated matrix
				Matrix4X4fCompose(result, rotation, scalar, translation);
			}
			return result;
		}
	};

}}
