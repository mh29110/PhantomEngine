#include <unordered_map>
#include "OpenGEX.h"
#include "common/Portable.h"
#include "interface/SceneParser.h"


namespace Phantom {
	class SceneBaseNode;
	class Scene;
    class OpengexParser : implements SceneParser
    {
    private:
		bool m_bUpIsYAxis;
    private:
		void ConvertOddlStructureToSceneNode(const ODDL::Structure & structure, std::shared_ptr<SceneBaseNode>& base_node, Scene& scene);
       
		bool CheckAvailableUniqueness(const Structure * local, const OGEX::SkinStructure* skinParent, StructureType type);
    public:
        OpengexParser() = default;
        virtual ~OpengexParser() = default;

		virtual std::unique_ptr<Scene> Parse(const std::string& buf);
       
    };
}

