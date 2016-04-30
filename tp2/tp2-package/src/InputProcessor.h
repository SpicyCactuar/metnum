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
    vector<double> labelY(images.labelYMedians.size(), -1);
    labelY[l] = 1;
    images.labelY.push_back(labelY);
    for (int i = 0; i < images.labelYMedians.size(); ++i)
        images.labelYMedians[i] += labelY[i];

    /* Pixel fetching and median sum */
    int i = 0;
    while(getline(input, pixelStr, ',')){
        int pixel = stoi(pixelStr);
        image.pixels[i] = pixel;
        images.medians[i] += pixel;
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
        // si es de train, la proceso a full, sino, solo me interesa la imagen
        if(isTrain == "1"){
            image.pixels = Pixels(imagesTrain.imgSizeSqr);
            populateDigitImageWithExtras(imagesTrain, image, lineStream);
            // Advance iterator to next image
            imagesTrain.correlation.push_back(image.pixels);
            imagesTrain.correlationPLSDA.push_back(image.pixels);
            imagesTrain.images.push_back(image);
        } else{
            image.pixels = Pixels(imagesTest.imgSizeSqr);
            populateDigitImageWithExtras(imagesTest, image, lineStream);
            // Advance iterator to next image
            imagesTest.images.push_back(image);
        }
    }
    input.close();
}

#endif
