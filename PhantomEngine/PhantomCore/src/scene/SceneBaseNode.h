#pragma once 
#include <string>
#include <vector>
#include <map>

#include "TreeNode.h"
#include "maths/PhMaths.h"
#include "SceneObjectTransform.h"
#include "SceneObjectAnimation.h"
namespace Phantom {

class SceneBaseNode :public TreeNode {
protected:
	std::string m_Name;
	std::vector<std::shared_ptr<SceneObjectTransform>>					m_Transforms;
	std::map<std::string, std::shared_ptr<SceneObjectTransform>>		m_LUTtransform;

	std::map <int, std::shared_ptr<SceneObjectAnimationClip>>			m_AnimationClips;

	std::shared_ptr<SceneObjectTransform>								m_objTransform;

public:
	SceneBaseNode() {};
	SceneBaseNode(const char* name) { m_Name = name; };
	SceneBaseNode(const std::string& name) { m_Name = name; };
	SceneBaseNode(const std::string&& name) { m_Name = std::move(name); };
	virtual ~SceneBaseNode() {};

	const std::string & GetName() { return m_Name; };

	const std::shared_ptr< maths::mat4x4> GetCalculatedTransform() const
	{
		std::shared_ptr< maths::mat4x4> result(new  maths::mat4x4());

		/*if (m_objTransform)//wtf!
		{
			*result = *result * (m_objTransform->GetMatrixFirst());
		}*/

		for (auto it = m_Transforms.rbegin(); it != m_Transforms.rend(); it++)
		{
			*result = *result * ( (**it).GetMatrixFirst() );
			if (m_Transforms.size() > 1) 
				assert("nonono");
		}
		//cascading
		const SceneBaseNode* parent = static_cast <SceneBaseNode*> (m_parent);
		
		while (parent && parent->m_Name != "scene")
		{
			*result = *(parent->GetCalculatedTransformForChild())
				*  *result;
			parent = static_cast <SceneBaseNode*> (parent->m_parent);
		}
		return result;
	}

	const std::shared_ptr< maths::mat4x4> GetCalculatedTransformForChild() const
	{
		std::shared_ptr< maths::mat4x4> result(new  maths::mat4x4());

		for (auto it = m_Transforms.rbegin(); it != m_Transforms.rend(); it++)
		{
			*result = *result * ((**it).GetMatrixFirst());
		}
	
		return result;
	}

	const std::shared_ptr<std::vector<std::string>> GetTreeChain() const
	{
		std::shared_ptr<std::vector<std::string>> chain = std::make_shared< std::vector<std::string >> ();
		const SceneBaseNode* parent = static_cast <SceneBaseNode*> (m_parent);
		while (parent && parent->m_Name != "scene")
		{
			chain->push_back(parent->m_Name);
			parent = static_cast <SceneBaseNode*> (parent->m_parent);
		}

		return chain;
	}

	void AppendTransform(const char* key, const std::shared_ptr<SceneObjectTransform>& transform)
	{
		m_Transforms.push_back(transform);
		m_LUTtransform.insert({ std::string(key),transform });
	}

	void ApplyObjectTransform(const std::shared_ptr<SceneObjectTransform> && transform)
	{
		m_objTransform = std::move(transform);
	}

	const std::weak_ptr<SceneObjectTransform> GetObjectTransform()
	{
		return m_objTransform;
	}

	std::shared_ptr<SceneObjectTransform> GetTransform(const std::string& key)
	{
		auto it = m_LUTtransform.find(key);
		if (it != m_LUTtransform.end())
		{
			return it->second;
		}
		else
		{
			assert(0);
			return std::shared_ptr<SceneObjectTransform>();
		}
	}

	void AttachAnimationClip(int clip_index, std::shared_ptr<SceneObjectAnimationClip> clip)
	{
		m_AnimationClips.insert({ clip_index, clip });
	}

	const std::map <int, std::shared_ptr<SceneObjectAnimationClip>>& GetAnimationClipMap() {
		return m_AnimationClips;
	}

	friend std::ostream& operator<<(std::ostream& out, const SceneBaseNode& node)
		{
			static thread_local int32_t indent = 0;
			indent++;

			out << std::string(indent, ' ') << "Scene Node" << std::endl;
			out << std::string(indent, ' ') << "----------" << std::endl;
			out << std::string(indent, ' ') << "Name: " << node.m_Name << std::endl;
			node.dump(out);
			out << std::endl;

			for (auto sub_node : node.m_children) {
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
		}
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
