//-------------------------------------------------------------------
// BasicBitmap.h
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
#include "../../API/IF_PlugIn.h"

class BasicBitmap
{
public:
   BasicBitmap(IF_Bitmap* src, bool makeCopy);
   ~BasicBitmap();

   int Width();
   int Height();

   RGBQUAD* GetPixel(int x, int y);
   void SetPixel(int x, int y, RGBQUAD* toSetTo);

   bool InBounds(int x, int y);

private:
   bool m_ownsBits;

   int m_width;
   int m_height;

   int m_bitsPerPixel;
   int m_stride;
   int m_totalBytes;
   int m_bytesPerPixel;

   BYTE* m_pBits;
   BITMAPINFO* m_pHeader;
};

