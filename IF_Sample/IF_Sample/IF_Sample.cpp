//-------------------------------------------------------------------
// IF_Sample.cpp
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

// IF_Sample.cpp 
// This file is the entry point from ACDSee into your plugin.
// IF_Init will always be called before any other function.
// After IF_Free is called, there will be no further function calls.

#include "stdafx.h"
#include "../../API/IF_PlugIn.h"
#include "IF_API_Wrapper.h"


namespace IF
{
  IF_API_Wrapper* g_IFAPIWrapper = NULL;
}

PLUGIN_API int __stdcall IF_Init(IF_ClientInfo* pci)
{
   IF::g_IFAPIWrapper = new IF_API_Wrapper(pci);
   return IFE_OK;
}

PLUGIN_API int __stdcall IF_Free()
{
   if(IF::g_IFAPIWrapper != NULL)
   {
      delete IF::g_IFAPIWrapper;
      IF::g_IFAPIWrapper = NULL;
   }
   return IFE_OK;
}

PLUGIN_API int __stdcall IF_GetPlugInInfo(IF_PlugInInfo** ppii)
{
   if(IF::g_IFAPIWrapper != NULL)
   {
      *ppii = &(IF::g_IFAPIWrapper->m_PlugInInfo);
   }
   return IFE_OK;
}

PLUGIN_API int __stdcall IF_RunFilter(IF_Bitmap* bitmap, IF_RenderInfo* pRI, DWORD filterID, IF_FilterParams* params)
{
   int ret = IFE_OK;
   if(IF::g_IFAPIWrapper != NULL)
   {
      ret = IF::g_IFAPIWrapper->RunFilter(bitmap, pRI, filterID, params);
   }
   return ret;
}

PLUGIN_API int __stdcall IF_RunMenuFilter(HWND hwndParent, IF_Bitmap* bitmap, IF_Bitmap* mask, DWORD filterID, IF_FilterParams** params)
{
   int ret = IFE_OK;
   if(IF::g_IFAPIWrapper != NULL)
   {
      ret = IF::g_IFAPIWrapper->RunMenuFilter(hwndParent, bitmap, mask, filterID, params);
   }
   return ret;
}

PLUGIN_API int __stdcall IF_RunMenuFilterAction(IF_Bitmap* bitmap, IF_Bitmap* mask, DWORD filterID, IF_FilterParams* params)
{
   int ret = IFE_OK;
   if(IF::g_IFAPIWrapper != NULL)
   {
      ret = IF::g_IFAPIWrapper->RunMenuFilterAction( bitmap, mask, filterID, params);
   }
   return ret;
}

//This will be called after IF_RunMenuFilter, to allow the plugin to delete any allocated params from that call.
PLUGIN_API int __stdcall IF_FreeAllocatedParams(IF_FilterParams* params)
{
   if(params)
   {
      for(int i=0; i<params->nParams; ++i)
      {
         delete[] params->pParams[i].pszParamValue;
      }
      if(params->pParams)
         delete[] params->pParams;
      delete params;
   }
   

   return IFE_OK;
}

