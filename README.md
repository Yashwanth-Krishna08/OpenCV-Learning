# Real-Time Face Detection (C++ / OpenCV)

A simple C++ application that detects faces in a live webcam feed using OpenCV and a Haar Cascade classifier. Detected faces are outlined with a rectangle in real time.

## Features

- Live video capture from the default webcam
- Face detection using `haarcascade_frontalface_alt.xml`
- Grayscale conversion and histogram equalization for better detection in uneven lighting
- Error handling for missing camera, failed frame grabs, and a missing cascade file
- Press `Esc` or `q` to quit

## How It Works

1. Opens the default camera (`VideoCapture(0)`).
2. Loads the Haar Cascade face classifier from an XML file.
3. For each frame:
   - Converts it to grayscale and equalizes the histogram
   - Runs `detectMultiScale` to find faces
   - Draws a rectangle around each detected face
   - Displays the result in a window

## Requirements

- C++11 or later
- [OpenCV](https://opencv.org/releases/) 4.x (with the `objdetect` module)
- A webcam
- A C++ compiler / IDE (Visual Studio, g++, clang, or CMake-based setup)

## Setup

### 1. Install OpenCV

Download OpenCV from [opencv.org](https://opencv.org/releases/) and extract it (for example to `C:/opencv`). Then add the OpenCV `bin` folder to your system `PATH`.

### 2. Get the Haar Cascade file

The cascade file ships with OpenCV at:

```
<opencv_dir>/sources/data/haarcascades/haarcascade_frontalface_alt.xml
```


### 3. Update the path in the code

In `main.cpp`, make sure the path matches where you placed the file:

```cpp
faceCascade.load("C:/Yachu/haarcascade_frontalface_alt.xml");
```

### 4. Configure your project

**Visual Studio**

- Add `<opencv_dir>/build/include` to *C/C++ → Additional Include Directories*
- Add `<opencv_dir>/build/x64/vc16/lib` to *Linker → Additional Library Directories*
- Add `opencv_world4xx.lib` (or `opencv_world4xxd.lib` for Debug) to *Linker → Input → Additional Dependencies*

**g++ (Linux / macOS)**

```bash
g++ main.cpp -o face_detection `pkg-config --cflags --libs opencv4`
```

**CMake**

```cmake
cmake_minimum_required(VERSION 3.10)
project(FaceDetection)

find_package(OpenCV REQUIRED)
add_executable(face_detection main.cpp)
target_link_libraries(face_detection ${OpenCV_LIBS})
```

## Usage

Build and run the program:

```bash
./face_detection
```

A window titled **Face Detection** opens showing your webcam feed with blue rectangles around detected faces. Press `Esc` or `q` to exit.

## Tuning Parameters

The detection call looks like this:

```cpp
faceCascade.detectMultiScale(grey, faces, 1.1, 5, 0, cv::Size(60, 60));
```

| Parameter | Value | Effect |
|---|---|---|
| `scaleFactor` | `1.1` | Lower (e.g. `1.05`) is more accurate but slower |
| `minNeighbors` | `5` | Higher means fewer false positives, but may miss faces |
| `minSize` | `60x60` | Ignores detections smaller than this |

## Troubleshooting

| Problem | Fix |
|---|---|
| `Cascade not loaded` | Check the XML file path and use forward slashes or escaped backslashes |
| `Camera not opened` | Close other apps using the webcam, or try `VideoCapture(1)` |
| `opencv_world4xx.dll not found` | Add OpenCV's `bin` folder to your `PATH` |
| Faces not detected | Improve lighting, face the camera directly, lower `minNeighbors` |
| Too many false detections | Increase `minNeighbors` or `minSize` |

## Limitations

- Haar Cascades work best on frontal, well-lit faces and struggle with side profiles, occlusion, and low light.
- For better accuracy, consider OpenCV's DNN-based detectors such as YuNet or a Caffe SSD face model.

## Project Structure

```
face-detection/
├── main.cpp
├── haarcascade_frontalface_alt.xml
└── README.md
```
