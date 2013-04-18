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

#ifndef TRIPCODE_CRAWLER_H_
#define TRIPCODE_CRAWLER_H_

#include <string>

namespace TripRipper
{
  class KeyspaceMapping;
  class TripcodeAlgorithm;
  class MatchingAlgorithm;
  class KeyspacePool;

  /**
   * The TripcodeCrawler class is the main workhorse class for computing
   * tripcodes. Each MPI process instantiates a TripcodeCrawler object. The
   * TripcodeCrawler fetches KeyspacePool objects from the master process and
   * searches for tripcodes in that pool until the pool is exhausted, then
   * requests another pool and repeats.
   */
  class TripcodeCrawler
  {
    public:
      TripcodeCrawler(const std::string &keyspaceStrategy, const std::string &tripcodeStrategy, const std::string &matchingStrategy, const std::string &matchString);
      ~TripcodeCrawler();

      void run();
      void doSearch();

    private:
      KeyspaceMapping *m_keyspaceMapping;
      TripcodeAlgorithm *m_tripcodeAlgorithm;
      MatchingAlgorithm *m_matchingAlgorithm;
  };
}

#endif
