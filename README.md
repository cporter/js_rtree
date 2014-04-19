js_rtree
========

Use an rtree from boost::geometry in a browser via emscripten

## Prerequisites

You'll need to have [emscripten](https://github.com/imvu/emscripten) installed.
This is nontrivial.  Make assumes that `em++` is in your path.

## Use:

See [The overly simple demo script](demo.js). It writes its output to the
console, so the demo is not exactly exciting.  See the [c++ source](rtree.cpp)
for the API.
