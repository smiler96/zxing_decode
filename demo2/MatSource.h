#ifndef __MAT_SOURCE_H_
#define __MAT_SOURCE_H_

//#include <zxing\ZXing.h>
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>

#include <fstream>
#include "zxing/LuminanceSource.h"
#include "zxing/common/Counted.h"
//#include "zxing/Reader.h"
//#include "zxing/common/GlobalHistogramBinarizer.h"
#include "zxing\common\HybridBinarizer.h"
#include "zxing/DecodeHints.h"
//#include "zxing/MultiFormatReader.h"
//#include "zxing/oned/CodaBarReader.h"
//#include "zxing/oned/Code39Reader.h"
//#include "zxing/oned/Code93Reader.h"
//#include "zxing/oned/Code128Reader.h"
//#include "zxing\oned\EAN13Reader.h"
#include "zxing\oned\MultiFormatOneDReader.h"

class MatSource : public zxing::LuminanceSource {
private:
    cv::Mat cvImage;

public:

	MatSource(cv::Mat &image): LuminanceSource(image.cols, image.rows)
	{
		cvImage = image.clone();
	}
	~MatSource()
	{
	}

	int getWidth() const { return cvImage.cols; }
	int getHeight() const { return cvImage.rows; }

    zxing::ArrayRef<char> getRow(int y, zxing::ArrayRef<char> row) const;
    zxing::ArrayRef<char> getMatrix() const;

};

#endif /* __MAT_SOURCE_H_ */
