//-------------------------------------------------------------------
// IF_API_Wrapper.h
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

#include "../../API/IF_PlugIn.h"

enum UI_CONTROL_ID: int;

class IF_API_Wrapper
{

public:
   IF_API_Wrapper(IF_ClientInfo*  pci);
   ~IF_API_Wrapper();


   int RunFilter(IF_Bitmap* bitmap, IF_RenderInfo* pRI, DWORD filterID, IF_FilterParams* params);
   int RunMenuFilter(HWND hwndParent, IF_Bitmap* bitmap, IF_Bitmap* mask, DWORD filterID, IF_FilterParams** outParams);
   int RunMenuFilterAction(IF_Bitmap* bitmap, IF_Bitmap* mask, DWORD filterID, IF_FilterParams* params);

   IF_PlugInInfo m_PlugInInfo;  // This structure is used in IF_GetPlugInInfo

private:
   HINSTANCE      m_hResInst;       // DLL instance

   int RunBlurFilter(IF_Bitmap* bitmap, IF_FilterParams* params);
   int RunDirectionalBlurFilter(IF_Bitmap* bitmap, IF_FilterParams* params);
   int RunInverseFilter(IF_Bitmap* bitmap, IF_FilterParams* params);
   int RunPointDarkenFilter(IF_Bitmap* bitmap, IF_RenderInfo* pRI, IF_FilterParams* params);
   int RunTintFilter(IF_Bitmap* bitmap, IF_FilterParams* params);

};