//-------------------------------------------------------------------
// ID_APIWrapper.h
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
#include "../../API/ID_PlugIn.h"

class CreateViewDialog;
class ID_APIWrapper
{
public:
   ID_APIWrapper(ID_ClientInfo* pci);
   ~ID_APIWrapper();

   ID_PlugInInfo m_pi;  // This structure is used in ID_GetPlugInInfo
   ID_ClientInfo m_ci;
   int m_iNumFormats;
   ID_FormatInfo* m_fi;

   int DoOpenImage(ID_SourceInfo*, ID_StateHdl*);
   int DoCloseImage(ID_StateHdl);
   int DoGetImageInfo(ID_StateHdl, ID_ImageInfo*);
   int DoGetPageInfo(ID_StateHdl, int iPage, ID_PageInfo*);
   int DoPageDecode(ID_StateHdl, ID_DecodeParam*, ID_ImageOut*);

   int CreateView(ID_CreateViewParam* pCVS);

   std::unique_ptr<CreateViewDialog> m_view;
};

