#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  /* Initializes the primitive data members with their respective values read from image; 
  populates the two-dimensional std::vector<std::vector<Color>> with values from the image’s image_. 
  Calculates and stores all paths through the image; 
  you may wish to maintain the row of the best path in a variable best_path_row_. */
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const; // Returns the width of the image
  size_t Height() const; // Returns the height of the image
  unsigned int MaxColorValue() const; // Returns the value stored in kMaxColorValue
  const std::vector<Path>& Paths() const; // Returns reference to const to paths_
  const std::vector<std::vector<Color>>& GetPathImage() const; // Returns reference to const to path_image_
  void ToPpm(const std::string& name) const; // Writes out path_image_ in plain PPM format; filename is name
private:
  /* Vector storing the paths traversals calculated on image_ from each row; 
  paths_.at(0) yields the Path object encoding the traversal across the 
  image starting from row 0; paths_.at(1) yields that from row 1; etc. */
  std::vector<Path> paths_;
  size_t width_ = 0; // Width of the image
  size_t height_ = 0; // Height of the image
  /* Original image overlaid with paths: the best path is colored green [RGB(31,253,13)]; 
  every other path is red [RGB(252,25,63)].  */
  std::vector<std::vector<Color>> path_image_;
  /* Maximum possible grayscale value for the image;
  shared across all instances of this type. */
  static const int kMaxColorValue = 255;
};

#endif