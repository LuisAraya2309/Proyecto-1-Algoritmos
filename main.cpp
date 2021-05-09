#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<vector>

using namespace std;
using namespace cv;


//uploadImageInfo performs the function of loading the base structure and all its information necessary to perform the search for the image
void uploadImageInfo(vector<vector<string>> &vec){

    string imagePath = "C:/Users/Sebastian/Pictures/Prueba2.jpg";
    int blueChannel; int greenChannel; int redChannel;
    Mat colorImage; colorImage = imread(imagePath);

    for (int imageColumns = 0; imageColumns < colorImage.rows; imageColumns++){
        for (int imageRows = 0; imageRows < colorImage.cols; imageRows++) {
            redChannel = colorImage.at<Vec3b>(imageColumns, imageRows)[2];
            greenChannel = colorImage.at<Vec3b>(imageColumns, imageRows)[1];
            blueChannel = colorImage.at<Vec3b>(imageColumns, imageRows)[0];

            string rgbValue = to_string(redChannel) +","+ to_string(greenChannel)  +","+ to_string(blueChannel);
            vec[imageColumns][imageRows] = rgbValue;
        }
    }
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
    const int rows = 3840 ; const int columns = 2160;
    vector<vector<string>> vec( columns , vector<string> (rows));
    uploadImageInfo(vec);

    return 0;
}