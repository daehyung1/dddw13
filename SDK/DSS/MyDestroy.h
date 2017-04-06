
#pragma once
#include "dss.h"


class MyDestroyObject
{
  
public:
  int m_result;
  
  void Init()
  {
    if(g_threadid==0||g_bioobject==NULL)
    {
      LOGPRINT("DSS_FP_Initialize를 호출하지 않았습니다.",8013);
      m_result=-1;
      return;
    }
    
    m_result=Process();
  }
  
  virtual int Process()=0;
  
};




class MyDestroy:public MyDestroyObject
{
  
public:
  MyDestroy()
  {
   // g_result=TRUE;
    Init();
  }
  
  ~MyDestroy()
  {
   // g_result=FALSE;
   // g_errorcode=0;
    Destroy();
    
  }
  
  int Process()
  {
    //g_bioobject->DSS_FP_Init();
    return 0;
  }
  
  void Destroy()
  {
    //g_bioobject->DSS_FP_Destroy_nBio();
  }
};
  
  
class MyOpen:public MyDestroyObject
{
  
  int m_isopen;
public:
  MyOpen()
  {
    m_isopen=-1;
    Init();
  }
  
  ~MyOpen()
  {
    Destroy();
  }
  
  int Process()
  {
    m_isopen=g_bioobject->DeviceOpen();
    return m_isopen;
  }
  
  void Destroy()
  {
    if(!m_isopen)
      g_bioobject->DeviceClose();
  }
  
};


