#include <iostream> 
#include <string>   
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core/core.hpp>        
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/highgui/highgui.hpp>  

using namespace std;
using namespace cv;

double getPSNR ( const Mat& I1, const Mat& I2);
int main(int argc, char *argv[])
{
    if (argc != 5) {
        cout << "Not enough parameters" << endl;
        return -1;
    }
    stringstream conv;

    const string videoSource = argv[1];
    int psnrTriggerValue, delay;
    conv << argv[2] << endl;       // put in the strings
    conv >> delay;        // take out the numbers

    char c;
    int frameNum = -1;          // Frame counter

    VideoCapture captRefrnc(videoSource);

    if (!captRefrnc.isOpened())
    {
        cout  << "Could not open video " << videoSource << endl;
        return -1;
    }

    Size refS = Size((int) captRefrnc.get(CV_CAP_PROP_FRAME_WIDTH),
                     (int) captRefrnc.get(CV_CAP_PROP_FRAME_HEIGHT));

    const char* WIN_RF = "Reference";

    // Windows
    namedWindow(WIN_RF, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(WIN_RF, 400       , 0);

    cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
         << " of nr#: " << captRefrnc.get(CV_CAP_PROP_FRAME_COUNT) << endl;

    Mat frame;
    double psnrV;
    Scalar mssimV;

    for(;;) //Show the image captured in the window and repeat
    {
        captRefrnc >> frame;

        if (frame.empty())
        {
            cout << " < < <  Game over!  > > > ";
            break;
        }

        ++frameNum;
        cout << "Frame: " << frameNum << "# ";

        // PSNR 
        psnrV = getPSNR(frame,frameUnderTest);
        cout << setiosflags(ios::fixed) << setprecision(3) << psnrV << "dB";

        cout << endl;

        imshow(WIN_RF, frame);

        c = (char)cvWaitKey(delay);
        if (c == 27) break;
    }

    return 0;
}
void getBrisque(cv::Mat frame, svm_model *model)
{
  float score = jd_brisque::computescore(frame, model);
  std::cout << "Frame " << (*framecount) << " score " << score << std::endl;
}

double getPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    Scalar s = sum(s1);        // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double mse  = sse / (double)(I1.channels() * I1.total());
        double psnr = 10.0 * log10((255 * 255) / mse);
        return psnr;
    }
}