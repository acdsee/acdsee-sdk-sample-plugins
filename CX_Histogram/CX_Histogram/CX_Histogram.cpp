//-------------------------------------------------------------------
// CX_HistoGram.cpp
//-------------------------------------------------------------------
// ACD SYSTEMS INTERNATIONAL INC.
// Copyright © 1994 - 2020 ACD Systems International Inc.
// All Rights Reserved
//
// NOTICE: ACD Systems International Inc. ("ACD") permits you to use,
// modify, and distribute this file in accordance with the terms of
// the ACDSee SDK license agreement accompanying it. If you have 
// received this file from a source other than ACD, then your use,
// modification, or distribution of it requires the prior written 
// permission of ACD.
//-------------------------------------------------------------------

#include "stdafx.h"
#include "CX_ApiWrapper.h"
#include "CX_Histogram.h"
#include "../../API/CX_PlugIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CCXHistogramApp

BEGIN_MESSAGE_MAP(CCXHistogramApp, CWinApp)
END_MESSAGE_MAP()


// CCXHistogramApp construction

CCXHistogramApp::CCXHistogramApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// CCXHistogramApp initialization

BOOL CCXHistogramApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

/******************************************
* START OF EXPORTED FUNCTION DECLARATIONS *
******************************************/

namespace CX
{
   CCXHistogramApp theApp;
   CX_APIWrapper* g_CXAPIWrapper = NULL;
}

/**********
* CX_Init *
***********/
PLUGIN_API int __stdcall CX_Init(
   CX_ClientInfo*  pci)  // (in) Information about the plug-in client (host)
{
   CX::g_CXAPIWrapper = new CX_APIWrapper(pci);
   return CXE_OK;
}

/**********
* CX_Free *
***********
* The client application will call this function once when it no longer
* needs the plug-in.  After CX_Free() is called, no other entry points
* may be called.  Normally, CX_Free() will be called immediately before
* unloading the plug-in DLL using FreeLibrary().
*
* CX_Free() will not be called if CX_Init() failed.
*
* The main purpose of CX_Free() is to give the plug-in a chance to free
* any DLLs it has dynamically loaded with LoadLibrary().
*
* Returns: CXE_OK.
*/
PLUGIN_API int __stdcall CX_Free()
{
   if(CX::g_CXAPIWrapper != NULL)
   {
      delete CX::g_CXAPIWrapper;
      CX::g_CXAPIWrapper = NULL;
   }
   return CXE_OK;
}

/*******************
* CX_GetPlugInInfo *
********************
* Returns a pointer to an CX_PlugInInfo.
* The plug-in owns the pointer and must not free it until the
* plug-in library is unloaded.
*/
PLUGIN_API int __stdcall CX_GetPlugInInfo(
   CX_PlugInInfo**  ppii) // (out) Plug-in information
{
   if(CX::g_CXAPIWrapper != NULL)
   {
      *ppii = &(CX::g_CXAPIWrapper->m_PlugInInfo);
   }
   return CXE_OK;
}

/*******************
* CX_InvokeCommand *
********************/
PLUGIN_API int __stdcall CX_InvokeCommand(
   CX_CommandParams*  pcp,  // (in ) Specifies command to invoke, and parameters
   CX_CommandResults* pcr)  // (out) Command results
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   int ret = CXE_OK;

   if (CX::g_CXAPIWrapper != NULL)
   {
      ret = CX::g_CXAPIWrapper->DoCX(pcp, pcr);
   }

   return ret;
}

/**********************
* CX_ShowPlugInDialog *
***********************
* Shows an "About" and/or "Options" dialog for this plug-in.
*/
PLUGIN_API int __stdcall CX_ShowPlugInDialog(
   HWND        hwndParent)  // (in ) Parent window
{
   MessageBoxW(hwndParent, L"This is a generic Command Extension Plug-In", L"Generic About Box", MB_OK | MB_ICONINFORMATION);
   return CXE_OK;
}

/**********
* CX_Help *
***********
* Displays help for the plug-in or a specific command.
*/
PLUGIN_API int __stdcall CX_Help(
   HWND        hWnd,        // Application window that is calling help                                 
   UINT        uCommand,    // Type of help requested (CX_HC_* value)
   DWORD       dwData)      // Additional data for help command
{
   return CXE_NotImplemented;
}

/******************
* CX_ErrorHandler *
*******************
* Handles an exception caused by the plug-in. The host will call this function if the
* plug-in causes an exception.
*
* The return value should be one of the CX_EHF_* flags.
*/
PLUGIN_API int __stdcall CX_ErrorHandler(
   CX_ErrorHandlerParams*    pehp)           // (in) Error Handler Parameters
{ 
   return CXE_NotImplemented;
}

/***********************
* CX_FormatInfoChanged *
************************
* Called by the plug-in host to determine whether or not to update any cached information about
* formats supported by this plug-in.
*
* Sets bChanged to TRUE if the host should update it's cache.
*/
PLUGIN_API int __stdcall CX_FormatInfoChanged(BOOL& bChanged)
{
   return CXE_NotImplemented;
}
