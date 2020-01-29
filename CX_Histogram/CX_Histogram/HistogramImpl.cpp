//-------------------------------------------------------------------
// HistogramImpl.cpp
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
#include "HistogramImpl.h"
#include "HistogramData.h"
#include "HistogramDialog.h"
#include "../../API/CX_PlugIn.h"

//Constructor
HistogramImpl::HistogramImpl()
{

}

//Destructor
HistogramImpl::~HistogramImpl()
{

}

//Upload Function
int HistogramImpl::ShowHistogram(HGLOBAL hPackedDib, HWND parentWnd)
{
   HistogramData data(256);
   int ret = ReadBitmapBits(hPackedDib, data);
   if(ret!=CXE_OK) return ret;

   HistogramDialog dlg(data, CWnd::FromHandlePermanent(parentWnd));
   INT_PTR nret = dlg.DoModal();

   return CXE_OK;
}

int HistogramImpl::ReadBitmapBits(HGLOBAL hPackedDib, HistogramData& data)
{
   if(hPackedDib == NULL)
   {
      return CXE_Error;
   }

   GlobalLock(hPackedDib);

   //Get bitmap header info
   BITMAPINFO &bmInfo = *(LPBITMAPINFO)hPackedDib;

   //Ensure that the packed bitmap is uncompressed and 24 bit.
   if(bmInfo.bmiHeader.biBitCount !=24 || bmInfo.bmiHeader.biClrUsed!=0 || bmInfo.bmiHeader.biCompression != BI_RGB)
   {
      return CXE_NotImplemented;
   }

   //Pointer to dib bits
   uint8_t* ptr = (uint8_t*)(LPVOID)((LPDWORD) (bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) +  ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));

   //Iterate over the bits of the bitmap
   long long count = 0;
   for(int i=0; i<bmInfo.bmiHeader.biHeight; ++i)
   {
      for(int j=0; j<bmInfo.bmiHeader.biWidth; ++j)
      {
         uint8_t blue = *ptr;
         ptr++;
         uint8_t green = *ptr;
         ptr++;
         uint8_t red = *ptr;
         ptr++;
         data.AddDataPoint(red, green, blue);
         count+=3;
      }
      //Move forward to DWORD border at end of row.
      while(count%4!=0)
      {
         count+=1;
         ptr++;
      }
   }
   GlobalUnlock(hPackedDib);
   return CXE_OK;
}




