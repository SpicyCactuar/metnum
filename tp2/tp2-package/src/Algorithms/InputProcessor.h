#ifndef InputProcessor_h
#define InputProcessor_h

#include "Types.h"

// -------- Forward Declarations --------

void populateDigitImageWithExtras(DigitImagesHelper&, DigitImage&, istream&, int);

// -------- Input population --------

void populateDigitImagesHelper(DigitImagesHelper &imagesHelper, string &inFileDir, int size = DEFAULT_IMAGE_SIDE_SIZE, int amount = DEFAULT_IMAGES_AMOUNT) {

	/* DigitImagesHelper sizes initialization */
    imagesHelper.init(size, amount);

    /* Input file fetching */
    string nameInFile = inFileDir + "train.csv";
    ifstream input(nameInFile);

    // First line is not needed, skip it
    string line;
    getline(input, line);

    /* Digit Images Helper population */
    int k = 0;
    while(getline(input, line) && k < amount){        
        stringstream lineStream(line);

        /* Particular Digit Image Population */
        DigitImage image;
    	image.pixels = Pixels(imagesHelper.img_size_sqr, 0.0);

    	populateDigitImageWithExtras(imagesHelper, image, lineStream, k);

    	// Advance iterator to next image
    	k++; 
        
        imagesHelper.correlation.push_back(image.pixels);
    }
    input.close();

    /* Median calculation */
	for (int i = 0; i < imagesHelper.img_size_sqr; ++i) {
        imagesHelper.medians[i] /= imagesHelper.samples;
    }

    /* Correlation calculation */
    for (int i = 0; i < imagesHelper.samples; ++i) {
        for (int j = 0; j < imagesHelper.img_size_sqr; ++j){
            imagesHelper.correlation[i][j] = (imagesHelper.correlation[i][j] - imagesHelper.medians[j]) / sqrt(imagesHelper.samples - 1);
        }
    }
}

void populateDigitImageWithExtras(DigitImagesHelper &imagesHelper, DigitImage &image, istream &input, int currentImage) {

	/* Label */
    string label;
    getline(input, label, ',');
    imagesHelper.labels[currentImage] = stoi(label);
    
    /* Pixel fetching and median sum */
    int i = 0;
    string pixelStr;
    while(getline(input, pixelStr, ',')){
        int pixel = stoi(pixelStr);
        image.pixels[i] = pixel;
        imagesHelper.medians[i] += pixel;
        i++;
    }	
}

#endif
