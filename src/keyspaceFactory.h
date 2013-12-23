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

#ifndef KEYSPACE_POOL_FACTORY_H_
#define KEYSPACE_POOL_FACTORY_H_

#include "common.h"

namespace TripRipper
{
  class KeyspaceMapping;
  class KeyspacePool;

  /**
   * The KeyspaceFactory is responsible for constructing KeyspacePool and
   * KeyspaceMapping objects from a serial representation of the object. Thisis
   * important for allowing the root MPI rank to communicate keyspace pools to
   * the TripcodeCrawler object for each rank. Because there can be many
   * different types of keyspace mappings, the particular type of KeyspacePool
   * needs to be communicated in the serial representation. This is an
   * implementation detail shared by both the KeyspaceFactory class and the
   * classes that implement KeyspaceMapping and KeyspacePool.
   */
  class KeyspaceFactory
  {
    private:
      KeyspaceFactory();
      ~KeyspaceFactory();

    public:
      static KeyspaceFactory *singleton();

      static KeyspaceMapping *deserializeKeyspaceMapping(const uint8_t *data, size_t size);
      static KeyspacePool *deserializeKeyspacePool(const uint8_t *data, size_t size);
  };
}

#endif
