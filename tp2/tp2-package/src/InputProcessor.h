#ifndef InputProcessor_h
#define InputProcessor_h

#include "Types.h"

void populateDigitImageWithExtras(DigitImages &images, DigitImage &image, istream &input) {
    /* Label */
    string label, pixelStr;
    getline(input, label, ',');
    int l = stoi(label);
    images.labels.push_back(l);
    image.label = l;
    //PLSDA purposes
    vector<double> labelY(LABELS_QTY, -1);
    labelY[l] = 1;
    images.labelY.push_back(labelY);
    for (int i = 0; i < LABELS_QTY; ++i)
        images.labelYMeans[i] += labelY[i];

    /* Pixel fetching and mean sum */
    int i = 0;
    while(getline(input, pixelStr, ',')){
        int pixel = stoi(pixelStr);
        image.pixels[i] = pixel;
        images.means[i] += pixel;
        i++;
    }
}

void populateDigitImages(DigitImages &imagesTrain, DigitImages &imagesTest, string &inFileDir, istream &inputStream) {
    /* DigitImages sizes initialization */
    imagesTrain.init();
    imagesTest.init();

    /* Input file fetching */
    string nameInFile = inFileDir + "train.csv";
    ifstream input(nameInFile);

    // First line is not needed, skip it
    string line, isTrain;
    getline(input, line);

    /* Digit Images  population */
    while(getline(input, line)){
        getline(inputStream, isTrain, ' ');
        stringstream lineStream(line);
        /* Particular Digit Image Population */
        DigitImage image;
        if(isTrain == "1"){
            image.pixels = vector<double>(DEFAULT_IMAGE_SIZE);
            populateDigitImageWithExtras(imagesTrain, image, lineStream);
            imagesTrain.centralized.push_back(image.pixels);
            imagesTrain.centralizedPLSDA.push_back(image.pixels);
            imagesTrain.images.push_back(image);
        } else{
            image.pixels = vector<double>(DEFAULT_IMAGE_SIZE);
            populateDigitImageWithExtras(imagesTest, image, lineStream);
            imagesTest.images.push_back(image);
            imagesTest.centralized.push_back(image.pixels);
            imagesTest.centralizedPLSDA.push_back(image.pixels);
        }
    }
    input.close();
}

#endif
