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

#ifndef TRIPCODE_CONTAINER_H_
#define TRIPCODE_CONTAINER_H_

#include "common.h"

namespace TripRipper
{
  /**
   * TripcodeContainer stores tripcodes along with their corresponding
   * passwords.
   *
   * TripcodeContainer objects are serializable for transmission from
   * TripcodeCrawler workers to the root process.
   *
   * TripcodeContainer objects can be merged together to form a single
   * container of results with merge().
   *
   * TripcodeContainer provides a verify() method for verifying the tripcodes
   * with a known-working tripcode algorithm.
   */
  class TripcodeContainer
  {
    public:
      TripcodeContainer();
      ~TripcodeContainer();

      void serialize(unsigned char *buffer, size_t size, bool &done);
      void deserialize(const unsigned char *buffer, size_t size, bool &done);

      void merge(const TripcodeContainer *source);

      bool verify();

      void insert(const std::pair<std::string, std::string> &tripcode);

    private:
      std::vector<std::pair<std::string, std::string> > m_tripcodes;
  };

  class TripcodeBlock
  {
  };
}

#endif
