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

#ifndef STRATEGY_FACTORY_H_
#define STRATEGY_FACTORY_H_

#include <string>
#include <map>

namespace TripRipper
{
  class KeyspaceMapping;
  class TripcodeAlgorithm;
  class MatchingAlgorithm;

  /**
   * The StrategyFactory class is a singleton factory class that constructs the
   * various strategy classes that TripRipper uses. These strategies can be
   * changed based on user configuration parameters. The three strategy classes
   * that StrategyFactory constructs include KeyspaceMapping,
   * TripcodeAlgorithm, and MatchingAlgorithm.
   */
  class StrategyFactory
  {
    private:
      StrategyFactory();
      ~StrategyFactory();

    public:
      static StrategyFactory *singleton();

      KeyspaceMapping *createKeyspaceMapping(const std::string &type);
      TripcodeAlgorithm *createTripcodeAlgorithm(const std::string &type);
      MatchingAlgorithm *createMatchingAlgorithm(const std::string &type);

    private:
      std::map<std::string, KeyspaceMapping *(*)()> m_keyspaceMappingCreators;
      std::map<std::string, TripcodeAlgorithm *(*)()> m_tripcodeAlgorithmCreators;
      std::map<std::string, MatchingAlgorithm *(*)()> m_matchingAlgorithmCreators;
  };
}

#endif
