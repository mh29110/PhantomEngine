#pragma once 
#include <string>
namespace Phantom {

class SceneBaseNode :public TreeNode {
protected:
	std::string m_Name;
};
}