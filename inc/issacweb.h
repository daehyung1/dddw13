/* 
	Copyright (C) 2003 PENTA SECURITY SYSTEMS, INC.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY 
	SOURCE CODE OF PENTA SECURITY SYSTEMS, INC.
	The copyright notice above does not evidence any actual or intended publication of 
	such source code.

	Filename : issacweb.h 
*/

#ifndef _ISSACWEB_H
#define _ISSACWEB_H

#ifdef LIB_FACE_WEB
#undef LIB_FACE_WEB
#endif

#ifdef PENTA_USE_DLL__WIN32
  #ifdef __BUILD_DLL
    #define LIB_FACE_WEB __declspec(dllexport)
  #else
    #define LIB_FACE_WEB 
  #endif
#else
  #ifdef WIN32
    #ifndef PENTA_BUILD_EXE
      #define LIB_FACE_WEB __declspec(dllimport)
    #else
      #define LIB_FACE_WEB 
    #endif
  #else
    #define LIB_FACE_WEB 
  #endif 
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif


#ifdef __cplusplus
extern "C" {
#endif

#define LICENSE_PATH  				"license.cer"
#define PRODUCT_NAME  				"ISSAC-Web Ver 2.0"
#define SHARED_NAME   				"issacweb_key"
#define ISSACWEB_SHARED_ID    1499
#define PUBLICKEY_ENC_BUFSIZE (256*4/3+6)
#define CERTIFICATE_DEFAULT_BUFSIZE		8192
#define PRIVKEY_DEFAULT_BUFSIZE				8192

typedef char					*issac_string;
typedef unsigned char *issac_binary;

// 2004. 02. 03
// ������ : std ������ �� �� �ְ� define �߰�
#define issacweb_server_decrypt_s(A, B, C) issacweb_hybrid_decrypt_s(A, B, C, PRIKEY)
#define issacweb_server_decrypt(A, B, C, D) issacweb_hybrid_decrypt(A, B, C, D, PRIKEY)
#define issacweb_client_encrypt_s(A, B, C, D) issacweb_hybrid_encrypt_s(A, B, C, PUBKEY, D)
#define issacweb_client_encrypt(A, B, C, D)   issacweb_hybrid_encrypt(A, B, C, PUBKEY, D)

typedef struct _issac_session {
  void *session;
} issac_session;

// 2005. 10.18 compile�� �ɼ����� �˰����� �����Ҽ� �ֵ��� �߰�
// USING_SEED, USING_ARIA

#ifdef USING_SEED
  #define IWEB_ALGO ISSACWEB_SEED
#endif

#ifdef USING_ARIA
  #define IWEB_ALGO ISSACWEB_ARIA
#endif

#ifdef USING_AES256
#define IWEB_ALGO ISSACWEB_AES256
#endif

enum ISSACWEB_SUPPORTED_SYMMETRIC_ENCRYPTION_ALGORITHM 
{
  ISSACWEB_SEED = 1,  
  ISSACWEB_ARIA,
  ISSACWEB_AES256
};

enum ISSACWEB_SUPPORTED_PUBLICKEY_ALGORITHM 
{
  ISSACWEB_RSA_SHA1 = 1,
  ISSACWEB_RSA_SHA256,
  ISSACWEB_RSA_SHA384,
  ISSACWEB_RSA_SHA512
};

enum ISSACWEB_SUPPORTED_PAGE_CHARSET
{
  ISSACWEB_CHARSET_NOT_ENCODING = 1,
  ISSACWEB_CHARSET_EUCKR,
  ISSACWEB_CHARSET_UTF8
};

typedef enum _ISSACWEB_RET_CODE
{
	IW_RET_FAIL = -1,
  IW_RET_SUCCESS = 0,
  IW_RET_INVALID_PARAM,
  IW_RET_MEMORY_ALLOC_ERR,
  IW_RET_CANNOT_OPEN_FILE,
  IW_RET_CANNOT_READ_FILE,
  IW_RET_CANNOT_WRITE_FILE,
  IW_RET_HYBRID_DECRYPT_FAIL,
  IW_RET_HYBRID_ENCRYPT_FAIL,
  IW_RET_CANNOT_GET_DECNAME,
  IW_RET_UNKNOWN_ERROR,
  
  IW_RET_BASE64_DECODE    = 30,
  IW_RET_BASE64_ENCODE,
  IW_RET_CAN_NOT_ADD_CERT = 80,
  IW_RET_INVALID_CERT     = 801,
  IW_RET_CAN_NOT_OPEN_CERT_STORE,
}ISSACWEB_RET_CODE;


// 2009. 10. 12
// ���������� �Ϻ�ȭ�ÿ� IV�� �׻� ���ϴ� ������ �����û

// �Ϻ�ȣȭ s
LIB_FACE_WEB int issacweb_encrypt_s_iv(char *outstring, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_decrypt_s_iv(void *outbuf, char *inputstring, void *key);
             
// �Ϻ�ȣȭ ex_s
LIB_FACE_WEB int issacweb_encrypt_ex_s_iv(char *outstring, void *input, int input_len, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_decrypt_ex_s_iv(void *outbuf, char *inputstring, void *key, int cipher_id);

// ���̺긮�� �Ϻ�ȣȭ ex2 
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2_iv(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2_iv(void *outbuf, void *input, int input_len, void *key, const char *prikey, int cipher_id, int publickey_id);

// ���̺긮�� ��ȣȭ s
LIB_FACE_WEB int issacweb_hybrid_decrypt_s_iv(void *outbuf, const char *inputstring, void *key, const char *prikey);

// ���̺긮�� �Ϻ�ȣȭ ex_s
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex_s_iv(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex_s_iv(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id);

// ���̺긮��  ��ȣȭ ex2_s
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2_s_iv(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id, int publickey_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2_s_iv(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);

// ����Ű�� �߰��� ���̺긮�� �Ϻ�ȣȭ ex_s
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex_s_iv(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex_iv(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id);


/*
  ������ �޸� ��(input�������� input_len��ŭ)�� �޼����� 
  �־��� key�� �̿��Ͽ� ��ȣȭ�Ѵ�.

  �Է�
      input : ��ȣȭ�� �޼���
      input_len : ��ȣȭ�� �޼����� ����Ʈ ��
      key : �־��� ���Ű
      cipher_id : ��ĪŰ �˰���
  ���
      outbuf : ��ȣȭ�� �޼���
               (input_len���� 8����Ʈ �̻��� �޸� ������ �Ҵ�Ǿ� �־�� �Ѵ�.)
*/
LIB_FACE_WEB int issacweb_encrypt(void *outbuf, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_encrypt_ex(void *outbuf, void *input, int input_len, void *key, int cipher_id);

/*
  �־��� key�� �̿��Ͽ� ������ �޸� ��(input�������� input_len��ŭ)�� 
  ��ȣȭ�� �޼����� ��ȣȭ�Ѵ�.

  �Է�
      input : ��ȣȭ�� �޼���
      input_len : ��ȣȭ�� �޼����� ����Ʈ ��
      key : �־��� ���Ű
      cipher_id : ��ĪŰ �˰���
  ���
      outbuf : ��ȣȭ�� �޼���
*/
LIB_FACE_WEB int issacweb_decrypt(void *outbuf, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_decrypt_ex(void *outbuf, void *input, int input_len, void *key, int cipher_id);

/*
   �Լ� issacweb_encrypt()�� �������� ��ȣȭ�� �޼����� null-terminated ��Ʈ������
   �־�����.
   (outstring�� (input_len+8)*(4/3) ����Ʈ �̻��� �޸� ������ �Ҵ�Ǿ� �־�� �Ѵ�.)
*/
LIB_FACE_WEB int issacweb_encrypt_s(char *outstring, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_encrypt_ex_s(char *outstring, void *input, int input_len, void *key, int cipher_id);

/*
   �Լ� issacweb_decrypt()�� �������� ��ȣȭ�� �޼����� null-terminated ��Ʈ������
   �־�����.
*/
LIB_FACE_WEB int issacweb_decrypt_s(void *outbuf, char *inputstring, void *key);
LIB_FACE_WEB int issacweb_decrypt_ex_s(void *outbuf, char *inputstring, void *key, int cipher_id);

/*
  ������ �޸� ��(input�������� input_len��ŭ)�� �޼����� 
  �־��� publickey�� �̿��Ͽ� ����Ű ��ȣȭ�Ѵ�.

  �Է�
      inbuf : ��ȣȭ�� �޼���
      inbuf_len : ��ȣȭ�� �޼����� ����Ʈ ��(80����Ʈ�� �Ѵ� ��� ���� �߻�)
      publickey : �־��� ����Ű(base64���ڵ��� ��Ʈ�� ����)
  ���
      outbuf : publickey�� ���� �Ǵ� �����Ű�θ� ��ȭȭ �� �� �ֵ���
               ��ȣȭ�� �޼���
               (128����Ʈ �̻��� �޸� ������ �Ҵ�Ǿ� �־�� �Ѵ�.)
  ���ϰ�
      outbuf�� ��µǴ� ��ȣ���� ����, ������ ���� �����ڵ�
*/
LIB_FACE_WEB int issacweb_publickey_encrypt(void *outbuf, const void *inbuf, int inbuf_len, const char *publickey);
LIB_FACE_WEB int issacweb_publickey_encrypt_ex(void *outbuf, const void *inbuf, int inbuf_len, const char *publickey, int publickey_id);

/*
  �־��� �����Ű�� �̿��Ͽ� ������ �޸� ��(input�������� input_len��ŭ)�� 
  ��ȣȭ�� �޼����� ��ȣȭ�Ѵ�.

  �Է�
      inbuf : ��ȣȭ�� �޼���
      inbuf_len : ��ȣȭ�� �޼����� ����Ʈ ��
      privatekey : �־��� �����Ű(base64���ڵ��� ��Ʈ�� ����)
  ���
      outbuf : ��ȣȭ�� �޼���
  ���ϰ�
      outbuf�� ��µǴ� ��ȣ���� ����, ������ ���� �����ڵ�
*/
LIB_FACE_WEB int issacweb_publickey_decrypt(void *outbuf, void *inbuf, int inbuf_len, const char *privatekey);
LIB_FACE_WEB int issacweb_publickey_decrypt_ex(void *outbuf, void *inbuf, int inbuf_len, const char *privatekey, int publickey_id);

/*
  error���� string���� ��ȯ���� �ش�.
*/
LIB_FACE_WEB const char *errorcode_to_string(int code);

#ifdef _IWEB_CLIENT

/* 
  ���������� SessionŰ�� �����Ͽ� �̸� �̿��Ͽ� �޽����� ��ȣȭ �� ��, �־��� ���������� ����Ű��
  ���� �� ����Ű�� SessionŰ�� ��ȣȭ�Ѵ�.
  <Parameters>
    �Է�     
        input     : ��ȣȭ �� �޽���
        input_len : input�� ����
        pub       : SessionŰ�� ��ȣȭ �ϴµ� ��� �� RSA ����Ű 
        cipher_id : ��ĪŰ �˰���
    ���    
        outbuf    : ��ȣȭ �� �޽���, (input_len + 16)��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
        key       : buffer to store generated session key(16 byte), ������ ��ȣȭ�Ͽ� ���� ��츦 ����Ͽ� ��ȣȭ�� ���� ������ �ξ�� �Ѵ�.
  <Return value>
    0, ��� ��  : ��ȣȭ �� �޽����� ����
    ���� ��       : ���� �޽���
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt(void *outbuf, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);

/* 
  ���������� SessionŰ�� �����Ͽ� �̸� �̿��Ͽ� �޽����� ��ȣȭ �� ��, �־��� ���������� ����Ű��
  ���� �� ����Ű�� SessionŰ�� ��ȣȭ�Ѵ�.
  <Parameters>
    �Է�     
        input     : ��ȣȭ �� �޽���
        input_len : input�� ����
        pub       : SessionŰ�� ��ȣȭ �ϴµ� ��� �� RSA ����Ű 
        cipher_id : ��ĪŰ �˰���
    ���    
        outstring : ��ȣȭ �� �޽���(base64�� encoding�Ǿ� ����)
        key       : buffer to store generated session key(16 byte), ������ ��ȣȭ�Ͽ� ���� ��츦 ����Ͽ� ��ȣȭ�� ���� ������ �ξ�� �Ѵ�.
  <Return value>
    0, ��� ��  : ��ȣȭ �� �޽����� ����
    ���� ��     : ���� �޽���
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_s(char *outstring, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex_s(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2_s(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);

LIB_FACE_WEB
int issacweb_hybrid_encrypt_file_s(OUT void* sessionKey, IN char *filePath, IN char *pubKey);

/*
 * decFilePath => ���� ���°��, ���������� �̸��� ��� �������ش�.

  2006. 1. 29 �����
  ������ decFilePath�� �ƹ��� �ǹ̰� ������
  decFilePath�� NULL�� ��쿡�� .enc�� ������ ����
  �����ϴ� ���� .enc�� �ƴ� ���, .dec�� ���̵��� ����
*/
LIB_FACE_WEB
int issacweb_decrypt_file_s(IN OUT char *decFilePath,IN char *filePath, IN void *sessionKey);

/* limited memory ȯ�濡�� ���� ��ȣȭ */
LIB_FACE_WEB
int issacweb_decrypt_file_lm_s(IN OUT char *decFilePath, IN char *encFilePath, IN void *sessionKey);

/*
  ���� : issacweb_hybrid_encrypt_with_sessionkey_ex_s �Լ��� timestamp ����� �߰���
  ���������� SessionŰ�� �����Ͽ� �̸� �̿��Ͽ� �޽����� ��ȣȭ �� ��, �־��� ���������� ����Ű��
  ���� �� ����Ű�� SessionŰ�� ��ȣȭ�Ѵ�.
  <Parameters>
    �Է�     
        input     : ��ȣȭ �� �޽���
        input_len : input�� ����
        pub       : SessionŰ�� ��ȣȭ �ϴµ� ��� �� RSA ����Ű 
        cipher_id : ��ĪŰ �˰���
        timeStamp : �������� �߱��� timestamp
    ���    
        outstring : ��ȣȭ �� �޽���(base64�� encoding�Ǿ� ����)
        key       : buffer to store generated session key(16 byte), ������ ��ȣȭ�Ͽ� ���� ��츦 ����Ͽ� ��ȣȭ�� ���� ������ �ξ�� �Ѵ�.
  <Return value>
    0, ��� ��  : ��ȣȭ �� �޽����� ����
    ���� ��     : ���� �ڵ�
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_and_timestamp_ex_s(
  char *outstring,
  void *input,
  int input_len,
  const char *pub,
  void *key,
  int cipher_id,
  char *timeStamp);


/** ver2.0���� ���� �߰���  Ŭ���̾�Ʈ�� �Լ��� **/
/* 
  �־��� SessionŰ�� ����Ͽ� �޽����� ��ȣȭ �� ��, �־��� ���������� ����Ű��
  ���� �� ����Ű�� SessionŰ�� ��ȣȭ�Ѵ�.
  <Parameters>
    �Է�     
        input     : ��ȣȭ �� �޽���
        input_len : input�� ����
        pub       : SessionŰ�� ��ȣȭ �ϴµ� ��� �� RSA ����Ű 
    ���    
        outbuf    : ��ȣȭ �� �޽���, (input_len + 16)��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
        key       : buffer to store generated session key(16 byte), ������ ��ȣȭ�Ͽ� ���� ��츦 ����Ͽ� ��ȣȭ�� ���� ������ �ξ�� �Ѵ�.
  <Return value>
    0, ��� ��  : ��ȣȭ �� �޽����� ����
    ���� ��       : ���� �޽���
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey(void *outbuf, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id);

/* 
  �־��� SessionŰ�� ����Ͽ� �޽����� ��ȣȭ �� ��, �־��� ���������� ����Ű��
  ���� �� ����Ű�� SessionŰ�� ��ȣȭ�Ѵ�.
  <Parameters>
    �Է�     
        input     : ��ȣȭ �� �޽���
        input_len : input�� ����
        pub       : SessionŰ�� ��ȣȭ �ϴµ� ��� �� RSA ����Ű 
    ���    
        outstring : ��ȣȭ �� �޽���(base64�� encoding�Ǿ� ����)
        key       : buffer to store generated session key(16 byte), ������ ��ȣȭ�Ͽ� ���� ��츦 ����Ͽ� ��ȣȭ�� ���� ������ �ξ�� �Ѵ�.
  <Return value>
    0, ��� ��  : ��ȣȭ �� �޽����� ����
    ���� ��     : ���� �޽���
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_s(char *outstring, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex_s(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
/**
	 @breif �޼����� �������� ����Ͽ� ����Ű ������� ��ȣȭ �Ѵ�.
	 @param outbuf        (Out) ��ȣȭ�� �޼���
	 @param inbuf         (In) ��ȣȭ�� ���� �޼���
	 @param inbuf_len     (In) ��ȣȭ�� ���� �޼����� ����(80 ����)
	 @param certificate   (In) ����Ű ��� ��ȣȭ�� �ʿ��� BASE64 ���ڵ��� ������

	 outbuf���� 256 Byte ��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.

	 @return
					- 0,���: Success, ��ȣȭ�� �޼����� ����
					- ����: Fail, Errorcode
	 @sa issacweb_publickey_encrypt_s 
	*/
LIB_FACE_WEB 
int issacweb_publickey_encrypt_c(issac_binary outbuf, issac_binary inbuf, int inbuf_len, issac_string certificate);

/**
	 @breif �޼����� �������� ����Ͽ� ����Ű ������� ��ȣȭ �Ѵ�.
	 @param outstring     (Out) ��ȣȭ�� �޼���, BASE64 ���ڵ��� ���ڿ�
	 @param inbuf         (In) ��ȣȭ�� ���� �޼���
	 @param inbuf_len     (In) ��ȣȭ�� ���� �޼����� ����(80 ����)
	 @param certificate   (In) ����Ű ��� ��ȣȭ�� �ʿ��� BASE64 ���ڵ��� ������

	 outstring���� 256*4/3 +6 Byte ��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.

	 @return
					- 0,���: Success, ��ȣȭ�� �޼����� ����
					- ����: Fail, Errorcode
	 @sa issacweb_publickey_encrypt 
	*/
LIB_FACE_WEB 
int issacweb_publickey_encrypt_cs(issac_string outstring, issac_binary inbuf, int inbuf_len, issac_string certificate);

/**
	 @breif �޼����� �������� ����Ͽ� ���̺긮�� ������� ��ȣȭ �Ѵ�.
	 @param outbuf        (Out) ��ȣȭ�� �޼���
	 @param input         (In) ��ȣȭ�� ���� �޼���
	 @param input_len     (In) ��ȣȭ�� ���� �޼����� ����
	 @param certificate   (In) ���̺긮�� ��� ��ȣȭ�� �ʿ��� BASE64 ���ڵ��� ������
	 @param key           (In) ��ȣȭ�� ���� ��ĪŰ(16 Byte)

	 outbuf���� input_len+300 Byte ��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.

	 @return
					- 0,���: Success, ��ȣȭ�� �޼����� ����
					- ����: Fail, Errorcode
	 @sa issacweb_hybrid_encrypt_s 
	*/
LIB_FACE_WEB
int issacweb_hybrid_encrypt_c(issac_binary outbuf, issac_binary input, int input_len, issac_string certificate, issac_binary key);

/**
	 @breif �޼����� �������� ����Ͽ� ���̺긮�� ������� ��ȣȭ �Ѵ�.
	 @param outstring     (Out) ��ȣȭ�� �޼���, BASE64 ���ڵ��� ���ڿ�
	 @param input         (In) ��ȣȭ�� ���� �޼���
	 @param input_len     (In) ��ȣȭ�� ���� �޼����� ����
	 @param certificate   (In) ���̺긮�� ��� ��ȣȭ�� �ʿ��� BASE64 ���ڵ��� ������
	 @param key           (In) ��ȣȭ�� ���� ��ĪŰ(16 Byte)

	 outstring���� (input_len+300)*4/3 Byte ��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.

	 @return
					- 0,���: Success, ��ȣȭ�� �޼����� ����
					- ����: Fail, Errorcode
	 @sa issacweb_hybrid_encrypt_s 
	*/
LIB_FACE_WEB 
int issacweb_hybrid_encrypt_cs(issac_string outstring, issac_binary input, int input_len, issac_string certificate, issac_binary key);

#endif /* _IWEB_CLIENT */

#ifdef _IWEB_SERVER

/**
  * �޽������� ����Ű�� ��ȣȭ�� ���Ű�� �����Ű�� ��ȣȭ �� ��, �ٽ� �� ���Ű�� �޽����� ��ȣȭ �ϴ� �Լ�
  * 
  * @param  outbuf        (Out) ��ȣȭ�� ������� ����ȴ�. inputstring�� ���� ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  inputstring   (In)  ��ȣȭ �� �޽���
  * @param  key           (Out) ��ȣȭ�� ���Ű�� ����ȴ�. 16byte�̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  prikey        (In)  ������ �����Ű, NULL�� ��� ���̺귯�� �ȿ� ����Ǿ� �ִ� �����Ű�� ���
  * @param  cipher_id     (In)  ��ĪŰ �˰���
  * @return
  *         - 0,���     : Success, ��ȣȭ �� �޽����� ����
  *         - ����       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt(void *outbuf, void *input, int input_len, void *key, const char *prikey);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex(void *outbuf, void *input, int input_len, void *key, const char *prikey, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2(void *outbuf, void *input, int input_len, void *key, const char *prikey, int cipher_id, int publickey_id);

/**
  * �޽������� ����Ű�� ��ȣȭ�� ���Ű�� �����Ű�� ��ȣȭ �� ��, �ٽ� �� ���Ű�� �޽����� ��ȣȭ �ϴ� �Լ�
  * 
  * @param  outbuf        (Out) ��ȣȭ�� ������� ����ȴ�. inputstring�� ���� ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  inputstring   (In)  ��ȣȭ �� �޽���, BASE64�� ���ڵ��� ���ڿ�
  * @param  key           (Out) ��ȣȭ�� ���Ű�� ����ȴ�. 16byte�̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  prikey        (In)  ������ �����Ű, NULL�� ��� ���̺귯�� �ȿ� ����Ǿ� �ִ� �����Ű�� ���
  * @param  cipher_id     (In)  ��ĪŰ �˰���
  * @return
  *         - 0,���     : Success, ��ȣȭ �� �޽����� ����
  *         - ����       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt_s(void *outbuf, const char *inputstring, void *key, const char *prikey);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex_s(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2_s(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id, int publickey_id);

LIB_FACE_WEB
int issacweb_hybrid_decrypt_file_s(OUT void *sessionKey, IN char *encFilePath, IN char *priKey );

/**
  * License ������ ���� �߰��� �Լ���
  * @author Jypark
  * @date   2000.10.24
  */
/**
  * �޽������� ����Ű�� ��ȣȭ�� ���Ű�� �����Ű�� ��ȣȭ �� ��, �ٽ� �� ���Ű�� �޽����� ��ȣȭ �ϴ� �Լ�
  * ������ �����Ű�� Ű ���� ��⿡�� �������� �����´�.
  * 
  * @param  outbuf        (Out) ��ȣȭ�� ������� ����ȴ�. inputstring�� ���� ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  inputstring   (In)  ��ȣȭ �� �޽���, BASE64�� ���ڵ��� ���ڿ�
  * @param  key           (Out) ��ȣȭ�� ���Ű�� ����ȴ�. 16byte�̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @return
  *         - 0,���     : Success, ��ȣȭ �� �޽����� ����
  *         - ����       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt2(void *outbuf, void *input, int input_len, void *key);

/**
  * �޽������� ����Ű�� ��ȣȭ�� ���Ű�� �����Ű�� ��ȣȭ �� ��, �ٽ� �� ���Ű�� �޽����� ��ȣȭ �ϴ� �Լ�
  * ������ �����Ű�� Ű ���� ���α׷����κ��� �������� �����´�.
  * 
  * @param  outbuf        (Out) ��ȣȭ�� ������� ����ȴ�. inputstring�� ���� ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  inputstring   (In)  ��ȣȭ �� �޽���, BASE64�� ���ڵ��� ���ڿ�
  * @param  key           (Out) ��ȣȭ�� ���Ű�� ����ȴ�. 16byte�̻��� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @return
  *         - 0,���     : Success, ��ȣȭ �� �޽����� ����
  *         - ����       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt2_s(void *outbuf, const char *inputstring, void *key); 

/* ���� ��ȣȭ �Լ� */
LIB_FACE_WEB int d2b_hybrid_decrypt(void *output, void *key, void *input, const void *prikey);

LIB_FACE_WEB int d2b_hybrid_decrypt2(void *output, void *key, void *input, const void *prikey);
LIB_FACE_WEB int d2b_get_certificate(char* certificate, int* certificate_len, int certificate_alloc_len, void *input);

LIB_FACE_WEB int d2s_hybrid_decrypt(void *output, void *key, void *input, const void *prikey);

/** ver2.0���� ���� �߰���  ������ �Լ��� **/
/**
  * �־��� ���Ű�� �޼����� ��ȣȭ �ؼ� �����ϸ� �޽������� ����Ű�� ��ȣȭ�� ���Ű�� �����Ű�� ��ȣȭ �� ��, 
  * �ٽ� �� ���Ű�� �޽����� ��ȣȭ �ϴ� �Լ�, �Լ� �Է����� ���� ��ȣȭ�� ���� ���Ű��  ��¿��� ���� ���� 
  * ��ȣȭ�� ���� ���Ű�� ���ؼ� ������ �־��� ���Ű�� �޼��� ��ȣȭ�� �����ߴٴ� ��
  * 
  * @param  outbuf        (Out) ��ȣȭ�� ������� ����ȴ�. inputstring�� ���� ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  inputstring   (In)  ��ȣȭ �� �޽���
  * @param  key           (In/Out) ��ȣȭ�� ���� ���Ű(16byte), �Լ��� �����Ų�Ŀ��� ���� ��ȣȭ�� ���� ���Ű�� ����ȴ�.
  * @param  prikey        (In)  ������ �����Ű, NULL�� ��� ���̺귯�� �ȿ� ����Ǿ� �ִ� �����Ű�� ���
  * @return
  *         - 0,���     : Success, ��ȣȭ �� �޽����� ����
  *         - ����       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt_with_sessionkey(void *outbuf, void *input, int input_len, void *key, const char *prikey);

/**
  * �־��� ���Ű�� �޼����� ��ȣȭ �ؼ� �����ϸ� �޽������� ����Ű�� ��ȣȭ�� ���Ű�� �����Ű�� ��ȣȭ �� ��, 
  * �ٽ� �� ���Ű�� �޽����� ��ȣȭ �ϴ� �Լ�, �Լ� �Է����� ���� ��ȣȭ�� ���� ���Ű��  ��¿��� ���� ���� 
  * ��ȣȭ�� ���� ���Ű�� ���ؼ� ������ �־��� ���Ű�� �޼��� ��ȣȭ�� �����ߴٴ� ��
  * 
  * @param  outbuf        (Out) ��ȣȭ�� ������� ����ȴ�. inputstring�� ���� ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.
  * @param  inputstring   (In)  ��ȣȭ �� �޽���, BASE64�� ���ڵ��� ���ڿ�
  * @param  key           (In/Out) ��ȣȭ�� ���� ���Ű(16byte), �Լ��� �����Ų�Ŀ��� ���� ��ȣȭ�� ���� ���Ű�� ����ȴ�.
  * @param  prikey        (In)  ������ �����Ű, NULL�� ��� ���̺귯�� �ȿ� ����Ǿ� �ִ� �����Ű�� ���
  * @return
  *         - 0,���     : Success, ��ȣȭ �� �޽����� ����
  *         - ����       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt_with_sessionkey_s(void *outbuf, const char *inputstring, void *key, const char *prikey);
#endif /* _IWEB_SERVER*/

LIB_FACE_WEB int issacweb_publickey_decrypt_c(issac_binary outbuf, issac_binary inbuf, int inbuf_len, void *privatekey_info);
LIB_FACE_WEB int issacweb_publickey_decrypt_cs(issac_binary outbuf, issac_string inputstring, issac_string privatekey_info);

/**
	 @breif ���۸� BASE64 ���ڵ� �Ѵ�.
	 @param outstring     (Out) BASE64 ���ڵ��� ���ڿ�
	 @param input         (In) ����
	 @param input_len     (In) ������ ����

	 outstring���� input_len*4/3+6 Byte ��ŭ�� �޸𸮰� �Ҵ�Ǿ� �־�� �Ѵ�.

	 @return
					- 0,���: Success, oustring�� ����
					- ����: Fail, Errorcode
	 @sa issacweb_base64_decode
	*/
LIB_FACE_WEB
int issacweb_base64_encode(issac_string outstring, issac_binary input, int input_len);

/**
	 @breif BASE64 ���ڵ��� ���ڿ��� ���ڵ� �Ѵ�.
	 @param outbuf        (Out) ���ڵ��� ����
	 @param inputstring   (In) BASE64 ���ڵ��� ���ڿ�

	 @return
					- 0,���: Success, outbuf�� ����
					- ����: Fail, Errorcode
	 @sa issacweb_base64_encode
	*/
LIB_FACE_WEB
int issacweb_base64_decode(issac_binary outbuf, issac_string inputstring);

/**
   @brief timestamp ���� �����ش�. 10 �ڸ� ���� + 10 �ڸ� �ð� -> 40 �ڸ�
   @return - SUCCESS(0) ����
           - FAIL(-1) ����
   @sa issacweb_timestamp_verify
  */
#define TIMESTAMP_LENGTH 50
LIB_FACE_WEB
int issacweb_timestamp_get(char *outstring);

/**
   @brief timestamp ���� �����Ѵ�.
   @return - SUCCESS(0) ����
           - FAIL(-1) ����
   @sa issacweb_timestamp_get
  */
LIB_FACE_WEB
int issacweb_timestamp_verify(char *timestamp, int allowedTimeSec);

LIB_FACE_WEB
int issacweb_encrypt_file_s(IN char *filePath, IN void *sessionKey);

LIB_FACE_WEB
int isssacweb_create_sessionkey(OUT void *sessionKey, IN const int sessionKeySize);

LIB_FACE_WEB
int issacweb_hash_message( issac_binary out, int *outlen, char *msg, int msglen );

LIB_FACE_WEB
int issacweb_hmac_message( issac_binary out, int *outlen, char *msg, int msglen );

LIB_FACE_WEB
int issacweb_EncodeWithAlpah(char *enKey, int *enKeyLen, void *deKey, int deKeyLen);

LIB_FACE_WEB
int issacweb_DecodeWithAlpah(void *deKey, int *deKeyLen, char *enKey, int enKeyLen);

LIB_FACE_WEB
int issacweb_getLicenseInfo( char *outstring);


#if defined(KCMVP)

LIB_FACE_WEB
int issacweb_InitializeCIS();

LIB_FACE_WEB
int issacweb_FinalizeCIS();

#endif

LIB_FACE_WEB
int issacweb_SetSymAlgorithm( int algId );

LIB_FACE_WEB
int issacweb_SetAsymAlgorithm( int algId );


#ifdef __cplusplus
}
#endif

#endif /* _ISSACWEB_H */

