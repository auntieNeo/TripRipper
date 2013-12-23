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

#ifndef LINEAR_KEYSPACE_H_
#define LINEAR_KEYSPACE_H_

#include "keyspace.h"

namespace TripRipper
{
  /**
   * The LinearKeyspace class describes a mapping onto the tripcode keyspace in
   * which each key is mapped in sequential order, one after the other.
   *
   * This is the simplest mapping possible. The primary disadvantage of this
   * mapping is that it can be easier for someone to guess your key if it
   * appears early in the keyspace and they know that you used this mapping.
   * Since DES has such a small keyspace to begin with, this might not matter to
   * you.
   */
  class LinearKeyspace : public KeyspaceMapping
  {
    public:
      LinearKeyspace();
      ~LinearKeyspace();

      uint64_t totalPools();
      uint64_t poolsLeft();
      size_t poolSize();
      KeyspacePool *getNextPool();

      void serialize(unsigned char *buffer, size_t size, bool &done) const;
      void deserialize(const unsigned char *buffer, size_t size, bool &done);
  };

  /**
   * The LinearKeyspacePool implements a KeyspacePool for LinearKeyspace. Keys
   * in this pool are from a single, contiguous portion of the keyspace.
   */
  class LinearKeyspacePool : public KeyspacePool
  {
    public:
      LinearKeyspacePool(uint64_t identifier);
      ~LinearKeyspacePool();

      uint64_t identifier()

      size_t blockSize() { return ; }
      size_t blockAlignment() { return ; }
      void setBlockAlignment(size_t alignment);
  };
}

#endif
