#ifndef JASS_CORE_H
#define JASS_CORE_H

#ifdef JASS_PLATFORM_WINDOWS
	#ifdef JASS_BUILD_DLL
		#define JASS_API __declspec(dllexport)
	#else
		#define JASS_API __declspec(dllimport)
	#endif
#else
	#error Jass only support Windows.
#endif

#define BIT(x) (1 << x)

#endif
