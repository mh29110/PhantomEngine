#pragma once 
#include "SceneOjbectTypeDef.h"
#include "SceneBaseObject.h"
#include "SceneObjectTransform.h"
#include "SceneBaseNode.h"
namespace Phantom {

	class SceneBoneNode :public SceneBaseNode
	{
	public :
		SceneBoneNode(const std::string& name) :SceneBaseNode(name) {}
	};

	class SkeletonBoneRefArray
	{
	public:
		SkeletonBoneRefArray(const int count):m_BoneCount(count) {};
		void AppendBone(const std::shared_ptr<SceneBoneNode>& bone)
		{
			m_BoneNodeArr.push_back(bone);
		}
		const std::vector<std::shared_ptr<SceneBoneNode>>& GetBoneNodeRefArr()
		{
			return m_BoneNodeArr;
		}
	protected:
		int m_BoneCount;
		std::vector<std::shared_ptr<SceneBoneNode>> m_BoneNodeArr;
	};


	class SceneObjectSkeleton : public SceneBaseObject
	{
	public:
		SceneObjectSkeleton() :SceneBaseObject(SceneObjectType::kSceneObjectTypeSkeleton) {}

		void ApplyTransform(const std::shared_ptr<SceneObjectTransform>&& transform);

		void ApplyBoneRefArr(const std::shared_ptr<SkeletonBoneRefArray>&& boneRefArr)
		{
			m_BoneRefArr = std::move(boneRefArr);
		}

		const std::weak_ptr<SceneObjectTransform> getTransform()
		{
			return m_Transform;
		}
		const std::weak_ptr<SkeletonBoneRefArray> GetBoneRefArr()
		{
			return m_BoneRefArr;
		}

	protected:
		std::shared_ptr<SceneObjectTransform>       m_Transform;
		std::shared_ptr<SkeletonBoneRefArray>       m_BoneRefArr;

		friend std::ostream& operator<<(std::ostream& out, const SceneObjectSkeleton& obj);

	};

}
