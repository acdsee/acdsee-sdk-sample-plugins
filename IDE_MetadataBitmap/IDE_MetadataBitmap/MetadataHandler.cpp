//-------------------------------------------------------------------
// MetadataHandler.cpp
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
#include "MetadataHandler.h"
#include "../../API/Metadata/Metadata.h"
#include "../../API/Metadata/MetadataUtil.h"

MetadataHandler::MetadataHandler(MD_MetadataList* inList)
   :m_list(inList)
{
   m_list->AddRef();
}

MetadataHandler::~MetadataHandler()
{
   m_list->Release();
}

MD_MetadataList* MetadataHandler::GetMetadataList()
{
   return this->m_list;
}

//Entry point for writing
bool MetadataHandler::WriteMetadataToFile(std::ofstream& openFile)
{
   int numMetadataItems = 0;
   if(this->m_list!=nullptr)
   {
      numMetadataItems = this->m_list->GetMetadataCount();
   }

   int numSupportedMetadataItems = 0;
   for(int i=0; i<numMetadataItems; ++i)
   {
      MD_MetadataItem* item = this->m_list->GetMetadataItem(i);
      if(IsMetadataTypeSupported(item->GetMetadataType()))
      {
         numSupportedMetadataItems+=1;
      }
      item->Release();
   }

   openFile.write((char*) &numSupportedMetadataItems, sizeof(int));

   for(int i=0; i<numMetadataItems; ++i)
   {
      MD_MetadataItem* item = this->m_list->GetMetadataItem(i);
      if(IsMetadataTypeSupported(item->GetMetadataType()))
      {
         WriteItemToFile(openFile, item);
      }
      item->Release();
   }
   return true;
}

//Entry point for reading
void MetadataHandler::ReadMetadataFromFile(std::ifstream& openFile)
{
   int numMetadataItems = 0;

   openFile.read((char*)&numMetadataItems, sizeof(int));

   for(int i=0; i<numMetadataItems; ++i)
   {
      MD_MetadataItem* md_item = ReadItemFromFile(openFile);
      if(m_list!=nullptr)
      {
         m_list->AddMetadataItem(md_item);
      }
      md_item->Release();
   }
}

bool MetadataHandler::IsMetadataTypeSupported(GUID id)
{
   if(METADATA_EXIF == id)
   {
      return true;
   }
   else if(METADATA_ACD == id)
   {
      return true;
   }

   return false;
}

//Writes a specific metadata item to file
void MetadataHandler::WriteItemToFile(std::ofstream& openFile, MD_MetadataItem* item)
{
   GUID itemGUID = item->GetMetadataType();
   WriteGUIDToFile(openFile, item->GetMetadataType());

   if(itemGUID == METADATA_EXIF)
   {
      CExifMetadataItem* pItem = (CExifMetadataItem*) item;

      MD_Item* item = pItem->GetExifMetadata();
      //get count
      MD_Item* curItem = item;
      int count = 0;
      while(curItem)
      {
         if(IsExifMDItemSupported(curItem))
         {
            count++;
         }
         curItem = curItem->pNext;
      }

      //Write count of exif metadata to file.
      WriteExifCountToFile(openFile, count);

      //Write each supported item to file
      curItem = item;
      while(curItem)
      {
         if(IsExifMDItemSupported(curItem))
         {
            WriteMDItemToFile(openFile, curItem);
         }
         curItem = curItem->pNext;
      }

   }
}

bool MetadataHandler::IsExifMDItemSupported(MD_Item* item)
{
   if(item->nDataID == MDT_MAKE || item->nDataID == MDT_MODEL)
   {
      return true;
   }
   return false;
}

void MetadataHandler::WriteMDItemToFile(std::ofstream& openFile, MD_Item* item)
{
   if(item->nDataID == MDT_MAKE  || item->nDataID == MDT_MODEL)
   {
      openFile.write((char*)&item->nDataID, sizeof(WORD));
      openFile.write((char*)&item->nTypeID, sizeof(WORD));
      openFile.write((char*)&item->nCount, sizeof(UINT));
      openFile.write((char*)item->pszData, sizeof(char) * item->nCount);
   }
}

MD_Item* MetadataHandler::ReadMDItemFromFile(std::ifstream& openFile)
{
   MD_Item* item = new MD_Item();

   openFile.read((char*)&item->nDataID, sizeof(WORD));
   openFile.read((char*)&item->nTypeID, sizeof(WORD));
   openFile.read((char*)&item->nCount, sizeof(UINT));

   item->pszData = new char[item->nCount];
   openFile.read((char*)item->pszData, sizeof(char) * item->nCount);

   return item;
}

//Reads a metadata item from file
//It is the callers responsibility to free the returned MD_MetdataItem
MD_MetadataItem* MetadataHandler::ReadItemFromFile(std::ifstream& openFile)
{
   GUID itemGUID = ReadGUIDFromFile(openFile);

   if(itemGUID == METADATA_EXIF)
   {

      int count = ReadExifCountFromFile(openFile);

      MD_Item* start;
      if(count == 0)
      {
         return new CExifMetadataItem(new MD_Item());
      }

      start = ReadMDItemFromFile(openFile);

      MD_Item* cur = start;
      for(int i=1; i<count; ++i)
      {
         cur->pNext = ReadMDItemFromFile(openFile);
         cur=cur->pNext;
      }

      return new CExifMetadataItem(start);
   }
   throw;//Something went wrong somewhere. Reading an unknown type of metadata.
   return nullptr; 
}

void MetadataHandler::WriteExifCountToFile(std::ofstream& openFile, int count)
{
   openFile.write((char*)&count, sizeof(int));
}

int MetadataHandler::ReadExifCountFromFile(std::ifstream& openFile)
{
   int count;
   openFile.read((char*)&count, sizeof(int));
   return count;
}

void MetadataHandler::WriteGUIDToFile(std::ofstream& openFile, GUID id)
{
   openFile.write((char*)&id, sizeof(GUID));
}

GUID MetadataHandler::ReadGUIDFromFile(std::ifstream& openFile)
{
   GUID itemGUID;
   openFile.read((char*)&itemGUID, sizeof(GUID));
   return itemGUID;

}

