//-------------------------------------------------------------------
// PartialExifMetadata.cpp
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
#include "../../API/Metadata.h"
#include "PartialExifMetadata.h"

PartialExifMetadata::PartialExifMetadata()
   : refCount(1), data(nullptr)
{
}

PartialExifMetadata::~PartialExifMetadata()
{
   if(data!=nullptr)
   {
      delete data;
      data = nullptr;
   }
}

GUID  PartialExifMetadata::GetMetadataType()
{
   return METADATA_EXIF;
}

void* PartialExifMetadata::GetMetadataData()
{
   return (void*) data;
}

void PartialExifMetadata::Release()
{
   refCount--;
   if(refCount==0)
   {
      delete this;
   }
}

int PartialExifMetadata::AddRef()
{
   refCount++;
   return 0;
}

void PartialExifMetadata::CreateData(char* inData)
{
   if(data!=nullptr)
   {
      delete data;
      data = nullptr;
   }

   size_t len = strlen(inData);
   data = new char[len];
   strncpy_s(data, len*sizeof(char), inData, len);

}

void PartialExifMetadata::WritePartialExifToFile(std::ofstream& openFile)
{
   size_t len = strlen(data);
   openFile.write((char*)&len, sizeof(int));
   openFile.write(data, sizeof(char)*len);
}

void PartialExifMetadata::ReadPartialExifFromFile(std::ifstream& openFile)
{
   if(data!=nullptr)
   {
      delete data;
      data = nullptr;
   }

   int len = 0;
   openFile.read((char*)&len, sizeof(int));
   data = new char[len];
   openFile.read(data, sizeof(char)*len);
}
