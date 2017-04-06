
#ifndef __DSS_FPAPI_HEADER
#define __DSS_FPAPI_HEADER

#ifdef __cplusplus
extern "C" {
#endif


#ifdef LIBSPEC
#undef LIBSPEC
#endif

#ifdef DSS_FPAPI_EXPORTS
#define LIBSPEC __declspec(dllexport)
#else
#define LIBSPEC __declspec(dllimport)
#endif



LIBSPEC int DSS_FPAPI_test(void);





#ifdef __cplusplus
}
#endif

#endif //__DSS_FPAPI_HEADER
