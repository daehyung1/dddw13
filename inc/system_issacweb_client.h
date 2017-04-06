/* 
  Copyright (C) 2000 PENTA SECURITY SYSTEMS, INC.
  All rights reserved

  THIS IS UNPUBLISHED PROPRIETARY 
  SOURCE CODE OF PENTA SECURITY SYSTEMS, INC.
  The copyright notice above does not evidence any actual or intended publication of 
  such source code.

  Filename : system_issacweb_client.h
  Description : system dependent functions of issacweb in client
*/

#ifndef _SYSTEM_ISSACWEB_CLIENT_H
#define _SYSTEM_ISSACWEB_CLIENT_H

#ifdef LIB_FACE
#undef LIB_FACE
#endif

#ifdef PENTA_USE_DLL__WIN32
  #ifdef __BUILD_DLL
    #define LIB_FACE __declspec(dllexport)
  #else
    #define LIB_FACE 
  #endif
#else
  #ifdef WIN32
    #ifndef PENTA_BUILD_EXE
      #define LIB_FACE __declspec(dllimport)
    #else
      #define LIB_FACE 
    #endif
  #else
    #define LIB_FACE 
  #endif 
#endif

#ifdef __cplusplus
extern "C" {
#endif
/*
#ifndef XPCOM
  #define issacweb_check_session_key    issacweb_check_session_key_win32
  #define issacweb_save_session_key     issacweb_save_session_key_win32
  #define issacweb_retrieve_session_key issacweb_retrieve_session_key_win32
  #define issacweb_delete_session_key   issacweb_delete_session_key_win32
  #define issacweb_session_key_delete   issacweb_session_key_delete_win32
#else
  #define issacweb_check_session_key    issacweb_check_session_key_pref
  #define issacweb_save_session_key     issacweb_save_session_key_pref
  #define issacweb_retrieve_session_key issacweb_retrieve_session_key_pref
  #define issacweb_delete_session_key   issacweb_delete_session_key_pref
  #define issacweb_session_key_delete   issacweb_session_key_delete_pref
#endif
*/

#if defined(XPCOM)
  #define issacweb_check_session_key    issacweb_check_session_key_pref
  #define issacweb_save_session_key     issacweb_save_session_key_pref
  #define issacweb_retrieve_session_key issacweb_retrieve_session_key_pref
  #define issacweb_delete_session_key   issacweb_delete_session_key_pref
  #define issacweb_session_key_delete   issacweb_session_key_delete_pref
#elif defined(UNIX_LINUX)
  #define issacweb_check_session_key    issacweb_check_session_key_unix
  #define issacweb_save_session_key     issacweb_save_session_key_unix
  #define issacweb_retrieve_session_key issacweb_retrieve_session_key_unix
  #define issacweb_delete_session_key   issacweb_delete_session_key_unix
  #define issacweb_session_key_delete   issacweb_session_key_delete_unix
#else    
  #define issacweb_check_session_key    issacweb_check_session_key_win32
  #define issacweb_save_session_key     issacweb_save_session_key_win32
  #define issacweb_retrieve_session_key issacweb_retrieve_session_key_win32
  #define issacweb_delete_session_key   issacweb_delete_session_key_win32
  #define issacweb_session_key_delete   issacweb_session_key_delete_win32

#if defined(HYUNDAE)
  #define issacweb_save_seed_key_Hyundae issacweb_save_seed_key_Hyundae_win32
  #define issacweb_retrieve_seed_key_Hyundae issacweb_retrieve_seed_key_Hyundae_win32
#endif


#endif

enum ERRORS_SYSTEM_ISSACWEB{
  ER_SYSTEM_ISSACWEB_SESSION_KEY_EXIST  = 30000,
  ER_SYSTEM_ISSACWEB_SAVE_SESSION_KEY_FAIL,
  ER_SYSTEM_ISSACWEB_RETRIEVE_SESSION_KEY_FAIL,
  ER_SYSTEM_ISSACWEB_DELETE_SESSION_KEY_FAIL,
  ER_SYSTEM_ISSACWEB_SESSION_KEY_DELETE_FAIL
};

/* 
  Parameter로 받는 값을 이용하여 키 이름을 지정 
  키를 지우는 함수를 호출해 주어야 한다.
*/

/* 같은 이름의 키가 존재하는지 확인 
  <Parameters>
  입력
    szKeyName : 값이 저장되는 레지스트리의 키 이름
  <Return Value>
    SUCCESS   : 키가 존재하지 않을 때
*/
#if defined(XPCOM)
LIB_FACE int issacweb_check_session_key_pref(const char *pszKeyName);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_check_session_key_unix(const char *pszKeyName);
#else
LIB_FACE int issacweb_check_session_key_win32(const char *pszKeyName);
#endif

/* 키를 저장
  <Parameters>
  입력
    szKeyName : 값이 저장되는 레지스트리의 키 이름
    key       : 저장할 키 값(16byte byte array)
  <Return Value>
    SUCCESS   : 키 저장에 성공하였을 때
*/
#if defined(XPCOM)
LIB_FACE int issacweb_save_session_key_pref(const char *pszKeyName, void *key);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_save_session_key_unix(const char *pszKeyName, void *key);
#else
LIB_FACE int issacweb_save_session_key_win32(const char *pszKeyName, void *key);
LIB_FACE int issacweb_save_seed_key_Hyundae_win32(const char *pszKeyName, const unsigned char *pszValue);
#endif

/* 저장된 키를 가져옴
  <Parameters>
  입력
    szKeyName : 값이 저장되는 레지스트리의 키 이름
  출력
    key       : 키를 저장할 버퍼(16byte byte array)
  <Return Value>
    SUCCESS   : 키 가져오기에 성공하였을 때
*/
#if defined(XPCOM)
LIB_FACE int issacweb_retrieve_session_key_pref(const char *pszKeyName, void *key);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_retrieve_session_key_unix(const char *pszKeyName, void *key);
#else
LIB_FACE int issacweb_retrieve_session_key_win32(const char *pszKeyName, void *key);
LIB_FACE int issacweb_retrieve_seed_key_Hyundae_win32(const char *pszKeyName, void *key);
#endif

/* 저장된 키를 삭제함
  <Parameters>
  입력
    szKeyName : 값이 저장되는 레지스트리의 키 이름
  출력
    key       : 키를 저장할 버퍼(16byte byte array)
  <Return Value>
    SUCCESS   : 키 삭제에 성공하였을 때
*/
#if defined(XPCOM)
LIB_FACE int issacweb_delete_session_key_pref(const char *pszKeyName);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_delete_session_key_unix(const char *pszKeyName);
#else
LIB_FACE int issacweb_delete_session_key_win32(const char *pszKeyName);
#endif

/*Registry에 저장된 하루이상이 지난 KeyName을 삭제한다 */
#if defined(XPCOM)
LIB_FACE int issacweb_session_key_delete_pref(const char *pszKeyName);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_session_key_delete_unix(const char *pszKeyName);
#else
LIB_FACE int issacweb_session_key_delete_win32(const char *pszKeyName);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_ISSACWEB_CLIENT_H */







