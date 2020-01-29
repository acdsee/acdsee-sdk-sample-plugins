//-------------------------------------------------------------------
// DirectionalBlur.cpp
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

namespace Filter_DirectionalBlur
{
   double CalcDistancePointLineSeg(double x, double y, double x1, double y1, double x2, double y2);

   void Run(IF_Bitmap* bitmap, double degree, int radius)
   {
      //Flip degree 180
      //Calc angle
      double angle = fmod(degree, 90);
      double sinA = sin(angle)*radius*2;
      double cosA = cos(angle)*radius*2;

      //based on quadrant calculate delta x/y
      double dx = 0;
      double dy = 0;
      if(degree >= 0 && degree < 90)
      {
         dx = cosA;
         dy = sinA;
      }
      else if(degree >= 90 && degree < 180)
      {
         dx = -sinA;
         dy = cosA;
      }
      else if(degree >= 180 && degree < 270)
      {
         dx = -cosA;
         dy = -sinA;
      }
      else if(degree >= 270 && degree < 360)
      {
         dx = sinA;
         dy = -cosA;
      }

      //create lookup table for weighting points in radius based on distance from line segment of the point.
      //Scales from 1 to 0.1
      double** weights = new double*[radius*2+1];
      for(int i=0; i<radius*2+1; ++i)
      {
         weights[i] = new double[radius*2+1];
      }

      double maxDist = sqrt(radius*radius + radius*radius);
      for(int i=-radius; i<=radius; ++i)
      {
         for(int j = -radius; j<=radius; ++j)
         {
            int ii = i+radius; //0 indexing 
            int jj = j+radius; //0 indexing 
            double dist = CalcDistancePointLineSeg(i, j, -dx, -dy, dx, dy);
            if(dist < 1)
            {
               weights[ii][jj] = 1;
            }
            else
            {
               weights[ii][jj] = 0.1;
            }
         }
      }

      //For each pixel, run the blur.
      BasicBitmap dst(bitmap, false);
      BasicBitmap src(bitmap, true);

      //Directional Blur Filter
      for(int y=0; y<src.Height(); ++y)
      {
         for(int x=0; x<src.Width(); ++x)
         {
            double rVal = 0;
            double gVal = 0;
            double bVal = 0;
            double count = 0;

            for(int i=-radius; i<=radius; ++i)
            {
               for(int j=-radius; j<=radius; ++j)
               {
                  if(!src.InBounds(x+i, y+j)) continue;

                  int ii = i+radius; //0 indexing 
                  int jj = j+radius; //0 indexing 
                  RGBQUAD* pixel = src.GetPixel(x+i, y+j);
                  rVal+= pixel->rgbRed * weights[ii][jj];
                  gVal+= pixel->rgbGreen * weights[ii][jj];
                  bVal+= pixel->rgbBlue * weights[ii][jj];
                  count+= weights[ii][jj];
               }
            }
            rVal/=count;
            gVal/=count;
            bVal/=count;

            RGBQUAD* pixel = src.GetPixel(x, y);

            RGBQUAD temp;
            temp.rgbBlue = (BYTE) std::round(bVal);
            temp.rgbGreen = (BYTE) std::round(gVal);
            temp.rgbRed = (BYTE) std::round(rVal);
            temp.rgbReserved = pixel->rgbReserved;

            dst.SetPixel(x,y,&temp);
         }
      }


      //cleanup weights
      for(int i=0; i<radius*2+1; ++i)
      {
         delete weights[i];
      }
      delete weights;
   }

   double CalcDistancePointLineSeg(double x, double y, double x1, double y1, double x2, double y2)
   {
      double A = x - x1;
      double B = y - y1;
      double C = x2 - x1;
      double D = y2 - y1;

      double dot = A*C + B*D;
      double len_sq = C*C + D*D;

      double param = -1;
      double xx, yy;

      if (len_sq != 0) //in case of 0 length line
         param = dot / len_sq;

      if(param<0)
      {
         xx = x1;
         yy = y1;
      }
      else if(param > 1)
      {
         xx = x2;
         yy = y2;
      }
      else 
      {
         xx = x1 + param * C;
         yy = y1 + param * D;
      }
      double  dx = x - xx;
      double dy = y - yy;
      return sqrt(dx * dx + dy * dy);
   }
}


