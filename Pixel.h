
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