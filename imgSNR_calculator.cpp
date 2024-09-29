#include "snr_header.hpp"
/* you'll find the defintion of the functions 
in the header i built */
#include <opencv2/quality/qualitybrisque.hpp>


double calculateSNR (const cv::Mat& originalImage, const cv::Mat& noisyImage);
cv::Mat addNoise (const cv::Mat originalImage);

int main() 
{
    cv::Mat originalImage = cv::imread("lenna.png", cv::IMREAD_GRAYSCALE);
    
    cv::Mat noisyImage = addNoise(originalImage);

    if (originalImage.empty() || noisyImage.empty() ) {
        std::cout << "Error: Could not load images!" << std::endl;
        return -1;
    }
    cv::imshow("originalImage", originalImage);
    cv::imshow("noisyImage Image", noisyImage);
    cv::waitKey(); 
    
    double snr = calculateSNR(originalImage, noisyImage);
    std::cout << "SNR (in dB): " << snr << std::endl;

    return 0;
}
