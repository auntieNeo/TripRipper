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

#ifndef MATCHING_ALGORITHM_H_
#define MATCHING_ALGORITHM_H_

#include "common.h"

namespace TripRipper
{
  class TripcodeContainer;

  /**
   * MatchingAlgorithm is an abstract class that allows for different algorithms
   * to be used when determining which tripcodes pass certain criteria. Because
   * millions of tripcodes are matched per second, it is fairly important for
   * this algorithm to be efficient, although larger performance gains are
   * likely to be had by improving the tripcode computation algorithm (see
   * the TripcodeAlgorithm class).
   *
   * Typical implementations of the MatchingAlgorithm class are simple string
   * matching algorithms and regular expression algorithms.
   */
  class MatchingAlgorithm
  {
    public:
      MatchingAlgorithm();
      virtual ~MatchingAlgorithm();

      virtual size_t inputAlignment() const = 0;
      virtual size_t inputStride() const = 0;

      /**
       * The virtual method setMatchString sets the string criteria to be used
       * by the implementing algorithm when matching tripcodes. The exact
       * format of matchString is up to the implementing algorithm.
       */
      virtual void setMatchString(const std::string &matchString) = 0;

      /**
       * The virtual matchTripcodes method must be implemented by derived
       * classes to find tripcode matches. Implementations must look through all
       * of the tripcodes contained in the tripcodes container and add any
       * matches to the provided matches container.
       */
      virtual void matchTripcodes(const TripcodeContainer *tripcodes, TripcodeContainer *matches) = 0;
  };
}

#endif
