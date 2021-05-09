#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<vector>

using namespace std;
using namespace cv;



struct Matrix
{
    const int vectorRows = 20 ;
    const int vectorColumns = 20;
    vector<vector<string>> vec( vectorColumns , vector<string> (vectorRows));
};

//uploadImageInfo performs the function of loading the base structure and all its information necessary to perform the search for the image
Matrix uploadImageInfo(){
    cout <<" no Mori"<< endl;
    Matrix imageMatrix;
    cout <<"Mori"<< endl;
    string imagePath = "C:/Users/Sebastian/Pictures/Prueba.jpg";
    int blueChannel;
    int greenChannel;
    int redChannel;
    Mat colorImage;
    colorImage = imread(imagePath);
    cout<<"Antes del for"<<endl;
    for (int imageRows = 0; imageRows < colorImage.rows; imageRows++){
        for (int imageColumns = 0; imageColumns < colorImage.cols; imageColumns++) {
            redChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[2];
            greenChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[1];
            blueChannel = colorImage.at<Vec3b>(imageRows, imageColumns)[0];

            string rgbValue = to_string(redChannel) +","+ to_string(greenChannel)  +","+ to_string(blueChannel);
            imageMatrix.vec[imageRows][imageColumns] = rgbValue;
        }
    }
    return imageMatrix;

}

/*CreateDataHash performs the function of analyzing the tones of line segments extracted from the vectors,
looks for a match with the second image and stores them in the hash if they match*/
void createDataHash(){
    
}

/*
int *createSecondImageArrayTrend(){
    const int imageRows = 3840 ;
    const int imageColumns = 2160;
    const int minimumCutoutSize = 108;
    int arrayTrend[(imageColumns/(minimumCutoutSize/2))*3];
}
*/

int main() {
    Matrix imageMatrix;
    imageMatrix = uploadImageInfo();
    cout<<imageMatrix.vec[2344][1999]<<endl;
    return 0;
}