//-------------------------------------------------------------------
// IE_APIWrapper.cpp
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
#include "IE_APIWrapper.h"

#include "../../API/IE_PlugIn.h"

#include "MetadataBitmap.h"
#include "MetadataBitmapSharedConstants.h"

using namespace MetadataBitmapConstants;

GUID pIE_MBMFormats[] = {METADATA_EXIF};

IE_APIWrapper::IE_APIWrapper(IE_ClientInfo* ci)
{
   //Setup Client Info
   m_ci.dwFlags = ci->dwFlags;
   wcsncpy_s(m_ci.szAppName, ci->szAppName, _countof(m_ci.szAppName));
   wcsncpy_s(m_ci.szCompany, ci->szCompany, _countof(m_ci.szCompany));

   //Number of supported formats
   m_iNumFormats = 1;

   //Set up format Info for each format
   m_fi = new IE_FormatInfo[m_iNumFormats];

   m_fi[0].dwFlags = FIF_EDITMODE;
   m_fi[0].dwID = MetadataBitmapConstants::IT_MBM;
   m_fi[0].iIcon = 0;
   wcsncpy_s(m_fi[0].szDefExt, L"MBM", _countof(m_fi[0].szDefExt));
   wcsncpy_s(m_fi[0].szName, L"Metadata Bitmap Format", _countof(m_fi[0].szName));
   wcsncpy_s(m_fi[0].szNameShort, L"MBM", _countof(m_fi[0].szNameShort));

   //Setup PlugIn Info
   m_pi.dwFlags = 0;
   m_pi.iIcon=0;
   m_pi.nFormats = m_iNumFormats;
   m_pi.nVersion = IE_VERSION;
   m_pi.pFormatInfo = m_fi;
   wcsncpy_s(m_pi.szTitle, L"Metadata Bitmap Format", _countof(m_pi.szTitle));
}

IE_APIWrapper::~IE_APIWrapper()
{
   delete m_fi;
}

int IE_APIWrapper::DoGetValidPixelFormats(DWORD dwFormatID, IE_EncodeParams* pEP, int* pnPixFormats, DWORD* pPixFormats)
{
   //Only support 24 bits per pixel RBG for simplicities sake
   *pnPixFormats = min(*pnPixFormats, nValidPixFmts);

   for(int i=0; i<*pnPixFormats; ++i)
   {
      *pPixFormats = ValidPixFmts[i];
      pPixFormats = pPixFormats + sizeof(DWORD);
   }
   
   return IEE_OK;
}

int IE_APIWrapper::DoImageEncode(IE_OutputInfo* pOI, IE_EncodeParams* pEP, IE_ImageInfo* pII, IE_PageInfo* pPI, IE_CallbackData* pCD)
{
   //Input validation
   bool isValidPixelFormat = false;
   for(int i=0; i<nValidPixFmts; ++i)
   {
      if(pPI->dwPixFormatFlags == ValidPixFmts[i]) isValidPixelFormat = true;
   }
   if(!isValidPixelFormat) return IEE_InvalidPixFormat;

   if(pPI->bHasTranparencyChannel)
   {
      return IEE_InvalidParam;
   }

   pOI->dwFormatID = MetadataBitmapConstants::IT_MBM;

   MetadataBitmap encoder;
   int success = encoder.WriteImage(std::wstring(pOI->pszFN), pPI->pBMI, pPI->pBits, pPI->pMetadataList);

   if(!success)
   {
      int error = encoder.GetLastError();

      switch(error)
         case 0:
         default:
            return IEE_Error;
   }

   return IEE_OK;
}

int IE_APIWrapper::DoGetSupportedMetadata(DWORD dwFormatID, int& nFormats, GUID** pFormats)
{
   *pFormats = pIE_MBMFormats;
	nFormats = sizeof(pIE_MBMFormats)/sizeof(pIE_MBMFormats[0]);
	return IDE_OK;
}

