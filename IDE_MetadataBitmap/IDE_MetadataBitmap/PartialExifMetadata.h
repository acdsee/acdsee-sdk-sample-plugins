//-------------------------------------------------------------------
// PartialExifMetadata.h
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
#include "../../API/Metadata.h"

class PartialExifMetadata : public MD_MetadataItem
{
public:
   PartialExifMetadata();
   ~PartialExifMetadata();

   GUID  GetMetadataType();
   void* GetMetadataData();
   void  Release();
   int   AddRef();
   void  CreateData(char* data);

   void  WritePartialExifToFile(std::ofstream& openFile);
   void  ReadPartialExifFromFile(std::ifstream& openFile);

private:
   char* data;
   int refCount;

};

