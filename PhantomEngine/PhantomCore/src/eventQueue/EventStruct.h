#pragma once
#include <list>
#include <map>


//be harmony
namespace Phantom {
	namespace EventQueue{

	enum EventId
	{
			EVT_TICK = 0,
			EVT_LOADSCENE_COMPLETED = 1,
	};
	struct Event
	{
		Event(int $id) : id($id)
		{}
		~Event() {}
		int id;
	};

	class EventHandler
	{
	public:
		virtual int HandleEvent(Event *evt)
		{
		   return 0;
		 }
	};

	template < typename Type>
	class ClassBasedEventHandler :public EventHandler
	{
	public :
		typedef int(Type::* HandlerFunc) (Event *evet);
	public:
		ClassBasedEventHandler(Type *ptr, HandlerFunc func) :m_ptr(ptr), m_func(func) {};
		virtual int HandleEvent(Event *evt)
		{
			if (m_ptr && m_func)
				return (m_ptr->*m_func)(evt);
			return 0;
		}
	private:
		Type * m_ptr;
		HandlerFunc m_func;
	};
}}