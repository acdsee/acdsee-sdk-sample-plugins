//-------------------------------------------------------------------
// CX_Histogram.h
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

// CX_Histogram.h : main header file for the CX_Histogram DLL
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CCXHistogramApp
// See CX_Histogram.cpp for the implementation of this class
//

class CCXHistogramApp : public CWinApp
{
public:
	CCXHistogramApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
