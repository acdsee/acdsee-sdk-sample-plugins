//-------------------------------------------------------------------
// TEMP
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
//Class is created in open image. Heap allocated. Passed as pointer in void*. Deleted in close image.
//ID_StateHdl*   phs points to an instance of this class always.
//Represents the entireity of a metadata bitmap. 
class CreateViewImpl
{
public:
   //Image Encode constructor
   CreateViewImpl();
   ~CreateViewImpl();

   void OpenDecodeImage(std::wstring filename);
   void CloseDecodeImage();

   void GetDecodeImageDimensions(SIZE& si);

   //Returns a handle to a packed dib.
   HGLOBAL GetPackedDIB();

   int GetDecodeImageBitsPerSample();
   int GetDecodeImageSamplesPerPixel();
   //true on success, false on fail. use geterror on failure to determine why it failed.
   bool DecodeImage();
protected:
   bool ReadTextIntoBitmap(std::wifstream& fileRead);
public:

   //Returns last error
   int GetLastError();
protected:
   //Reads in metadata + bitmap, stores it.
   bool hasFileBeenDecoded;

   std::wifstream decodeFile;
   bool hasOpenDecodeFile;

   SIZE decodeFileDimensions;

   HGLOBAL packedDIB;
   bool mustFreeDIB;  //If we havnt given the dib away.

   std::wstring fileText;

};