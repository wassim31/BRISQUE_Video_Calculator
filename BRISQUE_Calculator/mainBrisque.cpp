#include <iostream> 
#include <string>   
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  
#include "brisque/brisque.h"
#include "brisque/libsvm/svm.h"
#include "useCameraInput.h"

using namespace std;
using namespace cv;
float getBrisque(cv::Mat frame,int frameNum, svm_model *model);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Not enough parameters" << endl;
        return -1;
    }
    string videoSource;
    if(std::strcmp(argv[1],"0") != 0) {
        videoSource = argv[1];
    } else {
        videoSource = useCameraInput();
    }
    int delay = std::stoi(argv[2]);;
    
    /*conv << argv[2] << endl;      
    conv >> delay;    */

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
    float brisqueValue;
    double countFrame = captRefrnc.get(CAP_PROP_FRAME_COUNT) / 2;
    cout << countFrame << "\n";
    
    for(;;) //Show the image captured in the window and repeat
    {
        captRefrnc >> frame;

        if (frame.empty())
        {
            cout << " < < <  Game over!  > > > ";
            break;
        }

        ++frameNum;
        brisqueValue = getBrisque(frame,frameNum, model);
        const string text = "Brisque at Frame " + std::to_string(frameNum) + ": " + std::to_string(brisqueValue);
        cv::putText(frame, 
        text,
        cv::Point(10, frame.rows / 4),
        cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(118, 185, 0),2);

        cout << endl;

        imshow(WIN_RF, frame);

        c = (char) waitKey(delay);
        if (c == 27) break;
    }
    
    return 0;
}

float getBrisque(cv::Mat frame,int frameNum, svm_model *model)
{
  float score = computescore(frame,model,frameNum);
  std::cout << "Frame " << frameNum << " score " << score << std::endl;
  return score;
}

