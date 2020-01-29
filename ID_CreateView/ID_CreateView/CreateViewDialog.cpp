//-------------------------------------------------------------------
// CreateViewDialog.cpp
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
#include "afxdialogex.h"
#include "CreateViewDialog.h"
#include "CreateViewImpl.h"
#include "../../API/ID_PlugIn.h"

//#include "resource.h"

BEGIN_MESSAGE_MAP(CreateViewDialog, CWnd)
   ON_WM_CREATE()
   ON_WM_PAINT()
END_MESSAGE_MAP()

void CreateViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CWnd::DoDataExchange(pDX);
}

IMPLEMENT_DYNAMIC(CreateViewDialog, CWnd )
CreateViewDialog::CreateViewDialog()
   : CWnd ()
{
}

CreateViewDialog::~CreateViewDialog()
{
}

LRESULT CreateViewDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message)
	{
      // ID_VWM_SETSOURCE (required)
      // Specifies the image to be displayed.
      // wReserved    = (WPARAM)wParam   // Reserved - set to 0
      // lpszwFileName = (LPCWSTR)lParam   // File containing image to display
      // Returns: IDE_* result code.
      // Note: the lpszwFileName buffer is temporary and must not be used after this
      // message has been processed.
      case( ID_VWM_SETSOURCE ):
      {
         std::wifstream file(std::wstring((LPCWSTR) lParam));

         file.seekg(0, std::ios::end);   
         fileText.reserve(file.tellg());
         file.seekg(0, std::ios::beg);

         fileText.assign((std::istreambuf_iterator<wchar_t>(file)), std::istreambuf_iterator<wchar_t>());
         return TRUE;
      }

      // ID_VWM_CALCMAGNIFICATION (required)
      // Calculates the highest magnification level that can be fully displayed 
      // within the given window dimensions.
      // siSize = (SIZE*)wParam  // Pointer to a SIZE structure that specifies the window dimensions.  
      // siMag  = (SIZE*)lParam  // Pointer to a SIZE structure that receives the magnification
      //                         // level, where cx is set to the numerator, and cy is set to
      //                         // the denominator.
      // Returns: 1 on success, 0 on error.
      case( ID_VWM_CALCMAGNIFICATION):
      {
         SIZE* out = (SIZE*) lParam;
         out->cx = 1;
         out->cy = 1;
         return TRUE;
      }

      // ID_VWM_SETMAGNIFICATION (required)
      // Specifies the magnification (zoom level) at which the image should be displayed.
      // The magnification level is represented as a fractional number, where 1/1
      // represents 100% magnification.
      // wReserved  = (WPARAM)wParam  // Reserved - set to 0
      // siMag      = (SIZE*)lParam   // Pointer to a SIZE structure that specifies the magnification
      //                              // level, where cx is set to the numerator, and cy is set to  
      //                              // the denominator.                                           
      //
      // Returns: 1 if magnification was set, 0 on error.
      //
      // Note: If the resulting display size of the image exceeds the window dimensions, then
      // the view should be scrollable, either through the additional of scroll bars,
      // or allowing the user to click and drag the image.
      case( ID_VWM_SETMAGNIFICATION ):
      {
         SIZE* out = (SIZE*) lParam;
         out->cx = 1;
         out->cy = 1;
         return TRUE;
      }

      // ID_VWM_GETMAGNIFICATION (required)
      // Retrieves the current magnification (zoom level).
      // The magnification level is represented as a fractional number, where 1/1
      // represents 100% magnification.
      // pNumerator   = (UINT*)wParam // Address of UINT that receives the numerator
      // pDenominator = (UINT)lParam  // Address of UINT that receives the denominator
      // Returns: 1 on success, 0 on error.
      case( ID_VWM_GETMAGNIFICATION ):
      {
         UINT* num = (UINT*) wParam;
         UINT* den = (UINT*) lParam;
         *num = 1;
         *den = 1;
         return TRUE;
      }
   }
   return CWnd::WindowProc(message, wParam, lParam);
}

int CreateViewDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // Create the window and make sure it doesn't return -1
   if (CWnd::OnCreate(lpCreateStruct) == -1)
      return -1;
   // else is implied
   return 0;
}

void CreateViewDialog::OnPaint() 
{
   CPaintDC dc(this); //Call begin paint on construction and end paint on destruction.
   RECT rc;
   this->GetWindowRect(&rc);  //Get Coordinates in device space (physical monitor)
   this->ScreenToClient(&rc); //Get Rect in logical space (application relative)
   CBrush white(0xFFFFFF);
   dc.FillRect(&rc,&white);
   dc.DrawTextW(fileText.c_str(), fileText.length(), &rc, DT_LEFT | DT_END_ELLIPSIS | DT_WORDBREAK);
}