#pragma once
#include <list>
#include <map>
#include "common/Singleton.h"
#include "EventStruct.h"


//be harmony
namespace Phantom {
	namespace EventQueue{
        class EventManager:public Singleton<EventManager>
	{
	public:
		typedef std::list<EventHandler*> HandlerList;
		typedef std::map<int ,HandlerList> IdHandlerMap;
	public:
		static EventManager& Instance() ;

		void AddEventHandler(int id, EventHandler * handler);
		void RemoveEventHandler(int id, EventHandler * handler) ;

		void clearEventHandler(int id);

		void DispatchEvent(Event* evt);
	public:
		EventManager();
		~EventManager();
    private:
		EventManager(const EventManager&);
		IdHandlerMap m_handlerMap;
	};
	
}}
