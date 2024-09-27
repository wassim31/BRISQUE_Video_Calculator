#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
double calculateSNR(const cv::Mat& original, const cv::Mat& noisy) {
    // Step 1: Calculate the mean of the original image (signal)
    Scalar meanSignal = cv::mean(original);

    // Step 2: Compute the noise (difference between noisy and original image)
    cv::Mat noise = noisy - original;

    // Step 3: Calculate the standard deviation of the noise
    cv::Scalar stddevNoise;
    cv::meanStdDev(noise, cv::noArray(), stddevNoise);

    // Step 4: Compute the SNR (in dB)
    double snr = 10 * std::log10((meanSignal[0] * meanSignal[0]) / (stddevNoise[0] * stddevNoise[0]));

    return snr;
}

cv::Mat addNoise(const cv::Mat original) {
		cv::Mat noise_matrix = cv::Mat(original.size(), original.type());
		cv::randn(noise_matrix,0,25);
        original+=noise_matrix;
        return original;
}
        

				
int main() {
    // Step 1: Load the original and noisy images (Grayscale)
    cv::Mat original = cv::imread("original_image.jpg", cv::IMREAD_GRAYSCALE);
    
    cv::Mat noisy = addNoise(original);

    // Check if the images were loaded successfully
    if (original.empty() || noisy.empty()) {
        std::cout << "Error: Could not load images!" << std::endl;
        return -1;
    }

    // Step 2: Calculate the SNR
    double snr = calculateSNR(original, noisy);
    std::cout << "SNR (in dB): " << snr << std::endl;

    return 0;
}