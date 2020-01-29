//-------------------------------------------------------------------
// MD_ReadWriteMetadataItem.h
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

#include "../../API/Metadata.h"

class MD_ReadWriteMetadataItem : MD_MetadataItem
{
public:
   virtual GUID  GetMetadataType() = 0;
   virtual void* GetMetadataData() = 0;
   virtual void  Release() = 0;
   virtual int   AddRef() = 0;

   virtual int   InitializeFromFile(std::ifstream& openInputFile) = 0;
   virtual int   WriteMetadataToFile(std::ofstream& openOutputFile) = 0;

protected:
   virtual ~MD_ReadWriteMetadataItem() {};

};

