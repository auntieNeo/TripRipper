add_executable(tripripper keyspace.cpp keyspaceFactory.cpp linearKeyspace.cpp main.cpp matchingAlgorithm.cpp openSSLTripcode.cpp strategyFactory.cpp strcmpMatching.cpp tripcodeAlgorithm.cpp tripcodeContainer.cpp tripcodeCrawler.cpp)
target_link_libraries(tripripper ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})

add_subdirectory(tests)
