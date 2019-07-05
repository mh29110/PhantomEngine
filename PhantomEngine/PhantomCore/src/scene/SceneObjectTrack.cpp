#include "SceneObjectTrack.h"
#include <iostream>
#include "maths/algorithm/Linear.h"
#include "maths/algorithm/Bezier.h"
using namespace Phantom;
using namespace std;
using namespace maths;
void SceneObjectTrack::Update(const float progress)
{
	static float pg = 0;
	pg+= (progress / 1000.0f);
	pg = pg > 10.0f ? 0.0f : pg;
	if (m_pTransform)
	{
		auto time_curve_type = m_Time->GetCurveType();
		float proportion = 0.0f;//±ÈÀý
		size_t idx = 0;
		switch (time_curve_type)
		{
		case Phantom::CurveType::kLinear:
			proportion = dynamic_pointer_cast<Linear<float, float>>(m_Time)->Reverse(pg, idx);
			break;
		case Phantom::CurveType::kBezier:
			proportion = dynamic_pointer_cast<Bezier<float, float >> (m_Time)->Reserve(pg, idx);
			break;
		default:
			assert(0);
			break;
		}

		auto value_curve_type = m_Value->GetCurveType();
		switch (value_curve_type)
		{
		case Phantom::CurveType::kLinear:
			switch (m_kTrackType)
			{
			case SceneObjectTrackType::kScalar:
			{
				auto new_val = dynamic_pointer_cast<Linear<float, float>>(m_Value)->Interpolate(proportion, idx);
				UpdateTransform(new_val);
				break;
			}
			case SceneObjectTrackType::kVector3:
			{
				break;
			}
			case SceneObjectTrackType::kQuoternion:
			{
				break;
			}
			case SceneObjectTrackType::kMatrix:
			{
				auto new_val = dynamic_pointer_cast<Linear<mat4x4, float>>(m_Value)->Interpolate(proportion, idx);
				UpdateTransform(new_val);
				break;
			}
			}
			break;
		case Phantom::CurveType::kBezier:
			switch (m_kTrackType)
			{
			case SceneObjectTrackType::kScalar:
			{
				auto new_value = dynamic_pointer_cast<Bezier<float, float>>(m_Value)->Interpolate(proportion, idx);
				UpdateTransform(new_value);
				break;
			}
			case SceneObjectTrackType::kVector3:
			{
				printf("ssdfd");
				break;
			}
			case SceneObjectTrackType::kQuoternion:
			{
				printf("ssdfd");
				break;
			}
			case SceneObjectTrackType::kMatrix:
			{
				printf("ssdfd");
				break;
			}
			}
			break;
		default:
			assert(0);
			break;
		}
	}
}
template<typename Tparam>
inline void SceneObjectTrack::UpdateTransform(const Tparam value)
{
	m_pTransform->Update(value);
}
