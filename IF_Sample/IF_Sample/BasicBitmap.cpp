//-------------------------------------------------------------------
// BasicBitmap.cpp
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
#include "BasicBitmap.h"

BasicBitmap::BasicBitmap(IF_Bitmap* src, bool makeCopy)
{
   m_width = src->pHeader->bmiHeader.biWidth;
   m_height = src->pHeader->bmiHeader.biHeight;

   m_bitsPerPixel = src->pHeader->bmiHeader.biBitCount;
   m_bytesPerPixel = m_bitsPerPixel/8;

   m_stride = src->bytesPerRow;
   m_totalBytes = m_stride*m_height;

   assert(m_height>0); //Make sure it is top down DIB

   if(makeCopy)
   {
      m_ownsBits = true;

      m_pBits = new BYTE[m_totalBytes];

      memcpy(m_pBits, src->pBits, m_totalBytes); //Create a copy of the bitmap
   }
   else
   {
      m_ownsBits = false;

      m_pBits = (BYTE*) src->pBits;
      m_pHeader = src->pHeader;
   }
}


BasicBitmap::~BasicBitmap()
{
   if(m_ownsBits)
   {
      delete[] m_pBits;
   }
}

RGBQUAD* BasicBitmap::GetPixel(int x, int y)
{
   return (RGBQUAD*)(m_pBits + (x*m_bytesPerPixel) + (m_stride* y));
}

void BasicBitmap::SetPixel(int x, int y, RGBQUAD* toSetTo)
{
   memcpy((m_pBits + (x*m_bytesPerPixel) + (m_stride* y)), toSetTo, sizeof(RGBQUAD)); 
}

bool BasicBitmap::InBounds(int x, int y)
{
   if(x<0||x>=m_width ||y<0 || y>=m_height) return false;
   return true;
}

int BasicBitmap::Width()
{
   return m_width;
}

int BasicBitmap::Height()
{
   return m_height;
}


