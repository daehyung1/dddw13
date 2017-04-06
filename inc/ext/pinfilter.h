#ifndef _PINFILTER_H
#define _PINFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBSPEC
#undef LIBSPEC
#endif

#ifdef _WIN32

#if defined(EXPORT_PINFILTER)
#define LIBSPEC __declspec(dllexport)
#elif defined(IMPORT_PINFILTER)
#define LIBSPEC __declspec(dllimport)
#else
#define LIBSPEC
#endif

#else  /*_WIN32*/

#define LIBSPEC
#endif /*_WIN32*/

	typedef enum {
		ER_PINFILTER_WRONG_LENGTH = -3000,
		ER_PINFILTER_SAME_CASE,
		ER_PINFILTER_DICTIONARY_WORD,
		ER_PINFILTER_NO_SYMBOL,
		ER_PINFILTER_INVALID_NEWNESS,
		ER_PINFILTER_ERR_CREATE_CONF,
		ER_PINFILTER_INVALID_CONTINUITY,
		ER_PINFILTER_INVALID_REPETITION,
		ER_PINFILTER_SIMILAR_EMPLOYEENUM
		//  ER_PINFILTER_INVALID_SAMENESS
	} ERR_PINFILTER;

	/* Global defines */
#define MIN_PIN_LEN_KEY							"MinPINLength"
#define CHECK_CASE_KEY							"CheckCase"
#define CHECK_SYMBOL_KEY						"CheckSymbol"
#define CHECK_DICTIONARY_KEY				"CheckDictionary"
#define CHECK_NEWNESS_KEY						"CheckNewness"
#define CHECK_NEWNESS_TH_KEY				"CheckNewness_ThresHold"

#define CHECK_CONTINUITY_KEY				"CheckContinuity"
#define CHECK_CONTINUITY_TH_KEY			"CheckContinuity_ThresHold"
#define CHECK_REPETITION_KEY				"CheckRepetition"
#define CHECK_REPETITION_TH_KEY			"CheckRepetition_ThresHold"
#define CHECK_EMPLOYEENUM_KEY				"CheckEmployeeNum"
#define CHECK_EMPLOYEENUM_TH_KEY		"CheckEmployeeNum_ThresHold"
#define EMPLOYEENUM_VALUE_KEY				"EmployeeNum"


	LIBSPEC
		int PINFILTER_CheckPIN(const char *pin, const char *oldPin);

	// 비밀번호 검사 항목에 대해서 인자로 받는다.
	LIBSPEC
		int PINFILTER_CheckPINEx(const char *pin, const char *oldPin, int nPinPolicy);

	LIBSPEC
		int PINFILTER_CheckPINEx2(const char *pin, const char *oldPin, const char *confFileName);

#ifdef __cplusplus
}
#endif

#endif /* _PINFILTER_H */
