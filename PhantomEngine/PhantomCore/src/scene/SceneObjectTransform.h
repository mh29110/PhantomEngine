﻿#pragma once
#include "SceneBaseObject.h"
#include "maths/PhMaths.h"
#include "ability/IAnimatable.h"

//The Transform structure holds one or more 4x4 transformation matrices.In the cases that a
//Transform structure is contained inside any type of node structure, a Texture structure, or a Skin
//structure, it must contain a single matrix.In the case that a Transform structure is contained inside a
//Skeleton structure, is must contain an array of matrices with one entry for each bone referenced by
//the skeleton.
namespace Phantom {
    class SceneObjectTransform : public SceneBaseObject, implements IAnimatable<float>
    {
        protected:
			std::vector< maths::mat4x4 > m_matrix;
            bool m_bSceneObjectOnly;

        public:
            SceneObjectTransform() : SceneBaseObject(SceneObjectType::kSceneObjectTypeTransform)
            {
				//todo  //md skeleton extra +1 . xxxxx
				if (m_matrix.size() == 0)
				{
					maths::mat4x4 m;
					m.identity();
					m_matrix.push_back(m);
				}
			}
			SceneObjectTransform(const maths::mat4x4& matrix, const bool object_only = false) : SceneBaseObject(SceneObjectType::kSceneObjectTypeTransform)
			{
				m_matrix.push_back(matrix); 
				m_bSceneObjectOnly = object_only;
			}
			const maths::mat4x4& GetMatrix() { return m_matrix[0]; }

			void Update(const float amount)
			{
				// should not be used.
				assert(0);
			}

			void Update(const maths::vec3 amount)
			{
				// should not be used.
				assert(0);
			}

			virtual void Update(const maths::mat4x4 amount) final
			{
				m_matrix[0] = amount;
			}

			void AppendMatrix(const maths::mat4x4 mat)
			{
				m_matrix.push_back(mat);
			}

        friend std::ostream& operator<<(std::ostream& out, const SceneObjectTransform& obj);
    };
  
	class SceneObjectTranslation : public SceneObjectTransform
	{
	private:
		char m_Kind = 0; // 0 for all ; x/y/z single

	public:
		SceneObjectTranslation() { m_Type = SceneObjectType::kSceneObjectTypeTranslate; }
		SceneObjectTranslation(const char axis, const float amount, const bool object_only = false)
			: SceneObjectTranslation()
		{
			m_Kind = axis;

			switch (axis) {
			case 'x':
				MatrixTranslation(m_matrix[0], amount, 0.0f, 0.0f);
				break;
			case 'y':
				MatrixTranslation(m_matrix[0], 0.0f, amount, 0.0f);
				break;
			case 'z':
				MatrixTranslation(m_matrix[0], 0.0f, 0.0f, amount);
				break;
			default:
				assert(0);
			}

			m_bSceneObjectOnly = object_only;
		}
		SceneObjectTranslation(const float x, const float y, const float z, const bool object_only = false)
			: SceneObjectTranslation()
		{
			m_Kind = 0;
			MatrixTranslation(m_matrix[0], x, y, z);
			m_bSceneObjectOnly = object_only;
		}

		void Update(const float amount) final
		{
			switch (m_Kind) {
			case 'x':
				MatrixTranslation(m_matrix[0], amount, 0.0f, 0.0f);
				break;
			case 'y':
				MatrixTranslation(m_matrix[0], 0.0f, amount, 0.0f);
				break;
			case 'z':
				MatrixTranslation(m_matrix[0], 0.0f, 0.0f, amount);
				break;
			default:
				assert(0);
			}
		}

		void Update(const maths::vec3 amount)
		{
			MatrixTranslation(m_matrix[0], amount.x, amount.y, amount.z);
		}
	};
}
