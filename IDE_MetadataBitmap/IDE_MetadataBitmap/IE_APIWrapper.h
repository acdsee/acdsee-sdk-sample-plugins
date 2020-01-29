//-------------------------------------------------------------------
// IE_APIWrapper.h
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
#include "../../API/IE_PlugIn.h"

//This is a wrapper around the ACDSee Image Encoding Plug-In API. An instance of this class is created on init and deleted on free.
class IE_APIWrapper
{
public:
   IE_APIWrapper(IE_ClientInfo* ci);
   ~IE_APIWrapper();

   IE_PlugInInfo m_pi;  // This structure is used in IE_GetPlugInInfo

   int DoGetValidPixelFormats(DWORD dwFormatID, IE_EncodeParams* pEP, int* pnPixFormats, DWORD* pPixFormats);
   int DoImageEncode(IE_OutputInfo*, IE_EncodeParams*, IE_ImageInfo*, IE_PageInfo*, IE_CallbackData*);
   int DoGetSupportedMetadata(DWORD dwFormatID, int& nFormats, GUID** pFormats);

protected:
   IE_ClientInfo m_ci;
   IE_FormatInfo* m_fi;
   int m_iNumFormats;
};

