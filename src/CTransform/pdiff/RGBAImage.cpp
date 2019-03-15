
#include "stdafx.hpp"

#include "CTransform/pdiff/RGBAImage.hpp"

bool RGBAImage::WritePPM()
{
  if (Width <= 0) return false;
  if (Height <= 0 ) return false;
  FILE *out;
  fopen_s(&out, Name.c_str(), "wb");
  if (!out) return false;
  fprintf(out, "P6\n%d %d 255\n", Width, Height);
  for (int y = 0; y < Height; y++) {
    for (int x = 0; x < Width; x++) {
      int i = x + y * Width;
      unsigned char r = Get_Red(i);
      unsigned char g = Get_Green(i);
      unsigned char b = Get_Blue(i);
      fwrite(&r, 1, 1, out);
      fwrite(&g, 1, 1, out);
      fwrite(&b, 1, 1, out);
    }
  }
  fclose(out);
  return true;
}
