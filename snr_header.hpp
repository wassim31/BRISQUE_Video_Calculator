#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
double calculateSNR(const cv::Mat& originalImage, const cv::Mat& noisyImage) {
    cv::Scalar meanSignal = cv::mean(originalImage);
    cv::Mat noise = noisyImage - originalImage;
    cv::Scalar stddevNoise, meanNoise;
    cv::meanStdDev(noise,meanNoise, stddevNoise);
    std::cout << "derivation : " << stddevNoise[0] << " noiseMean: " << meanNoise[0] << "\n";
    /* here i'm testing if the calculated standard-derivation & mean 
    of the noise is close to the theoritical one */
    double snr = 10 * std::log10((meanSignal[0]) / (stddevNoise[0]));

    return snr;
}

cv::Mat addNoise(const cv::Mat originalImage) {
		cv::Mat noise_matrix = cv::Mat(originalImage.size(), originalImage.type());
		cv::randn(noise_matrix,0,1);
        return originalImage + noise_matrix;
}
        