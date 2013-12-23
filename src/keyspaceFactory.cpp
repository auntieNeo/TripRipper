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

#include "keyspaceFactory.h"
#include "keyspace.h"
#include "linearKeyspace.h"
#include "common.h"

#include <arpa/inet.h>

namespace TripRipper
{
  KeyspaceFactory::KeyspaceFactory()
  {
  }

  KeyspaceFactory::~KeyspaceFactory()
  {
  }

  KeyspaceFactory *KeyspaceFactory::singleton()
  {
    static KeyspaceFactory instance;
    return &instance;
  }

  /**
   * The deserializeKeyspaceMapping method calls the appropriate
   * deserialization method for the given serialized data and returns a pointer
   * to the deserialized object.
   *
   * The caller assumes ownership of the returned object.
   */
  static KeyspaceMapping *deserializeKeyspaceMapping(const uint8_t *data, size_t size)
  {
    assert(size >= sizeof(const uint32_t));
    uint32_t type = ntohl(*reinterpret_cast<const uint32_t*>(data));
    KeyspaceMapping *mapping = NULL;
    switch(static
  }

  /**
   * The deserializeKeyspacePool method calls the appropriate deserialization
   * method for the given serialized data and returns a pointer to the
   * deserialized object.
   *
   * The caller assumes ownership of the returned object.
   */
  KeyspacePool *KeyspaceFactory::deserializeKeyspacePool(const uint8_t *data, size_t size)
  {
    assert(size >= sizeof(const uint32_t));
    uint32_t type = ntohl(*reinterpret_cast<const uint32_t*>(data));
    KeyspacePool *pool = NULL;
    switch(static_cast<KeyspacePool::Type>(type))
    {
      case KeyspacePool::LINEAR:
        {
          pool = new LinearKeyspacePool();
          pool->deserialize(data, size);
        }
        break;
      default:
        assert(false);
    }
    return pool;
  }
}
