#ifndef InputProcessor_h
#define InputProcessor_h

#include "Types.h"

void medianAndCorrelationCalc(DigitImagesHelper &imagesHelper){
    for (int i = 0; i < imagesHelper.img_size_sqr; ++i)
        imagesHelper.medians[i] /= imagesHelper.samples;
    for (int i = 0; i < imagesHelper.samples; ++i)
        for (int j = 0; j < imagesHelper.img_size_sqr; ++j)
            imagesHelper.correlation[i][j] = (imagesHelper.correlation[i][j] - imagesHelper.medians[j]) / sqrt(imagesHelper.samples - 1);
}

void populateDigitImageWithExtras(DigitImagesHelper &imagesHelper, DigitImage &image, istream &input, int currentImage) {
    /* Label */
    string label, pixelStr;
    getline(input, label, ',');
    image.label = stoi(label);

    /* Pixel fetching and median sum */
    int i = 0;
    while(getline(input, pixelStr, ',')){
        int pixel = stoi(pixelStr);
        image.pixels[i] = pixel;
        imagesHelper.medians[i] += pixel;
        i++;
    }
}

void populateDigitImagesHelper(DigitImagesHelper &imagesHelperTrain, DigitImagesHelper &imagesHelperTest, string &inFileDir, istream &inputStream) {
    /* DigitImagesHelper sizes initialization */
    imagesHelperTrain.init();
    imagesHelperTest.init();

    /* Input file fetching */
    string nameInFile = inFileDir + "train.csv";
    ifstream input(nameInFile);

    // First line is not needed, skip it
    string line, isTrain;
    getline(input, line);

    /* Digit Images Helper population */
    int kTrain = 0, kTest = 0;
    while(getline(input, line)){
        getline(inputStream, isTrain, ' ');
        stringstream lineStream(line);
        /* Particular Digit Image Population */
        DigitImage image;
        // si es de train, la proceso a full, sino, solo me interesa la imagen
        if(isTrain == "1"){
            image.pixels = Pixels(imagesHelperTrain.img_size_sqr, 0.0);
            populateDigitImageWithExtras(imagesHelperTrain, image, lineStream, kTrain);
            // Advance iterator to next image
            kTrain++;
            imagesHelperTrain.correlation.push_back(image.pixels);
            imagesHelperTrain.images.push_back(image);
        } else{
            image.pixels = Pixels(imagesHelperTest.img_size_sqr, 0.0);
            populateDigitImageWithExtras(imagesHelperTest, image, lineStream, kTest);
            // Advance iterator to next image
            kTest++;
            imagesHelperTest.images.push_back(image);
        }
    }
    cout << kTrain << " " << kTest << endl;
    imagesHelperTrain.samples = kTrain;
    imagesHelperTest.samples = kTest;
    input.close();

    medianAndCorrelationCalc(imagesHelperTrain);
}

#endif
