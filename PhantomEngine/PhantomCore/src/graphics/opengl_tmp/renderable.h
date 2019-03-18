#pragma once

#include "GVertexArray.h"
#include "../maths/PhMaths.h"
#include "shader.h"


namespace Phantom { namespace graphics {
	class Renderable
	{
	public:
		Renderable(Phantom::maths::vec3 pos, Phantom::maths::vec3 color, Shader& shader);
		inline const GVertexArray* getVAO() const { return m_Vao; }

		inline Shader& getShader() const { return m_Shader; }
		inline const Phantom::maths::vec3& getPosition() const { return m_Position; }
		inline const Phantom::maths::vec3& getColor() const { return m_Color; }

		virtual ~Renderable();
	protected:
		Phantom::maths::vec3 m_Position;
		Phantom::maths::vec3 m_Color;

		GVertexArray* m_Vao;
		Shader& m_Shader;//并非我创建的，尽量用引用。
	private:
	};

} } 