#ifndef JASS_EVENT_H
#define JASS_EVENT_H

#include "jasspch.h"
#include "EventEnums.h"

namespace Jass {

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

	class JASS_API Event {

	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & (int)category;
		}

	};

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}

#endif // !JASS_EVENT_H
