//-------------------------------------------------------------------
// ID_MetadataBitmap.cpp
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

// ID_MetadataBitmap.cpp : Defines the exported functions for the DLL application.
//
//This file is the entry point for the image decode plug-in implemented for this sample.

#include "stdafx.h"
#include "ID_APIWrapper.h"
#include "../../API/ID_PlugIn.h"

namespace ID
{
   ID_APIWrapper* g_IDAPIWrapper = NULL;
}

/**********
* ID_Init *
***********
* The client application will call this function once after loading the
* plug-in library.  The plug-in must not maintain the pointer to
* PI_CallerInfo; it should make a copy the information in the structure.
* The plug-in should store application-specific options in
* HKEY_CURRENT_USER\Software\<szCompany>\<szAppName>
*/
PLUGIN_API int __stdcall ID_Init(
   ID_ClientInfo* pci)
{
   ID::g_IDAPIWrapper = new ID_APIWrapper(pci);
   return IDE_OK;
}

/**********
* ID_Free *
***********
* The client application will call this function once when it no longer
* needs the plug-in.  After ID_Free() is called, no other entry points
* may be called.  Normally, ID_Free() will be called immediately before
* unloading the plug-in DLL using FreeLibrary().
*
* ID_Free() will not be called if ID_Init() failed.
*
* The main purpose of ID_Free() is to give the plug-in a chance to free
* any DLLs it has dynamically loaded with LoadLibrary().
*
* Returns: IDE_OK.
*/
PLUGIN_API int __stdcall ID_Free()
{
   if(ID::g_IDAPIWrapper != NULL)
   {
      delete ID::g_IDAPIWrapper;
      ID::g_IDAPIWrapper = NULL;
   }
   return IDE_OK;
}

/*******************
* ID_GetPlugInInfo *
********************
* Returns a pointer to an ID_PlugInInfo struct.
* The plug-in owns the pointer and must not free it until the
* plug-in library is unloaded.
*/
PLUGIN_API int __stdcall ID_GetPlugInInfo(
   ID_PlugInInfo** pi)
{
   if(ID::g_IDAPIWrapper != NULL)
   {
      *pi = &(ID::g_IDAPIWrapper->m_pi);
   }
   return IDE_OK;
}

/**********************
* ID_ShowPlugInDialog *
***********************
* Show an "About" and/or "Options" dialog for this plug-in.
*/
PLUGIN_API int __stdcall ID_ShowPlugInDialog(
   HWND  hwndParent)  // Parent window
{
   MessageBoxW(hwndParent, L"This is a generic Image Decode Plug-In", L"Generic About Box", MB_OK | MB_ICONINFORMATION);
   return IDE_OK;
}

/***************
* ID_OpenImage *
****************/
PLUGIN_API int __stdcall ID_OpenImage(
   ID_SourceInfo* psi,   // [in]  Image source data.
   ID_StateHdl*   phs)   // [out] Image state handle
{
   int ret = IDE_OK;

   if (ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoOpenImage(psi, phs);
   }

   return ret;
}

/****************
* ID_CloseImage *
*****************/
PLUGIN_API int __stdcall ID_CloseImage(
   ID_StateHdl hs)       // [in]  Image state handle
{
   int ret = IDE_OK;

   if (ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoCloseImage(hs);
   }

   return ret;
}

/******************
* ID_GetImageInfo *
*******************/
PLUGIN_API int __stdcall ID_GetImageInfo(
   ID_StateHdl   hs,     // [in]  Image state handle
   ID_ImageInfo* pii)    // [out] Image information
{

   int ret = IDE_OK;

   if (ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoGetImageInfo(hs, pii);
   }

   return ret;
}

/*****************
* ID_GetPageInfo *
******************/
PLUGIN_API int __stdcall ID_GetPageInfo(
   ID_StateHdl   hs,      // [in]  Image state handle
   int           iPage,   // [in]  Page number (0-based) to get information for
   ID_PageInfo*  ppi)     // [out] Page information
{

   int ret = IDE_OK;

   if (ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoGetPageInfo(hs, iPage, ppi);
   }

   return ret;
}

/****************
* ID_PageDecode *
*****************/
PLUGIN_API int __stdcall ID_PageDecode(
   ID_StateHdl     hs,   // [in]  Image state handle
   ID_DecodeParam* pdp,  // [in]  Decoding parameters
   ID_ImageOut*    pio)  // [out] Output parameters  
{

   int ret = IDE_OK;

   if (ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoPageDecode(hs, pdp, pio);
   }

   return ret;
}

/***********************
* ID_GetMetadataList *
***********************
*
* Gets all or some of the metadata in an image. nMetaTypes = 0 and guidTypes == NULL to get all.
*/
PLUGIN_API int __stdcall ID_GetMetadataList(ID_StateHdl hs, int iPage, int nMetaTypes, GUID* guidTypes, MD_MetadataList* pList)
{
   int ret = IDE_OK;
   if(ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoGetMetadataList(hs, iPage, nMetaTypes, guidTypes, pList);
   }
   return ret;
}


/***********************
* GetSupportedMetadata *
************************
*
* Gets the list of supported metadata types for the image format specified.
*/
PLUGIN_API int __stdcall ID_GetSupportedMetadata(
   DWORD dwFormatID,                   // (in ) Format ID
   int& nFormats,                      // (out) Number of supported formats
   GUID** pFormats)                    // (out) GUIDs of supported formats
{
   int ret = IDE_OK;

   if(ID::g_IDAPIWrapper != NULL)
   {
      ret = ID::g_IDAPIWrapper->DoGetSupportedMetadata(dwFormatID, nFormats, pFormats);
   }
   return ret;
}
