# Microsoft Developer Studio Project File - Name="DSS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DSS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DSS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DSS.mak" CFG="DSS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DSS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DSS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DSS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../inc" /I "../../../inc/bg" /I "../../../inc/bio" /I "../../../../cis/build/include/cis-2.4" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSS_EXPORTS" /D "TMAX" /D "SCMOD_MANAGER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 Msimg32.lib IF_SDK.lib ssa.lib scmodext_v2.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/DestSecs.dll" /libpath:"../../../lib" /libpath:"../../../bin" /libpath:"../../../../cis/build/bin" /libpath:"../../../lib/bio" /libpath:"../../../bin/bio" /libpath:"../../../lib/bg" /libpath:"../../../../BigGate/build/lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\DestSecs.dll ..\..\..\bin\DestSecs.dll	copy release\DestSecs.lib ..\..\..\lib\DestSecs.lib	copy DSS.h ..\..\..\inc\DSS.h	copy DssFpError.h ..\..\..\inc\DssFpError.h
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DSS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSS_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../inc" /I "../../../inc/bg" /I "../../../inc/bio" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSS_EXPORTS" /D "TMAX" /D "SCMOD_MANAGER" /FR /Yu"stdafx.h" /FD /GZ "" /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Msimg32.lib IF_SDK.lib ssa.lib scmodext_v2.lib scmod.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/DestSecs.dll" /pdbtype:sept /libpath:"../../../lib" /libpath:"../../../bin" /libpath:"../../../../cis/build/bin" /libpath:"../../../lib/bio" /libpath:"../../../bin/bio" /libpath:"../../../lib/bg"
# Begin Special Build Tool
TargetPath=.\Debug\DestSecs.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy         debug\DestSecs.dll         ..\..\..\bin\DestSecs.dll        	copy         debug\DestSecs.lib         ..\..\..\lib\DestSecs.lib        	copy         DSS.h         ..\..\..\inc\DSS.h        	copy         DssFpError.h         ..\..\..\inc\DssFpError.h        	copy         $(TargetPath)         .\TestDssStdcall\Debug\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "DSS - Win32 Release"
# Name "DSS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DllLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\DSS.cpp
# End Source File
# Begin Source File

SOURCE=.\DssFpError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\common\ifgetpath_cpp.cpp

!IF  "$(CFG)" == "DSS - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "DSS - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ISignDtpDLL.cpp
# End Source File
# Begin Source File

SOURCE=.\MyBioApi.cpp
# End Source File
# Begin Source File

SOURCE=.\nBioApi.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DllLoad.h
# End Source File
# Begin Source File

SOURCE=.\DSS.h
# End Source File
# Begin Source File

SOURCE=.\DssFpError.h
# End Source File
# Begin Source File

SOURCE=.\ISignDtpDLL.h
# End Source File
# Begin Source File

SOURCE=.\MyBioApi.h
# End Source File
# Begin Source File

SOURCE=.\MyNBioApi.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\NITGEN eNBSP\SDK\inc\NBioAPI.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\img\BT_G_Cancel_DOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\img\BT_G_Cancel_ON.bmp
# End Source File
# Begin Source File

SOURCE=.\img\BT_G_Cancel_OVER.bmp
# End Source File
# Begin Source File

SOURCE=.\img\BT_G_OK_down..bmp
# End Source File
# Begin Source File

SOURCE=.\img\BT_G_OK_On.bmp
# End Source File
# Begin Source File

SOURCE=.\img\BT_G_OK_Over.bmp
# End Source File
# Begin Source File

SOURCE=.\progress.bmp
# End Source File
# Begin Source File

SOURCE=.\progress0.bmp
# End Source File
# Begin Source File

SOURCE=.\progress1.bmp
# End Source File
# Begin Source File

SOURCE=.\Script2.rc
# End Source File
# Begin Source File

SOURCE=.\img\SVRFPAUTH_BODY_G.bmp
# End Source File
# Begin Source File

SOURCE=.\img\SVRFPAUTH_INNER_BODY_G.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\if_progress.avi
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
