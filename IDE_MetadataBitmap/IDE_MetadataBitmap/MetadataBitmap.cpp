//-------------------------------------------------------------------
// MetadataBitmap.cpp
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
#include "MetadataBitmap.h"
#include "MetadataHandler.h"
#include "../../API/Metadata/Metadata.h"
#include "../../API/Metadata/MetadataUtil.h"

MetadataBitmap::MetadataBitmap()
   :hasOpenDecodeFile(false), hasFileBeenDecoded(false), mustFreeDIB(false)
{

}

MetadataBitmap::~MetadataBitmap()
{
   //Free dib if havnt handed it off to someone
   if(mustFreeDIB)
   {
      GlobalFree(this->packedDIB);
      mustFreeDIB = false;
   }
}

//Opens a file for decoding
void MetadataBitmap::OpenDecodeImage(std::wstring filename)
{
   this->decodeFile.open(filename, std::ifstream::in | std::ifstream::binary);
   hasOpenDecodeFile = true;
   hasFileBeenDecoded = false;
}

void MetadataBitmap::CloseDecodeImage()
{
   if(hasOpenDecodeFile)
   {
      this->decodeFile.close();
      hasOpenDecodeFile = false;
   }
}

void MetadataBitmap::GetDecodeImageDimensions(SIZE& si)
{
   DecodeImage(nullptr);
   si.cx = decodeFileDimensions.cx;
   si.cy = decodeFileDimensions.cy;
}

int MetadataBitmap::GetNumDecodeMetadataTypes()
{
   MD_MetadataList* pList = (MD_MetadataList*)new CMetadataList();
   DecodeImage(pList);
   int ret = pList->GetMetadataCount();
   pList->Release();
   return ret;
}

HGLOBAL MetadataBitmap::GetDecodeMetadataGUIDArray()
{
  
   MD_MetadataList* pList = (MD_MetadataList*)new CMetadataList();
   DecodeImage(pList);

   HGLOBAL arr = GlobalAlloc(GMEM_MOVEABLE, sizeof(GUID) * pList->GetMetadataCount());
   GUID* pguidTypesSrc = (GUID*)GlobalLock(arr);
   for (int i = 0; i < pList->GetMetadataCount(); i++)
   {
      pguidTypesSrc[i] = pList->GetMetadataItem(i)->GetMetadataType();
   }
   GlobalUnlock(pguidTypesSrc);
   pList->Release();

   return arr;
}

HGLOBAL MetadataBitmap::GetPackedDIB()
{
   DecodeImage(nullptr);
   mustFreeDIB = false;
   return packedDIB;
}

bool MetadataBitmap::DecodeImage(MD_MetadataList* pMetadata)
{ 
   try
   {
      this->decodeFile.clear();
      this->decodeFile.seekg(0, std::ifstream::ios_base::beg);
      MetadataHandler mdHandler(pMetadata);
      mdHandler.ReadMetadataFromFile(this->decodeFile); //Results go into pMetadata
      return ReadBitmap(this->decodeFile);
   } 
   catch (...)
   {
      return false;
   }
   return true; 
}

bool MetadataBitmap::WriteImage(std::wstring outfilename, BITMAPINFO* pBitmapInfo, void* pBits, MD_MetadataList* pMetadata)
{ 
   std::ofstream fileWriter;

   try
   {
      fileWriter.open(outfilename, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

      MetadataHandler mdHandler(pMetadata);
      mdHandler.WriteMetadataToFile(fileWriter); //Writes metadata from pMetadata
      WriteBitmap(fileWriter, pBitmapInfo, pBits);

      fileWriter.close();
   }
   catch (...)
   {
      if(fileWriter.is_open())
      {
         fileWriter.close();
      }
      return false;
   }
   return true; 
}

bool MetadataBitmap::WriteBitmap(std::ofstream& fileWriter, BITMAPINFO* pBitmapInfo, void* pBits)
{
   BITMAPINFOHEADER header;
   header = pBitmapInfo->bmiHeader;

   int   nPalEntries  = GetDIBColormapLen(header);
   int   nDstBpp      = (header.biCompression == BI_BITFIELDS) ? 24 : min(24, header.biBitCount);
   int   nSrcRowBytes = (header.biWidth * header.biBitCount + 31) / 32 * 4;
   int   nDstRowBytes = (header.biWidth * nDstBpp + 31) / 32 * 4;
   DWORD nBytesDst    = nDstRowBytes * abs(header.biHeight);
   DWORD nDIBSize     = header.biSize + nPalEntries * sizeof(RGBQUAD) + nBytesDst;

   this->decodeFileDimensions.cx = header.biWidth;
   this->decodeFileDimensions.cy = header.biHeight;

   //Write header
   fileWriter.write((char*) pBitmapInfo, sizeof(BITMAPINFOHEADER) + nPalEntries * sizeof(RGBQUAD));
   //Write bits
   fileWriter.write((char*) pBits, nDIBSize - (sizeof(BITMAPINFOHEADER) + nPalEntries * sizeof(RGBQUAD)));

   return true;
}

bool MetadataBitmap::ReadBitmap(std::ifstream& fileRead)
{
   BITMAPINFOHEADER header;

   fileRead.read((char*)&header, sizeof(BITMAPINFOHEADER));

   int   nPalEntries  = GetDIBColormapLen(header);
   int   nDstBpp      = (header.biCompression == BI_BITFIELDS) ? 24 : min(24, header.biBitCount);
   int   nSrcRowBytes = (header.biWidth * header.biBitCount + 31) / 32 * 4;
   int   nDstRowBytes = (header.biWidth * nDstBpp + 31) / 32 * 4;
   DWORD nBytesDst    = nDstRowBytes * abs(header.biHeight);
   DWORD nDIBSize     = header.biSize + nPalEntries * sizeof(RGBQUAD) + nBytesDst;

   if(mustFreeDIB)
   {
      GlobalFree(this->packedDIB);
   }

   this->decodeFileDimensions.cx = header.biWidth;
   this->decodeFileDimensions.cy = header.biHeight;

   this->packedDIB = GlobalAlloc(GMEM_FIXED, nDIBSize);
   mustFreeDIB = true;

   BYTE* locked = (BYTE*)GlobalLock(this->packedDIB);
   if(locked == NULL) return false;
   
   BYTE* ptr = locked;

   CopyMemory(ptr, &header, sizeof(BITMAPINFOHEADER));

   ptr = ptr + sizeof(BITMAPINFOHEADER);

   //Read in pallete
   fileRead.read((char*)ptr, nPalEntries * sizeof(RGBQUAD)); 

   ptr = ptr + nPalEntries * sizeof(RGBQUAD);

   //Read in bits
   fileRead.read((char*) ptr, nDIBSize - (sizeof(BITMAPINFOHEADER) + nPalEntries * sizeof(RGBQUAD)));

   GlobalUnlock(locked);
   

   return true;
}


int MetadataBitmap::GetLastError()
{
   return 0;
}


/*********************
 * GetDIBColormapLen *
 *********************/
inline int MetadataBitmap::GetDIBColormapLen(const BITMAPINFOHEADER& header)
{
   if (header.biClrUsed) return min(256, header.biClrUsed);
   if (header.biBitCount <= 8) return 1 << header.biBitCount;
   return 0;
}

