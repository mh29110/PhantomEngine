#pragma once 
#include <iostream>
#include <list>
namespace Phantom {

class TreeNode {
protected:
	TreeNode* m_parent;
	std::list<std::shared_ptr<TreeNode>> m_children;
protected:
	virtual void dump(std::ostream& out) const {};
public:
	virtual ~TreeNode() {};

	virtual void AppendChild(std::shared_ptr<TreeNode> && sub_node)
	{
		sub_node->m_parent = this;
		m_children.push_back(std::move(sub_node));
	}
	//friend std::ostream& operator<<(std::ostream& out, const TreeNode& node)
	//{
	//	static thread_local int32_t indent = 0;
	//	indent++;

	//	out << std::string(indent, ' ') << "Tree Node" << std::endl;
	//	out << std::string(indent, ' ') << "----------" << std::endl;
	//	node.dump(out);
	//	out << std::endl;

	//	for (const std::shared_ptr<TreeNode>& sub_node : node.m_Children) {
	//		out << *sub_node << std::endl;
	//	}

	//	indent--;

	//	return out;
	//}
};
}