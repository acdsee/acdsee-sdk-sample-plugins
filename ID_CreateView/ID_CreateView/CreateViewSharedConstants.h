//-------------------------------------------------------------------
// CreateViewSharedConstants.h
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
#include "../../API/IE_PlugIn.h"

/****************
 * ValidPixFmts *
 ****************/
namespace CreateViewConstants
{
   static DWORD ValidPixFmts[] =
   {
      PFF_24BPP_RGB
   };
   static const int nValidPixFmts = (sizeof(ValidPixFmts)/sizeof(DWORD));

   enum
   {
      IT_TXT = MAKE_FORMATID('T', 'X', 'T', '\0'),
   };
}
