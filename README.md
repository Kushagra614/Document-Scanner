# Document Scanner with OpenCV

## Overview

This project showcases a robust document scanning application using the OpenCV library in C++. It is designed to automate the process of scanning documents, extracting them from their background, and producing a clean, top-down view.

The application is versatile and can either capture images in real-time from a webcam or process pre-existing image files. It follows a series of image processing steps to enhance and prepare the image for further analysis:

- **Image Acquisition**: 
  - Capture an image using a webcam.
  - Alternatively, read an image file from disk.

- **Pre-processing**:
  - Convert the image to grayscale.
  - Apply Gaussian blur to reduce noise.
  - Use edge detection to highlight the document’s edges.

- **Contour Detection**:
  - Identify and extract contours in the image.
  - Focus on the contour that best represents the document.

- **Perspective Transformation**:
  - Apply a perspective transformation to correct the view of the document.
  - Ensure the document appears as if viewed from directly above.

- **Cropping**:
  - Crop the perspective-corrected image to tightly fit the document area.

## Features

- **Real-time Image Capture**: 
  - Capture images directly from a webcam for immediate document scanning.
  - Process static image files from disk for offline document scanning.

- **Advanced Image Pre-processing**: 
  - Grayscale conversion for simplified image analysis.
  - Gaussian blur to reduce image noise and improve edge detection.
  - Canny edge detection for precise contour detection.

- **Contour Detection and Analysis**:
  - Automatic detection and extraction of document contours.
  - Identification of the largest quadrilateral contour representing the document.

- **Perspective Correction**:
  - Transform the perspective of the document to provide a top-down view.
  - Correct angle distortions to ensure a straightened document appearance.

- **Image Cropping**:
  - Focus the cropped area on the document to eliminate unwanted borders.
  - Produce a clean and clear image of the document.

## Dependencies

- **OpenCV** (4.5.0 or later)
- **C++11** or later

## Usage

1. **Build and Compile**:
   - Ensure you have OpenCV installed and configured with your C++ compiler.
   - Compile the source code with your preferred build system.

2. **Run the Application**:
   - Execute the compiled application.
   - Choose whether to capture an image from a webcam or load an image from a file.
   - Follow the on-screen instructions to process and view the document scan.
