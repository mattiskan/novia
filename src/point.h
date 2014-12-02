//-*-c++-*-
#ifndef NOVIA_POINT_H
#define NOVIA_POINT_H

#include <ostream>

namespace Novia {

  class Point {
    const int x_, y_;
    
  public:
    Point(int x, int y);
    
    int x() const;
    int y() const;

    double distance_to(const Point& other) const;
    double distance_squared(const Point& other) const;

    Point& operator+(const Point& rhs) const;
    Point& operator+=(const Point& rhs) const;

    Point& operator-(const Point& rhs) const;
    Point& operator-=(const Point& rhs) const;

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const Point& p);    
  };

  std::ostream& operator<<(std::ostream& out, const Point& p);

}
#endif
