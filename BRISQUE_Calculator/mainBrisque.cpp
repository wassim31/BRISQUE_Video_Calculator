#include <iostream> 
#include <string>   
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  
#include "brisque/brisque.h"
#include "brisque/libsvm/svm.h"

using namespace std;
using namespace cv;
void getBrisque(cv::Mat frame,int frameNum, svm_model *model);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Not enough parameters" << endl;
        return -1;
    }
    stringstream conv;

    const string videoSource = argv[1];
    int delay;
    conv << argv[2] << endl;       // put in the strings
    conv >> delay;        // take out the numbers

    char c; // to stop 
    int frameNum = -1;          // Frame counter

    VideoCapture captRefrnc(videoSource);

    if (!captRefrnc.isOpened())
    {
        cout  << "Could not open video " << videoSource << endl;
        return -1;
    }

    Size refS = Size((int) captRefrnc.get(CAP_PROP_FRAME_WIDTH),
                     (int) captRefrnc.get(CAP_PROP_FRAME_HEIGHT));

    const char* WIN_RF = "Reference";

    // Windows
    namedWindow(WIN_RF, WINDOW_AUTOSIZE);
    moveWindow(WIN_RF, 400       , 0);

    cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
         << " of nr#: " << captRefrnc.get(CAP_PROP_FRAME_COUNT) << endl;

    cv::Mat frame;
    double psnrV;
    cv::Scalar mssimV;
    struct svm_model *model = (struct svm_model *) svm_load_model("allmodel");
    for(;;) //Show the image captured in the window and repeat
    {
        captRefrnc >> frame;

        if (frame.empty())
        {
            cout << " < < <  Game over!  > > > ";
            break;
        }

        ++frameNum;
        getBrisque(frame,frameNum, model);

        cout << endl;

        imshow(WIN_RF, frame);

        c = (char) waitKey(delay);
        if (c == 27) break;
    }

    return 0;
}

void getBrisque(cv::Mat frame,int frameNum, svm_model *model)
{
  float score = computescore(frame,model,frameNum);
  std::cout << "Frame " << frameNum << " score " << score << std::endl;
}

