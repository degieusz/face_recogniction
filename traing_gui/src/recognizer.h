#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/contrib/contrib.hpp"
namespace face {

class recognizer
{
public:
	bool detect(std::vector<cv::Mat>& detected_faces, const cv::Mat& input);

	bool recognize(const cv::Mat& detected_face,
	 const cv::Ptr<cv::FaceRecognizer>& trained_recognizer) const;

	bool load_face_cascade();
private:
	bool detect_impl(std::vector<cv::Mat>& detected_faces, const cv::Mat& input);
	cv::CascadeClassifier cascade;
	cv::Mat frame_to_auth;
};

}

#endif // RECOGNIZER_H
