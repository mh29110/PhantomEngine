#include "Classes.h"

using namespace rtti;

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(Component, Collider)
CLASS_DEFINITION(Collider, BoxCollider)
CLASS_DEFINITION(Component, RenderImage)