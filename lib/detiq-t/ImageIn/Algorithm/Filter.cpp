/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Filter.h"
#include <cmath>

using namespace std;
using namespace imagein;
using namespace algorithm;

Filter::Filter (unsigned int w, unsigned int h) : GrayscaleImage_t<double>(w, h)
{
//  _mtrx = new int[h * w];
}

Filter::Filter (const Filter& m) : GrayscaleImage_t<double>(m)
{
//  _mtrx = new int [_width * _height];

//  for(int i = 0; i < _width * _height; i++)
//    _mtrx[i] = m._mtrx[i];
}

Filter::~Filter ()
{
//  delete[] _mtrx
}

//Filter::Line Filter::operator[] (int i)
//{
//  return Line (i, *this);
//}

//Filter::Line::Line (int i, Filter& m) : _width (m._width)
//{
//  _rry = m._mtrx + i * m._height;
//}

//int& Filter::Line::operator[] (int i)
//{
//  return *(_rry + i);
//}

//Filter::iterator Filter::begin ()
//{
//  return iterator (*this);
//}

//Filter::iterator Filter::end ()
//{
//  Filter::iterator it (*this);
//  it._j = -1;
//  it._i = -1;

//  return it;
//}

//Filter::iterator::iterator (Filter& m) : _Filter (m), _i (0), _j (0)
//{
//}

//Filter::iterator Filter::iterator::operator++ ()
//{
//  Filter::iterator res (*this);

//  _i++;

//  if (_i == _Filter.width())
//  {
//    _i = 0;
//    _j++;
//  }

//  if (_j == _Filter.height())
//  {
//    _i = -1;
//    _j = -1;
//  }
  
//  return res;
//}

//int& Filter::iterator::operator* ()
//{
//  return _Filter[_i][_j];
//}

//bool Filter::iterator::operator!= (iterator it)
//{
//  return _i != it._i || _j != it._j;
//}

//std::pair<int, int> Filter::iterator::pos ()
//{
//  return make_pair (_i, _j);
//}

std::vector<Filter*> Filter::uniform(int numPixels = 3)
{
  Filter* filter = new Filter(numPixels, numPixels);
  for(int i = 0; i < numPixels; i++)
  {
    for(int j = 0; j < numPixels; j++)
    {
//      filter->setPixelAt(i, j, 1;
        filter->setPixelAt(i, j, 1.);
    }
  }
  std::vector<Filter*> filters;
  filters.push_back(filter);
  return filters;
}

const double pi = 3.1415926535897932384626433832795;
const double pid2 = 1.57079632679489661923132169163975144209858469968755291;
const double sqrt2 = 1.414213562373095048801688724209698078569671875376948;

inline double gauss(int x, int y, double sigma) {
    const double sigma2 = sigma * sigma;
    return std::exp( - (x*x + y*y) / (2. * sigma2) ) / (2. * pi * sigma2);
}

std::vector<Filter*> Filter::gaussian(unsigned int size, double sigma) {
    Filter* filter = new Filter(size, size);

    const int offsetX = (filter->getWidth() - 1) / 2;
    const int offsetY = (filter->getHeight() - 1) / 2;
    const double coef = 1. / gauss(offsetX, offsetY, sigma);
    for(unsigned int j = 0; j < filter->getHeight(); ++j) {
        for(unsigned int i = 0; i < filter->getWidth(); ++i) {
            const int x = i - offsetX;
            const int y = j - offsetY;
            const double value = std::floor( (coef * gauss(x, y, sigma)) + 0.5);
            filter->setPixelAt(i, j, value);
        }
    }

    std::vector<Filter*> filters;
    filters.push_back(filter);
    return filters;
}

std::vector<Filter*> Filter::gaussian(double alpha)
{
  std::vector<double> gaussCoef;
  double min(0);

  for (int i = 0; ; i++)
  {
  double coef = 10000.0 * std::exp(-(std::pow(i, 2.0)) / (2.0 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));
  if (i == 0) min = coef / 10 + 1;
  if (coef < min)
    break;
  else
    gaussCoef.push_back(coef);
  }

  Filter* f = new Filter(gaussCoef.size() * 2 - 1, gaussCoef.size() * 2 - 1);
  int center = gaussCoef.size() - 1;

  for(unsigned int i = 0; i < gaussCoef.size(); i++)
  {
    for(unsigned int j = i; j < gaussCoef.size(); j++)
    {
      if(i == 0) /* values are already in gaussCoef, so no compute needed */
      {
//        (*f)[center][center + j] = gaussCoef[j];
          f->setPixelAt(center, center + j, gaussCoef[i]);

        if(j != 0)
        {
//          (*f)[center][center - j] = gaussCoef[j];
//          (*f)[center - j][center] = gaussCoef[j];
//          (*f)[center + j][center] = gaussCoef[j];
          f->setPixelAt(center, center - j, gaussCoef[j]);
          f->setPixelAt(center - j, center, gaussCoef[j]);
          f->setPixelAt(center + j, center, gaussCoef[j]);
        }
      }
      else
      {
        double coef = 10000.0 * std::exp(-(std::pow(i, 2) + std::pow(j, 2)) / (2 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));

//        (*f)[center + i][center + j] = coef;
//        (*f)[center + i][center - j] = coef;
//        (*f)[center - i][center + j] = coef;
//        (*f)[center - i][center - j] = coef;
//        (*f)[center + j][center + i] = coef;
//        (*f)[center + j][center - i] = coef;
//        (*f)[center - j][center + i] = coef;
//        (*f)[center - j][center - i] = coef;
          f->setPixelAt(center + i, center + j, coef);
          f->setPixelAt(center + i, center - j, coef);
          f->setPixelAt(center - i, center + j, coef);
          f->setPixelAt(center - i, center - j, coef);
          f->setPixelAt(center + j, center + i, coef);
          f->setPixelAt(center + j, center - i, coef);
          f->setPixelAt(center - j, center + i, coef);
          f->setPixelAt(center - j, center - i, coef);
      }
    }
  }
  std::vector<Filter*> filters;
  filters.push_back(f);
  return filters;
}

std::vector<Filter*> Filter::prewitt(int numPixels = 3)
{
  std::vector<Filter*> filters;
  
  for(int vertical = 1 ; vertical >= 0 ; --vertical)
  {
    int width = 3, height = 3;
    
    if(vertical == 1) height = numPixels;
    else width = numPixels;
    
    Filter* filter = new Filter(width, height);
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
      {
        if((vertical == 1 && i == 0) || (vertical == 0 && j == 0)) {
//          filter->setPixelAt(i, j, -1;
            filter->setPixelAt(i, j, -1.);
        }
        else if((vertical == 1 && i == width - 1) || (vertical == 0 && j == height - 1)) {
//          filter->setPixelAt(i, j, 1;
            filter->setPixelAt(i, j, 1.);
        }
        else {
//          filter->setPixelAt(i, j, 0;
            filter->setPixelAt(i, j, 0.);
        }
      }
    }
    filters.push_back(filter);
  }
  return filters;
}

std::vector<Filter*> Filter::roberts()
{
  std::vector<Filter*> filters;
  
  for(int h = 1 ; h >= 0 ; --h)
  {				
    Filter* filter = new Filter(2, 2);
    for(int i = 0; i < 2; ++i)
    {
      for(int j = 0; j < 2; ++j)
      {
        if((h == 1 && i == 0 && j == 1) || (h == 0 && i == 0 && j == 0)) {
//          filter->setPixelAt(i, j, -1;
            filter->setPixelAt(i, j, -1.);
        }
        else if((h == 1 && i == 1 && j == 0) || (h == 0 && i == 1 && j == 1)) {
//          filter->setPixelAt(i, j, 1;
            filter->setPixelAt(i, j, 1.);
        }
        else {
//          filter->setPixelAt(i, j, 0;
            filter->setPixelAt(i, j, 0.);
        }
      }
    }
    filters.push_back(filter);
  }
  
  return filters;
}

std::vector<Filter*> Filter::sobel()
{
  std::vector<Filter*> filters;
  
  for(int vertical = 1 ; vertical >= 0 ; --vertical)
  {
    int width = 3, height = 3;
    
    Filter* filter = new Filter(width, height);
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
      {
        if(vertical == 1)
        {
          if(i == 0)
            if(j == 1) filter->setPixelAt(i, j, -2);
            else filter->setPixelAt(i, j, -1.);
          else if(i == 2)
            if(j == 1) filter->setPixelAt(i, j, 2);
            else filter->setPixelAt(i, j, 1.);
          else filter->setPixelAt(i, j, 0.);
        }
        else
        {
          if(j == 0)
            if(i == 1) filter->setPixelAt(i, j, -2);
            else filter->setPixelAt(i, j, -1.);
          else if(j == 2)
            if(i == 1) filter->setPixelAt(i, j, 2);
            else filter->setPixelAt(i, j, 1.);
          else filter->setPixelAt(i, j, 0.);
        }
      }
    }
    filters.push_back(filter);
  }
  return filters;
}

std::vector<Filter*> Filter::squareLaplacien()
{
  std::vector<Filter*> filters;
  
  int width = 3, height = 3;
  
  Filter* filter = new Filter(width, height);
  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      if((i == 0 && (j == 0 || j == 2)) || ((i == 2 && (j == 0 || j == 2))))
        filter->setPixelAt(i, j, 0.);
      else if(i == 1 && j == 1)
        filter->setPixelAt(i, j, -4.);
      else
        filter->setPixelAt(i, j, 1.);
    }
  }
  filters.push_back(filter);
  
  return filters;
}
