CXX = g++
CXXFLAGS = -Iinclude -std=c++11 -O3

.PHONY: all bloom graph

all: \
build/std_unordered_set \
build/google_dense_hash_set \
build/google_sparse_hash_set \
build/tsl_robin_set \
build/bloom_filter

build/std_unordered_set: src/std_unordered_set.cpp src/template.cpp
	$(CXX) $(CXXFLAGS) -o build/std_unordered_set src/std_unordered_set.cpp

bloom:
	$(CXX) $(CXXFLAGS) -o build/bloom_filter src/bloom_filter.cpp

build/bloom_filter: src/bloom_filter.cpp src/template.cpp
	$(CXX) $(CXXFLAGS) -o build/bloom_filter src/bloom_filter.cpp

build/google_dense_hash_set: src/google_dense_hash_set.cpp src/template.cpp
	$(CXX) $(CXXFLAGS) -o build/google_dense_hash_set src/google_dense_hash_set.cpp

build/google_sparse_hash_set: src/google_sparse_hash_set.cpp src/template.cpp
	$(CXX) $(CXXFLAGS) -o build/google_sparse_hash_set src/google_sparse_hash_set.cpp

build/tsl_robin_set: src/tsl_robin_set.cpp src/template.cpp
	$(CXX) $(CXXFLAGS) -o build/tsl_robin_set src/tsl_robin_set.cpp

graph:
	gnuplot -p graph.plot