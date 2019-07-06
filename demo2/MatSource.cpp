#include "MatSource.h"
#include <zxing/common/IllegalArgumentException.h>

zxing::ArrayRef<char> MatSource::getRow(int y, zxing::ArrayRef<char> row) const {

	int width_ = getWidth();
	if (!row)
		row = zxing::ArrayRef<char>(width_);
	const char *p = cvImage.ptr<char>(y);
	for (int x = 0; x<width_; ++x, ++p)
		row[x] = *p;
	return row;
}

zxing::ArrayRef<char> MatSource::getMatrix() const {

	int width_ = getWidth();
	int height_ = getHeight();
	zxing::ArrayRef<char> matrix = zxing::ArrayRef<char>(width_*height_);
	for (int y = 0; y < height_; ++y)
	{
		const char *p = cvImage.ptr<char>(y);
		for (int x = 0; x < width_; ++x, ++p)
		{
			matrix[y*width_ + x] = *p;
		}
	}
	return matrix;
}
