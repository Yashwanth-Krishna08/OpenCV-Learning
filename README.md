# OpenCV Shape Detection

A C++ program that detects geometric shapes in an image using OpenCV. It finds each shape's outline, counts its corners, and labels it directly on the image.

## Features

- Detects **triangles, squares, rectangles, pentagons, hexagons and circles**
- Distinguishes squares from rectangles, even when the shape is rotated (`minAreaRect`)
- Uses **circularity** to identify circles reliably
- Draws the outline and the shape name on the output image
- Prints area, corner count, circularity and shape type to the console
- Ignores small noise using an area threshold

## How It Works

```
Image -> Grayscale -> Gaussian Blur -> Canny Edges -> Dilate -> Find Contours -> Classify
```

1. **Grayscale**: edge detection only needs brightness.
2. **Gaussian blur**: removes small noise so it isn't detected as edges.
3. **Canny edge detection**: produces thin white outlines of the shapes.
4. **Dilation**: thickens the edges to close small gaps, so each shape forms one continuous contour.
5. **Find contours**: `findContours` with `RETR_EXTERNAL` extracts the outer outline of each shape.
6. **Polygon approximation**: `approxPolyDP` simplifies each contour to a polygon (tolerance = 2% of the perimeter).
7. **Classification**: the number of polygon corners decides the shape.

### Classification Rules

| Corners | Shape | Extra check |
|---------|-------|-------------|
| 3 | Triangle | none |
| 4 | Square or Rectangle | `min(w,h) / max(w,h) > 0.95` gives Square |
| 5 | Pentagon | none |
| 6 | Hexagon | none |
| 7+ | Circle | circularity `> 0.8` |
| other | Unknown | none |

**Circularity** is `4 * PI * area / perimeter^2`. It equals 1 for a perfect circle and is lower for every other shape (a square is about 0.785).

**Square vs. rectangle** uses `cv::minAreaRect` and divides the shorter side by the longer side. The ratio is always between 0 and 1 and does not depend on the shape's rotation.

## Requirements

- C++ compiler (C++11 or later)
- [OpenCV](https://opencv.org/releases/) 4.x
- Tested with Visual Studio on Windows

## Build and Run

### Visual Studio

1. Install OpenCV and add it to your project:
   - **Include directories:** `<opencv>/build/include`
   - **Library directories:** `<opencv>/build/x64/vc16/lib`
   - **Linker input:** `opencv_world4xx.lib` (or `opencv_world4xxd.lib` for Debug)
2. Add the `.cpp` file to the project and make sure it is **included in the build**.
3. Put your image in the project folder.
4. Set the image path in `main()`:
   ```cpp
   std::string path = "3.jpeg";
   ```
5. Build and run with **F5** or **Ctrl+F5**.

> Running the `.exe` directly from `x64/Debug` changes the working directory, so a relative path will not work. Use a full path in that case, with forward slashes (`C:/Users/...`) or double backslashes (`C:\\Users\\...`).

### CMake (Linux / macOS / Windows)

```cmake
cmake_minimum_required(VERSION 3.10)
project(shape_detection)

find_package(OpenCV REQUIRED)
add_executable(shape_detection chapter7.cpp)
target_link_libraries(shape_detection ${OpenCV_LIBS})
```

```bash
mkdir build && cd build
cmake ..
make
./shape_detection
```

## Usage

1. Set `path` in `main()` to your image.
2. Run the program.
3. A window shows the image with blue outlines and orange labels. Press any key to close it.
4. The console prints details for each detected shape:

```
Area: 15234, corners: 4, circularity: 0.78, type: Square
Area: 9876, corners: 3, circularity: 0.60, type: Triangle
```

## Tuning

| Parameter | Location | Effect |
|-----------|----------|--------|
| `area < 1000` | `getContours` | Minimum shape size. Raise it to ignore more noise, lower it for small shapes. |
| `0.02 * peri` | `approxPolyDP` | Polygon tolerance. Try `0.01` to `0.04` if corner counts are wrong. |
| `Canny(25, 75)` | `main` | Edge sensitivity (low, high thresholds). |
| `circularity > 0.8` | `getContours` | Circle cutoff. Raise to `0.85` to `0.9` if non-circles are labeled circles. |
| `ar > 0.95` | `getContours` | Square cutoff. Lower it to be more forgiving of slightly uneven squares. |

## Project Structure

```
Shape_detection/
├── Shape_detection.slnx
├── Shape_detection.vcxproj
├── Shape_detection.filters
├── Shape_detection.cpp     # Shape detection program
├── 3.jpeg           # Sample input image
└── README.md
```

## Limitations

- Works best with clear shapes on a plain background.
- Touching or overlapping shapes may merge into one contour.
- Thresholds depend on image resolution and lighting, so they may need adjusting.
- Corner-count classification can mislabel heavily distorted shapes.

