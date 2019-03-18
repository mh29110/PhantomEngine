#pragma once
#include "SceneBaseNode.h"
#include "SceneObjectGeometry.h"
#include "GfxStruct.h"
#include "PhMaths.h"


namespace Phantom
{
	class SceneGeometryNode : public SceneNode<SceneObjectGeometry>
	{
	protected:
		bool        m_bVisible;
		bool        m_bShadow;
		bool        m_bMotionBlur;
		std::vector<std::string> m_Materials;
		void*       m_pRigidBody = nullptr;

	protected:
		virtual void dump(std::ostream& out) const
		{
			SceneNode::dump(out);
			out << "Visible: " << m_bVisible << std::endl;
			out << "Shadow: " << m_bShadow << std::endl;
			out << "Motion Blur: " << m_bMotionBlur << std::endl;
			out << "Material(s): " << std::endl;
			for (auto material : m_Materials) {
				out << material << std::endl;
			}
		};

	public:
		using SceneNode::SceneNode;

		void SetVisibility(bool visible) { m_bVisible = visible; };
		const bool Visible() { return m_bVisible; };
		void SetIfCastShadow(bool shadow) { m_bShadow = shadow; };
		const bool CastShadow() { return m_bShadow; };
		void SetIfMotionBlur(bool motion_blur) { m_bMotionBlur = motion_blur; };
		const bool MotionBlur() { return m_bMotionBlur; };
		using SceneNode::AddSceneObjectRef;
		void AddMaterialRef(const std::string& key) { m_Materials.push_back(key); };
		void AddMaterialRef(const std::string&& key) { m_Materials.push_back(std::move(key)); };
		std::string GetMaterialRef(const size_t index)
		{
			if (index < m_Materials.size())
				return m_Materials[index];
			else
				return std::string("default");
		};

		const std::shared_ptr< maths::mat4x4> GetCalculatedTransform() const
		{
			std::shared_ptr< maths::mat4x4> result(new  maths::mat4x4());
			maths::mat4x4 mu(1.0f);
			mu = mu.scale(maths::vec3(1.0f,1.5f,1.0f));
			*result = *result * mu ;
			return result;
		}

		void LinkRigidBody(void* rigidBody)
		{
			m_pRigidBody = rigidBody;
		}

		void* UnlinkRigidBody()
		{
			void* rigidBody = m_pRigidBody;
			m_pRigidBody = nullptr;

			return rigidBody;
		}

		void* RigidBody() { return m_pRigidBody; }
	};
}