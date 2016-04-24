#ifndef InputProcessor_h
#define InputProcessor_h

#include "Types.h"

// ---- Forward declarations ----

void populateDigitImageRow(ifstream&, DigitImage&, int);
void populateDigitImage(ifstream&, DigitImage&);

// ---- Forward declarations ----

const int PIXEL_DIGIT_NUMBERS = 3;
const char COMMA = ',';

// ---- Functions ----

void populateDigitImage(ifstream &input, DigitImage &image) {
    // Skip First Line
    while(input.get() != '\n');
    
	// Get Label
	char charLabel;
	input.get(charLabel);
	image.label = (int) charLabel;

	char charPixel[PIXEL_DIGIT_NUMBERS + 1];
	auto imageSideSize = image.pixels.size();

	for (auto i = 0; i < imageSideSize; i++) {
		for (auto j = 0; j < imageSideSize; j++) {
			// Get Pixel
			input.getline(charPixel, PIXEL_DIGIT_NUMBERS + 1, COMMA);
			image.pixels[i][j] = atoi(charPixel);
		}
	}
}

#endif
