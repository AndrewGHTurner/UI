#ifndef UI_DLL_INTERFACE
#define UI_DLL_INTERFACE

#ifdef BUILDING_DLL
#define UI_API __declspec(dllexport)
#else
#define UI_API __declspec(dllimport)
#endif

#endif // !UI_DLL_INTERFACE

