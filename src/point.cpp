#include "point.h"

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

  std::ostream& operator<<(std::ostream& out, const Point& p){
    out << "not implemented";
    return out;
  }

}
