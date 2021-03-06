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

#include <getopt.h>
#include <mpi.h>
#include <cstdlib>
#include <iostream>
#include "tripcodeCrawler.h"

#define USAGE(status) do { \
  fprintf(stderr, "Usage: tripripper [mpi_arguments] [options] search_string\n\n"); \
  fprintf(stderr, "   Options\n"); \
  fprintf(stderr, "   -k --keyspace-mapping=[mapping]\n"); \
  fprintf(stderr, "      The keyspace mapping determines which keys in the keyspace will be\n"); \
  fprintf(stderr, "      searched, and in what order.\n"); \
  fprintf(stderr, "   -t --tripcode-algorithm=[algorithm]\n"); \
  fprintf(stderr, "      The algorithm that computes the tripcodes. There are a variety of tripcode\n"); \
  fprintf(stderr, "      algorithms available, depending on the hardware, each with different\n"); \
  fprintf(stderr, "      performance characteristics.\n"); \
  exit(status); \
  } while (0)

void tripRipperExit()
{
  MPI_Finalize();
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  atexit(tripRipperExit);

  std::string keyspaceMapping, tripcodeAlgorithm, matchingAlgorithm, searchString;

  // parse options with getopts
  while(1)
  {
    static struct option long_options[] = {
      {"keyspace-mapping", required_argument, NULL, 'k'},
      {"tripcode-algorithm", required_argument, NULL, 't'},
      {"matching-algorithm", required_argument, NULL, 'm'},
      {"search-string", required_argument, NULL, 's'},
      {"help", no_argument, NULL, 'h'}
    };

    char opt = getopt_long(argc, argv, "k:t:m:", long_options, NULL);

    if(opt == -1)
      break;

    switch(opt)
    {
      case 'k':
        if(optarg == NULL)
        {
          USAGE(EXIT_FAILURE);
        }
        keyspaceMapping = std::string(optarg);
        std::cout << "keyspaceMapping: " << keyspaceMapping << std::endl;
        break;
      case 't':
        if(optarg == NULL)
        {
          USAGE(EXIT_FAILURE);
        }
        tripcodeAlgorithm = std::string(optarg);
        std::cout << "tripcodeAlgorithm: " << tripcodeAlgorithm << std::endl;
        break;
      case 'm':
        if(optarg == NULL)
        {
          USAGE(EXIT_FAILURE);
        }
        matchingAlgorithm = std::string(optarg);
        std::cout << "matchingAlgorithm: " << matchingAlgorithm << std::endl;
        break;
      case 'h':
        USAGE(EXIT_SUCCESS);
        break;
      case '?':
        USAGE(EXIT_FAILURE);
        break;
      default:
        break;
    };
  }
  // get the search string
  if(optind >= argc)
  {
    USAGE(EXIT_FAILURE);
  }
  searchString = std::string(argv[optind]);

  TripRipper::TripcodeCrawler crawler(keyspaceMapping, tripcodeAlgorithm, matchingAlgorithm, searchString);

  crawler.run();

  return EXIT_SUCCESS;
}
