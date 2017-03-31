#include "objdetect.hpp"
#include <vector>
#include <string>
#include <ctime>

#include <opencv2/opencv.hpp>
#if CV_MAJOR_VERSION==3
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/highgui/highgui_c.h>
#else
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#endif

#if CV_MAJOR_VERSION==3
cv::Ptr<cv::cuda::CascadeClassifier> haar;
cv::Ptr<cv::cuda::HOG> hog;
#else
cv::gpu::CascadeClassifier_GPU * haar;
cv::gpu::HOGDescriptor * hog;
#endif

#define haar_scaleFactor 1.05
#define haar_minNeighbors 3

int initialize_objdetect()
{
#if CV_MAJOR_VERSION==3
	if(cv::cuda::getCudaEnabledDeviceCount() == 0)
		return -1;
	cv::cuda::setDevice(0);

	// Initialize built-in OpenCV detectors
    haar = cv::cuda::CascadeClassifier::create("haarcascade_fullbody.xml");
    haar->setScaleFactor(haar_scaleFactor);
    haar->setMinNeighbors(haar_minNeighbors);

    hog = cv::cuda::HOG::create();
	hog->setSVMDetector(hog->getDefaultPeopleDetector());
#else
    haar = new cv::gpu::CascadeClassifier_GPU;
    haar->load("haarcascade_fullbody.xml");
    haar->findLargestObject = false;

    hog = new cv::gpu::HOGDescriptor;
    hog->setSVMDetector(cv::gpu::HOGDescriptor::getDefaultPeopleDetector());
#endif
    // Warm up GPUS    
    for (int i = 0; i < 3; i++) {
        cv::Mat blank_frame(360, 360, CV_8UC1);
        find_target_haar_gpu(blank_frame);
        find_target_hog_gpu(blank_frame);
    }

    return 0;
}

struct coord find_target_haar_gpu(cv::Mat frame)
{
	struct coord result = {-1.0, -1.0, -1.0, -1.0};
	std::clock_t start, end;

#if CV_MAJOR_VERSION==3
	cv::cuda::GpuMat objbuf;
	std::vector<cv::Rect> targets;

	start = std::clock();

	cv::cuda::GpuMat image_gpu(frame);

	haar->detectMultiScale(image_gpu, objbuf);
	haar->convert(objbuf, targets);

	end = std::clock();

	if (targets.size() > 0) {
		cv::Rect target = targets[0];
#else
	int detections_num;
    cv::Mat faces_downloaded, frameDisp;
    cv::gpu::GpuMat frame_gpu, facesBuf_gpu;

	start = std::clock();

    frame_gpu.upload(frame);

    detections_num = haar->detectMultiScale(frame_gpu, facesBuf_gpu, haar_scaleFactor, haar_minNeighbors);
    facesBuf_gpu.colRange(0, detections_num).download(faces_downloaded);

	end = std::clock();

    if (detections_num > 0) {
    	cv::Rect target = faces_downloaded.ptr<cv::Rect>()[0];
#endif
		result.x = target.x;
		result.y = target.y;
		result.w = target.width;
		result.h = target.height;
    }

    result.t = (end - start) / (double)(CLOCKS_PER_SEC);

	return result;
}

struct coord find_target_hog_gpu(cv::Mat frame)
{
	struct coord result = {-1.0, -1.0, -1.0, -1.0};
	std::clock_t start, end;

	std::vector<cv::Rect> targets;
#if CV_MAJOR_VERSION==3
	start = std::clock();

	cv::cuda::GpuMat image_gpu(frame);

	hog->detectMultiScale(image_gpu, targets);
#else
    cv::gpu::GpuMat gpu_img;

	start = std::clock();

    gpu_img.upload(frame);

    hog->detectMultiScale(gpu_img, targets);
#endif

	end = std::clock();

	if (targets.size() > 0) {
		cv::Rect target = targets[0];

		result.x = target.x;
		result.y = target.y;
		result.w = target.width;
		result.h = target.height;
	}

    result.t = (end - start) / (double)(CLOCKS_PER_SEC);

	return result;
}

