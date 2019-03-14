#pragma once 
#include "SceneOjbectTypeDef.h"
#include "guid.hpp"
namespace Phantom {
	using namespace xg;
class SceneBaseObject
{
public:
	const Guid& GetGuid() const { return m_Guid; };

protected:
	Guid m_Guid;
	SceneObjectType m_Type;
protected:
	SceneBaseObject(SceneObjectType type) : m_Type(type) { m_Guid = newGuid(); };
	SceneBaseObject(Guid& guid, SceneObjectType type) : m_Guid(guid), m_Type(type) {};
	SceneBaseObject(Guid&& guid, SceneObjectType type) : m_Guid(std::move(guid)), m_Type(type) {};
	SceneBaseObject(SceneBaseObject&& obj) : m_Guid(std::move(obj.m_Guid)), m_Type(obj.m_Type) {};
	SceneBaseObject& operator=(SceneBaseObject&& obj) { this->m_Guid = std::move(obj.m_Guid); this->m_Type = obj.m_Type; return *this; };
	virtual ~SceneBaseObject() {};
private :
	SceneBaseObject() = delete;
	SceneBaseObject(SceneBaseObject& obj) = delete;
	SceneBaseObject& operator= (SceneBaseObject& obj) = delete;

friend std::ostream& operator<<(std::ostream& out, const SceneBaseObject& obj);
};
}