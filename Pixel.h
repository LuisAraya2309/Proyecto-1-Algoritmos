#include <iostream>

using namespace std;

class Pixel{
    //Atributes
    int redValue, greenValue,blueValue;

    //Constructor

    public:
        Pixel(){
            this->redValue = 0;
            this->greenValue = 0;
            this->blueValue = 0;
        }


        Pixel(int pRedValue,int pGreenValue,int pBlueGreen){

            this->redValue = pRedValue;
            this->greenValue = pGreenValue;
            this->blueValue = pBlueGreen;

        }

        void printPixel(){
            cout<<"Red: "<<redValue<<" ,Green: "<<greenValue<<" ,Blue: "<<blueValue<<endl;
        }

        void printPixelSegment(){
            cout<<redValue<<","<<greenValue<<","<<blueValue<<"  ";
        }

        //Setter

        void setRed( int pRed) {
        redValue= pRed;
        }

        void setGreen( int pGreen) {
        greenValue = pGreen;
        }

        void setBlue( int pBlue) {
        blueValue = pBlue;
        }

        // Getter

        int getRed() {
        return redValue;
        }

        int getGreen(){
            return greenValue;
        }

        int getBlue(){
            return blueValue;
        }

};