# Install OpenCV 4.5 on Ubuntu 22.04

## Build OpenCV for Python and C++ from sources

   as the basis for our instructions
1. Let's open the most recent release of opencv to the date of this video capturing:
   https://github.com/opencv/opencv/releases/tag/4.5.1
2. Create a tmp folder for all archives:
   `mkdir ~/opencv4.5-tmp && cd ~/opencv4.5-tmp`
3. We need to download opencv sources:
   `wget https://github.com/opencv/opencv/archive/4.5.1.zip -O opencv.zip`
4. We need to download opencv-contrib sources:
   `wget https://github.com/opencv/opencv_contrib/archive/4.5.1.zip -O opencv_contrib.zip`
5. Unzip the opencv files:
   `unzip opencv.zip`
6. Unzip the opencv-contrib files:
   `unzip opencv_contrib.zip`
7. Move the files to simple directories:
   `mv opencv-4.5.1/ opencv`
8. Move opencv-contrib files to simple directories:
   `mv opencv_contrib-4.5.1/ opencv_contrib`
9. Make build directory:
   `cd opencv && mkdir build && cd build`
10. Copy and run the following command. Install cmake if it is not available on the system.
   ```bash
   cmake -D CMAKE_BUILD_TYPE=DEBUG \
         -D CMAKE_INSTALL_PREFIX=~/opencv4.5-custom \
         -D OPENCV_EXTRA_MODULES_PATH=~/opencv4.5-tmp/opencv_contrib/modules \
         -D OPENCV_GENERATE_PKGCONFIG=ON \
         -D BUILD_EXAMPLES=ON ..
   ```
1. Make the project:
   ```
   make -j4
   ```
1. Install opencv:
   ```
   sudo make install
   ```
1. Ensure that it is updated in the library storage:
   ```
   sudo ldconfig
   ```
