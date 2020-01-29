//-------------------------------------------------------------------
// IE_MetadataBitmap.cpp
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

// IE_MetadataBitmap.cpp : Defines the exported functions for the DLL application.
//

//This file is the entry point for the image encode plug-in implemented for this sample.

#include "stdafx.h"
#include "IE_APIWrapper.h"
#include "../../API/IE_PlugIn.h"

namespace IE
{
   IE_APIWrapper* g_IEAPIWrapper = NULL;
}

/**********
* IE_Init *
***********
* The client application will call this function once after loading the
* plug-in library.  The plug-in must not maintain the pointer to
* PI_CallerInfo; it should make a copy the information in the structure.
*/
PLUGIN_API int __stdcall IE_Init(
   IE_ClientInfo* pci)
{
   IE::g_IEAPIWrapper = new IE_APIWrapper(pci);
   return IEE_OK;
}

/**********
* IE_Free *
***********
* The client application will call this function once when it no longer
* needs the plug-in.  After IE_Free() is called, no other entry points
* may be called.  Normally, IE_Free() will be called immediately before
* unloading the plug-in DLL using FreeLibrary().
*
* IE_Free() will not be called if IE_Init() failed.
*
* The main purpose of IE_Free() is to give the plug-in a chance to free
* any DLLs it has dynamically loaded with LoadLibrary().
*
* Returns: IEE_OK.
*/
PLUGIN_API int __stdcall IE_Free()
{
   if(IE::g_IEAPIWrapper != NULL)
   {
      delete IE::g_IEAPIWrapper;
      IE::g_IEAPIWrapper = NULL;
   }
   return IEE_OK;
}

/*******************
* IE_GetPlugInInfo *
********************
* Returns a pointer to an IE_PlugInInfo.
* The plug-in owns the pointer and must not free it until the
* plug-in library is unloaded.
*/
PLUGIN_API int __stdcall IE_GetPlugInInfo(
   IE_PlugInInfo**   pi)
{
   if(IE::g_IEAPIWrapper != NULL)
   {
      *pi = &(IE::g_IEAPIWrapper->m_pi);
   }
   return IEE_OK;
}

/**********************
* IE_ShowPlugInDialog *
***********************
* Shows an "About" and/or "Options" dialog for this plug-in.
*/
PLUGIN_API int __stdcall IE_ShowPlugInDialog(
   HWND              hwndParent)      // (in ) Parent window
{

   MessageBoxW(hwndParent, L"This is a generic Image Encoding Plug-In", L"Generic About Box", MB_OK | MB_ICONINFORMATION);
   return IEE_OK;
}

/**************************
* IE_GetValidPixelFormats *
***************************
* Requests an enumeration of all pixel formats supported by the specified
* format and encoding parameters.
*
* Note: If *pnPixFormats is set to 20 by the caller, then "new" pixel formats
* (as designated in the comments for the definitions of PFF_*)
* must not be returned by the plug-in.  This is a workaround for a bug in versions
* of ACDSee prior to 7, which rejected file formats that returned unrecognized
* pixel formats.
*
*/
PLUGIN_API int __stdcall IE_GetValidPixelFormats(
   DWORD             dwFormatID,      // (in ) ID of format to get PixFormats for
   IE_EncodeParams*  pEP,             // (in ) Encoding parameters
   int*              pnPixFormats,    // (i/o) On entry, size of pPixFormats array.  On exit, #pixel valid formats.
   DWORD*            pPixFormats)     // (out) Array of valid pixel formats
{
   int ret = IEE_OK;

   if (IE::g_IEAPIWrapper != NULL)
   {
      ret = IE::g_IEAPIWrapper->DoGetValidPixelFormats(dwFormatID, pEP, pnPixFormats, pPixFormats);
   }

   return ret;
}

/*****************
* IE_ImageEncode *
******************
* Writes a single-page image in one go.
*/
PLUGIN_API int __stdcall IE_ImageEncode(
   IE_OutputInfo*   pOI,             // (in ) Output information
   IE_EncodeParams* pEP,             // (in ) Encoding parameters
   IE_ImageInfo*    pII,             // (in ) Image information
   IE_PageInfo*     pPI,             // (in ) Page  information
   IE_CallbackData* pCD)             // (in ) Progress callback data
{
   int ret = IEE_OK;

   if (IE::g_IEAPIWrapper != NULL)
   {
      ret = IE::g_IEAPIWrapper->DoImageEncode(pOI, pEP, pII, pPI, pCD);
   }

   return ret;
}


/**************************
* IE_GetSupportedMetadata *
***************************
* Gets the supported Metadata types of the format. pFormats should be assigned to a plug-in allocated array of 
* GUID's, representing the supported metadata types. 
*/
PLUGIN_API int __stdcall IE_GetSupportedMetadata(
   DWORD  dwFormatID,                  // (in ) Format ID
   int&   nFormats,                    // (out) Number of supported formats
   GUID** pFormats)                    // (out) GUIDs of supported formats
{
   int ret = IEE_OK;

   if (IE::g_IEAPIWrapper != NULL)
   {
      ret = IE::g_IEAPIWrapper->DoGetSupportedMetadata(dwFormatID, nFormats, pFormats);
   }

   return ret;
}