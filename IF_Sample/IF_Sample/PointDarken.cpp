//-------------------------------------------------------------------
// PointDarken.cpp
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

namespace Filter_PointDarken
{
   void DarkenPixel(RGBQUAD* pixel, double amount); //Amount from 0 to 1.0
   void Run(IF_Bitmap* bitmap, IF_RenderInfo* pRI, double px, double py, int strength, bool linear)
   {
      BasicBitmap dst(bitmap, false);

      if(pRI->fIsROI)
      {
         py = 1.0-py;
      }
      
      double scaleFactor = strength/100.0f;
      int width;
      int height; 
      if(pRI->fIsROI)
      {
         width = pRI->szFullScaledImage.cx;
         height = pRI->szFullScaledImage.cy;
      }
      else
      {
         width = dst.Width();
         height = dst.Height();
      }
      int xPos = static_cast<int>(px*width);
      int yPos = static_cast<int>(py*height);

      double maxDist = sqrt(width*width+height*height);

      //Point Darken
      for(int y=0; y<dst.Height(); ++y)
      {
         for(int x=0; x<dst.Width(); ++x)
         {
            double dx;
            double dy;
            if(pRI->fIsROI)
            {
               dx = x+pRI->rcROI.left - xPos;
               dy = dst.Height()-y+pRI->rcROI.top - yPos;
            }
            else
            {
               dx = x-xPos;
               dy = y-yPos;
            }
            double dist = sqrt(dx*dx+dy*dy);

            double darkenAmount;
            if(linear)
            {
               darkenAmount = ((maxDist-dist)/maxDist)*scaleFactor;
            }
            else
            {
               darkenAmount = min((((maxDist-dist)/(maxDist+dist))*scaleFactor*1.25), 1.0f);
            }

            RGBQUAD* pixel = dst.GetPixel(x, y);
            DarkenPixel(pixel, darkenAmount);
            dst.SetPixel(x, y, pixel);
         }
      }
   }

   void DarkenPixel(RGBQUAD* pixel, double amount)
   {
      pixel->rgbBlue = static_cast<BYTE>(pixel->rgbBlue - (pixel->rgbBlue)*amount);
      pixel->rgbRed = static_cast<BYTE>(pixel->rgbRed - (pixel->rgbRed)*amount);
      pixel->rgbGreen = static_cast<BYTE>(pixel->rgbGreen - (pixel->rgbGreen)*amount);
   }
}