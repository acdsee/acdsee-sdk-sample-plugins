//-------------------------------------------------------------------
// HistogramData.cpp
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
#include "HistogramData.h"

HistogramData::HistogramData(int nBuckets)
   : m_nBuckets(nBuckets), m_blueVals(nBuckets), m_greenVals(nBuckets), m_redVals(nBuckets), maxVal(-1), m_nNumDataPoints(0)
{

}

HistogramData::~HistogramData()
{

}

void HistogramData::AddDataPoint(uint8_t red, uint8_t green, uint8_t blue)
{
   m_redVals[red] += 1;
   m_blueVals[blue] += 1;
   m_greenVals[green] += 1;
   m_nNumDataPoints++;
}

double HistogramData::calcMax()
{
   if(maxVal!=-1) return maxVal;

   for(double val : m_blueVals)
   {
      maxVal = max(maxVal, val);
   }

   for(double val : m_redVals)
   {
      maxVal = max(maxVal, val);
   }

   for(double val : m_greenVals)
   {
      maxVal = max(maxVal, val);
   }

   return maxVal;
}