#ifndef _COMPAREARGS_H
#define _COMPAREARGS_H

#include "CTransform/pdiff/RGBAImage.hpp"

// Args to pass into the comparison function
class CompareArgs
{
public:
	CompareArgs();
	~CompareArgs();
#ifdef NOT_OPENHOLDEM
	bool Parse_Args(int argc, char **argv);
	void Print_Args();
#endif
	
	RGBAImage		*ImgA;		 // Image A
	RGBAImage		*ImgB;		 // Image B
	bool			Verbose;		 // Print lots of text or not
	float			FieldOfView; // Field of view in degrees
	float			Gamma;			 // The gamma to convert to linear color space
	float			Luminance;	 // the display's luminance
	unsigned int	ThresholdPixels; // How many pixels different to ignore
	unsigned int	PixelsFailed;		 // Number of pixels that are perceptually different
};

#endif