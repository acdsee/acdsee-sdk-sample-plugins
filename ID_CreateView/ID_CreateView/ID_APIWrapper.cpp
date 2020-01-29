//-------------------------------------------------------------------
// ID_APIWrapper.cpp
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
#include "ID_APIWrapper.h"

#include "../../API/ID_PlugIn.h"
#include "CreateViewImpl.h"
#include "CreateViewSharedConstants.h"
#include "CreateViewDialog.h"

ID_APIWrapper::ID_APIWrapper(ID_ClientInfo* ci)
{
   //Setup Client Info
   m_ci.dwFlags = ci->dwFlags;
   wcsncpy_s(m_ci.szAppName, ci->szAppName, _countof(m_ci.szAppName));
   wcsncpy_s(m_ci.szCompany, ci->szCompany, _countof(m_ci.szCompany));

   //Number of supported formats
   m_iNumFormats = 1;

   //Set up format Info for each format
   m_fi = new ID_FormatInfo[m_iNumFormats];

   m_fi[0].dwFlags = FIF_VIEWWINDOW;
   m_fi[0].dwID = CreateViewConstants::IT_TXT;
   m_fi[0].iIcon = 0;
   m_fi[0].color = RGB(200, 200, 255);

   m_fi[0].pszExtList = new wchar_t[5];

   lstrcpynW(m_fi[0].pszExtList, L"TXT", 4);
   m_fi[0].pszExtList[3] = L'\0';
   m_fi[0].pszExtList[4] = L'\0';

   wcsncpy_s(m_fi[0].szDefExt, L"TXT", _countof(m_fi[0].szDefExt));
   wcsncpy_s(m_fi[0].szName, L"TXT CV Format", _countof(m_fi[0].szName));
   wcsncpy_s(m_fi[0].szNameShort, L"TXT", _countof(m_fi[0].szNameShort));

   //Setup PlugIn Info
   m_pi.dwFlags = 0;
   m_pi.iIcon = 0;
   m_pi.nFormats = m_iNumFormats;
   m_pi.nVersion = ID_VERSION;
   m_pi.pFormatInfo = m_fi;
   wcsncpy_s(m_pi.szTitle, L"TXT CV Format", _countof(m_pi.szTitle));

}

ID_APIWrapper::~ID_APIWrapper()
{
   delete m_fi->pszExtList;
   delete m_fi;
}

int ID_APIWrapper::DoOpenImage(ID_SourceInfo* psi, ID_StateHdl* phs)
{
   CreateViewImpl* decoder = new CreateViewImpl();
   decoder->OpenDecodeImage(std::wstring(psi->pszFN));

   *phs = decoder;
   return IDE_OK;
}

int ID_APIWrapper::DoCloseImage(ID_StateHdl hs)
{
   CreateViewImpl* decoder = (CreateViewImpl*)hs;
   decoder->CloseDecodeImage();
   delete decoder;

   return IDE_OK;
}

int ID_APIWrapper::DoGetImageInfo(ID_StateHdl hs, ID_ImageInfo* pii)
{
   CreateViewImpl* decoder = (CreateViewImpl*)hs;

   //Flags
   pii->dwFlags = 0;

   //Format
   pii->dwFormatID = CreateViewConstants::IT_TXT;

   //Dimensions
   decoder->GetDecodeImageDimensions(pii->si);

   //Bits per sample
   pii->nBPS = decoder->GetDecodeImageBitsPerSample();
   pii->nSPP = decoder->GetDecodeImageSamplesPerPixel();

   //Number of pages - 1
   pii->nPages = 1;

   //number of metadata types
   pii->nMetadataTypes = 0;

   //GUID array of metadata types
   pii->hMetadataTypes = NULL;

   return IDE_OK;
}

int ID_APIWrapper::DoGetPageInfo(ID_StateHdl hs, int iPage, ID_PageInfo* ppi)
{
   CreateViewImpl* decoder = (CreateViewImpl*)hs;

   //Make sure it is only wants the first page
   if(iPage!=0)
      return IDE_NoPage;

   //flags
   ppi->dwFlags = PPF_RGB;

   //dimensions
   decoder->GetDecodeImageDimensions(ppi->si);

   //bits per sample
   ppi->nBPS = decoder->GetDecodeImageBitsPerSample();

   //samples per pixel
   ppi->nSPP = decoder->GetDecodeImageSamplesPerPixel();

   //frame delay in ms
   ppi->nDelay = 0;

   //page title
   wcsncpy_s(ppi->szTitle, L"", _countof(ppi->szTitle));

   //number of metadata types
   ppi->nMetadataTypes = 0;

   //GUID array of metadata types
   ppi->hMetadataTypes = NULL;

   return IDE_OK;
}

int ID_APIWrapper::DoPageDecode(ID_StateHdl hs, ID_DecodeParam* pdp, ID_ImageOut* pio)
{
   CreateViewImpl* decoder = (CreateViewImpl*)hs;

   //Only support full image decoding.
   if(pio->dwFlags && PID_RECT)
   {
      return IDE_InvalidParam;
   }
   SIZE si;
   decoder->GetDecodeImageDimensions(si);

   //No IOF_ flags to set
   pio->dwFlags = POF_TOPDOWN;

   //Handle to a packed dib
   pio->hdib = decoder->GetPackedDIB();

   //Not used
   pio->hemf = NULL;

   //We only decode the full image for this type
   pio->rc.bottom = si.cy;
   pio->rc.right = si.cx;
   pio->rc.left = 0;
   pio->rc.top = 0;


   return IDE_OK;
}


int ID_APIWrapper::CreateView( ID_CreateViewParam* pCVS)
{
   //Create View Object. Save on the object. Remember to delete when in destructor.
   m_view = std::make_unique<CreateViewDialog>();
   m_view->Create(NULL, NULL, WS_CHILD, CRect(0,0,100,100), CWnd::FromHandlePermanent(pCVS->hwndParent), 0);

   //Assign View Object to the params
   pCVS->hwndView = m_view->GetSafeHwnd();

   return IDE_OK;
}