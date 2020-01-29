//-------------------------------------------------------------------
// Inverse.cpp
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

namespace Filter_Inverse
{
   void Run(IF_Bitmap* bitmap)
   {
      BasicBitmap dst(bitmap, false);

      //Basic Inverse Filter
      for(int y=0; y<dst.Height(); ++y)
      {
         for(int x=0; x<dst.Width(); ++x)
         {

            RGBQUAD* pixel = dst.GetPixel(x, y);

            pixel->rgbBlue = 256-pixel->rgbBlue;
            pixel->rgbGreen = 256-pixel->rgbGreen;
            pixel->rgbRed = 256-pixel->rgbRed;

            dst.SetPixel(x, y, pixel);
         }
      }
   }
}