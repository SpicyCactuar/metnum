#ifndef Types_h
#define Types_h

#include "Imports.h"

const auto DEFAULT_IMAGE_SIDE_SIZE = 28;

using Matrix = vector<vector<double> >;
using Pixel = int;
using PixelMatrix = vector<vector<Pixel>>;

struct DigitImage {

	DigitImage(int label = -1, int imageSideSize = DEFAULT_IMAGE_SIDE_SIZE) : 
	pixels(imageSideSize, vector<Pixel>(imageSideSize, -1)),
	label(label) {}

	int label;
	PixelMatrix pixels;

	void printPixels(ostream &output) {
		auto size = pixels.size();
		for (auto i = 0; i < size; i++) {
			output << '[';
			for (auto j = 0; j < size; j++) {
				output << pixels[i][j];

				if(j < size - 1) { output << ','; }
			}
			output << ']' << endl;
		}
	}

	void prettyPrint(ostream &output) {

		output << endl << "LABEL" << endl << "=====" << endl << endl;
		output << label << endl << endl;

		output << "PIXELS" << endl << "======" << endl << endl;
		printPixels(output);

	}
};

#endif
