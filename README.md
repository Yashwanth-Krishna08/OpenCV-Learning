# HSV Color Detection using OpenCV

A beginner-level computer vision project built with **C++ and OpenCV** to explore HSV color spaces and color detection using interactive trackbars.

## 📌 About the Project

This program detects a selected range of colors in an image by converting it from BGR to HSV color space. Interactive trackbars allow the user to adjust Hue, Saturation, and Value thresholds and observe how the detected color mask changes.

## ✨ Features

- Load and display an image.
- Convert BGR images to HSV color space.
- Adjust minimum and maximum HSV values using trackbars.
- Generate a binary mask based on the selected color range.
- Display the original image, HSV image, and detection mask.

## 🛠️ Technologies Used

- C++
- OpenCV
- Visual Studio

## ⚙️ How It Works

1. **Load Image:** Reads an image using `cv::imread()`.
2. **Color Conversion:** Converts BGR to HSV using `cv::cvtColor()`.
3. **Threshold Adjustment:** Uses trackbars to modify the minimum and maximum HSV values.
4. **Mask Generation:** Uses `cv::inRange()` to identify pixels within the selected HSV range.
5. **Display Results:** Shows the original image, HSV image, and binary mask using `cv::imshow()`.

## 🚀 Getting Started

### Requirements

- Windows
- Visual Studio with the C++ development workload
- OpenCV installed and configured
- An input image

### Run the Project

1. Clone or download this repository.
2. Open the Visual Studio solution or project file.
3. Configure the OpenCV include paths, library paths, and linker dependencies.
4. Update the image path in the source code to match your local image location.
5. Build and run the program.
6. Adjust the trackbars to experiment with different HSV ranges.

## 🎮 Controls

- **Hue min / Hue max:** Adjust the accepted hue range.
- **Saturation min / Saturation max:** Adjust the accepted saturation range.
- **Vmin / Vmax:** Adjust the accepted brightness range.

White pixels in the mask represent pixels within the selected HSV range. Black pixels represent pixels outside it.

## 📚 Concepts Learned

- Image loading and display in OpenCV
- BGR and HSV color spaces
- Interactive trackbars
- HSV thresholding
- Binary masks and basic image segmentation

## 🔮 Future Improvements

- Display only the detected color in the original image.
- Add real-time webcam color detection.
- Experiment with different objects and lighting conditions.



---

**Part of my OpenCV learning journey:** experimenting with C++ and computer vision through practical projects.
