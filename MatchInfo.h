#include "Trend.h"
#include <vector>
using namespace std;


class MatchInfo{

    //Atributes
    
    Trend segmentTrend;
    vector<Pixel> segmentColors;
    int begin, end, rowPosition;

    //Constructor

    public:
        MatchInfo(){
            this->begin = 0;
            this->end = 0;
            this->rowPosition= 0;
        }


        MatchInfo(Trend pSegmentTrend ,vector<Pixel> pSegmentColors ,int pBegin ,int pEnd ,int pRowPosition){
            this->segmentTrend = pSegmentTrend;
            this->segmentColors = pSegmentColors;
            this->rowPosition = pRowPosition;
            this->end = pEnd;
            this->begin= pBegin;

        }

        void printMatchInfo(){
            segmentTrend.printTrend();
            cout<<"Segment colors"<<endl;
            /*
            for(int segmentColorIndex = 0; segmentColorIndex < 192 ; segmentColorIndex++){
                segmentColors[segmentColorIndex].printPixelSegment();
            }
            */
            cout<<endl<<"Begin of the segment: "<<begin<<" ,End of the segment: "<<end<<" ,Row position of the segment: "<<rowPosition<<endl<<endl;
        }

        // Setter

        void setSegmentTrend( Trend pSegmentTrend) {
        segmentTrend = pSegmentTrend;
        }

        void setSegmentColors( vector<Pixel> pSegmentColors) {
        segmentColors = pSegmentColors;
        }

        void setBegin( int pBegin) {
        begin= pBegin;
        }

        void setEnd( int pEnd) {
        end = pEnd;
        }

        void setRowPosition( int pRowPosition) {
        rowPosition = pRowPosition;
        }

        // Getter

        Trend getSegmentTrend() {
        return segmentTrend;
        }

        vector<Pixel> getSegmentColors(){
            return segmentColors;
        }

        int getBegin(){
            return begin;
        }

        int getEnd(){
            return end;
        }

        int getRowPosition(){
            return rowPosition;
        }

};