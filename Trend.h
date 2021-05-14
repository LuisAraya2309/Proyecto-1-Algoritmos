#include <iostream>
#include "Pixel.h"
using namespace std;

class Trend{
    //Atributes
    Pixel trend;
    int rowPosition;

    //Constructor

    public:
        Trend(){
            this->rowPosition = 0;
        }


        Trend(int pRowPosition, Pixel pTrend){

            this->rowPosition = pRowPosition;
            this->trend = pTrend;
        }

        void printTrend(){
            cout<<"Second Image Trend: "<<endl;
            trend.printPixel();
            cout<<"Row position: "<<rowPosition<<endl;
        }

        //Setter

        void setTrend( Pixel pTrend) {
        trend= pTrend;
        }

        void setRow( int pRow) {
        rowPosition = pRow;
        }

        // Getter

        Pixel getTrend() {
        return trend;
        }

        int getRow(){
            return rowPosition;
        }
};