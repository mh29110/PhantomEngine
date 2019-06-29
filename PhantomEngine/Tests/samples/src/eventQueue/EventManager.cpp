#pragma once

#include "EventManager.h"


//be harmony
namespace Phantom {
	namespace EventQueue {
		EventManager & EventManager::Instance()
		{
			static EventManager  _inst;
			return _inst;
		}
		void EventManager::AddEventHandler(int id, EventHandler * handler) {
			if (handler == NULL)
				return;
			auto pair = m_handlerMap.insert(std::make_pair(id, HandlerList()));//注意map的insert用法
			auto it = pair.first;
			if (it == m_handlerMap.end())
				return;
			it->second.push_back(handler);
		}
		void EventManager::RemoveEventHandler(int id, EventHandler * handler) {
			if (handler == NULL)
				return;
			auto it = m_handlerMap.find(id);
			if (it == m_handlerMap.end())
				return;
			auto listIt = std::find(it->second.begin(), it->second.end(), handler);
			if (listIt != it->second.end())
			{
				it->second.erase(listIt);
			}

		}

		void EventManager::clearEventHandler(int id) {
			m_handlerMap.erase(id);
		}

		void EventManager::DispatchEvent(Event* evt)
		{
			auto it = m_handlerMap.find(evt->id);
			if (it == m_handlerMap.end())
				return;
			auto &handler_list = it->second;
			for (auto listIt = handler_list.begin(); listIt != handler_list.end(); listIt++)
			{
				if ((*listIt) == NULL) continue;
				(*listIt)->HandleEvent(evt);
			}

		}
		EventManager::EventManager() {}
		EventManager ::~EventManager() {};
		EventManager::EventManager(const EventManager&) {}
	}
}