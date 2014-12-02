#include "point.h"
#include <cmath>

namespace Novia {

  Point::Point(int x, int y)
    : x_(x), y_(y){
    
  }

  int Point::x() const {
    return x_;
  }

  int Point::y() const {
    return y_;
  }


  double Point::distance_to(const Point& other) const {
    return sqrt(distance_squared(other));
  }

  double Point::distance_squared(const Point& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return dx*dx + dy*dy;
  }


  std::ostream& operator<<(std::ostream& out, const Point& p){
    out << "not implemented";
    return out;
  }

}
