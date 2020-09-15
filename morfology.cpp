#include "morfology.h"

void morfology::draw(mm morfologyType, kernel kernelShape, Color foreground, Color background, QImage* img){
    if(morfologyType == opening){
        morfology::draw(erosion, kernelShape, foreground, background, img);
        morfologyType = dilation;
    }
    else if(morfologyType == closing){
        morfology::draw(dilation, kernelShape, foreground, background, img);
        morfologyType = erosion;
    }

    long tmpPosition;
    int width = img->width(), height = img->height();
    std::vector<int> toCheck, toChange;
    Color primaryColor, secondaryColor;

    if(kernelShape == cube)
        toCheck = {-width-1, -width, -width+1, -1, 1, width-1, width, width+1};
    else if(kernelShape == cross)
        toCheck = {-width, -1, 1, width};

    primaryColor = (morfologyType == dilation)?foreground:background;       //dylacja -> wypełnienie kolorem pierwszoplanowym
    secondaryColor = (morfologyType == dilation)?background:foreground;      //erozja -> wypełnienie kolorem tła

    for( long i = 0; i < 4 * width * height; i += 4){
        if(secondaryColor == &img->bits()[i]){
            for(unsigned long k=0; k < toCheck.size(); k++){
                tmpPosition = i + 4 * toCheck[k];
                if(tmpPosition >= 0 && tmpPosition < width*height*4
                   && (tmpPosition/4)%width != 0)                               //pomiń piksel przechodzący do nowej linii
                    if(primaryColor == &(img->bits()[tmpPosition])){
                        toChange.push_back(i);                              //zapamietaj ktore piksele zmienic
                        break;
                    }
            }
        }
    }
    while(toChange.size() > 0){
        primaryColor.convertToUChar(&img->bits()[toChange.back()]);         //zamaluj oznaczone piksele
        toChange.pop_back();
    }
}

