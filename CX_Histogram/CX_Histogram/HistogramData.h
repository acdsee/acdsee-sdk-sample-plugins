//-------------------------------------------------------------------
// HistogramData.h
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

class HistogramData
{
public:
   HistogramData(int nBuckets);
   ~HistogramData();

   std::vector<double> m_redVals;
   std::vector<double> m_greenVals;
   std::vector<double> m_blueVals;

   void AddDataPoint(uint8_t red, uint8_t green, uint8_t blue);
   double calcMax();

   int m_nBuckets;
   double maxVal;
   long m_nNumDataPoints;
};