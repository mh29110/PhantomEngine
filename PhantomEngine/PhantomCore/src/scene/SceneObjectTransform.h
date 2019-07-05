#pragma once
#include "SceneBaseObject.h"
#include "maths/PhMaths.h"
#include "ability/IAnimatable.h"

namespace Phantom {
    class SceneObjectTransform : public SceneBaseObject, implements IAnimatable<float>
    {
        protected:
            maths::mat4x4 m_matrix;
            bool m_bSceneObjectOnly;

        public:
            SceneObjectTransform() : SceneBaseObject(SceneObjectType::kSceneObjectTypeTransform)
            {  }
			SceneObjectTransform(const maths::mat4x4& matrix, const bool object_only = false) : SceneObjectTransform()
			{
				m_matrix = matrix; 
				m_bSceneObjectOnly = object_only;
			}
			const maths::mat4x4& GetMatrix() { return m_matrix; }

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
				m_matrix = amount;
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
				MatrixTranslation(m_matrix, amount, 0.0f, 0.0f);
				break;
			case 'y':
				MatrixTranslation(m_matrix, 0.0f, amount, 0.0f);
				break;
			case 'z':
				MatrixTranslation(m_matrix, 0.0f, 0.0f, amount);
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
			MatrixTranslation(m_matrix, x, y, z);
			m_bSceneObjectOnly = object_only;
		}

		void Update(const float amount) final
		{
			switch (m_Kind) {
			case 'x':
				MatrixTranslation(m_matrix, amount, 0.0f, 0.0f);
				break;
			case 'y':
				MatrixTranslation(m_matrix, 0.0f, amount, 0.0f);
				break;
			case 'z':
				MatrixTranslation(m_matrix, 0.0f, 0.0f, amount);
				break;
			default:
				assert(0);
			}
		}

		void Update(const maths::vec3 amount)
		{
			MatrixTranslation(m_matrix, amount.x, amount.y, amount.z);
		}
	};
}
