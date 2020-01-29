//-------------------------------------------------------------------
// IF_API_Util.cpp
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
#include "IF_API_Util.h"
#include "../../API/IF_PlugIn.h"

namespace IF_Util
{
   void SetupSlider(
      IF_SliderInfo* slider,
      int id, 
      const wchar_t* displayText,
      float fMin,
      float fMax, 
      float fStart,
      float fStep,
      BOOL bHasSpinButtons, 
      BOOL bHasEditBox,
      BOOL bHasBorder)
   {
      lstrcpyn(slider->szTitle, displayText, _countof(slider->szTitle));
      slider->nSliderID = id;      
      slider->fMin = fMin;           
      slider->fMax = fMax;           
      slider->fStartVal = fStart;   
      slider->fStep = fStep;
      slider->bHasEditBox = bHasEditBox;    
      slider->bHasBorder = bHasBorder;     
   }

   void SetupAnglePicker(IF_AnglePickerInfo* anglePicker, int id, const wchar_t* pszTitle, float defaultPos)
   {
      anglePicker->nAnglePickerID = id;
      anglePicker->fDefaultPos = defaultPos;
      lstrcpyn(anglePicker->szTitle, pszTitle, _countof(anglePicker->szTitle));
   }

   void SetupColorPicker(
      IF_ColorPickerInfo* colorPicker,
      int id, 
      const wchar_t* displayText,
      const wchar_t* buttonText, 
      COLORREF defaultColor,
      BOOL bHasToggleButton, 
      BOOL bToggleButtonDefault)
   {
      colorPicker->nColorPickerID = id;
      lstrcpyn(colorPicker->szTitle, displayText, _countof(colorPicker->szTitle));
      lstrcpyn(colorPicker->szToggleButtonText, buttonText, _countof(colorPicker->szToggleButtonText));
      colorPicker->defaultColor = defaultColor;
      colorPicker->bHasToggleButton = bHasToggleButton;
      colorPicker->bToggleButtonDefaultState = bToggleButtonDefault;
   }

   void SetupButtonGroup(IF_ButtonGroupInfo* buttonGroup, int id, int nButtons, const wchar_t* displayText,  bool bIsRadio)
   {
      buttonGroup->nButtonGroupID = id;
      buttonGroup->nButtons = nButtons;
      buttonGroup->pButtonInfo = new IF_ButtonInfo[nButtons];
      lstrcpyn(buttonGroup->szTitle, displayText, _countof(buttonGroup->szTitle));
      buttonGroup->bIsRadio = bIsRadio;
   }

   void SetupButton(IF_ButtonInfo* button, int id, const wchar_t* displayText, bool bDefaultState)
   {
      button->nButtonID = id;
      lstrcpyn(button->szText, displayText, _countof(button->szText));
      button->bDefaultState = bDefaultState;
   }

   void DeleteButtonGroupContents(IF_ButtonGroupInfo* buttonGroup)
   {
      if(buttonGroup->pButtonInfo!=NULL)
      {
         delete[] buttonGroup->pButtonInfo;
      }
   }

   void AllocateArrays(IF_UISpecification* pUISpec, int nSliders, int nColorPickers, int nAnglePickers, int nButtonGroups)
   {
      pUISpec->nSliders = nSliders;
      pUISpec->pSliderInfo = new IF_SliderInfo[nSliders];

      pUISpec->nColorPickers = nColorPickers;
      pUISpec->pColorPickerInfo = new IF_ColorPickerInfo[nColorPickers];

      pUISpec->nAnglePickers = nAnglePickers;
      pUISpec->pAnglePickerInfo = new IF_AnglePickerInfo[nAnglePickers];

      pUISpec->nButtonGroups = nButtonGroups;
      pUISpec->pButtonGroupInfo = new IF_ButtonGroupInfo[nButtonGroups];
   }

   void SetupFilterInfo(IF_FilterInfo* pFilterInfo, DWORD dwFlags, DWORD dwID, bool bIsNativeGUI, const wchar_t* pszName, const wchar_t* pszNameShort)
   {
      pFilterInfo->dwFlags = dwFlags;
      pFilterInfo->dwID = dwID;
      pFilterInfo->bIsNativeGUIFilter = bIsNativeGUI; 
      lstrcpyn(pFilterInfo->szName, pszName, _countof(pFilterInfo->szName));
      lstrcpyn(pFilterInfo->szNameShort, pszNameShort, _countof(pFilterInfo->szNameShort));
   }
}