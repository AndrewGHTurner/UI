#ifndef PAGE_DLL_INTERFACE
#define PAGE_DLL_INTERFACE

#ifdef BUILDING_DLL
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

#endif // !UI_DLL_INTERFACE

