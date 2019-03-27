#pragma once 
#include <string>
#include <vector>
#include "TreeNode.h"
#include "PhMaths.h"
#include "SceneObjectTransform.h"
namespace Phantom {

class SceneBaseNode :public TreeNode {
protected:
	std::string m_Name;
	std::vector<std::shared_ptr<SceneObjectTransform>> m_Transforms;
public:
	SceneBaseNode() {};
	SceneBaseNode(const char* name) { m_Name = name; };
	SceneBaseNode(const std::string& name) { m_Name = name; };
	SceneBaseNode(const std::string&& name) { m_Name = std::move(name); };
	virtual ~SceneBaseNode() {};

	const std::shared_ptr< maths::mat4x4> GetCalculatedTransform() const
	{
		std::shared_ptr< maths::mat4x4> result(new  maths::mat4x4());
		for (auto it = m_Transforms.rbegin(); it != m_Transforms.rend(); it++)
		{
			*result = *result * (**it).GetMatrix();
		}
		return result;
	}
	void AppendTransform(const char* key, const std::shared_ptr<SceneObjectTransform>& transform)
	{
		m_Transforms.push_back(transform);
	}
	/*friend std::ostream& operator<<(std::ostream& out, const BaseSceneNode& node)
		{
			static thread_local int32_t indent = 0;
			indent++;

			out << std::string(indent, ' ') << "Scene Node" << std::endl;
			out << std::string(indent, ' ') << "----------" << std::endl;
			out << std::string(indent, ' ') << "Name: " << node.m_strName << std::endl;
			node.dump(out);
			out << std::endl;

			for (auto sub_node : node.m_Children) {
				out << *sub_node << std::endl;
			}

			for (auto trans : node.m_Transforms) {
				out << *trans << std::endl;
			}

			for (auto anim_clip : node.m_AnimationClips) {
				out << *anim_clip.second << std::endl;
			}

			indent--;

			return out;
		}*/
};


template <typename T>
class SceneNode : public SceneBaseNode {
    protected:
        std::string m_keySceneObject;

    protected:
        virtual void dump(std::ostream& out) const 
        { 
            out << m_keySceneObject << std::endl;
        };

    public:
        using SceneBaseNode::SceneBaseNode;
        SceneNode() = default;

        void AddSceneObjectRef(const std::string& key) { m_keySceneObject = key; };

        const std::string& GetSceneObjectRef() { return m_keySceneObject; };
};

typedef SceneBaseNode SceneEmptyNode;

}
