#pragma once

#include "GVertexArray.h"
#include "../maths/maths.h"
#include "shader.h"

using namespace phantom::maths;
namespace phantom { namespace graphics {

	class Renderable
	{
	public:
		Renderable(vec3 pos, vec3 color, Shader& shader);
		inline const GVertexArray* getVAO() const { return m_Vao; }

		inline Shader& getShader() const { return m_Shader; }
		inline const vec3& getPosition() const { return m_Position; }
		inline const vec3& getColor() const { return m_Color; }

		virtual ~Renderable();
	protected:
		vec3 m_Position;
		vec3 m_Color;

		GVertexArray* m_Vao;
		Shader& m_Shader;//并非我创建的，尽量用引用。
	private:
	};

} } 