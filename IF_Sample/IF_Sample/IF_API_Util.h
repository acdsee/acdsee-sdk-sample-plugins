//-------------------------------------------------------------------
// IF_API_Util.h
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

#include "../../API/IF_PlugIn.h"

//This is a collection of useful functions for setting up the struct's that define your plugin.
namespace IF_Util
{
   void SetupSlider(
      IF_SliderInfo* slider,
      int id,
      const wchar_t* displayText = L"", 
      float fMin = 0.0f, float fMax = 100.0f,
      float fStart = 0.0f, float fStep = 1.0f, 
      BOOL bHasSpinButtons = true,
      BOOL bHasEditBox = true,
      BOOL bHasBorder = true);

   void SetupColorPicker(
      IF_ColorPickerInfo* colorPicker,
      int id, 
      const wchar_t* displayText = L"",
      const wchar_t* buttonText = L"", 
      COLORREF defaultColor = RGB(0,0,0),
      BOOL bHasToggleButton = true,
      BOOL bToggleButtonDefault = true);

   void SetupAnglePicker(
      IF_AnglePickerInfo* anglePicker, 
      int id, 
      const wchar_t* pszTitle = L"", 
      float defaultPos = 0.0f);

   void SetupButtonGroup(
      IF_ButtonGroupInfo* buttonGroup, 
      int id, 
      int nButtons,
      const wchar_t* displayText = L"",
      bool bIsRadio=false);

   void SetupButton(
      IF_ButtonInfo* button,
      int id,
      const wchar_t* displayText = L"",
      bool bDefaultState = true);

   void DeleteButtonGroupContents(IF_ButtonGroupInfo* buttonGroup);

   void AllocateArrays(IF_UISpecification* pUISpec, int nSliders, int nColorPickers, int nAnglePickers, int nButtonGroups);

   void SetupFilterInfo(IF_FilterInfo* pFilterInfo, DWORD dwFlags, DWORD dwID, bool bIsNativeGUI, const wchar_t* pszName, const wchar_t* pszNameShort);

}