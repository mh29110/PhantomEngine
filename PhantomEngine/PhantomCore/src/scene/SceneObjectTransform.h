#pragma once
#include "SceneBaseObject.h"
#include "maths/PhMaths.h"

namespace Phantom {
    class SceneObjectTransform : public SceneBaseObject
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
        friend std::ostream& operator<<(std::ostream& out, const SceneObjectTransform& obj);
    };
  
}
