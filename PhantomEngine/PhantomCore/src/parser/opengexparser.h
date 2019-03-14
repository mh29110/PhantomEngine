#include <unordered_map>
#include "OpenGEX.h"
#include "portable.h"
#include "SceneParser.h"

namespace Phantom {
    class OpengexParser : implements SceneParser
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<SceneBaseNode>> m_SceneObjects;

    private:
        void ConvertOddlStructureToSceneNode(const ODDL::Structure& structure, std::unique_ptr<SceneBaseNode>& base_node)
        {
           
        }

    public:
        OpengexParser() = default;
        virtual ~OpengexParser() = default;

        virtual std::unique_ptr<SceneBaseNode> Parse(const std::string& buf)
        {
            std::unique_ptr<SceneBaseNode> root_node (new SceneBaseNode("scene root node"));
            OGEX::OpenGexDataDescription  openGexDataDescription;

            ODDL::DataResult result = openGexDataDescription.ProcessText(buf.c_str());
            if (result == ODDL::kDataOkay)
            {
                const ODDL::Structure* structure = openGexDataDescription.GetRootStructure()->GetFirstSubnode();
                while (structure)
                {
                    ConvertOddlStructureToSceneNode(*structure, root_node);

                    structure = structure->Next();
                }
            }

            return std::move(root_node);
        }
    };
}

