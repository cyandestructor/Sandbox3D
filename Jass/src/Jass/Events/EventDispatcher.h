#ifndef JASS_EVENTDISPATCHER_H
#define JASS_EVENTDISPATCHER_H

#include "Event.h"

namespace Jass {

	class JASS_API EventDispatcher {

		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) :
			m_event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> func);

	private:
		Event& m_event;

	};

	template<typename T>
	inline bool EventDispatcher::Dispatch(EventFn<T> func)
	{
		if (m_event.GetEventType() == T::GetStaticType()) {
			m_event.isHandled = func(*(T*)&m_event);
			return true;
		}
		return false;
	}

}

#endif // !JASS_EVENTDISPATCHER_H
