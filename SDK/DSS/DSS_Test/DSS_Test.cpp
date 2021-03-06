// DSS_Test.cpp : Defines the entry point for the application.
//
//旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
//早  濛撩橾 : 2006.11.16                                     早
//早  濛撩濠 : 歜謙僥                                         早
//早  頂  辨 : IF_SDK蒂 DSS煎 衙ёи DLL曖 纔蝶お囀萄.        早
//曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭
//

#include "stdafx.h"
#include "resource.h"
#include "DSS.h"

// Error Code
#define IDN_ERR_CODE_405                405

#define MAX_LOADSTRING                  100
#define MAX_BUFFER_SIZE                 4096
#define BUFFER_SIZE                     1024
#define FILE_COUNT                      3
#define DEFAULT_FILE_COUNT              1
#define FILE_INDEX                      0
#define ISSUCCESS(x)                    (x) ? TEXT("= Success") : TEXT("= Failure")

#define REG_USER_DN                     TEXT("cn=偃嫦纔蝶攪7_8C1BCBBDFFA9AC1C9DD8,ou=pki users,o=kookmin,c=kr")
#define REG_USER_DN2                    TEXT("cn=薑撩敕_782006D73B5C1CDE1D07,ou=pki users,o=kookmin,c=kr")
#define REG_SUB_KEY                     TEXT("SOFTWARE\\Penta Security Systems\\LogonManager\\User Map")
#define REGISTRY_USER_GROUP             TEXT("Group")
#define REGISTRY_USER_GROUPADMIN        TEXT("GroupAdmin")
#define REGISTRY_USER_IMAGE_PATH        TEXT("ImagePath")
#define REGISTRY_USER_EMPLOYEENUMBER    TEXT("EmployeeNumber")

#define IDC_LISTBOX   1
#define IDC_EDITBOX   2
#define IDC_BTN1      3
#define IDC_BTN2      4
#define IDC_BTN3      5
#define IDC_BTN4      6
#define IDC_BTN5      7
#define IDC_BTN6      8
#define IDC_BTN7      9
#define IDC_BTN8     10
#define IDC_BTN9     11
#define IDC_BTN10    12
#define IDC_BTN11    13
#define IDC_BTN12    14
#define IDC_BTN13    15
#define IDC_BTN14    16
#define IDC_BTN15    17

// Global Variables:
HINSTANCE hInst;
TCHAR     szTitle[MAX_LOADSTRING];
TCHAR     szWindowClass[MAX_LOADSTRING];
TCHAR     g_szResult[MAX_BUFFER_SIZE];
HWND      hWnd;
HWND      hListBox, hEditBox;
HWND      hButton1,  hButton2,  hButton3,  hButton4,  hButton5;
HWND      hButton6,  hButton7,  hButton8,  hButton9,  hButton10;
HWND      hButton11, hButton12, hButton13, hButton14, hButton15;
RECT      rt = {5, 5, 285, 390};

// Foward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
void InsertResultData(PTCHAR pfun_name, BOOL bret, PTCHAR pMoreInfo, PTCHAR target);
void InsertResultData(PTCHAR pfun_name, BOOL bret);
void CardResultData(PTCHAR pfun_name, BOOL bret);
void LonginStatusResult(PTCHAR pfun_name, INT nret);
void VerifyEmpResult(PTCHAR pfun_name, INT nret);
BOOL SetIFFILELIST(IFFILELIST *iffilelist, PTCHAR szSrcName, PTCHAR szTgtName);

// 纔蝶お л熱
void Test_EncryptFiles();
void Test_EncryptFilesTo();
void Test_EncryptAdd();
void Test_DecryptFiles();
void Test_CheckCard();
void Test_GetSSOStatus();
void Test_VerifyEmp();
void Test_GetUserImagePathCheckDownLoad();
void Test_GetGroup();
void Test_GetGroupAdmin();
void Test_getSubjectCN();
void Test_GetRegDefaultImage();
void Test_DeleteUserImageInfo();
void Test_SendLog();
void Test_GetVersion();

// Procedure 
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
  MSG msg;
  HACCEL hAccelTable;
  
  // Initialize global strings
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_DSS_TEST, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);
  
  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow)) 
  {
    return FALSE;
  }
  
  hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DSS_TEST);
  
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  
  return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wcex;
  
  wcex.cbSize = sizeof(WNDCLASSEX); 
  
  wcex.style			= CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc	= (WNDPROC)WndProc;
  wcex.cbClsExtra		= 0;
  wcex.cbWndExtra		= 0;
  wcex.hInstance		= hInstance;
  wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DSS_TEST);
  wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName	= NULL;//(LPCSTR)IDC_DSPAPI_TEST;
  wcex.lpszClassName	= szWindowClass;
  wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
  
  return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // Store instance handle in our global variable
  
  hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, 780, 500, NULL, NULL, hInstance, NULL);
  
  if (!hWnd)
  {
    return FALSE;
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  TCHAR szHello[MAX_LOADSTRING];
  LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
  
  switch (message) 
  {
  case WM_CREATE:
    {
      hListBox = CreateWindow(TEXT("listbox"), TEXT("ListBox"), 
                              WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY, 
                              0, 0, 460, 390, hWnd, (HMENU)IDC_LISTBOX, 0, hInst, 0);
      hEditBox = CreateWindow(TEXT("edit"), TEXT("EditBox"), 
                              WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
                              0, 400, 460, 20, hWnd, (HMENU)IDC_EDITBOX, 0, hInst, 0);
      hButton1 = CreateWindow(TEXT("button"), TEXT("DSPAPI_EncryptFiles"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465,   0, 300, 30, hWnd, (HMENU)IDC_BTN1, 0, hInst, 0);
      hButton2 = CreateWindow(TEXT("button"), TEXT("DSPAPI_EncryptFilesTo"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465,  30, 300, 30, hWnd, (HMENU)IDC_BTN2, 0, hInst, 0);
      hButton3 = CreateWindow(TEXT("button"), TEXT("DSPAPI_EncryptAdd"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465,  60, 300, 30, hWnd, (HMENU)IDC_BTN3, 0, hInst, 0);
      hButton4 = CreateWindow(TEXT("button"), TEXT("DSPAPI_DecryptFiles"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465,  90, 300, 30, hWnd, (HMENU)IDC_BTN4, 0, hInst, 0);
      hButton5 = CreateWindow(TEXT("button"), TEXT("DSPAPI_CheckCard"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 120, 300, 30, hWnd, (HMENU)IDC_BTN5, 0, hInst, 0);
      hButton6 = CreateWindow(TEXT("button"), TEXT("DSPAPI_GetSSOStatus"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 150, 300, 30, hWnd, (HMENU)IDC_BTN6, 0, hInst, 0);
      hButton7 = CreateWindow(TEXT("button"), TEXT("DSPAPI_VerifyEmp"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 180, 300, 30, hWnd, (HMENU)IDC_BTN7, 0, hInst, 0);
      hButton8 = CreateWindow(TEXT("button"), TEXT("DSPAPI_GetUserImagePathCheckDownLoad"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 210, 300, 30, hWnd, (HMENU)IDC_BTN8, 0, hInst, 0);
      hButton9 = CreateWindow(TEXT("button"), TEXT("DSPAPI_GetGroup"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 240, 300, 30, hWnd, (HMENU)IDC_BTN9, 0, hInst, 0);
      hButton10 = CreateWindow(TEXT("button"), TEXT("DSPAPI_GetGroupAdmin"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 270, 300, 30, hWnd, (HMENU)IDC_BTN10, 0, hInst, 0);
      hButton11 = CreateWindow(TEXT("button"), TEXT("Test_getSubjectCN"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 300, 300, 30, hWnd, (HMENU)IDC_BTN11, 0, hInst, 0);
      hButton12 = CreateWindow(TEXT("button"), TEXT("Test_GetRegDefaultImage"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 330, 300, 30, hWnd, (HMENU)IDC_BTN12, 0, hInst, 0);
      hButton13 = CreateWindow(TEXT("button"), TEXT("Test_DeleteUserImageInfo"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 360, 300, 30, hWnd, (HMENU)IDC_BTN13, 0, hInst, 0);
      hButton14 = CreateWindow(TEXT("button"), TEXT("Test_SendLog"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 390, 300, 30, hWnd, (HMENU)IDC_BTN14, 0, hInst, 0);
      hButton15 = CreateWindow(TEXT("button"), TEXT("Test_GetVersion"), 
                              WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                              465, 420, 300, 30, hWnd, (HMENU)IDC_BTN15, 0, hInst, 0);
    }
    break;
    
  case WM_COMMAND:
    {
      switch(wParam) {
      case IDC_BTN1:  Test_EncryptFiles();                  break;
      case IDC_BTN2:  Test_EncryptFilesTo();              	break;
      case IDC_BTN3:  Test_EncryptAdd();                    break;
      case IDC_BTN4:  Test_DecryptFiles();                  break;
      case IDC_BTN5:  Test_CheckCard();                     break;
      case IDC_BTN6:  Test_GetSSOStatus();                  break;
      case IDC_BTN7:  Test_VerifyEmp();                     break;
      case IDC_BTN8:  Test_GetUserImagePathCheckDownLoad(); break;
      case IDC_BTN9:  Test_GetGroup();                      break;
      case IDC_BTN10: Test_GetGroupAdmin();                 break;
      case IDC_BTN11: Test_getSubjectCN();                  break;
      case IDC_BTN12: Test_GetRegDefaultImage();            break;
      case IDC_BTN13: Test_DeleteUserImageInfo();           break;
      case IDC_BTN14: Test_SendLog();                       break;
      case IDC_BTN15: Test_GetVersion();                    break;
      }
    }
    break;
    
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
    
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

BOOL SetIFFILELIST(IFFILELIST *iffilelist, PTCHAR szSrcName, PTCHAR szTgtName)
{
  if( !szSrcName && !szSrcName )
    return FALSE;
  
  lstrcpy(iffilelist->szSrcName,  szSrcName);
  lstrcpy(iffilelist->szTgtName,  szTgtName);
  
  return TRUE;
}

void InsertResultData(PTCHAR pfun_name, BOOL bret, PTCHAR pMoreInfo, PTCHAR target)
{
  TCHAR temp[BUFFER_SIZE] = {0,};
  INT   index = 0;

  wsprintf(temp, TEXT("%s %s  Info : %s"), pfun_name, 
    ISSUCCESS(bret), lstrlen(pMoreInfo) ? pMoreInfo : target);
  
  index = SendMessage(hListBox, LB_GETCURSEL,0,0);
  SendMessage(hListBox, LB_ADDSTRING, index, (LPARAM)temp);
}

void InsertResultData(PTCHAR pfun_name, BOOL bret)
{
  TCHAR temp[BUFFER_SIZE] = {0,};
  INT   index = 0;
  
  wsprintf(temp, TEXT("%s Info : %s"), pfun_name, ISSUCCESS(bret));
  
  index = SendMessage(hListBox, LB_GETCURSEL,0,0);
  SendMessage(hListBox, LB_ADDSTRING, index, (LPARAM)temp);
}

void CardResultData(PTCHAR pfun_name, INT nret)
{
  TCHAR temp[BUFFER_SIZE] = {0,};  
  INT   index = 0;
  TCHAR szCardState[5][256] = {{TEXT("蘋萄鳶殮 鼻鷓")},
                               {TEXT("蘋萄陛 橈朝 鼻鷓")},
                               {TEXT("葬渦晦 螃盟")},
                               {TEXT("SSO 婦溼Щ煎斜極檜 撲纂腎雖 彊懊擠")},
                               {TEXT("л熱 ��轎 褒ぬ")}};
  
  wsprintf(temp, TEXT("%s = %s"), pfun_name, 
    (nret == IDN_ERR_CODE_405 ) ? TEXT("蘋萄葬渦 open error") : szCardState[nret]);
  
  index = SendMessage(hListBox, LB_GETCURSEL,0,0);
  SendMessage(hListBox, LB_ADDSTRING, index, (LPARAM)temp);
}

void LonginStatusResult(PTCHAR pfun_name, INT nret)
{
  INT   index = 0;
  TCHAR temp[BUFFER_SIZE] = {0,};
  TCHAR szLoginStatus[5][256] = {{TEXT("煎斜檣 鼻鷓(ISSAC-File)")},
                                 {TEXT("煎斜檣 鼻鷓 (OAC)")}, 
                                 {TEXT("煎斜嬴醒 鼻鷓")}, 
                                 {TEXT("SSOЩ煎斜極檜 撲纂 腎雖 彊懊蝙")}, 
                                 {TEXT("憲熱橈朝 縑楝")}};
  
  wsprintf(temp, TEXT("%s = %s"), pfun_name, szLoginStatus[nret]);
  
  index = SendMessage(hListBox, LB_GETCURSEL,0,0);
  SendMessage(hListBox, LB_ADDSTRING, index, (LPARAM)temp);
}

void VerifyEmpResult(PTCHAR pfun_name, INT nret)
{
  TCHAR temp[BUFFER_SIZE] = {0,};
  INT   index = 0;

  if( nret == 0xffffffff )
  {
    wsprintf(temp, TEXT("%s = 籀葬 褒ぬ"), pfun_name);
  }
  else if( nret < 100 )
  {
    TCHAR szVerifyEmp[12][256] = {{TEXT("鼻鷓(good) 嶸�蕉�(valid)")},
                                  {TEXT("鼻鷓(good) 嶸�蕉�(invalid)")},
                                  {TEXT("鼻鷓(revoke) 嶸�蕉�(valid)")},
                                  {TEXT("鼻鷓(revoke) 嶸�蕉�(invalid)")},
                                  {TEXT("煎斜嬴醒 鼻鷓")},
                                  {TEXT("⑷營 餌辨濠曖 CN擊 陛螳螢熱 橈蝙")},
                                  {TEXT("⑷營餌辨濠曖 衛葬橡擊 陛螳螢熱橈蝙")},
                                  {TEXT("嶸�褲狫� 彊擎 衛葬橡")},
                                  {TEXT("�秣瞍麥凶懋�")},
                                  {TEXT("�秣磔釋� 縑楝")},
                                  {TEXT("鱔褐遽綠 縑楝")},
                                  {TEXT("等檜攪 瞪歎 縑楝")}};
    
    wsprintf(temp, TEXT("%s = %s"), pfun_name, szVerifyEmp[nret]);
  }
  else if( nret > 100 && nret < 200 )
  {
    TCHAR szVerifyEmp2[6][256] = {{TEXT("檣隸憮諦 橾纂ж朝 餌辨濠陛 橈擠")},
                                  {TEXT("DB縑楝")},
                                  {TEXT("檣隸憮蒂 瓊擊 熱 橈擠")},
                                  {TEXT("霜錳薑爾蒂 瓊擊 熱 橈擠")},
                                  {TEXT("橢擎 ч廓高檜 傘鼠 躑")},
                                  {TEXT("澀跤瞪歎嫡擎 瞪僥")}};
    wsprintf(temp, TEXT("%s = %s"), pfun_name, szVerifyEmp2[nret]);
  }
  else if( nret >= 200 && nret < 300 )
  {
    switch(nret) {
    case 200:
      wsprintf(temp, TEXT("%s = SSO陛 撲纂腎雖 彊懊擠"), pfun_name);
      break;
    case 201:
      wsprintf(temp, TEXT("%s = SSO �秣瞍麥� 螃盟"), pfun_name);
      break;
    case 203:
      wsprintf(temp, TEXT("%s = 塭檜粽楝葬煎萄 褒ぬ"), pfun_name);
      break;
    case 221:
      wsprintf(temp, TEXT("%s = 塭檜粽楝葬 л熱 ��轎褒ぬ"), pfun_name);
      break;
    }
  }
  else if( nret == 300 )
  {
    wsprintf(temp, TEXT("%s = 殮溘高 螃盟"), pfun_name);
  }
  index = SendMessage(hListBox, LB_GETCURSEL,0,0);
  SendMessage(hListBox, LB_ADDSTRING, index, (LPARAM)temp);
}



void Test_EncryptFiles()
{
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  //													DSPAPI_EncryptFiles
  // 
  // Desc.        : 懍���� й だ橾菟擊 懍���� и棻 . 頂睡縑憮 EncryptFile��轎 
  // 
  //													Param
  // pFileList    : 錳獄 だ橾菟曖 葬蝶お                            [ in / out ]
  // nFileCnt     : 懍���� п撿 й だ橾菟曖 偎熱, 撩奢и 偎熱 葬欐  [ in / out ]
  //
  //
  // return value : 撩奢ж賊 TRUE, 褒ぬж賊 FALSE 
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
 
  INT        nCount = FILE_COUNT;
  IFFILELIST filelist[FILE_COUNT] = {0,};
  BOOL       bRet = FALSE;
  TCHAR src_data[FILE_COUNT][MAX_LOADSTRING] = {{TEXT("sample_data\\sample1.txt")},
                                                {TEXT("sample_data\\sample2.xls")},
                                                {TEXT("sample_data\\sample3.ppt")}};
  
  TCHAR tgt_data[FILE_COUNT][MAX_LOADSTRING] = {{TEXT("sample_data\\sample1.enc")},
                                                {TEXT("sample_data\\sample2.enc")},
                                                {TEXT("sample_data\\sample3.enc")}};
  
  for( int i = 0; i < FILE_COUNT; ++i )
  {
    if( !SetIFFILELIST(&filelist[i], src_data[i], tgt_data[i]) )
    {
      MessageBox(hWnd, TEXT("SetIFFILELIST() 褒ぬ"), TEXT("info"), MB_OK);
      return;
    }
    
    bRet = DSS_EncryptFiles(&filelist[i], &i);
    
    if( bRet )
      InsertResultData(TEXT("DSPAPI_EncryptFiles"), bRet, filelist[i].szMoreInfo, tgt_data[i]);
  }
}



void Test_EncryptFilesTo()
{
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  //													DSPAPI_EncryptFilesTo
  // ---------------------------------------------------------------------------
  //													
  // 餌辨濠煎睡攪 熱褐濠 葬蝶お蒂 �僱磈炾� 餌辨濠諦 熱褐濠曖 Cert蒂 �僱磈狤� 
  // だ橾縑 渠п 懍���飛� 熱чи棻.
  // ---------------------------------------------------------------------------
  //													
  // pFileList    : 錳獄 だ橾菟曖 葬蝶お                            [ in / out ]
  // pFileCnt     : 懍���� п撿 й だ橾菟曖 偎熱, 撩奢и 偎熱 葬欐  [ in / out ]
  //
  //----------------------------------------------------------------------------
  // 撩奢ж賊 TRUE, 褒ぬж賊 FALSE 
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  BOOL bRet    = FALSE;
  INT  nCount2 = 0;
  IFFILELIST filelist = {0,}; 
  TCHAR src_data[256] = TEXT("sample_data\\sample1.txt");
  TCHAR tgt_data[256] = TEXT("sample_data\\sample1.enc");
  
  if( !SetIFFILELIST(&filelist, src_data, tgt_data) )
  {
    MessageBox(hWnd, TEXT("SetIFFILELIST() 褒ぬ"), TEXT("info"), MB_OK);
    return;
  }

  bRet = DSS_EncryptFilesTo(&filelist, &nCount2);
  if( bRet )
  {
     InsertResultData(TEXT("DSPAPI_EncryptFilesTo"), bRet, filelist.szMoreInfo, tgt_data);
  }
}



void Test_EncryptAdd()
{
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  //														DSPAPI_EncryptAdd
  // -----------------------------------------------------------------------
  // 懍���音� だ橾縑 熱褐濠 蹺陛
  //
  // lpszEncryptedFileName : 熱褐濠蒂 蹺陛й 懍���音� だ橾
  //
  // return value : 撩奢ж賊 TRUE, 褒ぬ衛 FALSE
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  BOOL  bRet = FALSE;
  IFFILELIST filelist = {0,}; 
  TCHAR src_data[256] = TEXT("sample_data\\sample1.txt");
  TCHAR tgt_data[256] = TEXT("sample_data\\sample1.enc");
  
  if( !SetIFFILELIST(&filelist, src_data, tgt_data) )
  {
    MessageBox(hWnd, TEXT("SetIFFILELIST() 褒ぬ"), TEXT("info"), MB_OK);
    return;
  }
  
  bRet = DSS_EncryptAdd(tgt_data);
  
  if( bRet )
    InsertResultData(TEXT("DSPAPI_EncryptAdd"), bRet);  
}



void Test_DecryptFiles()
{
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  //													DSPAPI_DecryptFiles
  // 
  // Desc.        : 懍���� й だ橾菟擊 懍���� и棻 
  //								餌辨濠曖 CnK蒂 陛螳螃堅 犒���飛� 熱чи棻
  // 
  //													Param
  // pFileList    : 犒�值倆� 懍���音� だ橾菟曖 葬蝶お               [ in / out ]
  // nFileCnt     : 犒���� п撿 й だ橾菟曖 偎熱, 撩奢и 偎熱 葬欐  [ in / out ]
  //
  //
  // return value : 撩奢ж賊 TRUE, 褒ぬж賊 FALSE 
  //收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
  INT   nCount = 0;
  BOOL  bRet   = FALSE;
  IFFILELIST filelist = {0,}; 
  TCHAR src_data[256] = TEXT("sample_data\\sample1.txt");
  TCHAR tgt_data[256] = TEXT("sample_data\\sample1.enc");
  
  if( !SetIFFILELIST(&filelist, src_data, tgt_data) )
  {
    MessageBox(hWnd, TEXT("SetIFFILELIST() 褒ぬ"), TEXT("info"), MB_OK);
    return;
  }

  bRet = DSS_DecryptFiles(&filelist, &nCount);
  InsertResultData(TEXT("DSPAPI_DecryptFiles"), bRet, filelist.szMoreInfo, tgt_data);
}



void Test_CheckCard()
{
  //旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
  //早                                                                              早
  //早                          DSPAPI_CheckCard   		                              早
  //早  2004. 08.22 梯鼻з                                                          早
  //早                                                                              早
  //早  蝶葆お蘋萄曖 鳶殮罹睡蒂 憲嬴魚棻.                                           早
  //早                                                                              早
  //早                                                                              早
  //早  return value :  0  = card Inserted                                          早
  //早                  1  = card removed                                           早
  //早                  IDN_ERR_CODE_405  = 蘋萄葬渦 open error 								    早
  //早                  SspMod_CONTEXT_NULL                                         早
  //曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭
  INT nRet = 0;
 
  nRet = DSS_CheckCard();
  CardResultData(TEXT("DSPAPI_CheckCard"), nRet);
}



void Test_GetSSOStatus()
{
  //旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
  //早                                                                              早
  //早                          DSPAPI_GetSSOStatus	                                早
  //早  2004. 08.22 梯鼻з                                                          早
  //早                                                                              早
  //早  1.  衛蝶蠱縑 MS煎 煎斜檣 ц朝雖, IF煎 煎斜檣 ц朝雖 憲嬴魚棻                早
  //早  2.  SSO縑 煎斜檣 ц朝雖 憲嬴魚棻                                            早
  //早  3.  唸婁                                                                    早
  //曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭
  INT nRet = FALSE;
  
  nRet = DSS_GetSSOStatus();
  LonginStatusResult(TEXT("DSPAPI_GetSSOStatus"), nRet);
}



void Test_VerifyEmp()
{
  //旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
  //早                                                                              早
  //早                          DSPAPI_VerifyEmp	                                  早
  //早  2004. 08.23 梯鼻з                                                          早
  //早                                                                              早
  //早  1.  殮溘高 褻餌				                                                      早
  //早  2.  SSO縑 煎斜檣 鼻鷓檣雖 褻餌                                              早
  //早  3.  瞪歎й ぬ韃 掘ж晦 (CN,Serial)                                          早
  //早  4.  TMAX 撲薑							                                                  早
  //早  5.  send    							                                                  早
  //早  6.  receive 							                                                  早
  //早  7.  唸婁高 return 				                                                  早
  //曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭
  TCHAR szEmpNum[MAX_PATH] ={0,};
  INT   nEmpNumLen = sizeof(szEmpNum);
  INT   nRet = 0;
  TCHAR szEmpName[MAX_PATH] ={0,};
  INT   nEmpNameLen = sizeof(szEmpName);
  INT   nRet2 = 0;
  
  nRet2 = DSS_VerifyEmp(&nRet,szEmpNum,&nEmpNumLen,szEmpName,&nEmpNameLen);
  VerifyEmpResult(TEXT("DSPAPI_VerifyEmp"), nRet2);
}



void Test_GetUserImagePathCheckDownLoad()
{
  CHAR  imagepath[256]  = {0,};
  CHAR  tempDN[512]     = {0,};
  TCHAR imagepath2[256] = {0,};
  TCHAR szTempDn[256]   = {0,};
  
  GetWindowText(hEditBox, szTempDn, sizeof(szTempDn));
  
  WideCharToMultiByte( CP_ACP, 0, szTempDn, lstrlen(szTempDn), tempDN, sizeof(tempDN), 0, 0 ); 

  // 餌辨濠曖 檜嘐雖蒂 壎戲煎睡攪 棻遴煎萄ж罹 唳煎蒂 溯雖蝶お葬縑 撲薑и棻.
  if( !DSS_GetUserImagePathCheckDownLoad((PTCHAR)tempDN, (PTCHAR)imagepath, sizeof(imagepath)) )
  {
    InsertResultData(TEXT("DSS_GetUserImagePathCheckDownLoad() 褒ぬ"), FALSE);
  }
  else
  {
    MultiByteToWideChar( CP_ACP, 0, imagepath, strlen(imagepath)+1, imagepath2, sizeof(imagepath2));
    InsertResultData(TEXT("DSS_GetUserImagePathCheckDownLoad() 撩奢"), TRUE);
    InsertResultData(imagepath2, TRUE);
  }
}



void Test_GetGroup()
{
  CHAR tempDN[256]={0,};
  TCHAR szTempDn[256] = {0,};
  
  GetWindowText(hEditBox, szTempDn, sizeof(szTempDn));

  WideCharToMultiByte( CP_ACP, 0, szTempDn, lstrlen(szTempDn), tempDN, sizeof(tempDN), 0, 0 ); 
  
  // 餌辨濠曖 ч廓 薑爾蒂 偵褐и棻.
  if( !DSS_GetGroup((PTCHAR)tempDN) )
  {
    InsertResultData(TEXT("DSS_GetGroup() 褒ぬ"), FALSE);
  }
  else
  {
    InsertResultData(TEXT("DSS_GetGroup() 撩奢"), TRUE);
  }
}



void Test_GetGroupAdmin()
{
  CHAR  tempDN[256]   = {0,};
  TCHAR szTempDn[256] = {0,};
  
  GetWindowText(hEditBox, szTempDn, sizeof(szTempDn));
  
  WideCharToMultiByte( CP_ACP, 0, szTempDn, lstrlen(szTempDn), tempDN, sizeof(tempDN), 0, 0 ); 

  // 餌辨濠曖 睡憮婦葬濠 薑爾蒂 偵褐и棻.
  if( DSS_GetGroupAdmin((PTCHAR)tempDN) != 0 )
  {
    InsertResultData(TEXT("DSS_GetGroupAdmin() 褒ぬ"), FALSE);
  }
  else
  {
    InsertResultData(TEXT("DSS_GetGroupAdmin() 撩奢"), TRUE);
  }
}



void Test_getSubjectCN()
{
  HKEY hKey;
  LONG regRet;
  
  TCHAR  buf[512], regbuf[512], *token;
  DWORD bufLen;
  TCHAR szTempDn[512] = {0,};
    
  lstrcpy(regbuf, TEXT("SOFTWARE\\Penta Security Systems\\LogOnManager"));
  regRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, regbuf, 0, KEY_ALL_ACCESS, &hKey);
  if(regRet != ERROR_SUCCESS) return;
  memset(buf, 0, 512);
  bufLen = 512;
  regRet = RegQueryValueEx(hKey, TEXT("Subject DN"), 0, NULL, (LPBYTE)buf, &bufLen);
  if(regRet != ERROR_SUCCESS) {
    RegCloseKey(hKey);
    InsertResultData(TEXT("Test_getSubjectCN() if(regRet != ERROR_SUCCESS) 褒ぬ"), FALSE);
    return;
  }
  RegCloseKey(hKey);
  
  if (buf[0] != 0) {
    token = wcstok(buf, TEXT(","));
    if(!token)
    {
      InsertResultData(TEXT("Test_getSubjectCN() if(!token) 褒ぬ"), FALSE);
      return;
    }
    lstrcpy(szTempDn, token+3) ;
  } else {
    InsertResultData(TEXT("Test_getSubjectCN() if(buf[0] != 0) 褒ぬ"), FALSE);
    return;
  }
  InsertResultData(TEXT("Test_getSubjectCN() 撩奢"), TRUE);
  InsertResultData(szTempDn, TRUE);
}

void Test_DeleteUserImageInfo()
{
  CHAR tempDN[MAX_PATH]       = {0,};
  TCHAR szTempDn[MAX_PATH]    = {0,};
  TCHAR szImagePath[MAX_PATH] = {0,};
  
  GetWindowText(hEditBox, szTempDn, sizeof(szTempDn));
  
  WideCharToMultiByte( CP_ACP, 0, szTempDn, lstrlen(szTempDn), tempDN, sizeof(tempDN), 0, 0 ); 
 
  if( !DSS_GetRegUserImagePath((PTCHAR)tempDN, szImagePath) )
  {
    InsertResultData(TEXT("Test_DeleteUserImageInfo() 褒ぬ"), FALSE);
    InsertResultData(TEXT("=> IF_GetRegUserImagePath() 褒ぬ"), FALSE);
    return;
  }

  if( !DSS_DeleteUserImageInfo((PTCHAR)tempDN, szImagePath) )
  {
    InsertResultData(TEXT("Test_DeleteUserImageInfo() 褒ぬ"), FALSE);
    return;
  }
  
  InsertResultData(TEXT("Test_DeleteUserImageInfo() 撩奢"), TRUE);
}

void Test_GetRegDefaultImage()
{
  CHAR  szDefImgPath[MAX_PATH]     = {0,};
  TCHAR szTempDefImgPath[MAX_PATH] = {0,};
  
  if( !DSS_GetRegDefaultImage((PTCHAR)szDefImgPath, MAX_PATH) )
  {
    InsertResultData(TEXT("Test_GetRegDefaultImage() 褒ぬ"), FALSE);
    return;
  }
  
  MultiByteToWideChar( CP_ACP, 0, szDefImgPath, strlen(szDefImgPath)+1, szTempDefImgPath, sizeof(szTempDefImgPath));
  InsertResultData(TEXT("Test_GetRegDefaultImage() 撩奢"), TRUE);
  InsertResultData(szTempDefImgPath, TRUE);
}

void Test_SendLog()
{
  CHAR  errMsg[MAX_PATH] = {0,};
  TCHAR szwErrMsg[MAX_PATH] = {0,};
  
  GetWindowText(hEditBox, szwErrMsg, sizeof(szwErrMsg));

  WideCharToMultiByte( CP_ACP, 0, szwErrMsg, lstrlen(szwErrMsg), errMsg, sizeof(errMsg), 0, 0 ); 

  if( DSS_SendLog('1', '1', '0', errMsg, 7) != 0 )
  {
    InsertResultData(TEXT("Test_TMax_SendLog() 褒ぬ"), FALSE);
    return;
  }
  MultiByteToWideChar( CP_ACP, 0, errMsg, strlen(errMsg)+1, szwErrMsg, sizeof(szwErrMsg));

  InsertResultData(TEXT("Test_TMax_SendLog() 撩奢"), TRUE);
  InsertResultData(szwErrMsg, TRUE);
}

void Test_GetVersion()
{
  CHAR  szVersion[MAX_PATH]     = {0,};
  TCHAR szTempVersion[MAX_PATH] = {0,};
  
  if( !DSS_GetVersion((PTCHAR)szVersion, MAX_PATH) )
  {
    InsertResultData(TEXT("DSS_GetVersion() 褒ぬ"), FALSE);
    return;
  }

  MultiByteToWideChar( CP_ACP, 0, szVersion, strlen(szVersion)+1, szTempVersion, sizeof(szTempVersion));

  if( lstrlen(szTempVersion) == 0 )
  {
    InsertResultData(TEXT("餌檜鍔陛 濛蝗棲棻. : 褒ぬ"), FALSE);
    return;
  }
  
  InsertResultData(TEXT("DSS_GetVersion() 撩奢"), TRUE);
  InsertResultData(szTempVersion, TRUE);

  if( !IF_GetVersion((PTCHAR)szVersion, MAX_PATH) )
  {
    InsertResultData(TEXT("IF_GetVersion() 褒ぬ"), FALSE);
    return;
  }

  MultiByteToWideChar( CP_ACP, 0, szVersion, strlen(szVersion)+1, szTempVersion, sizeof(szTempVersion));
  
  if( lstrlen(szTempVersion) == 0 )
  {
    InsertResultData(TEXT("餌檜鍔陛 濛蝗棲棻. : 褒ぬ"), FALSE);
    return;
  }

  InsertResultData(TEXT("IF_GetVersion() 撩奢"), TRUE);
  InsertResultData(szTempVersion, TRUE);
} 