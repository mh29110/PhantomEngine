#include "renderer.h"
namespace Phantom { namespace graphics {
	using namespace Phantom::maths;
	void Renderer::submit(const Renderable* renderable)
	{
		m_RenderQueue.push_back(renderable);
	}

	void Renderer::flush()
	{
		while (!m_RenderQueue.empty())
		{
			const Renderable* renderable = m_RenderQueue.front();
			renderable->getVAO()->bind();

			mat4x4 wm = mat4x4::translation(renderable->getPosition());
			renderable->getShader().setUniformMat4(MVP_NAME_M, wm);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

			renderable->getVAO()->unbind();

			m_RenderQueue.pop_front();
		}
	}
} }