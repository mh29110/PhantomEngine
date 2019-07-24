#pragma once 
#include "SceneOjbectTypeDef.h"
#include "SceneBaseObject.h"
#include "SceneObjectSkeleton.h"

namespace Phantom {
	class Skeleton;
	class SkinBoneCountArray
	{
	public:
		SkinBoneCountArray(const unsigned short* data, const int data_size) :m_pData(data), m_szData(data_size) {};
		SkinBoneCountArray() = delete;
		~SkinBoneCountArray() { delete m_pData; };
		const unsigned short* GetData() const { return m_pData; }
		int GetVertexCount() const { return m_szData; }
	protected:
		const unsigned short * m_pData;
		const int m_szData;

	};

	class SkinBoneIndexArray
	{
	public:
		SkinBoneIndexArray(const unsigned short* data, const int data_size) :m_pData(data), m_szData(data_size) {};
		SkinBoneIndexArray() = delete;
		~SkinBoneIndexArray() { delete m_pData; };
		const unsigned short* GetData() const { return m_pData; }
		int GetDataSize() const { return m_szData; }
	protected:
		const unsigned short * m_pData;
		const int m_szData;

	};

	class SkinBoneWeightArray
	{
	public:
		SkinBoneWeightArray(const float* data, const int data_size) :m_pData(data), m_szData(data_size) {};
		SkinBoneWeightArray() = delete;
		~SkinBoneWeightArray() { delete m_pData; };
		const float* GetData() const { return m_pData; }
		int GetDataSize() const { return m_szData; }
	protected:
		const float * m_pData;
		const int m_szData;

	};


	class SceneObjectSkin : public SceneBaseObject
	{
	public:
		SceneObjectSkin() :SceneBaseObject(SceneObjectType::kSceneObjectTypeSkin) {}
		void AddBoneCountArr(std::shared_ptr<SkinBoneCountArray>&& arr) {
			m_BoneCountArr = std::move(arr);
		};
		const std::weak_ptr<SkinBoneCountArray> GetBoneCountArray()
		{
			return m_BoneCountArr;
		}
		void AddBoneIndexArr(std::shared_ptr <SkinBoneIndexArray>&& arr) {
			m_BoneIndexArr = std::move(arr);
		};
		const std::weak_ptr<SkinBoneIndexArray> GetBoneIndexArray()
		{
			return m_BoneIndexArr;
		}
		void AddBoneWeightArr(std::shared_ptr <SkinBoneWeightArray>&& arr) {
			m_BoneWeightArr = std::move(arr);
		};
		const std::weak_ptr<SkinBoneWeightArray> GetBoneWeightArray()
		{
			return m_BoneWeightArr;
		}
		void AddSkeleton(std::shared_ptr <SceneObjectSkeleton>&& ske) {
			m_Skeleton = std::move(ske);
		};
		const std::weak_ptr<SceneObjectSkeleton> GetSkeleton()
		{
			return m_Skeleton;
		}
		void ApplySkinTransform(maths::mat4x4 mat)
		{
			m_SkinMat = std::move(mat);
		}
		const maths:: mat4x4& GetSkinMatrix()
		{
			return m_SkinMat;
		}
	protected:
		//const  transform //bind-pose transforms for all bones.
		std::shared_ptr<SkinBoneCountArray>    m_BoneCountArr;
		std::shared_ptr<SkinBoneIndexArray>    m_BoneIndexArr;
		std::shared_ptr<SkinBoneWeightArray>   m_BoneWeightArr;
		std::shared_ptr<SceneObjectSkeleton>   m_Skeleton;
		maths::mat4x4                                 m_SkinMat;

		friend std::ostream& operator<<(std::ostream& out, const SceneObjectSkin& obj);

	};

}
