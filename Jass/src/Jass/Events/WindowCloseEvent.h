#ifndef JASS_WINDOWCLOSEEVENT_H
#define JASS_WINDOWCLOSEEVENT_H

#include "Event.h"

namespace Jass {

	class JASS_API WindowCloseEvent :public Event {

	public:
		WindowCloseEvent() {}

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryApplication;
		}

		EVENT_CLASS_TYPE(WindowClose)

	};

}

#endif // !JASS_WINDOWCLOSEEVENT_H
