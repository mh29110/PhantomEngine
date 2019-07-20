#pragma once 
#include "SceneOjbectTypeDef.h"
#include "SceneBaseObject.h"
#include "SceneObjectTransform.h"
#include "SceneBaseNode.h"
namespace Phantom {

	class BoneNode :public SceneBaseNode
	{
	public :
		BoneNode(const std::string& name) :SceneBaseNode(name) {}
	};

	class SkeletonBoneRefArray
	{
	public:
		SkeletonBoneRefArray(const int count):m_BoneCount(count) {};
		void AppendBone(const std::shared_ptr<BoneNode>& bone)
		{
			m_BoneNodeArr.push_back(bone);
		}
	protected:
		int m_BoneCount;
		std::vector<std::shared_ptr<BoneNode>> m_BoneNodeArr;
	};


	class SceneObjectSkeleton : public SceneBaseObject
	{
	public:
		SceneObjectSkeleton():SceneBaseObject(SceneObjectType::kSceneObjectTypeSkeleton) {}
		
		void ApplyTransform(const std::shared_ptr<SceneObjectTransform>&& transform);

		void ApplyBoneRefArr(const std::shared_ptr<SkeletonBoneRefArray>&& boneRefArr)
		{
			m_BoneRefArr = std::move(boneRefArr);
		}

	protected:
		std::shared_ptr<SceneObjectTransform>       m_Transform;
		std::shared_ptr<SkeletonBoneRefArray>       m_BoneRefArr;

		friend std::ostream& operator<<(std::ostream& out, const SceneObjectSkeleton& obj);

	};

}
