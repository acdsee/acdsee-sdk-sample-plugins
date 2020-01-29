//-------------------------------------------------------------------
// CX_ApiWrapper.cpp
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
#include "CX_ApiWrapper.h"
#include "HistogramImpl.h"
#include "../../API/CX_PlugIn.h"

CX_APIWrapper::CX_APIWrapper(CX_ClientInfo*  pci) 
{
   // Set up structures for supported commands
   m_CommandInfo[0].dwFlags = CX_CI_BTNLABEL | CX_CI_CATEGORIES;

   //What type of files does command work with
   m_CommandInfo[0].dwValidFlags = CVF_NONONIMAGES | CVF_NOMULTIPLE;
   m_CommandInfo[0].iIcon = 0;

   //Choose which category of plugin you are making
   m_CommandInfo[0].dwCategories =  CX_CN_SHARE;

   //Name of the Command
   std::wstring pszCommandName(L"Sample Show Histogram");

   //Text of the menu item used to run the command
   std::wstring pszMenuItemName(L"Sample Show Histogram");

   //Description of the Command
   std::wstring pszDescription(L"Sample Show Histogram");

   //If command has a button, the button text for the command
   std::wstring pszButtonLabel(L"Sample Show Histogram");

   wcsncpy_s(m_CommandInfo[0].szName,         pszCommandName.c_str(),  _countof(m_CommandInfo[0].szName));
   wcsncpy_s(m_CommandInfo[0].szMenuItemName, pszMenuItemName.c_str(), _countof(m_CommandInfo[0].szMenuItemName));
   wcsncpy_s(m_CommandInfo[0].szDescription,  pszDescription.c_str(),  _countof(m_CommandInfo[0].szDescription));
   wcsncpy_s(m_CommandInfo[0].szBtnLabel,     pszButtonLabel.c_str(),  _countof(m_CommandInfo[0].szBtnLabel));

   // Set up the plug-in info structure
   m_PlugInInfo.dwFlags = 0;
   m_PlugInInfo.nVersion = CX_VERSION;

   //Title of the PlugIn
   std::wstring pszPlugInTitle(L"Sample Show Histogram");
   wcsncpy_s(m_PlugInInfo.szTitle, pszPlugInTitle.c_str(), _countof(m_PlugInInfo.szTitle));

   m_PlugInInfo.nCommands = 1;
   m_PlugInInfo.pCommandInfo = m_CommandInfo;
}

CX_APIWrapper::~CX_APIWrapper()
{
}

int CX_APIWrapper::DoCX(
   CX_CommandParams*  pcp,  // (in ) Specifies command to invoke, and parameters
   CX_CommandResults* pcr)  // (out) Command results)
{

   //Get a list of selected image's file names
   std::vector<std::wstring> selectedFileNames;
   for (int i = 0; i < pcp->nFiles; ++i)
   {
      CX_FileInfo fileInfo = pcp->pfi[i];
      if (fileInfo.dwAttribs & IAF_IMAGE) //If the file is an image
      {
         selectedFileNames.emplace_back(std::wstring(fileInfo.pszFN));
      }
   }

   int ret = 0;
   for(auto file : selectedFileNames)
   {   
      try
      {
         //Arbritary max size
         SIZE maxSize;
         maxSize.cx = 100000;
         maxSize.cy = 100000;

         //Use a callback to decode the file into a packed DIB. This must be later freed.
         CX_DecodeImageParams dip;
         dip.dwFlags = DIF_COMMONPAL;
         dip.iPage = 0;
         dip.hdib = NULL;
         dip.pfProgress = NULL;
         dip.pParam = NULL;
         dip.siMax = maxSize;
         pcp->cb.DecodeFileImage(file.c_str(), &dip);

         //Calculate/show a histogram in a dialog.
         HistogramImpl histoImpl;
         ret = histoImpl.ShowHistogram(dip.hdib, pcp->hwndParent);

         //Free the packed DIB
         GlobalFree(dip.hdib);
      }
      catch (...)
      {

      }
      if(ret != CXE_OK)
      {
         return ret;
      }
   }

   return ret;
}

