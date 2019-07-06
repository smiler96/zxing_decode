#ifndef ZXING_DECODE
#define ZXING_DECODE

#include <string>
#include "MatSource.h"

bool decode_by_zxing(cv::Mat& matGray, std::string& code);


#endif // !ZXING_DECODE

