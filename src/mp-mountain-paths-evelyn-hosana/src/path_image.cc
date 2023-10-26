#include "path_image.hpp"

#include <fstream>

// Initializes the primitive data members with their respective values read from
// image Populates the two-dimensional std::vector<std::vector<Color>> with
// values from the image’s image_ Calculates and stores all paths through the
// image; you may wish to maintain the row of the best path in a variable
// best_path_row_.
PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  (void)image;
  (void)dataset;
}
// Returns the width of the image
size_t PathImage::Width() const { return width_; }

// Returns the width of the image
size_t PathImage::Height() const { return height_; }

// Returns the value stored in kMaxColorValue
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

// Returns reference to const to paths_
const std::vector<Path>& PathImage::Paths() const { return paths_; }

// Returns reference to const to path_image_
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

// Writes out path_image_ in plain PPM format; filename is name
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  if (!ofs.is_open()) {
    throw std::runtime_error("File is not open!");
  }
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (int i = 0; i < (int)height_; i++) {
    for (int j = 0; j < (int)width_; j++) {
      Color color = path_image_.at(i).at(j);
      ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
  }
  ofs << std::endl;
}