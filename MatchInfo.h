#include "Pixel.h"
#include <vector>
using namespace std;

class MatchInfo{

    //Atributes
    
    Pixel segmentTrend;
    vector<Pixel> segmentColors;
    int begin, end, rowPosition;

    //Constructor

    public:
        MatchInfo(){
            this->begin = 0;
            this->end = 0;
            this->rowPosition= 0;
        }


        MatchInfo(Pixel pSegmentTrend ,vector<Pixel> pSegmentColors ,int pBegin ,int pEnd ,int pRowPosition){
            this->segmentTrend = pSegmentTrend;
            this->segmentColors = pSegmentColors;
            this->rowPosition = pRowPosition;
            this->end = pEnd;
            this->begin= pBegin;

        }

        // Setter

        void setSegmentTrend( Pixel pSegmentTrend) {
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

        Pixel getSegmentTrend() {
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