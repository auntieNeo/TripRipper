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

namespace TripRipper
{
  GlibcTripcode::GlibcTripcode()
  {
    m_data = new crypt_data;
  }

  GlibcTripcode::~GlibcTripcode()
  {
    delete m_data;
  }
  
  /**
   * This method implements using the reentrant crypt(3) function in glibc. This
   * is not very efficient or practical, only for demonstration purposes.
   */
  void GlibcTripcode::computeTripcodes(const KeyBlock *keys, TripcodeContainer *results)
  {
    uint8_t tripcode[11];
    uint8_t *keyData = keys->data();
    char *hash;

    for(size_t i = 0; i < keys->numKeys(); ++i)
    {
      uint8_t *currentTripcode = keyData + i * keys->tripcodeDatumSize();
      hash = crypt_r(currentTripcode, currentTripcode + 1, m_data);
      strncpy(static_cast<char*>(tripcode), hash + 3, 10);
    }
  }
}
