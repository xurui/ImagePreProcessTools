#include<opencv2/opencv.hpp>
#include <iostream>

class PreProcessTool {
public:
	void dataset_read(const std::string& pre_path, const std::string& after_path);
	void image_resize(const std::string& pre_path, const std::string& after_path, int shrink, int width, int height);
	void image_HistEqualize_pre_process(const std::string& pre_path, const std::string& after_path);
	void image_flip_process(const std::string& pre_path, const std::string& after_path);
	void images_from_video(const std::string& s, const std::string& after_path);
	void images_to_video(const std::string& pre_path, const std::string& s);
	void smoothing_image(const std::string& pre_path, const std::string& after_path);
	void merge_videos(const std::string& pre_path, const std::string& s);
	void detect_edge_image(const std::string& pre_path, const std::string& after_path);
	void convert_color_space_image(const std::string& pre_path, const std::string& after_path);
};
