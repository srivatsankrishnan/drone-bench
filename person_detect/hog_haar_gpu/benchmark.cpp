#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "objdetect.hpp"

using namespace std;

void help(string prog_name) {
	string message = "Object detection benchmark.\n\noptional arguments:\n  -h, --help            show this help message and exit\n  --data DATA           Location of dataset. Default: ..\n  --max_samples M_S\n                        Maximum number of samples to test. Default: 614\n";

	cout << "usage: " << prog_name << " [-h] [--data DATA] [--max_samples M_S]" << endl << endl;
	cout << message;
}

int str2int(string s) {
	int result = 0;

	for (int i = 0; i < s.size(); i++) {
		result *= 10;
		result += int(s[i] - '0');
	}

	return result;
}

int main(int argc, const char ** argv) {
	string dataset = "..";
	int max_samples = 1000;
	double total_time, avg;
	int samples;
	std::ifstream pos_lst;

    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "--data")
            dataset = argv[++i];
        else if (string(argv[i]) == "--max_samples")
        {
        	max_samples = str2int(string(argv[++i]));
        }
        else if (string(argv[i]) == "--help" || string(argv[i]) == "-h")
        {
            help(string(argv[0]));
            return 0;
        }
    }

    if (dataset[dataset.length() - 1] == '/') {
        dataset = dataset.substr(0, dataset.size()-1);
    }

    // Initialize Haar and HOG object detectors
    initialize_objdetect();

    // Test HOG
	total_time = 0;
	samples = 0;

	pos_lst.open((dataset + "/dataset/pos.lst").c_str());
	for (string line; pos_lst >> line;) {
    	cv::Mat img;
    	string image_name = dataset + "/" + line;

#if CV_MAJOR_VERSION==3
    	img = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
#else
    	img = cv::imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
#endif

    	struct coord result = find_target_hog_gpu(img);

    	total_time += result.t;
    	samples++;

    	if (samples >= max_samples)
    		break;
	}

	avg = total_time / (double) samples;
	cout << "Object detection algorithm: find_target_hog_gpu" << endl;
	cout << "\tAverage time to detect targets (s): " << avg << endl;
	cout << "\tFPS: " << 1.0/avg << endl;

	pos_lst.close();

    // Test Haar
	total_time = 0;
	samples = 0;

	pos_lst.open((dataset + "/dataset/pos.lst").c_str());
	for (string line; pos_lst >> line;) {
    	cv::Mat img;
    	string image_name = dataset + "/" + line;

#if CV_MAJOR_VERSION==3
    	img = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
#else
    	img = cv::imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
#endif

    	struct coord result = find_target_haar_gpu(img);

    	total_time += result.t;
    	samples++;

    	if (samples >= max_samples)
    		break;
	}

	avg = total_time / (double) samples;
	cout << "Object detection algorithm: find_target_haar_gpu" << endl;
	cout << "\tAverage time to detect targets (s): " << avg << endl;
	cout << "\tFPS: " << 1.0/avg << endl;

	return 0;
}