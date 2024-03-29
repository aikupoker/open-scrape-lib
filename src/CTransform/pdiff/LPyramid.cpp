#include "stdafx.hpp"
#include "CTransform/pdiff/LPyramid.hpp"

LPyramid::LPyramid(float *image, int width, int height):
  Width(width),
  Height(height)
{
  // Make the Laplacian pyramid by successively
  // copying the earlier levels and blurring them
  for (int i=0; i<MAX_PYR_LEVELS; i++) {
    if (i == 0) {
      Levels[i] = Copy(image);
    } else {
      log_malloc(4);
      Levels[i] = new float[Width * Height];
      Convolve(Levels[i], Levels[i - 1]);
    }
  }
}

LPyramid::~LPyramid()
{
  for (int i=0; i<MAX_PYR_LEVELS; i++) {
    if (Levels[i]) {
      log_delete(4);
      delete Levels[i];
    }
  }
}

float *LPyramid::Copy(float *img)
{
  int max = Width * Height;
  log_malloc(4);
  float *out = new float[max];
  for (int i = 0; i < max; i++) out[i] = img[i];
  
  return out;
}

void LPyramid::Convolve(float *a, float *b)
// convolves image b with the filter kernel and stores it in a
{
  int y,x,i,j,nx,ny;
  const float Kernel[] = {0.05f, 0.25f, 0.4f, 0.25f, 0.05f};

  for (y=0; y<Height; y++) {
    for (x=0; x<Width; x++) {
      int index = y * Width + x;
      a[index] = 0.0f;
      for (i=-2; i<=2; i++) {
        for (j=-2; j<=2; j++) {
          nx=x+i;
          ny=y+j;
          if (nx<0) nx=-nx;
          if (ny<0) ny=-ny;
          if (nx>=Width) nx=2*Width-nx-1;
          if (ny>=Height) ny=2*Height-ny-1;
          a[index] += Kernel[i+2] * Kernel[j+2] * b[ny * Width + nx];
        }
      }
    }
  }
}

float LPyramid::Get_Value(int x, int y, int level)
{
  int index = x + y * Width;
  int l = level;
  if (l > MAX_PYR_LEVELS) l = MAX_PYR_LEVELS;
  return Levels[level][index];
}
