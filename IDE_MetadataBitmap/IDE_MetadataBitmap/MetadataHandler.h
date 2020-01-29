//-------------------------------------------------------------------
// MetadataHandler.h
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
#include "../../API/Metadata/Metadata.h"
class MetadataHandler
{
public:
   MetadataHandler(MD_MetadataList* inList);
   ~MetadataHandler();

   MD_MetadataList* GetMetadataList();

   bool WriteMetadataToFile(std::ofstream& openFile);
   void ReadMetadataFromFile(std::ifstream& openFile);

private:

   void WriteItemToFile(std::ofstream& openFile, MD_MetadataItem* item);
   MD_MetadataItem* ReadItemFromFile(std::ifstream& openFile);

   bool IsMetadataTypeSupported(GUID id);

   MD_MetadataList* m_list;

   bool IsExifMDItemSupported(MD_Item* item);

   void WriteGUIDToFile(std::ofstream& openFile, GUID id);
   GUID ReadGUIDFromFile(std::ifstream& openFile);

   void WriteMDItemToFile(std::ofstream& openFile, MD_Item* item);
   MD_Item* ReadMDItemFromFile(std::ifstream& openFile);


   void WriteExifCountToFile(std::ofstream& openFile, int count);
   int ReadExifCountFromFile(std::ifstream& openFile);
};

