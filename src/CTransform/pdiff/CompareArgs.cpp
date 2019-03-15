#include "stdafx.hpp"
#include "CTransform/pdiff/CompareArgs.hpp"
#include "CTransform/pdiff/RGBAImage.hpp"
#include <stdio.h>

static const char* copyright = 
"PerceptualDiff version 1.0, Copyright (C) 2006 Yangli Hector Yee\n\
PerceptualDiff comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome\n\
to redistribute it under certain conditions;\n\
See the GPL page for details: http://www.gnu.org/copyleft/gpl.html\n\n";

static const char *usage =
"PeceptualDiff image1.tif image2.tif\n\n\
   Compares image1.tif and image2.tif using a perceptually based image metric\n\
   Options:\n\
\t-verbose       : Turns on verbose mode\n\
\t-fov deg       : Field of view in degrees (0.1 to 89.9)\n\
\t-threshold p	 : #pixels p below which differences are ignored\n\
\t-gamma g       : Value to convert rgb into linear space (default 2.2)\n\
\t-luminance l   : White luminance (default 100.0 cdm^-2)\n\
\t-output o.ppm  : Write difference to the file o.ppm\n\
\n\
\n Note: Input files can also be in the PNG format\
\n";

CompareArgs::CompareArgs()
{
  ImgA = NULL;
  ImgB = NULL;
  Verbose = false;
  FieldOfView = 45.0f;
  Gamma = 2.2f;
  ThresholdPixels = 100;
  Luminance = 100.0f;
  PixelsFailed = 0;
}

CompareArgs::~CompareArgs()
{
  if (ImgA) {
    log_delete(20);
    delete ImgA;
  }
  if (ImgB) {
    log_delete(7);
    delete ImgB;
  }
}
