## Project Presentation

a C++ real-time visual stream acquisition system that incorporates quality control using the BRISQUE (Blind/Referenceless Image Spatial Quality Evaluator) metric. The main goal is to analyze the quality of video frames either from a webcam or stored video files without the need for a reference image.

### Requirements to use this project :
```
Linux-based operating system.
C17+
G++
OpenCV 4.10.0+
LIBSVM
Python3.8
cmake3.30
make
gcc.
```
### Compile the project : 
```
cmake brisque/.
g++ -o main mainBrisque.cpp brisque/libsvm/svm.o brisque/computescore.o brisque/brisque.o $(pkg-config --cflags --libs opencv4)
```

## Execution

for a raw video in your filesystem : 
```
./main <pathToVideo/video> frame_delay_in_ms
```
to use your computer camera :
```
./main 0 frame_delay_in_ms
```
### Python utilization:

to plot results in c++ , i tried to port matplotlib in c++ using the library : https://github.com/lava/matplotlib-cpp/ but it creates many linking problems , so i'll extract the results as a txt or csv and plot them easily with a python script.
