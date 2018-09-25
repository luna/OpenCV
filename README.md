# Facial Recognition in Luna using OpenCV library

Detecting Faces using Cascade Classifiers. 
To use the example following dependencies are required to run on MacOS and Linux:
 - ImageMagick6
 - OpenCV 3.4
 - [MacOS] you may need to install the Tesseract library: `brew install tesseract`.
 
The example is working from version 1.4 of Luna Studio.

If you have OpenCV 3 in version different than 3.4 you can recompile the `csv.cpp` as a shared library with your OpenCV with command:
```g++ `pkg-config --cflags --libs opencv` -lstdc++ -Wall -pedantic -shared -fPIC -o ./native_libs/linux/cv.so ./native_libs/src/cv.cpp```
