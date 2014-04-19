
CXXFLAGS = -Wno-warn-absolute-paths -std=c++11 -I/usr/local/include

all: rtree.js

rtree.js: rtree.cpp
	em++ $(CXXFLAGS) --bind $^ -o $@
