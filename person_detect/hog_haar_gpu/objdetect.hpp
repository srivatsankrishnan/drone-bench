#ifndef OBJDETECT_HPP

#include <opencv2/opencv.hpp>

struct coord {
	double x, y, w, h, t;
};

int initialize_objdetect();

struct coord find_target_haar_gpu(cv::Mat frame);
struct coord find_target_hog_gpu(cv::Mat frame);

#define OBJDETECT_HPP
#endif