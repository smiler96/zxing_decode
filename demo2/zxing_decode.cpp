#include "zxing_decode.h"

const char* my_code_type[] = {
	"NONE",
	"AZTEC",
	"CODABAR",
	"CODE_39",
	"CODE_93",
	"CODE_128",
	"DATA_MATRIX",
	"EAN_8",
	"EAN_13",
	"ITF"
	"MAXICODE",
	"PDF_417",
	"QR_CODE",
	"RSS_14",
	"RSS_EXPANDED",
	"UPC_A",
	"UPC_E",
	"UPC_EAN_EXTENSION"
};

bool decode_by_zxing(cv::Mat& matGray, std::string& code)
{
	zxing::Ref<zxing::LuminanceSource> source(new MatSource(matGray));
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	//zxing::Ref<zxing::Reader> reader;
	//reader.reset(new zxing::oned::EAN13Reader);
	//reader.reset(new zxing::oned::Code128Reader);
	zxing::oned::MultiFormatOneDReader reader(zxing::DecodeHints::DEFAULT_HINT);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::HybridBinarizer(source));
	//zxing::Ref<zxing::Binarizer> binarizer(new zxing::);
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	try
	{
		zxing::Ref<zxing::Result> result(reader.decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::DEFAULT_HINT)));
		//zxing::Ref<zxing::Result> result(zxing::MultiFormatReader().decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::EAN_13_HINT)));
		code = result->getText()->getText();
		fprintf(stdout, "recognization result: %s\n", code.c_str());
		std::cout << "barcode type is: " << my_code_type[result->getBarcodeFormat().value] << "\n\n";
		return true;
	}
	catch (zxing::Exception& e)
	{
		std::cout << "Error: " << e.what() << "\n";
		return false;
	}
	
}
