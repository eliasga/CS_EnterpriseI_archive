/*
 * rt_look2d_normal.c
 *
 * Real-Time Workshop code generation for Simulink model "TemplateLgV2.mdl".
 *
 * Model Version              : 1.114
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 30 09:45:10 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 */

#include "rt_look2d_normal.h"

/* Function: rt_Lookup2D_Normal ==============================================
 * Abstract:
 *      2D normal lookup routine for data type of real_T
 */
real_T rt_Lookup2D_Normal (const real_T *xVals, const int_T numX,
  const real_T *yVals, const int_T numY,
  const real_T *zVals,
  const real_T x, const real_T y)
{
  int_T xIdx, yIdx;
  real_T ylo, yhi;
  real_T Zx0yhi, Zx0ylo, xlo, xhi;
  real_T corner1, corner2;
  xIdx = rt_GetLookupIndex(xVals,numX,x);
  xlo = xVals[xIdx];
  xhi = xVals[xIdx+1];
  yIdx = rt_GetLookupIndex(yVals,numY,y);
  ylo = yVals[yIdx];
  yhi = yVals[yIdx+1];
  corner1 = *(zVals + xIdx + (numX * yIdx));
  corner2 = *(zVals + (xIdx+1) + (numX * yIdx));
  Zx0ylo = INTERP(x, xlo, xhi, corner1, corner2);
  corner1 = *(zVals + xIdx + (numX * (yIdx+1)));
  corner2 = *(zVals + (xIdx+1) + (numX*(yIdx+1)));
  Zx0yhi = INTERP(x, xlo, xhi, corner1, corner2);
  return (INTERP(y,ylo,yhi,Zx0ylo,Zx0yhi));
}
