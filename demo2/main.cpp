#include <string>
#include <fstream>
#include <zxing/LuminanceSource.h>
#include <zxing/common/Counted.h>
#include <zxing/Reader.h>

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/DecodeHints.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/oned/CodaBarReader.h>
#include <zxing/oned/Code39Reader.h>
#include <zxing/oned/Code93Reader.h>
#include <zxing/oned/Code128Reader.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "MatSource.h"

int main()
{
	std::string image_name = "./image/2.jpg";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source(new MatSource(matGray));
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::Code128Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::CODE_128_HINT)));

	/*std::string txt = "Code128.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
	fprintf(stderr, "fail to open file: %s\n", txt.c_str());
	return -1;
	}
	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());*/

	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	zxing::ArrayRef< zxing::Ref<zxing::ResultPoint> > rpoints = result->getResultPoints();
	cv::Point point0(rpoints[0]->getX()+30, rpoints[0]->getY()+50);
	cv::Point point1(rpoints[1]->getX()-30, rpoints[1]->getY()-50);
	cv::putText(matSrc, str2, cv::Point(rpoints[1]->getX() - 10, rpoints[1]->getY() - 10), 1, 2, cv::Scalar(0, 0, 255));
	cv::rectangle(matSrc, cv::Rect(point1, point0), cv::Scalar(0, 0, 255), 2);
	cv::imshow("locate", matSrc);
	cv::waitKey(0);
	cv::imwrite("image/2res.jpg", matSrc);

	return 0;
}