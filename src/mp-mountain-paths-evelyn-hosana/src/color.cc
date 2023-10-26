#include "color.hpp"
#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  static const int kMaxColorValue = 255;
  if ((r >= 0 && r <= kMaxColorValue) && (g >= 0 && g <= kMaxColorValue) && (b >= 0 && b <= kMaxColorValue)) {
    red_ = r;
    green_ = g;
    blue_ = b;
  } else {
    throw std::invalid_argument ("Invalid color input; out of range");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}