#ifndef _RGBAIMAGE_H
#define _RGBAIMAGE_H

#include <string>
#include "memory_log.hpp"

// assumes data is in the ABGR format
class RGBAImage
{
public:
  RGBAImage(int w, int h, const char *name = 0)
  {
    Width = w;
    Height = h;
    if (name) Name = name;
    log_malloc(30);
    Data = new unsigned int[w * h];
  };
  ~RGBAImage()
  {
    if (Data) {
      log_delete(30);
      delete[] Data;
    }
  }
  unsigned char Get_Red(unsigned int i) { return (Data[i] & 0xFF); }
  unsigned char Get_Green(unsigned int i) { return ((Data[i]>>8) & 0xFF); }
  unsigned char Get_Blue(unsigned int i) { return ((Data[i]>>16) & 0xFF); }
  unsigned char Get_Alpha(unsigned int i) { return ((Data[i]>>24) & 0xFF); }
  void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned int i)
  { Data[i] = r | (g << 8) | (b << 16) | (a << 24); }
  int Get_Width(void) const { return Width; }
  int Get_Height(void) const { return Height; }
  void Set(int x, int y, unsigned int d) { Data[x + y * Width] = d; }
  unsigned int Get(int x, int y) const { return Data[x + y * Width]; }
  unsigned int Get(int i) const { return Data[i]; }
  const std::string &Get_Name(void) const { return Name; }
  
  bool WritePPM();
#ifdef NOT_OPENHOLDEM
  static RGBAImage* ReadTiff(char *filename);
  static RGBAImage* ReadPNG(char *filename);
#endif
protected:
  int Width;
  int Height;
  std::string Name;
  unsigned int *Data;
};

#endif
