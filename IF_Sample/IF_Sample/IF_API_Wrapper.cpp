//-------------------------------------------------------------------
// IF_API_Wrapper.cpp
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

#include "IF_API_Wrapper.h"

#include "../../API/IF_PlugIn.h"
#include "IF_API_Util.h"

#include "Blur.h"
#include "DirectionalBlur.h"
#include "Inverse.h"
#include "PointDarken.h"
#include "Tint.h"
#include "resource.h"

//ID's for the UI controls, used to identify/parse parameters passed to filters.
enum UI_CONTROL_ID
{
   BLUR_RADIUS,

   DIRBLUR_RADIUS,
   DIRBLUR_DIRECTION,

   POINTDARKEN_STRENGTH,
   POINTDARKEN_SCALETYPE,
   POINTDARKEN_SCALETYPE_LINEAR,
   POINTDARKEN_SCALETYPE_EXPONENTIAL,

   TINT_STRENGTH,
};

//ID's for filters.
enum FILTER_ID
{
   FID_BLUR,
   FID_DIRBLUR,
   FID_INVERSE,
   FID_DARKEN,
   FID_TINT,
   FID_TOTALCOUNT,
};

//This constructor sets up all of the information detailing the filters contained in the plugin
IF_API_Wrapper::IF_API_Wrapper(IF_ClientInfo*  pci)
{
   //Setup plugin info
   m_PlugInInfo.dwFlags = 0;
   CLSIDFromString(L"{945b36e0-f26b-4f8a-bf73-3c6a8c5a6a2f}", &m_PlugInInfo.guid); //Each Plugin should have a GUID generated for it every version.
   m_PlugInInfo.iIcon = IDI_ICON1;
   m_PlugInInfo.nFilters = FID_TOTALCOUNT;
   m_PlugInInfo.nVersion = IF_VERSION;
   m_PlugInInfo.pFilterInfo = new IF_FilterInfo[FID_TOTALCOUNT];

   lstrcpyn(m_PlugInInfo.szTitle, L"Sample Filter Plug-Ins", _countof(m_PlugInInfo.szTitle));


   //Setup Filter Info

   //Blur
   IF_Util::SetupFilterInfo(&m_PlugInInfo.pFilterInfo[FID_BLUR], 0, FID_BLUR, true, L"Sample Blur", L"Blur");
   m_PlugInInfo.pFilterInfo[FID_BLUR].iIcon = IDI_ICON1;

   //DirectionalBlur
   IF_Util::SetupFilterInfo(&m_PlugInInfo.pFilterInfo[FID_DIRBLUR], 0, FID_DIRBLUR, true, L"Sample Directional Blur", L"D-Blur");
   m_PlugInInfo.pFilterInfo[FID_DIRBLUR].iIcon = IDI_ICON1;

   //Inverse
   IF_Util::SetupFilterInfo(&m_PlugInInfo.pFilterInfo[FID_INVERSE], 0, FID_INVERSE, false, L"Sample Inverse", L"Inverse");
   m_PlugInInfo.pFilterInfo[FID_INVERSE].iIcon = IDI_ICON1;

   //Point Darken
   IF_Util::SetupFilterInfo(&m_PlugInInfo.pFilterInfo[FID_DARKEN], 0, FID_DARKEN, true, L"Sample Point Darken", L"Darken");
   m_PlugInInfo.pFilterInfo[FID_DARKEN].iIcon = IDI_ICON1;

   //Tint
   IF_Util::SetupFilterInfo(&m_PlugInInfo.pFilterInfo[FID_TINT], 0, FID_TINT, true, L"Sample Tint", L"Tint");
   m_PlugInInfo.pFilterInfo[FID_TINT].iIcon = IDI_ICON1;

   //Setup GUI Specification

   IF_UISpecification* pUISpec;
   //Blur
   pUISpec = &m_PlugInInfo.pFilterInfo[FID_BLUR].uiSpec;

   pUISpec->previewFlags = IF_FDBP_CANZOOM | IF_FDBP_CANRENDERSCALED | IF_FDBP_CANRENDERROI;
   pUISpec->dialogFlags  = IF_FDBD_HAS_PREVIEW_HISTOGRAM;
   pUISpec->filterTool = IF_TOOL_NONE;
   pUISpec->bSquishUI = false;

   IF_Util::AllocateArrays(pUISpec, 1, 0, 0, 0);
   IF_Util::SetupSlider(&pUISpec->pSliderInfo[0], BLUR_RADIUS, L"Radius", 1, 10, 1, 1);

   //Directional Blur
   pUISpec = &m_PlugInInfo.pFilterInfo[FID_DIRBLUR].uiSpec;

   pUISpec->previewFlags = IF_FDBP_CANZOOM | IF_FDBP_CANRENDERSCALED | IF_FDBP_CANRENDERROI;
   pUISpec->dialogFlags  = IF_FDBD_HAS_PREVIEW_HISTOGRAM;
   pUISpec->filterTool = IF_TOOL_NONE;
   pUISpec->bSquishUI = false;

   IF_Util::AllocateArrays(pUISpec, 1, 0, 1, 0);
   IF_Util::SetupSlider(&pUISpec->pSliderInfo[0], DIRBLUR_RADIUS, L"Radius", 1, 10, 1, 1);
   IF_Util::SetupAnglePicker(&pUISpec->pAnglePickerInfo[0], DIRBLUR_DIRECTION, L"Direction");

   //Inverse
   pUISpec = &m_PlugInInfo.pFilterInfo[FID_INVERSE].uiSpec;

   pUISpec->previewFlags = IF_FDBP_CANZOOM | IF_FDBP_CANRENDERSCALED | IF_FDBP_CANRENDERROI;
   pUISpec->dialogFlags  = IF_FDBD_HAS_PREVIEW_HISTOGRAM;
   pUISpec->filterTool = IF_TOOL_NONE;
   pUISpec->bSquishUI = false;

   IF_Util::AllocateArrays(pUISpec, 0, 0, 0, 0);

   //Point Darken
   pUISpec = &m_PlugInInfo.pFilterInfo[FID_DARKEN].uiSpec;

   pUISpec->previewFlags = IF_FDBP_CANZOOM | IF_FDBP_CANRENDERSCALED | IF_FDBP_CANRENDERROI;
   pUISpec->dialogFlags  = IF_FDBD_HAS_PREVIEW_HISTOGRAM;
   pUISpec->filterTool = IF_TOOL_POSITIONSELECT;
   pUISpec->bSquishUI = false;

   IF_Util::AllocateArrays(pUISpec, 1, 0, 0, 1);
   IF_Util::SetupSlider(&pUISpec->pSliderInfo[0], POINTDARKEN_STRENGTH, L"Strength", 0, 100, 1, 1);
   IF_Util::SetupButtonGroup(&pUISpec->pButtonGroupInfo[0], POINTDARKEN_SCALETYPE, 2, L"Distance Scaling Type", true);
   IF_Util::SetupButton(&pUISpec->pButtonGroupInfo[0].pButtonInfo[0], POINTDARKEN_SCALETYPE_LINEAR, L"Linear", true);
   IF_Util::SetupButton(&pUISpec->pButtonGroupInfo[0].pButtonInfo[1], POINTDARKEN_SCALETYPE_EXPONENTIAL, L"Exponential", false);



   //Tint
   pUISpec = &m_PlugInInfo.pFilterInfo[FID_TINT].uiSpec;

   pUISpec->previewFlags = IF_FDBP_CANZOOM | IF_FDBP_CANRENDERSCALED | IF_FDBP_CANRENDERROI;
   pUISpec->dialogFlags  = IF_FDBD_HAS_PREVIEW_HISTOGRAM;
   pUISpec->filterTool = IF_TOOL_COLORSELECT;
   pUISpec->bSquishUI = false;

   IF_Util::AllocateArrays(pUISpec, 1, 0, 0, 0);
   IF_Util::SetupSlider(&pUISpec->pSliderInfo[0], TINT_STRENGTH, L"Strength", 0, 100, 50, 1);
}


//Free all allocated memory for the pluginInfo.
IF_API_Wrapper::~IF_API_Wrapper()
{
   if(m_PlugInInfo.nFilters>0)
   {
      for(int i=0; i<m_PlugInInfo.nFilters; ++i)
      {
         if(m_PlugInInfo.pFilterInfo[i].uiSpec.pSliderInfo != NULL)
         {
            delete[] m_PlugInInfo.pFilterInfo[i].uiSpec.pSliderInfo;
         }
         if(m_PlugInInfo.pFilterInfo[i].uiSpec.pColorPickerInfo != NULL)
         {
            delete[] m_PlugInInfo.pFilterInfo[i].uiSpec.pColorPickerInfo;
         }
         if(m_PlugInInfo.pFilterInfo[i].uiSpec.pAnglePickerInfo != NULL)
         {
            delete[] m_PlugInInfo.pFilterInfo[i].uiSpec.pAnglePickerInfo;
         }
         if(m_PlugInInfo.pFilterInfo[i].uiSpec.pButtonGroupInfo != NULL)
         {
            for(int j=0; j<m_PlugInInfo.pFilterInfo[i].uiSpec.nButtonGroups; ++j)
            {
               IF_Util::DeleteButtonGroupContents(&m_PlugInInfo.pFilterInfo[i].uiSpec.pButtonGroupInfo[j]);
            }
            delete[] m_PlugInInfo.pFilterInfo[i].uiSpec.pButtonGroupInfo;
         } 
      }
      delete[] m_PlugInInfo.pFilterInfo;
   }
}

//Calls the appropriate Native GUI filter code, based on the filterID passed in.
//These filters all have bIsNativeGUIFilter set to true, and are called when you enter the filter.
int IF_API_Wrapper::RunFilter(IF_Bitmap* bitmap, IF_RenderInfo* pRI, DWORD filterID, IF_FilterParams* params)
{
  if( bitmap->pHeader->bmiHeader.biBitCount > 32)
  {
     MessageBoxW(NULL, L"Greater then 32-bit bitmaps not supported by sample", L"Not Supported", MB_OK);
     return IFE_Error;
  }
  switch(filterID)
  {
   case FID_BLUR:
      return RunBlurFilter(bitmap, params);
   case FID_DIRBLUR:
      return RunDirectionalBlurFilter(bitmap, params);
   case FID_INVERSE:
      return RunInverseFilter(bitmap, params);
   case FID_DARKEN:
      return RunPointDarkenFilter(bitmap, pRI, params);
   case FID_TINT:
      return RunTintFilter(bitmap, params);
  }
  return IFE_FilterNotFound;

}

//Calls the appropriate Foreign Filter code, based on the filterID passed in.
//These filters all have bIsNativeGUIFilter set to false, and are called from the Tools Menu
//As we are not popping up a dialog, we ignore the parent handle.
//We also ignore the mask, running filter on the entire image.
int IF_API_Wrapper::RunMenuFilter(HWND hwndParent, IF_Bitmap* bitmap, IF_Bitmap* mask, DWORD filterID, IF_FilterParams** outParams)
{
   if( bitmap->pHeader->bmiHeader.biBitCount > 32)
   {
      MessageBoxW(NULL, L"Greater then 32-bit bitmaps not supported by sample", L"Not Supported", MB_OK);
      return IFE_Error;
   }
   switch(filterID)
   {
      case FID_INVERSE:
         int ret = MessageBoxW(hwndParent, L"Do you want to run the filter?", L"Confirmation", MB_OKCANCEL);
         if(ret == IDOK)
         {
            return RunInverseFilter(bitmap, nullptr);
         }
         else
         {
            *outParams = new IF_FilterParams;
            (*outParams)->nParams = 1;
            (*outParams)->pParams = new IF_SingleParam[1];
            (*outParams)->pParams[0].nParamLength = 1;
            (*outParams)->pParams[0].pszParamValue = new wchar_t[2];
            lstrcpynW((*outParams)->pParams[0].pszParamValue, L"0", 1);
            (*outParams)->pParams[0].nParamID = 0;
         }
   }
   return IFE_FilterNotFound;
}
//Run the menu filter based off the params passed in, which are the same params that we passed out in 
// RunMenuFilter. Do not show any sort of UI.
int IF_API_Wrapper::RunMenuFilterAction(IF_Bitmap* bitmap, IF_Bitmap* mask, DWORD filterID, IF_FilterParams* params)
{
   switch(filterID)
   {
      case FID_INVERSE:
         return RunInverseFilter(bitmap, params);
   }
   return IFE_FilterNotFound;
}

//Parse Parameters then call filter
int IF_API_Wrapper::RunBlurFilter(IF_Bitmap* bitmap, IF_FilterParams* params)
{
   int radius = 1;
   
   for(int i=0; i< params->nParams; ++i)
   {
      if(params->pParams[i].nParamID==BLUR_RADIUS)
      {
         radius = _wtoi(params->pParams[i].pszParamValue);
      }
   }
   Filter_Blur::Run(bitmap, radius);
   return IFE_OK;
}

//Parse Parameters then call filter
int IF_API_Wrapper::RunDirectionalBlurFilter(IF_Bitmap* bitmap, IF_FilterParams* params)
{
   int radius = 1;
   double direction = 0.0f;
   for(int i=0; i< params->nParams; ++i)
   {
      if(params->pParams[i].nParamID==DIRBLUR_DIRECTION)
      {
         direction = _wtof(params->pParams[i].pszParamValue);
      }
      if(params->pParams[i].nParamID==DIRBLUR_RADIUS)
      {
         radius = _wtoi(params->pParams[i].pszParamValue);
      }
   }
   Filter_DirectionalBlur::Run(bitmap,direction, radius);
   return IFE_OK;
}

//Parse Parameters then call filter
int IF_API_Wrapper::RunInverseFilter(IF_Bitmap* bitmap, IF_FilterParams* params)
{
   if(params!=nullptr)
   {
      for(int i=0; i<params->nParams; ++i)
      {
         if(params->pParams[i].nParamID == 0)
         {
            return IFE_OK;
         }
      }
   }
   Filter_Inverse::Run(bitmap);
   return IFE_OK;
}

//Parse Parameters then call filter
int IF_API_Wrapper::RunPointDarkenFilter(IF_Bitmap* bitmap, IF_RenderInfo* pRI, IF_FilterParams* params)
{
   int strength = 1;
   int xPos = 0;
   int yPos = 0;
   bool linear = true;
   for(int i=0; i< params->nParams; ++i)
   {
      if(params->pParams[i].nParamID==POINTDARKEN_STRENGTH)
      {
         strength = _wtoi(params->pParams[i].pszParamValue);
      }
      if(params->pParams[i].nParamID==IF_TOOL_POSITIONSELECT_PARAM_X)
      {
         xPos = _wtoi(params->pParams[i].pszParamValue);
      }
      if(params->pParams[i].nParamID==IF_TOOL_POSITIONSELECT_PARAM_Y)
      {
         yPos = _wtoi(params->pParams[i].pszParamValue);
      }
      if(params->pParams[i].nParamID==POINTDARKEN_SCALETYPE_EXPONENTIAL)
      {
         bool checked = static_cast<bool>(_wtoi(params->pParams[i].pszParamValue));
         if(checked) linear = false;
      }
      if(params->pParams[i].nParamID==POINTDARKEN_SCALETYPE_LINEAR)
      {
         bool checked = static_cast<bool>(_wtoi(params->pParams[i].pszParamValue));
         if(checked) linear = true;      
      }

   }
   Filter_PointDarken::Run(bitmap, pRI, xPos/1000.0f,yPos/1000.0f, strength, linear);
   return IFE_OK;
}

//Parse Parameters then call filter
int IF_API_Wrapper::RunTintFilter(IF_Bitmap* bitmap, IF_FilterParams* params)
{
   int strength = 1;
   COLORREF col = 0;
   for(int i=0; i< params->nParams; ++i)
   {
      if(params->pParams[i].nParamID==TINT_STRENGTH)
      {
         strength = _wtoi(params->pParams[i].pszParamValue);
      }
      if(params->pParams[i].nParamID==IF_TOOL_COLORSELECT_PARAM_COLORREF)
      {
         col = _wtoi(params->pParams[i].pszParamValue);
      }

   }
   Filter_Tint::Run(bitmap, col, strength);
   return IFE_OK;
}
