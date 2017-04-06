#ifndef __RESURR_H__
#define __RESURR_H__

#include <windows.h>

#ifdef RESURR_EXPORTS
#define RESURR_LIBSPEC __declspec(dllexport) 
#else
#define RESURR_LIBSPEC
#endif

#ifdef __cplusplus
extern "C"
{
#endif

RESURR_LIBSPEC void SummonGuardian(char **serviceNames);

#ifdef __cplusplus
}
#endif


#endif
