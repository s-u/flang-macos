/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

#include "mthdecls.h"

#ifndef WIN64
float
__mth_i_amod(float f, float g)
{
#if defined(WIN64)
  return __fmth_i_amod(f, g);
#else
  return fmodf(f, g);
#endif
}
#endif
