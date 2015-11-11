/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define untitled_P                    untitled_P DataSection(".NIVS.defaultparams")
#endif

/*
 * untitled_data.c
 *
 * Code generation for model "untitled".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Mar 17 15:44:28 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "untitled.h"
#include "untitled_private.h"

/* Block parameters (auto storage) */
P_untitled_T untitled_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/NIVeriStand In1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/NIVeriStand In1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/NIVeriStand In1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/NIVeriStand In1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/NIVeriStand In1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/NIVeriStand In1'
                                        */
  2.0                                  /* Expression: 2
                                        * Referenced by: '<Root>/Gain'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_untitled_T_sizes[] DataSection(".NIVS.defaultparamsizes") =
  {
  { sizeof(P_untitled_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },
};

#endif
