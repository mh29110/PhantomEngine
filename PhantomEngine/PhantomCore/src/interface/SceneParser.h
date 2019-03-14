#pragma once
#include <memory>
#include <string>
#include "IInterface.h"
#include "SceneBaseNode.h"

namespace Phantom {
    IInterface SceneParser
    {
    public:
        virtual std::unique_ptr<SceneBaseNode> Parse(const std::string& buf) = 0;
    };
}

