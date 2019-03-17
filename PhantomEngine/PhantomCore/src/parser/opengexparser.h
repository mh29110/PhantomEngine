#include <unordered_map>
#include "OpenGEX.h"
#include "Portable.h"
#include "SceneParser.h"
#include "SceneGeometryNode.h"
#include "SceneObjectGeometry.h"
#include "SceneObjectMaterial.h"
#include "SceneObjectTexture.h"
#include "Scene.h"

namespace Phantom {
    class OpengexParser : implements SceneParser
    {
    private:
    private:
		void ConvertOddlStructureToSceneNode(const ODDL::Structure & structure, std::shared_ptr<SceneBaseNode>& base_node, Scene& scene);
       

    public:
        OpengexParser() = default;
        virtual ~OpengexParser() = default;

		virtual std::unique_ptr<Scene> Parse(const std::string& buf);
       
    };
}

