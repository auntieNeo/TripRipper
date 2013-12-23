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

#ifndef KEYSPACE_MAPPING_H_
#define KEYSPACE_MAPPING_H_

#include "common.h"

namespace TripRipper
{
  class KeyspacePool;
  class KeyBlock;

  /**
   * The KeyspaceMapping class is an abstract class that defines a mapping
   * (hopefully a bijective one) from a set of KeyspacePool objects onto the
   * tripcode keyspace. Essentially this defines the order in which the keyspace
   * is searched, and how many keys are in each KeyspacePool object.
   *
   * Another benefit provided by this architecture is that KeyspaceMapping
   * objects can be serialized and stored so that searches can be suspended and
   * subsequently resumed at a later time.
   */
  class KeyspaceMapping
  {
    public:
      /**
       * Type defines an enum value for each of the classes that implements
       * KeyspaceMapping. These values are used in the serialization and
       * deserialization of KeyspaceMapping objects.
       * 
       * \sa KeyspacePool::Type, KeyspaceFactory::deserializeKeyspaceMapping()
       */
      enum Type { LINEAR = 1 };

      KeyspaceMapping();
      virtual ~KeyspaceMapping();

      void setOutputAlignment(size_t alignment) { m_outputAlignment = alignment; }
      size_t outputAlignment() const { return m_outputAlignment; }
      void setOutputStride(size_t stride) { m_outputStride = stride; }
      size_t outputStride() const { return m_outputStride; }

      /**
       * Returns the total number of pools in this mapping.
       */
      virtual uint64_t totalPools() = 0;

      /**
       * Returns the number of pools that have not yet been searched, i.e. the
       * pools that have not yet been checked out with checkoutNextPool() and
       * subsequently checked in with checkinPool().
       */
      virtual uint64_t poolsLeft() = 0;

      /**
       * Returns the number of keys in each pool. This is allowed to be an
       * approximation of the average pool size in the case that the number of
       * keys in each pool differs.
       */
      virtual size_t poolSize() = 0;

      /**
       * This method returns the next available pool in the mapping ready for
       * searching. The caller assumes ownership of the returned KeyspacePool
       * object.
       */
      virtual KeyspacePool *checkoutNextPool() = 0;

      /**
       * The checkinPool() method marks the given pool as exhausted in the
       * KeyspaceMapping object. That way the KeyspaceMapping object knows that
       * the pool no longer needs to be searched for tripcodes.
       *
       * It is important to note that the KeyspacePool provided to the
       * checkinPool() method is likely an entirely different object than the
       * KeyspacePool object created by checkoutNextPool. This is because a
       * KeyspacePool is usually serialized and then sent back before it is
       * checked in. Implementations need to determine which pool is being
       * checked in by examining the object. Serialized and deserialized objects
       * should preserve the information needed to check in a pool.
       *
       * \sa abandonPool()
       */
      virtual void checkinPool(KeyspacePool *) = 0;

      /**
       * This method works similarly to checkinPool, but instead of marking the
       * pool as having been searched the pool is returned to the set of
       * unsearched pools. This is used if a TripcodeCrawler has timed out and
       * we want to make a pool available to other TripcodeCrawlers.
       */
      virtual void abandonPool(KeyspacePool *) = 0;

      /**
       * Abstract method to serialize the entire KeyspaceMapping object so that
       * it can be  deserialized and searching of the keyspace can resume at a
       * later time. Implementations should assume that any currently checked
       * out pools are abandoned if they are still checked out at serialization
       * time.
       */
      virtual void serialize(unsigned char *buffer, size_t size, bool &done) const = 0;

      /**
       * Abstract method for reading a KeyspaceMapping object from its serial
       * representation. This method overwrites the state of the current object.
       * Implementations should consider throwing an assertion if this method is
       * would overwrite the state of a KeyspaceMapping that is already in use.
       *
       * This method should not be called directly. You should call
       * KeyspaceFactory::deserializeKeyspaceMapping() instead.
       */
      virtual void deserialize(const unsigned char *buffer, size_t size, bool &done) = 0;

    private:
      size_t m_outputAlignment, m_outputStride;
  };

  /**
   * The abstract KeyspacePool class represents a chunk of the keyspace that a
   * TripcodeCrawler can work on.
   *
   * The KeyspacePool needs to be sent over the wire to each TripcodeCrawler,
   * so implementing classes need to be able to create a serialized
   * representation of their instances. These serialized representations need
   * to be readable by the KeyspacePoolFactory class.
   *
   * A KeyspacePool object creates KeyBlock objects suitable for processing.
   */
  class KeyspacePool
  {
    friend class KeyspaceFactory;

    public:
      /**
       * Type defines an enum value for each of the classes that implement
       * KeyspacePool. These values are used in the serialization and
       * deserialization of KeyspacePool objects.
       * 
       * \sa KeyspaceMapping::Type, KeyspaceFactory::deserializeKeyspacePool()
       */
      enum Type { LINEAR = 1 };

      KeyspacePool();
      virtual ~KeyspacePool();

      /**
       * This method returns the size in bytes of each block that the pool
       * returns. The block size must be a multiple of the value returned by
       * blockAlignment().
       *
       * \sa getNextBlock()
       */
      virtual size_t blockSize() = 0;

      /**
       * This method returns the address alignment of the output keys in bytes.
       *
       * \sa setOutputAlignment()
       */
      virtual size_t outputAlignment() = 0;

      /**
       * This method sets the address alignment of the output keys in bytes.
       * This alignment must be a multiple of 2.
       *
       * \sa outputAlignment()
       */
      virtual void setOutputAlignment(size_t alignment) = 0;

      /**
       * This method returns the number of spacer bytes that occur between
       * output keys.
       *
       * \sa setOutputStride()
       */
      virtual size_t outputStride() = 0;

      /**
       * This method sets the number of spacer bytes to be placed between output
       * keys. The values of these spacers can by anything and should be ignored
       * by the tripcode algorithm.
       *
       * \sa outputStride()
       */
      virtual void setOutputStride(size_t stride) = 0;

      /**
       * This method returns true if output keys are packed into 56 contiguous
       * bits rather than 64 bits with the high bit on each byte irrelevant to
       * the key.
       *
       * \sa setOutputPackHighBit()
       */
      virtual bool outputPackHighBit();

      /**
       * This method sets whether or not to pack the high bits of the output
       * keys. If the value of packHighBit is true, then output keys will be
       * packed into 56 contiguous bits. Otherwise, output keys will occupy 8
       * bytes with the high bit of each byte irrelevant to the value of the
       * key.
       */
      virtual void setOutputPackHighBit(bool packHighBit) = 0;

      /**
       * This method returns a pointer to the next block in the pool. 
       */
      virtual KeyBlock *getNextBlock() = 0;

      /**
       * This method returns a pointer to a serial representation of the given
       * KeyspacePool object. The size in bytes of the returned buffer is
       * returned in the size argument.
       *
       * Callers assume ownership of the returned buffer.
       *
       * The exact representation of the serialized pool object is determined
       * by implementing classes. Since serialized pools must be read by the
       * KeyspaceFactory class, the representation of serialized pools is an
       * implementation detail shared by implementing classes and the
       * KeyspaceFactory class.
       */
      virtual uint8_t *serialize(size_t *size) const = 0;

    protected:
      /**
       * Read a KeyspacePool object from the serialized representation pointed
       * to by buffer. The size argument is the size in bytes of buffer.
       *
       * This method needs to be implemented by implementing classes, but should
       * never be called directly except by the KeyspaceFactory class. To
       * deserialize a KeyspacePool, use the
       * KeyspaceFactory::deserializeKeyspacePool() method.
       *
       * \sa serialize(), KeyspaceFactory::deserializeKeyspacePool()
       */
      virtual void deserialize(const uint8_t *buffer, size_t size) = 0;
  };

  /**
   * The KeyBlock class is a container for inputs to the tripcode algorithm,
   * packed in such a way to allow for efficient processing.
   *
   * A KeyBlock is a further division of the keyspace of a KeyspacePool.
   */
  class KeyBlock
  {
    public:
      KeyBlock();
      virtual ~KeyBlock();
  };
}

#endif
