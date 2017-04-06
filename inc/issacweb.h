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
// 박정현 : std 용으로 쓸 수 있게 define 추가
#define issacweb_server_decrypt_s(A, B, C) issacweb_hybrid_decrypt_s(A, B, C, PRIKEY)
#define issacweb_server_decrypt(A, B, C, D) issacweb_hybrid_decrypt(A, B, C, D, PRIKEY)
#define issacweb_client_encrypt_s(A, B, C, D) issacweb_hybrid_encrypt_s(A, B, C, PUBKEY, D)
#define issacweb_client_encrypt(A, B, C, D)   issacweb_hybrid_encrypt(A, B, C, PUBKEY, D)

typedef struct _issac_session {
  void *session;
} issac_session;

// 2005. 10.18 compile시 옵션으로 알고리즘을 선택할수 있도록 추가
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
// 국보연에서 암복화시에 IV를 항상 변하는 값으로 변경요청

// 암복호화 s
LIB_FACE_WEB int issacweb_encrypt_s_iv(char *outstring, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_decrypt_s_iv(void *outbuf, char *inputstring, void *key);
             
// 암복호화 ex_s
LIB_FACE_WEB int issacweb_encrypt_ex_s_iv(char *outstring, void *input, int input_len, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_decrypt_ex_s_iv(void *outbuf, char *inputstring, void *key, int cipher_id);

// 하이브리드 암복호화 ex2 
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2_iv(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2_iv(void *outbuf, void *input, int input_len, void *key, const char *prikey, int cipher_id, int publickey_id);

// 하이브리드 복호화 s
LIB_FACE_WEB int issacweb_hybrid_decrypt_s_iv(void *outbuf, const char *inputstring, void *key, const char *prikey);

// 하이브리드 암복호화 ex_s
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex_s_iv(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex_s_iv(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id);

// 하이브리드  복호화 ex2_s
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2_s_iv(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id, int publickey_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2_s_iv(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);

// 세션키가 추가된 하이브리드 암복호화 ex_s
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex_s_iv(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex_iv(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id);


/*
  임의의 메모리 블럭(input번지부터 input_len만큼)의 메세지를 
  주어진 key를 이용하여 암호화한다.

  입력
      input : 암호화될 메세지
      input_len : 암호화될 메세지의 바이트 수
      key : 주어진 비밀키
      cipher_id : 대칭키 알고리즘
  출력
      outbuf : 암호화된 메세지
               (input_len보다 8바이트 이상의 메모리 영역이 할당되어 있어야 한다.)
*/
LIB_FACE_WEB int issacweb_encrypt(void *outbuf, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_encrypt_ex(void *outbuf, void *input, int input_len, void *key, int cipher_id);

/*
  주어진 key를 이용하여 임의의 메모리 블럭(input번지부터 input_len만큼)의 
  암호화된 메세지를 복호화한다.

  입력
      input : 암호화된 메세지
      input_len : 암호화된 메세지의 바이트 수
      key : 주어진 비밀키
      cipher_id : 대칭키 알고리즘
  출력
      outbuf : 복호화된 메세지
*/
LIB_FACE_WEB int issacweb_decrypt(void *outbuf, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_decrypt_ex(void *outbuf, void *input, int input_len, void *key, int cipher_id);

/*
   함수 issacweb_encrypt()의 변형으로 암호화된 메세지가 null-terminated 스트링으로
   주어진다.
   (outstring은 (input_len+8)*(4/3) 바이트 이상의 메모리 영역이 할당되어 있어야 한다.)
*/
LIB_FACE_WEB int issacweb_encrypt_s(char *outstring, void *input, int input_len, void *key);
LIB_FACE_WEB int issacweb_encrypt_ex_s(char *outstring, void *input, int input_len, void *key, int cipher_id);

/*
   함수 issacweb_decrypt()의 변형으로 복호화될 메세지가 null-terminated 스트링으로
   주어진다.
*/
LIB_FACE_WEB int issacweb_decrypt_s(void *outbuf, char *inputstring, void *key);
LIB_FACE_WEB int issacweb_decrypt_ex_s(void *outbuf, char *inputstring, void *key, int cipher_id);

/*
  임의의 메모리 블럭(input번지부터 input_len만큼)의 메세지를 
  주어진 publickey를 이용하여 공개키 암호화한다.

  입력
      inbuf : 암호화될 메세지
      inbuf_len : 암호화될 메세지의 바이트 수(80바이트를 넘는 경우 에러 발생)
      publickey : 주어진 공개키(base64인코딩된 스트링 형태)
  출력
      outbuf : publickey와 쌍이 되는 비공개키로만 복화화 할 수 있도록
               암호화된 메세지
               (128바이트 이상의 메모리 영역이 할당되어 있어야 한다.)
  리턴값
      outbuf에 출력되는 암호문의 길이, 음수인 경우는 에러코드
*/
LIB_FACE_WEB int issacweb_publickey_encrypt(void *outbuf, const void *inbuf, int inbuf_len, const char *publickey);
LIB_FACE_WEB int issacweb_publickey_encrypt_ex(void *outbuf, const void *inbuf, int inbuf_len, const char *publickey, int publickey_id);

/*
  주어진 비공개키를 이용하여 임의의 메모리 블럭(input번지부터 input_len만큼)의 
  암호화된 메세지를 복호화한다.

  입력
      inbuf : 암호화된 메세지
      inbuf_len : 암호화된 메세지의 바이트 수
      privatekey : 주어진 비공개키(base64인코딩된 스트링 형태)
  출력
      outbuf : 복호화된 메세지
  리턴값
      outbuf에 출력되는 복호문의 길이, 음수인 경우는 에러코드
*/
LIB_FACE_WEB int issacweb_publickey_decrypt(void *outbuf, void *inbuf, int inbuf_len, const char *privatekey);
LIB_FACE_WEB int issacweb_publickey_decrypt_ex(void *outbuf, void *inbuf, int inbuf_len, const char *privatekey, int publickey_id);

/*
  error값을 string으로 변환시켜 준다.
*/
LIB_FACE_WEB const char *errorcode_to_string(int code);

#ifdef _IWEB_CLIENT

/* 
  내부적으로 Session키를 생성하여 이를 이용하여 메시지를 암호화 한 뒤, 주어진 인증서에서 공개키를
  얻어내어 이 공개키로 Session키를 암호화한다.
  <Parameters>
    입력     
        input     : 암호화 할 메시지
        input_len : input의 길이
        pub       : Session키를 암호화 하는데 사용 될 RSA 공개키 
        cipher_id : 대칭키 알고리즘
    출력    
        outbuf    : 암호화 된 메시지, (input_len + 16)만큼의 메모리가 할당되어 있어야 한다.
        key       : buffer to store generated session key(16 byte), 서버가 암호화하여 보낼 경우를 대비하여 복호화를 위해 저장해 두어야 한다.
  <Return value>
    0, 양수 값  : 암호화 된 메시지의 길이
    음수 값       : 에러 메시지
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt(void *outbuf, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);

/* 
  내부적으로 Session키를 생성하여 이를 이용하여 메시지를 암호화 한 뒤, 주어진 인증서에서 공개키를
  얻어내어 이 공개키로 Session키를 암호화한다.
  <Parameters>
    입력     
        input     : 암호화 할 메시지
        input_len : input의 길이
        pub       : Session키를 암호화 하는데 사용 될 RSA 공개키 
        cipher_id : 대칭키 알고리즘
    출력    
        outstring : 암호화 된 메시지(base64로 encoding되어 있음)
        key       : buffer to store generated session key(16 byte), 서버가 암호화하여 보낼 경우를 대비하여 복호화를 위해 저장해 두어야 한다.
  <Return value>
    0, 양수 값  : 암호화 된 메시지의 길이
    음수 값     : 에러 메시지
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_s(char *outstring, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex_s(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_encrypt_ex2_s(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id, int publickey_id);

LIB_FACE_WEB
int issacweb_hybrid_encrypt_file_s(OUT void* sessionKey, IN char *filePath, IN char *pubKey);

/*
 * decFilePath => 값이 없는경우, 내부적으로 이름을 지어서 리턴해준다.

  2006. 1. 29 김덕수
  기존에 decFilePath가 아무런 의미가 없었음
  decFilePath가 NULL인 경우에만 .enc를 빼도록 수정
  수정하는 차에 .enc가 아닌 경우, .dec를 붙이도록 수정
*/
LIB_FACE_WEB
int issacweb_decrypt_file_s(IN OUT char *decFilePath,IN char *filePath, IN void *sessionKey);

/* limited memory 환경에서 파일 복호화 */
LIB_FACE_WEB
int issacweb_decrypt_file_lm_s(IN OUT char *decFilePath, IN char *encFilePath, IN void *sessionKey);

/*
  개요 : issacweb_hybrid_encrypt_with_sessionkey_ex_s 함수에 timestamp 기능을 추가함
  내부적으로 Session키를 생성하여 이를 이용하여 메시지를 암호화 한 뒤, 주어진 인증서에서 공개키를
  얻어내어 이 공개키로 Session키를 암호화한다.
  <Parameters>
    입력     
        input     : 암호화 할 메시지
        input_len : input의 길이
        pub       : Session키를 암호화 하는데 사용 될 RSA 공개키 
        cipher_id : 대칭키 알고리즘
        timeStamp : 서버에서 발급한 timestamp
    출력    
        outstring : 암호화 된 메시지(base64로 encoding되어 있음)
        key       : buffer to store generated session key(16 byte), 서버가 암호화하여 보낼 경우를 대비하여 복호화를 위해 저장해 두어야 한다.
  <Return value>
    0, 양수 값  : 암호화 된 메시지의 길이
    음수 값     : 에러 코드
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_and_timestamp_ex_s(
  char *outstring,
  void *input,
  int input_len,
  const char *pub,
  void *key,
  int cipher_id,
  char *timeStamp);


/** ver2.0에서 새로 추가된  클라이언트용 함수들 **/
/* 
  주어진 Session키를 사용하여 메시지를 암호화 한 뒤, 주어진 인증서에서 공개키를
  얻어내어 이 공개키로 Session키를 암호화한다.
  <Parameters>
    입력     
        input     : 암호화 할 메시지
        input_len : input의 길이
        pub       : Session키를 암호화 하는데 사용 될 RSA 공개키 
    출력    
        outbuf    : 암호화 된 메시지, (input_len + 16)만큼의 메모리가 할당되어 있어야 한다.
        key       : buffer to store generated session key(16 byte), 서버가 암호화하여 보낼 경우를 대비하여 복호화를 위해 저장해 두어야 한다.
  <Return value>
    0, 양수 값  : 암호화 된 메시지의 길이
    음수 값       : 에러 메시지
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey(void *outbuf, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex(void *outbuf, void *input, int input_len, const char *pub, void *key, int cipher_id);

/* 
  주어진 Session키를 사용하여 메시지를 암호화 한 뒤, 주어진 인증서에서 공개키를
  얻어내어 이 공개키로 Session키를 암호화한다.
  <Parameters>
    입력     
        input     : 암호화 할 메시지
        input_len : input의 길이
        pub       : Session키를 암호화 하는데 사용 될 RSA 공개키 
    출력    
        outstring : 암호화 된 메시지(base64로 encoding되어 있음)
        key       : buffer to store generated session key(16 byte), 서버가 암호화하여 보낼 경우를 대비하여 복호화를 위해 저장해 두어야 한다.
  <Return value>
    0, 양수 값  : 암호화 된 메시지의 길이
    음수 값     : 에러 메시지
*/
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_s(char *outstring, void *input, int input_len, const char *pub, void *key);
LIB_FACE_WEB int issacweb_hybrid_encrypt_with_sessionkey_ex_s(char *outstring, void *input, int input_len, const char *pub, void *key, int cipher_id);
/**
	 @breif 메세지를 인증서를 사용하여 공개키 방식으로 암호화 한다.
	 @param outbuf        (Out) 암호화된 메세지
	 @param inbuf         (In) 암호화할 원문 메세지
	 @param inbuf_len     (In) 암호화할 원문 메세지의 길이(80 이하)
	 @param certificate   (In) 공개키 방식 암호화에 필요한 BASE64 인코딩된 인증서

	 outbuf에는 256 Byte 만큼의 메모리가 할당되어 있어야 한다.

	 @return
					- 0,양수: Success, 암호화된 메세지의 길이
					- 음수: Fail, Errorcode
	 @sa issacweb_publickey_encrypt_s 
	*/
LIB_FACE_WEB 
int issacweb_publickey_encrypt_c(issac_binary outbuf, issac_binary inbuf, int inbuf_len, issac_string certificate);

/**
	 @breif 메세지를 인증서를 사용하여 공개키 방식으로 암호화 한다.
	 @param outstring     (Out) 암호화된 메세지, BASE64 인코딩된 문자열
	 @param inbuf         (In) 암호화할 원문 메세지
	 @param inbuf_len     (In) 암호화할 원문 메세지의 길이(80 이하)
	 @param certificate   (In) 공개키 방식 암호화에 필요한 BASE64 인코딩된 인증서

	 outstring에는 256*4/3 +6 Byte 만큼의 메모리가 할당되어 있어야 한다.

	 @return
					- 0,양수: Success, 암호화된 메세지의 길이
					- 음수: Fail, Errorcode
	 @sa issacweb_publickey_encrypt 
	*/
LIB_FACE_WEB 
int issacweb_publickey_encrypt_cs(issac_string outstring, issac_binary inbuf, int inbuf_len, issac_string certificate);

/**
	 @breif 메세지를 인증서를 사용하여 하이브리드 방식으로 암호화 한다.
	 @param outbuf        (Out) 암호화된 메세지
	 @param input         (In) 암호화할 원문 메세지
	 @param input_len     (In) 암호화할 원문 메세지의 길이
	 @param certificate   (In) 하이브리드 방식 암호화에 필요한 BASE64 인코딩된 인증서
	 @param key           (In) 암호화에 쓰일 대칭키(16 Byte)

	 outbuf에는 input_len+300 Byte 만큼의 메모리가 할당되어 있어야 한다.

	 @return
					- 0,양수: Success, 암호화된 메세지의 길이
					- 음수: Fail, Errorcode
	 @sa issacweb_hybrid_encrypt_s 
	*/
LIB_FACE_WEB
int issacweb_hybrid_encrypt_c(issac_binary outbuf, issac_binary input, int input_len, issac_string certificate, issac_binary key);

/**
	 @breif 메세지를 인증서를 사용하여 하이브리드 방식으로 암호화 한다.
	 @param outstring     (Out) 암호화된 메세지, BASE64 인코딩된 문자열
	 @param input         (In) 암호화할 원문 메세지
	 @param input_len     (In) 암호화할 원문 메세지의 길이
	 @param certificate   (In) 하이브리드 방식 암호화에 필요한 BASE64 인코딩된 인증서
	 @param key           (In) 암호화에 쓰일 대칭키(16 Byte)

	 outstring에는 (input_len+300)*4/3 Byte 만큼의 메모리가 할당되어 있어야 한다.

	 @return
					- 0,양수: Success, 암호화된 메세지의 길이
					- 음수: Fail, Errorcode
	 @sa issacweb_hybrid_encrypt_s 
	*/
LIB_FACE_WEB 
int issacweb_hybrid_encrypt_cs(issac_string outstring, issac_binary input, int input_len, issac_string certificate, issac_binary key);

#endif /* _IWEB_CLIENT */

#ifdef _IWEB_SERVER

/**
  * 메시지안의 공개키로 암호화된 비밀키를 비공개키로 복호화 한 뒤, 다시 이 비밀키로 메시지를 복호화 하는 함수
  * 
  * @param  outbuf        (Out) 복호화된 결과값이 저장된다. inputstring의 길이 만큼 메모리가 할당되어 있어야 한다.
  * @param  inputstring   (In)  복호화 할 메시지
  * @param  key           (Out) 복호화된 비밀키가 저장된다. 16byte이상의 메모리가 할당되어 있어야 한다.
  * @param  prikey        (In)  서버의 비공개키, NULL일 경우 라이브러리 안에 저장되어 있는 비공개키를 사용
  * @param  cipher_id     (In)  대칭키 알고리즘
  * @return
  *         - 0,양수     : Success, 복호화 된 메시지의 길이
  *         - 음수       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt(void *outbuf, void *input, int input_len, void *key, const char *prikey);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex(void *outbuf, void *input, int input_len, void *key, const char *prikey, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2(void *outbuf, void *input, int input_len, void *key, const char *prikey, int cipher_id, int publickey_id);

/**
  * 메시지안의 공개키로 암호화된 비밀키를 비공개키로 복호화 한 뒤, 다시 이 비밀키로 메시지를 복호화 하는 함수
  * 
  * @param  outbuf        (Out) 복호화된 결과값이 저장된다. inputstring의 길이 만큼 메모리가 할당되어 있어야 한다.
  * @param  inputstring   (In)  복호화 할 메시지, BASE64로 인코딩된 문자열
  * @param  key           (Out) 복호화된 비밀키가 저장된다. 16byte이상의 메모리가 할당되어 있어야 한다.
  * @param  prikey        (In)  서버의 비공개키, NULL일 경우 라이브러리 안에 저장되어 있는 비공개키를 사용
  * @param  cipher_id     (In)  대칭키 알고리즘
  * @return
  *         - 0,양수     : Success, 복호화 된 메시지의 길이
  *         - 음수       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt_s(void *outbuf, const char *inputstring, void *key, const char *prikey);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex_s(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id);
LIB_FACE_WEB int issacweb_hybrid_decrypt_ex2_s(void *outbuf, const char *inputstring, void *key, const char *prikey, int cipher_id, int publickey_id);

LIB_FACE_WEB
int issacweb_hybrid_decrypt_file_s(OUT void *sessionKey, IN char *encFilePath, IN char *priKey );

/**
  * License 관리를 위해 추가된 함수들
  * @author Jypark
  * @date   2000.10.24
  */
/**
  * 메시지안의 공개키로 암호화된 비밀키를 비공개키로 복호화 한 뒤, 다시 이 비밀키로 메시지를 복호화 하는 함수
  * 서버의 비공개키는 키 관리 모듈에서 동적으로 가져온다.
  * 
  * @param  outbuf        (Out) 복호화된 결과값이 저장된다. inputstring의 길이 만큼 메모리가 할당되어 있어야 한다.
  * @param  inputstring   (In)  복호화 할 메시지, BASE64로 인코딩된 문자열
  * @param  key           (Out) 복호화된 비밀키가 저장된다. 16byte이상의 메모리가 할당되어 있어야 한다.
  * @return
  *         - 0,양수     : Success, 복호화 된 메시지의 길이
  *         - 음수       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt2(void *outbuf, void *input, int input_len, void *key);

/**
  * 메시지안의 공개키로 암호화된 비밀키를 비공개키로 복호화 한 뒤, 다시 이 비밀키로 메시지를 복호화 하는 함수
  * 서버의 비공개키는 키 관리 프로그램으로부터 동적으로 가져온다.
  * 
  * @param  outbuf        (Out) 복호화된 결과값이 저장된다. inputstring의 길이 만큼 메모리가 할당되어 있어야 한다.
  * @param  inputstring   (In)  복호화 할 메시지, BASE64로 인코딩된 문자열
  * @param  key           (Out) 복호화된 비밀키가 저장된다. 16byte이상의 메모리가 할당되어 있어야 한다.
  * @return
  *         - 0,양수     : Success, 복호화 된 메시지의 길이
  *         - 음수       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt2_s(void *outbuf, const char *inputstring, void *key); 

/* 이중 암호화 함수 */
LIB_FACE_WEB int d2b_hybrid_decrypt(void *output, void *key, void *input, const void *prikey);

LIB_FACE_WEB int d2b_hybrid_decrypt2(void *output, void *key, void *input, const void *prikey);
LIB_FACE_WEB int d2b_get_certificate(char* certificate, int* certificate_len, int certificate_alloc_len, void *input);

LIB_FACE_WEB int d2s_hybrid_decrypt(void *output, void *key, void *input, const void *prikey);

/** ver2.0에서 새로 추가된  서버용 함수들 **/
/**
  * 주어진 비밀키로 메세지를 복호화 해서 실패하면 메시지안의 공개키로 암호화된 비밀키를 비공개키로 복호화 한 뒤, 
  * 다시 이 비밀키로 메시지를 복호화 하는 함수, 함수 입력으로 넣은 복호화에 사용될 비밀키와  출력에서 나온 실제 
  * 복호화에 사용된 비밀키를 비교해서 같으면 주어진 비밀키로 메세지 목호화에 성공했다는 뜻
  * 
  * @param  outbuf        (Out) 복호화된 결과값이 저장된다. inputstring의 길이 만큼 메모리가 할당되어 있어야 한다.
  * @param  inputstring   (In)  복호화 할 메시지
  * @param  key           (In/Out) 복호화에 사용될 비밀키(16byte), 함수를 실행시킨후에는 실제 복호화에 사용된 비밀키가 저장된다.
  * @param  prikey        (In)  서버의 비공개키, NULL일 경우 라이브러리 안에 저장되어 있는 비공개키를 사용
  * @return
  *         - 0,양수     : Success, 복호화 된 메시지의 길이
  *         - 음수       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt_with_sessionkey(void *outbuf, void *input, int input_len, void *key, const char *prikey);

/**
  * 주어진 비밀키로 메세지를 복호화 해서 실패하면 메시지안의 공개키로 암호화된 비밀키를 비공개키로 복호화 한 뒤, 
  * 다시 이 비밀키로 메시지를 복호화 하는 함수, 함수 입력으로 넣은 복호화에 사용될 비밀키와  출력에서 나온 실제 
  * 복호화에 사용된 비밀키를 비교해서 같으면 주어진 비밀키로 메세지 목호화에 성공했다는 뜻
  * 
  * @param  outbuf        (Out) 복호화된 결과값이 저장된다. inputstring의 길이 만큼 메모리가 할당되어 있어야 한다.
  * @param  inputstring   (In)  복호화 할 메시지, BASE64로 인코딩된 문자열
  * @param  key           (In/Out) 복호화에 사용될 비밀키(16byte), 함수를 실행시킨후에는 실제 복호화에 사용된 비밀키가 저장된다.
  * @param  prikey        (In)  서버의 비공개키, NULL일 경우 라이브러리 안에 저장되어 있는 비공개키를 사용
  * @return
  *         - 0,양수     : Success, 복호화 된 메시지의 길이
  *         - 음수       : Fail, Errorcode
  */
LIB_FACE_WEB int issacweb_hybrid_decrypt_with_sessionkey_s(void *outbuf, const char *inputstring, void *key, const char *prikey);
#endif /* _IWEB_SERVER*/

LIB_FACE_WEB int issacweb_publickey_decrypt_c(issac_binary outbuf, issac_binary inbuf, int inbuf_len, void *privatekey_info);
LIB_FACE_WEB int issacweb_publickey_decrypt_cs(issac_binary outbuf, issac_string inputstring, issac_string privatekey_info);

/**
	 @breif 버퍼를 BASE64 인코딩 한다.
	 @param outstring     (Out) BASE64 인코딩된 문자열
	 @param input         (In) 버퍼
	 @param input_len     (In) 버퍼의 길이

	 outstring에는 input_len*4/3+6 Byte 만큼의 메모리가 할당되어 있어야 한다.

	 @return
					- 0,양수: Success, oustring의 길이
					- 음수: Fail, Errorcode
	 @sa issacweb_base64_decode
	*/
LIB_FACE_WEB
int issacweb_base64_encode(issac_string outstring, issac_binary input, int input_len);

/**
	 @breif BASE64 인코딩된 문자열을 디코딩 한다.
	 @param outbuf        (Out) 디코딩된 버퍼
	 @param inputstring   (In) BASE64 인코딩된 문자열

	 @return
					- 0,양수: Success, outbuf의 길이
					- 음수: Fail, Errorcode
	 @sa issacweb_base64_encode
	*/
LIB_FACE_WEB
int issacweb_base64_decode(issac_binary outbuf, issac_string inputstring);

/**
   @brief timestamp 값을 돌려준다. 10 자리 랜덤 + 10 자리 시간 -> 40 자리
   @return - SUCCESS(0) 성공
           - FAIL(-1) 실패
   @sa issacweb_timestamp_verify
  */
#define TIMESTAMP_LENGTH 50
LIB_FACE_WEB
int issacweb_timestamp_get(char *outstring);

/**
   @brief timestamp 값을 검증한다.
   @return - SUCCESS(0) 성공
           - FAIL(-1) 실패
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

