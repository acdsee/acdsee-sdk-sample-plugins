//-------------------------------------------------------------------
// CX_ApiWrapper.h
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
#include "../../API/CX_PlugIn.h"

class CX_APIWrapper
{

public:
   CX_APIWrapper(CX_ClientInfo*  pci);
   ~CX_APIWrapper();

   CX_PlugInInfo m_PlugInInfo;  // This structure is used in CX_GetPlugInInfo

   int DoCX(
      CX_CommandParams*  pcp,   // (in ) Specifies command to invoke, and parameters
      CX_CommandResults* pcr);  // (out) Command results)

private:
   CX_CommandInfo m_CommandInfo[1];	// This is also used in CX_GetPlugInInfo
   HINSTANCE      m_hResInst;       // DLL instance
};