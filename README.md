Document Scanner with OpenCV
Overview
This project showcases a robust document scanning application using the OpenCV library in C++. It is designed to automate the process of scanning documents, extracting them from their background, and producing a clean, top-down view.

The application is versatile and can either capture images in real-time from a webcam or process pre-existing image files. It follows a series of image processing steps to enhance and prepare the image for further analysis:

Image Acquisition: Capture an image using a webcam or read an image file from disk.
Pre-processing: Convert the image to grayscale, apply Gaussian blur to reduce noise, and use edge detection to highlight the document’s edges.
Contour Detection: Identify and extract contours in the image, focusing on the contour that best represents the document.
Perspective Transformation: Apply a perspective transformation to correct the view of the document, ensuring it appears as if viewed from directly above.
Cropping: Crop the perspective-corrected image to tightly fit the document area.
