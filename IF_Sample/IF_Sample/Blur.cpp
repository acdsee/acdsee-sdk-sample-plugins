//-------------------------------------------------------------------
// Blur.cpp
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
#include "Blur.h"
#include "BasicBitmap.h"

namespace Filter_Blur
{
   void Run(IF_Bitmap* bitmap, int radius)
   {
      BasicBitmap dst(bitmap, false);
      BasicBitmap src(bitmap, true);

      //Basic Blur Filter
      for(int y=0; y<src.Height(); ++y)
      {
         for(int x=0; x<src.Width(); ++x)
         {
            int rVal = 0;
            int gVal = 0;
            int bVal = 0;
            int count = 0;

            for(int i=-radius; i<=radius; ++i)
            {
               for(int j=-radius; j<=radius; ++j)
               {
                  if(!src.InBounds(x+i, y+j)) continue;

                  RGBQUAD* pixel = src.GetPixel(x+i, y+j);
                  rVal+= pixel->rgbRed;
                  gVal+= pixel->rgbGreen;
                  bVal+= pixel->rgbBlue;
                  count++;
               }
            }
            rVal/=count;
            gVal/=count;
            bVal/=count;

            RGBQUAD* pixel = src.GetPixel(x, y);

            RGBQUAD temp;
            temp.rgbBlue = (BYTE)bVal;
            temp.rgbGreen = (BYTE) gVal;
            temp.rgbRed = (BYTE) rVal;
            temp.rgbReserved = pixel->rgbReserved;

            dst.SetPixel(x, y, &temp);
         }

      }

   }
}