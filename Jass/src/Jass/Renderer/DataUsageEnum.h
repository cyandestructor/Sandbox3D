#ifndef JASS_DATAUSAGEENUM_H
#define JASS_DATAUSAGEENUM_H

namespace Jass {

	enum class DataUsage
	{
		StreamDraw, StreamRead, StreamCopy,
		StaticDraw, StaticRead, StaticCopy,
		DynamicDraw, DynamicRead, DynamicCopy
	};

}

#endif // !JASS_DATAUSAGEENUM_H
