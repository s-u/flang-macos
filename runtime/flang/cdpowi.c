/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "mthdecls.h"

void
__mth_i_cdpowi(dcmplx_t *dcmplx, double real, double imag, int i)
{
  int k;
  double fr, fi, gr, gi, tr, ti;

  fr = 1;
  fi = 0;
  k = i;
  gr = real;
  gi = imag;
  if (k < 0)
    k = -k;
  while (k) {
    if (k & 1) {
      tr = fr * gr - fi * gi;
      ti = fr * gi + fi * gr;
      fr = tr;
      fi = ti;
    }
    k = (unsigned)k >> 1;
    tr = gr * gr - gi * gi;
    ti = 2.0 * gr * gi;
    gr = tr;
    gi = ti;
  }
  if (i < 0)
    __mth_i_cddiv(dcmplx, 1.0, 0.0, fr, fi);
  else {
    d_dummy(fr, fi);
  }
}
