#include "point.h"
#include <cmath>

namespace novia {

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

  Point Point::operator+(const Point& rhs) const {
    return Point(x_ + rhs.x_, y_ + rhs.y_);
  }

  Point Point::operator-(const Point& rhs) const {
    return Point(x_ - rhs.x_, y_ - rhs.y_);
  }

  bool Point::operator==(const Point& rhs) const {
    return x_ == rhs.x_ && y_ == rhs.y_;
  }

  bool Point::operator!=(const Point& rhs) const {
    return !(*this == rhs);
  }

  std::ostream& operator<<(std::ostream& out, const Point& p){
    out << "(" << p.x_ << "," << p.y_ << ")";
    return out;
  }

  Json::Value Point::serialize() const {
    Json::Value serialized(Json::objectValue);
    serialized["x"] = Json::Value(x());
    serialized["y"] = Json::Value(y());
    return serialized;
  }

}
