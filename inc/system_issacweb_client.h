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
  Parameter�� �޴� ���� �̿��Ͽ� Ű �̸��� ���� 
  Ű�� ����� �Լ��� ȣ���� �־�� �Ѵ�.
*/

/* ���� �̸��� Ű�� �����ϴ��� Ȯ�� 
  <Parameters>
  �Է�
    szKeyName : ���� ����Ǵ� ������Ʈ���� Ű �̸�
  <Return Value>
    SUCCESS   : Ű�� �������� ���� ��
*/
#if defined(XPCOM)
LIB_FACE int issacweb_check_session_key_pref(const char *pszKeyName);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_check_session_key_unix(const char *pszKeyName);
#else
LIB_FACE int issacweb_check_session_key_win32(const char *pszKeyName);
#endif

/* Ű�� ����
  <Parameters>
  �Է�
    szKeyName : ���� ����Ǵ� ������Ʈ���� Ű �̸�
    key       : ������ Ű ��(16byte byte array)
  <Return Value>
    SUCCESS   : Ű ���忡 �����Ͽ��� ��
*/
#if defined(XPCOM)
LIB_FACE int issacweb_save_session_key_pref(const char *pszKeyName, void *key);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_save_session_key_unix(const char *pszKeyName, void *key);
#else
LIB_FACE int issacweb_save_session_key_win32(const char *pszKeyName, void *key);
LIB_FACE int issacweb_save_seed_key_Hyundae_win32(const char *pszKeyName, const unsigned char *pszValue);
#endif

/* ����� Ű�� ������
  <Parameters>
  �Է�
    szKeyName : ���� ����Ǵ� ������Ʈ���� Ű �̸�
  ���
    key       : Ű�� ������ ����(16byte byte array)
  <Return Value>
    SUCCESS   : Ű �������⿡ �����Ͽ��� ��
*/
#if defined(XPCOM)
LIB_FACE int issacweb_retrieve_session_key_pref(const char *pszKeyName, void *key);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_retrieve_session_key_unix(const char *pszKeyName, void *key);
#else
LIB_FACE int issacweb_retrieve_session_key_win32(const char *pszKeyName, void *key);
LIB_FACE int issacweb_retrieve_seed_key_Hyundae_win32(const char *pszKeyName, void *key);
#endif

/* ����� Ű�� ������
  <Parameters>
  �Է�
    szKeyName : ���� ����Ǵ� ������Ʈ���� Ű �̸�
  ���
    key       : Ű�� ������ ����(16byte byte array)
  <Return Value>
    SUCCESS   : Ű ������ �����Ͽ��� ��
*/
#if defined(XPCOM)
LIB_FACE int issacweb_delete_session_key_pref(const char *pszKeyName);
#elif defined(UNIX_LINUX)
LIB_FACE int issacweb_delete_session_key_unix(const char *pszKeyName);
#else
LIB_FACE int issacweb_delete_session_key_win32(const char *pszKeyName);
#endif

/*Registry�� ����� �Ϸ��̻��� ���� KeyName�� �����Ѵ� */
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







