#include <iostream>
#include <color.hpp>
#include <elevation_dataset.hpp>
#include <grayscale_image.hpp>
#include <path_image.hpp>
#include <path.hpp>

int main() {
  ElevationDataset elevation("example-data/ex_input_data/all-tie-row1-2w-3h.dat", 2, 3);
  // GrayscaleImage grayscale("example-data/ex_output_grayscale/map-input-480-480.ppm", 480, 480);
  return 0;
}