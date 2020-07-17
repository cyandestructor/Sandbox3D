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

#ifdef JASS_ENABLE_ASSERTS
	#define JASS_ASSERT(x, ...) { if(!(x)) { JASS_ERR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JASS_CORE_ASSERT(x, ...) { if(!(x)) { JASS_CORE_ERR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JASS_ASSERT(x, ...)
	#define JASS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#endif
