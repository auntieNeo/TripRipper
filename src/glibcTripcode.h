/*******************************************************************************
 * Copyright 2012 Jonathan Glines <auntieNeo@gmail.com>                        *
 *                                                                             *
 * Permission is hereby granted, free of charge, to any person obtaining a     *
 * copy of this software and associated documentation files (the "Software"),  *
 * to deal in the Software without restriction, including without limitation   *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
 * and/or sell copies of the Software, and to permit persons to whom the       *
 * Software is furnished to do so, subject to the following conditions:        *
 *                                                                             *
 * The above copyright notice and this permission notice shall be included in  *
 * all copies or substantial portions of the Software.                         *
 *                                                                             *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
 * DEALINGS IN THE SOFTWARE.                                                   *
 ******************************************************************************/

#ifndef GLIBC_TRIPCODE_H_
#define GLIBC_TRIPCODE_H_

#include "common.h"
#include <crypt.h>

namespace TripRipper
{
  /**
   * The GlibcTripcode class implements the tripcode algorithm using the UNIX
   * crypt(3) from glibc. Since crypt(3) isn't optimized for processing large
   * datasets, this class is only intended to be used for demonstration
   * purposes.
   */
  class GlibcTripcode : public TripcodeAlgorithm
  {
    public:
      GlibcTripcode();
      virtual ~GlibcTripcode();

      size_t inputAlignment() const { return 1; }
      size_t inputStride() const { return 0; }
      bool inputPackHighBit() const { return false; }

      void computeTripcodes(const KeyBlock *keys, TripcodeContainer *results);

    private:
      crypt_data *m_data;
  };
}

#endif
