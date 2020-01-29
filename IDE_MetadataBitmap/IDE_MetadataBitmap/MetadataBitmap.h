//-------------------------------------------------------------------
// MetadataBitmap.h
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
#include "MetadataHandler.h"

//Class is created in open image. Heap allocated. Passed as pointer in void*. Deleted in close image.
//ID_StateHdl*   phs points to an instance of this class always.
//Represents the entireity of a metadata bitmap. 
class MetadataBitmap
{
public:
   //Image Encode constructor
   MetadataBitmap();
   ~MetadataBitmap();

   void OpenDecodeImage(std::wstring filename);
   void CloseDecodeImage();

   void GetDecodeImageDimensions(SIZE& si);
   int GetNumDecodeMetadataTypes();
   HGLOBAL GetDecodeMetadataGUIDArray();

   //Returns a handle to a packed dib.
   HGLOBAL GetPackedDIB();

   //true on success, false on fail. use geterror on failure to determine why it failed.
   bool DecodeImage(MD_MetadataList* pMetadata);
   bool WriteImage(std::wstring outfilename, BITMAPINFO* pBitmapInfo, void* pBits, MD_MetadataList* pMetadata);
protected:
   bool ReadBitmap(std::ifstream& fileRead);
   bool WriteBitmap(std::ofstream& fileWriter, BITMAPINFO* pBitmapInfo, void* pBits);
public:

   //Returns last error. You might want to implement this.
   int GetLastError();
protected:
   //Bitmap handlng Utilities
   inline int GetDIBColormapLen(const BITMAPINFOHEADER& bmih);


   //Reads in metadata + bitmap, stores it.
   bool hasFileBeenDecoded;

   std::ifstream decodeFile;
   bool hasOpenDecodeFile;

   SIZE decodeFileDimensions;

   HGLOBAL packedDIB;
   bool mustFreeDIB;  //If we havnt given the dib away.
};

