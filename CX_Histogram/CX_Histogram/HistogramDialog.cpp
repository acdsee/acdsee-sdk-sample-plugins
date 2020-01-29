//-------------------------------------------------------------------
// HistogramDialog.cpp
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
#include "HistogramDialog.h"
#include "HistogramData.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(HistogramDialog, CDialog)
   ON_WM_CREATE()
   ON_WM_PAINT()
   ON_WM_DESTROY()
   ON_WM_CLOSE()
END_MESSAGE_MAP()

void HistogramDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

IMPLEMENT_DYNAMIC(HistogramDialog, CDialog )
HistogramDialog::HistogramDialog(HistogramData inData, CWnd* parentWnd)
   : CDialog (IDD_DIALOG1, parentWnd), data(inData)
{

}

HistogramDialog::~HistogramDialog()
{

}

BOOL HistogramDialog::OnInitDialog()
{
   CDialog::OnInitDialog();

   return TRUE;
}

int HistogramDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // Create the window and make sure it doesn't return -1
   if (CDialog::OnCreate(lpCreateStruct) == -1)
      return -1;
   // else is implied
   return 0;

}

void HistogramDialog::OnPaint() 
{
   CDialog::OnPaint();

   HGDIOBJ oldObject;

   CClientDC dc(this);

   RECT windRect;
   GetWindowRect(&windRect);
   ScreenToClient(&windRect);

   int height =(windRect.bottom-50);
   double xScale = (windRect.right-1)/256.0;
   double yScale = (height * 0.97)/data.calcMax();

   CBrush* blackBrush = new CBrush();
   blackBrush->CreateSolidBrush(RGB(0,0,0));
   dc.FillRect(&windRect, blackBrush);
   delete blackBrush;

   int buckets = data.m_nBuckets;

   double curX;

   oldObject = dc.SelectObject(GetStockObject(DC_PEN ));
   dc.SetDCPenColor(RGB(255,0,0)); 
   curX = 0.0;
   dc.MoveTo(static_cast<int>(curX), height);
   for(int i=0; i<buckets; ++i)
   {
      dc.LineTo(static_cast<int>(curX), static_cast<int>((height) - (data.m_redVals[i] * yScale)));
      curX += xScale;
   }

   dc.SetDCPenColor(RGB(0,255,0)); 
   curX = 0.0;
   dc.MoveTo(static_cast<int>(curX),height);
   for(int i=0; i<buckets; ++i)
   {
      dc.LineTo(static_cast<int>(curX), static_cast<int>((height) - (data.m_greenVals[i] * yScale)));
      curX += xScale;
   }

   dc.SetDCPenColor(RGB(0,0,255)); 
   curX = 0.0;
   dc.MoveTo(static_cast<int>(curX),height);
   for(int i=0; i<buckets; ++i)
   {
      dc.LineTo(static_cast<int>(curX), static_cast<int>((height) - (data.m_blueVals[i] * yScale)));
      curX += xScale;
   }

   dc.SelectObject(oldObject);
}

void HistogramDialog::OnCancel()
{
   CDialog::OnCancel();
}
