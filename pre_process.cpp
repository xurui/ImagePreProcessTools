#include"pre_process.h"

using namespace cv;
using namespace std;

/*image convertion jpgTopng*/
void PreProcessTool::dataset_read(const string& pre_path, const string& after_path) {
	vector<String> image_dataset;
	Mat convert_temp;
	glob(pre_path + "/*.jpg", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		convert_temp = imread(image_dataset[i]);
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", convert_temp);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}


/*resize image*/
void PreProcessTool::image_resize(const string& pre_path, const string& after_path, int shrink, int width, int height) {
	vector<String> image_dataset;
	Mat read_temp;
	Mat convert_temp;
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		read_temp = imread(image_dataset[i]);
		resize(read_temp, convert_temp, cv::Size(read_temp.cols / shrink, read_temp.rows / shrink), -1, -1, INTER_AREA);
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", convert_temp);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}


/*pre-process image (Histogram Equalization)*/
void PreProcessTool::image_HistEqualize_pre_process(const string& pre_path, const string& after_path) {
	vector<String> image_dataset;
	Mat image;
	enum {CHANNEL_MAX = 3};
	vector<Mat> channel_image;
	Mat after_pro_image;
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); ++i) {
		image = imread(image_dataset[i]);
		split(image, channel_image);
		for (int j = 0; j < CHANNEL_MAX; ++j){
			equalizeHist(channel_image[j], channel_image[j]);
		}
		merge(channel_image, after_pro_image);
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", after_pro_image);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}


/*flip image*/
void PreProcessTool::image_flip_process(const string& pre_path, const string& after_path) {
	vector<String> image_dataset;
	Mat read_temp;
	Mat convert_temp;
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		read_temp = imread(image_dataset[i]);
		flip(read_temp, convert_temp,1);
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", convert_temp);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}

/*extract images from video*/
void PreProcessTool::images_from_video(const string& s, const string& after_path) {
	VideoCapture capture(s);
	if (!capture.isOpened())
        cout << "fail to open!"<< endl;
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	Mat img;
	int i = 3897;
	while (capture.read(img)) {
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", img);
		cout << "saving "<< i <<"image, please wait......" << endl;
		++i;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
}

/*combine images into video*/
void PreProcessTool::images_to_video(const string& pre_path, const string& s) {
	vector<String> image_dataset;
	Mat read_temp;
	Size framesize = Size(640,480);
	const int rate = 30;
	const int cv_fourcc = CV_FOURCC('X','V','I','D');
	VideoWriter video(s, cv_fourcc, rate,framesize,1);
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		read_temp = imread(image_dataset[i]);
		video << read_temp;
	}
}

/*merge several videos into one video*/
void PreProcessTool::merge_videos(const string& pre_path, const string& s) {
	vector<String> video_dataset;
	vector<Mat> image_seq;
	Mat img_from_video, img_to_video;
	Size framesize = Size(640,480);
	const int rate = 30;
	const int cv_fourcc = CV_FOURCC('X','V','I','D');
	glob(pre_path + "/*.avi", video_dataset);
	VideoWriter video(s, cv_fourcc, rate, framesize, 1);
	for (int i = 0; i < video_dataset.size(); i++) {
		VideoCapture capture(video_dataset[i]);
		if (!capture.isOpened())
			cout << "fail to open!"<< endl;
		long totalFrameNumber = static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT));
		long frame_num = 0;
		while (frame_num < totalFrameNumber) {
			capture.read(img_from_video);
			video << img_from_video;
			frame_num++;
		}
		std::cout << "We have merged " << i + 1 << " videos,  please wait......" << std::endl;
	}
}

void PreProcessTool::smoothing_image(const string& pre_path, const string& after_path) {
	vector<String> image_dataset;
	Mat read_temp;
	Mat convert_temp;
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		read_temp = imread(image_dataset[i]);
		dilate(read_temp, read_temp, cv::Mat(), cv::Point(-1,-1), 1, 1, 1);
		medianBlur(read_temp, read_temp, 3);
		dilate(read_temp, convert_temp, cv::Mat(), cv::Point(-1,-1), 1, 1, 1);
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", convert_temp);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}

/*edge detection for images*/
void PreProcessTool::detect_edge_image(const string& pre_path, const string& after_path) {
	vector<String> image_dataset;
	Mat read_temp;
	Mat convert_temp;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	const int ddepth = CV_16S;
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		read_temp = imread(image_dataset[i]);
		cvtColor(read_temp, read_temp, CV_RGB2GRAY);
		/*equalizeHist(read_temp, convert_temp);*/
		//cv::Canny(read_temp, convert_temp, 40, 120);  //Canny thresholds input with a ratio 1:3
		cv::Sobel(read_temp, grad_x, ddepth, 1, 0, 3);
		convertScaleAbs( grad_x, abs_grad_x );
		Sobel( read_temp, grad_y, ddepth, 0, 1, 3);
		convertScaleAbs( grad_y, abs_grad_y );

		// // Total Gradient (approximate)
		addWeighted( abs_grad_x, 0, abs_grad_y, 1, 0, convert_temp );
		bool ok = imwrite(after_path + "/" + format("%d", i) + ".png", convert_temp);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}

/*convert images from rgb to HSV/YUV*/
void PreProcessTool::convert_color_space_image(const string& pre_path, const string& after_path) {
	vector<String> image_dataset;
	Mat read_temp;
	std::vector<cv::Mat> splited;
	Mat convert_temp;
	const int ddepth = CV_16S;
	glob(pre_path + "/*.png", image_dataset);
	for (int i = 0; i < image_dataset.size(); i++) {
		read_temp = imread(image_dataset[i]);
		/*convert image to from rgb to YUV(CV_BGR2YUV) or to HSV(CV_BGR2HSV)*/
		cvtColor(read_temp, read_temp, CV_BGR2HSV);
		cv::split(read_temp, splited);
		/*extract image in channel0(H/Y), channel1(S/U), channel2(V)*/
		convert_temp = splited[1];
		bool ok = imwrite(after_path +"/"+ format("%d", i) +".png", convert_temp);
		cout << "saving "<< i <<"image, please wait......" << endl;
		if (!ok)
			CV_Error(CV_StsInternal, "ERROR: image cannot write!");
	}
	// Check: files not empty
	CV_Assert(image_dataset.size() != size_t(0));
}
