#pragma once
#include <glad/glad.h>
#include "renderable.h"
#include "../maths/maths.h"
#include <deque>

extern const char* MVP_NAME_M;
extern const char* MVP_NAME_V;
extern const char* MVP_NAME_P;

namespace phantom { namespace graphics {

	class Renderer
	{
	public:
		virtual void submit(const Renderable* renderable);
		virtual void flush();
	private:
		std::deque<const Renderable*> m_RenderQueue;
	};

} } 