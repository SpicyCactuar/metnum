#ifndef InputProcessor_h
#define InputProcessor_h

#include "Types.h"

void populateDigitImageWithExtras(DigitImages &images, istream &input) {
    /* Label */
    string label, pixelStr;
    getline(input, label, ',');
    int l = stoi(label);
    images.labels.push_back(l);
    //PLSDA purposes
    vector<double> labelY(LABELS_QTY, -1);
    labelY[l] = 1;
    images.labelY.push_back(labelY);
    for (int i = 0; i < LABELS_QTY; ++i)
        images.labelYMeans[i] += labelY[i];

    /* Pixel fetching and mean sum */
    int i = 0;
    vector<double> image(DEFAULT_IMAGE_SIZE);
    while(getline(input, pixelStr, ',')){
        int pixel = stoi(pixelStr);
        image[i] = pixel;
        images.means[i] += pixel;
        i++;
    }
    images.images.push_back(image);
    images.centralized.push_back(image);
    images.centralizedPLSDA.push_back(image);
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
        if(isTrain == "1")
            populateDigitImageWithExtras(imagesTrain, lineStream);
        else
            populateDigitImageWithExtras(imagesTest, lineStream);
    }
    input.close();
}

#endif
