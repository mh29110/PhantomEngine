#pragma once
#include <memory>
#include <string>
#include "IInterface.h"
#include "SceneBaseNode.h"
#include "Scene.h"

namespace Phantom {
    IInterface SceneParser
    {
    public:
        virtual std::unique_ptr<Scene> Parse(const std::string& buf) = 0;
    };
}

