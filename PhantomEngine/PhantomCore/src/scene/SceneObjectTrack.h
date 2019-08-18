#pragma once
#include "common/Portable.h"
#include "SceneBaseObject.h"
#include "ability/IAnimatable.h"
#include "scene/SceneObjectTransform.h"
#include "maths/algorithm/Curve.h"

namespace Phantom {
	ENUM(SceneObjectTrackType)
	{
		kScalar = "SCAL"_i32,
		kVector3 = "VEC3"_i32,
		kQuoternion = "QUON"_i32,
		kMatrix = "MATX"_i32
	};

	class SceneObjectTrack :public SceneBaseObject, public IAnimatable<float>
	{
	public:
		SceneObjectTrack() = delete;
		SceneObjectTrack(std::shared_ptr<SceneObjectTransform> trans,
			std::shared_ptr<CurveBase> time,
			std::shared_ptr<CurveBase> value,
			SceneObjectTrackType type) :SceneBaseObject(SceneObjectType::kSceneObjectTypeTrack),
			m_pTransform(trans), m_Time(time), m_Value(value), m_kTrackType(type) {}

		void Update(const float time_point) final;

	private:
		template <typename Tparam>
		void UpdateTransform(const Tparam value);
		std::shared_ptr<SceneObjectTransform> m_pTransform;
		std::shared_ptr<CurveBase> m_Time;
		std::shared_ptr<CurveBase> m_Value;
		const SceneObjectTrackType m_kTrackType;
	};
	
}
