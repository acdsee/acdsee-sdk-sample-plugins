//-------------------------------------------------------------------
// CreateViewImpl.cpp
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
#include "CreateViewImpl.h"
#include "DIBUtil.h"

CreateViewImpl::CreateViewImpl()
   :hasOpenDecodeFile(false), hasFileBeenDecoded(false), mustFreeDIB(false)
{

}

CreateViewImpl::~CreateViewImpl()
{
   //Free dib if havn't handed it off to someone
   if(mustFreeDIB)
   {
      if(this->packedDIB != NULL)
      {
         GlobalFree(this->packedDIB);
         this->packedDIB = NULL;
      }
      mustFreeDIB = false;
   }
}

//Opens a file for decoding
void CreateViewImpl::OpenDecodeImage(std::wstring filename)
{
   this->decodeFile.open(filename, std::wifstream::in | std::wifstream::binary);
   hasOpenDecodeFile = true;
   hasFileBeenDecoded = false;
}

void CreateViewImpl::CloseDecodeImage()
{
   if(hasOpenDecodeFile)
   {
      this->decodeFile.close();
      hasOpenDecodeFile = false;
   }
}

void CreateViewImpl::GetDecodeImageDimensions(SIZE& si)
{
   DecodeImage();
   if(packedDIB!=NULL)
   {
      LPSTR dib = (LPSTR) GlobalLock(packedDIB);
      si.cx = DIBWidth(dib);
      si.cy = DIBHeight(dib);
      GlobalUnlock(packedDIB);
   }
   else
   {
      si.cx = 0;
      si.cy = 0;
   }
}

int CreateViewImpl::GetDecodeImageBitsPerSample()
{
   DecodeImage();
   int ret = 0;
   if(packedDIB!=NULL)
   {
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(packedDIB);

      if(lpbi->biBitCount == 24 || lpbi->biBitCount ==32 )
      {
         ret = 8;
      }
      GlobalUnlock(packedDIB);
   }

   return ret;
}

int CreateViewImpl::GetDecodeImageSamplesPerPixel()
{
   DecodeImage();
   int ret = 0;
   if(packedDIB!=NULL)
   {
      LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(packedDIB);
      if(lpbi->biBitCount == 24 )
      {
         ret = 3;
      }
      else if (lpbi->biBitCount == 32)
      {
         ret = 4;
      }
      GlobalUnlock(packedDIB);
   }
   return ret;
}

HGLOBAL CreateViewImpl::GetPackedDIB()
{
   DecodeImage();
   mustFreeDIB = false;
   hasFileBeenDecoded = false;
   return packedDIB;
}

bool CreateViewImpl::DecodeImage()
{ 
   if(hasFileBeenDecoded)
   {
      return true;
   }
   try
   {
      return ReadTextIntoBitmap(this->decodeFile);
   } 
   catch (...)
   {
      return false;
   }
   return true; 
}

bool CreateViewImpl::ReadTextIntoBitmap(std::wifstream& fileRead)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);

   decodeFile.seekg(0, std::ios::end);   
   fileText.reserve(decodeFile.tellg());
   decodeFile.seekg(0, std::ios::beg);

   fileText.assign((std::istreambuf_iterator<wchar_t>(decodeFile)), std::istreambuf_iterator<wchar_t>());

   HDC memDC = CreateCompatibleDC(NULL);

   if(memDC == NULL)
      return false;

   HBITMAP hBitmap = CreateCompatibleBitmap(memDC, desktop.right - desktop.left, 10000);
   if(hBitmap == NULL)
   {
      DeleteDC(memDC);
      return false;
   }

   SelectObject(memDC, hBitmap);

   RECT r;
   r.bottom=10000;
   r.left = 0;
   r.top = 0;
   r.right=desktop.right - desktop.left;
   int neededHeight = DrawTextW(memDC, fileText.c_str(), -1, &r, DT_LEFT | DT_END_ELLIPSIS | DT_WORDBREAK);

   HBITMAP hFullBitmap = CreateCompatibleBitmap(memDC, desktop.right - desktop.left, neededHeight);
   r.bottom = neededHeight;
   SelectObject(memDC, hFullBitmap);

   FillRect(memDC, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
   DrawTextW(memDC, fileText.c_str(), -1, &r, DT_LEFT | DT_END_ELLIPSIS | DT_WORDBREAK);

   if(packedDIB != NULL && mustFreeDIB)
   {
      GlobalFree(packedDIB);
      packedDIB = NULL;
      mustFreeDIB = false;
   }
   packedDIB = BitmapToDIB(hFullBitmap, NULL);

   DeleteObject(hBitmap);
   DeleteObject(hFullBitmap);
   DeleteDC(memDC);

   if(packedDIB == NULL)
      return false;
   mustFreeDIB = true;
   hasFileBeenDecoded = true;
   return true;
}

int CreateViewImpl::GetLastError()
{
   return 0;
}

