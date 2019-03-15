#ifndef _METRIC_H
#define _METRIC_H

class CompareArgs;

// Image comparison metric using Yee's method
// References: A Perceptual Metric for Production Testing, Hector Yee, Journal of Graphics Tools 2004
bool Yee_Compare(CompareArgs &args);

#endif
