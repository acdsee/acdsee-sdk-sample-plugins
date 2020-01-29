//-------------------------------------------------------------------
// HistogramImpl.h
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
#include "HistogramData.h"

class HistogramImpl
{
public:
   HistogramImpl();
   ~HistogramImpl();

   //Return a CXE code
   int ShowHistogram(HGLOBAL hPackedDib, HWND parentWnd);

protected:
   int ReadBitmapBits(HGLOBAL hPackedDib, HistogramData& data);
};