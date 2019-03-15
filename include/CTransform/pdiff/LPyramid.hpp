#ifndef _LPYRAMID_H
#define _LPYRAMID_H

#define MAX_PYR_LEVELS 8

class LPyramid
{
public:
  LPyramid(float *image, int width, int height);
  virtual ~LPyramid();
  float Get_Value(int x, int y, int level);
protected:
  float *Copy(float *img);
  void Convolve(float *a, float *b);
  
  // Succesively blurred versions of the original image
  float *Levels[MAX_PYR_LEVELS];

  int Width;
  int Height;
};

#endif // _LPYRAMID_H
