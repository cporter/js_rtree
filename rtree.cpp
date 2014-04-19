

#include <emscripten/bind.h>
#include <map>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;



struct Vect {
  double x, y, z;
};

class RTree {
 private:
  typedef bg::model::point<double, 3, bg::cs::cartesian> point;
  typedef bg::model::box<point> box;
  typedef std::pair<box, int> value;

  bgi::rtree<value, bgi::quadratic<16>> rtree;
 public:

  void AddPoint (int id, Vect loc) {
    point p { loc.x, loc.y, loc.z };
    box b { p, p };
    rtree.insert(std::make_pair (b, id));
  }

  void AddBox (int id, Vect bl, Vect tr) {
    box b { point { bl.x, bl.y, bl.z }, point { tr.x, tr.y, tr.z } };
    rtree.insert (std::make_pair (b, id));
  }

  void RemovePoint (int id, Vect loc) {
    point p { loc.x, loc.y, loc.z };
    box b { p, p };
    rtree.remove(std::make_pair (b, id));
  }
  
  void RemoveBox (int id, Vect bl, Vect tr) {
    box b { point { bl.x, bl.y, bl.z }, point { tr.x, tr.y, tr.z } };
    rtree.remove(std::make_pair (b, id));
  }

  std::vector<int> FindAll (Vect bl, Vect tr) {
    std::vector<value> results;
    box q { point { bl.x, bl.y, bl.z }, point { tr.x, tr.y, tr.z } };
    rtree . query (bgi::intersects(q), std::back_inserter (results));
    std::vector<int> output;
    output . reserve (results . size ());
    for (const value& v : results)
      output . push_back (v . second);
    return output;
  }

  // todo: make this a boost::optional<int> and figure out how to represent
  //       those properly in js. (rather than the whole magic number "-1")
  int FindNearest (Vect loc) {
    std::vector<value> results;
    rtree.query (bgi::nearest (point { loc.x, loc.y, loc.z }, 1),
                 std::back_inserter (results));
    if (0 < results . size ())
      return results[0] . second;
    return -1;
  }
};

EMSCRIPTEN_BINDINGS(stuff) {
  using namespace emscripten;

  register_vector<int>("VectorInt");

  value_array<Vect>("Vect")
      .element(&Vect::x)
      .element(&Vect::y)
      .element(&Vect::z)
      ;

  class_<RTree> ("RTree")
      .constructor<> ()
      .function("AddPoint", &RTree::AddPoint)
      .function("AddBox", &RTree::AddBox)
      .function("RemovePoint", &RTree::RemovePoint)
      .function("RemoveBox", &RTree::RemoveBox)
      .function("FindAll", &RTree::FindAll)
      .function("FindNearest", &RTree::FindNearest)
      ;
}
