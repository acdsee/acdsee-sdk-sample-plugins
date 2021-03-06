//-------------------------------------------------------------------
// ID_CreateViewMFC.cpp
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

// ID_CreateView.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ID_CreateViewMFC.h"

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

// CIDECreateViewApp

BEGIN_MESSAGE_MAP(CIDECreateViewApp, CWinApp)
END_MESSAGE_MAP()


// CIDECreateViewApp construction

CIDECreateViewApp::CIDECreateViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIDECreateViewApp object

CIDECreateViewApp theApp;


// CIDECreateViewApp initialization

BOOL CIDECreateViewApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
