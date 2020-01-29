//-------------------------------------------------------------------
// Tint.cpp
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
#include "BasicBitmap.h"

namespace Filter_Tint
{
   void Run(IF_Bitmap* bitmap, COLORREF color, int strength)
   {
      double range = strength/100.0f;
      BasicBitmap dst(bitmap, false);

      int r = GetRValue(color);
      int b = GetBValue(color);
      int g = GetGValue(color);

      double rScale = (1-0.5*range)+r*(range/255);
      double bScale = (1-0.5*range)+b*(range/255);
      double gScale = (1-0.5*range)+g*(range/255);


      //Tint
      for(int y=0; y<dst.Height(); ++y)
      {
         for(int x=0; x<dst.Width(); ++x)
         {
            RGBQUAD* pixel = dst.GetPixel(x, y);

            pixel->rgbBlue = min(pixel->rgbBlue * bScale, 255);
            pixel->rgbGreen = min(pixel->rgbGreen * gScale, 255);
            pixel->rgbRed = min(pixel->rgbRed * rScale, 255);
            dst.SetPixel(x, y, pixel);
         }
      }
   }
}
