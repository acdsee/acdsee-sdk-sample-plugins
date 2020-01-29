//-------------------------------------------------------------------
// CreateViewDialog.h
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

#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "afxdialogex.h"

class CreateViewImpl;

class CreateViewDialog : public CWnd
{
   DECLARE_DYNAMIC(CreateViewDialog)

public:
   CreateViewDialog::CreateViewDialog();
   ~CreateViewDialog();

protected:

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //Message Handlers
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnPaint();
   DECLARE_MESSAGE_MAP()

   //Text to display
   std::wstring fileText;
};