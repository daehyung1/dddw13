
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HTTPCON_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HTTPCON_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __HTTPCON_HEADER
#define __HTTPCON_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBSPEC
#undef LIBSPEC
#endif

#ifdef HTTPCON_EXPORTS
#define LIBSPEC __declspec(dllexport)
#else
#define LIBSPEC __declspec(dllimport)
#endif
  

enum {
  HCERR_SUCCESS = 0,
  HCERR_FAIL,
  HCERR_OPEN,
  HCERR_CONNECT,
  HCERR_OPEN_REQUEST,
  HCERR_SEND_REQUEST,         // 5
  HCERR_END_REQUEST,   
  HCERR_QUERY_INFO,
  HCERR_QUERY_STATUSCODE,
  HCERR_READ_FILE,
  HCERR_WRITE_FILE,           // 10
  HCERR_GET_RESPONSE,  
  HCERR_RESPONSE_RES,  
  HCERR_URL_ENCODING,
  HCERR_ENCNBASE64ENCODE,
  HCERR_DECNBASE64DECODE,     // 15
  HCERR_MORE_BUFFER,
  HCERR_GET_COOKIE,
  HCERR_SET_COOKIE,
  HCERR_UNKNOWN,              
};


LIBSPEC char *HttpCon_URLEncode(const char *str);

LIBSPEC char *HttpCon_CanonicalizeUrl(const char *str);

LIBSPEC int HttpCon_GetCookie( LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPTSTR lpszBuf, DWORD dwBufLen );
LIBSPEC int HttpCon_SetCookie( LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPTSTR lpszCookieData );

LIBSPEC int HttpCon_GetEIPResponse( LPCTSTR  lpszSavePath,    // (in)   response xmlfile
                                    LPINT    nErrCode,        // (out)  errcode
                                    LPTSTR   lpszErrMsg,      // (out)  errMsg
                                    LPTSTR   lpszData,        // (out)  response data
                                    DWORD    dwBufLen );      // (out)  response data size





// Request Function ----------------------------------------------------------------------------
LIBSPEC int HttpCon_Request( LPCTSTR  lpszServerName,       // (in)   Server name
                             WORD     wServerPort,          // (in)   Server port        
                             LPCTSTR  lpszObjPath,          // (in)   Target Page Path
                             LPCTSTR  lpszReqData,          // (in)   Filled Form data                                
                             LPDWORD  dwStatusCode,         // (out)  server return code
                             LPTSTR   lpszErrMsg,           // (out)  Error Message Buffer
                             DWORD    dwErrMsgLen,          // (in)   Error Message Buffer Length 
                             LPCTSTR  lpszResSavePath,      // (in)   response xmlfile
                             LPDWORD  dwResFileSize );      // (out)  response file size 

LIBSPEC int HttpCon_RequestEx( LPCTSTR  lpszServerName,       // (in)   Server name
                               WORD     wServerPort,          // (in)   Server port        
                               LPCTSTR  lpszObjPath,          // (in)   Target Page Path
                               LPCTSTR  lpszReqData,          // (in)   Filled Form data                                
                               LPDWORD  dwStatusCode,         // (out)  server return code
                               LPTSTR   lpszErrMsg,           // (out)  Error Message Buffer
                               DWORD    dwErrMsgLen,          // (in)   Error Message Buffer Length 
                               LPCTSTR  lpszResSavePath,      // (in)   response xmlfile
                               LPDWORD  dwResFileSize,        // (out)  response file size 
                               LPCTSTR  lpszfopenmode );      // (in)   file open mode
// Keep Connect Function ----------------------------------------------------------------------------
LIBSPEC int HttpCon_Initialize( LPCTSTR  lpszServerName, WORD  wServerPort );

LIBSPEC int HttpCon_KeepConnectRequest( LPCTSTR    lpszObjPath,          // (in)   Target Page Path
                                        LPCTSTR    lpszReqData,          // (in)   Filled Form data                                                                     
                                        LPDWORD    dwStatusCode,         // (out)  server return code
                                        LPTSTR     lpszErrMsg,           // (out)  Error Message Buffer
                                        DWORD      dwErrMsgLen,          // (in)   Error Message Buffer Length 
                                        LPCTSTR    lpszResSavePath,      // (in)   response xmlfile
                                        LPDWORD    dwResFileSize );      // (out)  response file size 
LIBSPEC void HttpCon_Finalize();




//----------------------------------------------------------------------------------------------------
// For Static Lib

LIBSPEC int HttpCon_Login( LPCTSTR  lpszServerName,    // (in)  Server name
                           WORD     wServerPort,       // (in)  Server port        
                           LPCTSTR  lpszloginObjPath,  // (in)  Login Target Page Path                           
                           LPCTSTR  lpszloginReqData,  // (in)  Filled Login Form data 
                           DWORD    *dwStatusCode );   // (out) HTTP Status Error Code

LIBSPEC int HttpCon_LoginNRequest( LPCTSTR  lpszServerName,    // (in)  Server name
                                   WORD     wServerPort,       // (in)  Server port        
                                   LPCTSTR  lpszloginObjPath,  // (in)  Login Target Page Path
                                   LPCTSTR  lpszSvcObjPath,    // (in)  Service Request Target Page Path
                                   LPCTSTR  lpszloginReqData,  // (in)  Filled Login Form data                                         
                                   LPCTSTR  lpszSvcReqData,    // (in)  Filled Service Request Form data                                         
                                   std::string   &strResponse, // (out) Response XML Data
                                   DWORD    *dwStatusCode );   // (out) HTTP Status Error Code

LIBSPEC int HttpCon_GetResponse2( LPCTSTR lpszSavePath,        // (in)   response xmlfile
                                  int     *nErrCode,           // (out)  errcode
                                  char    *pszErrMsg,          // (out)  errMsg
                                  std::string  &strResData );  // (out)  response data

//-----------------------------------------------------------------------------------------------

               


#ifdef __cplusplus
}
#endif

#endif //__HTTPCON_HEADER
