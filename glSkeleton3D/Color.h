//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ColorH
#define ColorH

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class Color                                                                     
{                                                             
    private:

        GLfloat r;   
        GLfloat g;
        GLfloat b;

    public:

        Color();
        Color(GLfloat r, GLfloat g, GLfloat b){
            this->r = r;
            this->g = g;
            this->b = b;
        };
        ~Color(){r=0; g=0; b=0;}

        void setColor(GLfloat r,GLfloat g, GLfloat b){
                this->r = r;
                this->g = g;
                this->b = b;
        }

        GLfloat getR(){return r;}
        GLfloat getG(){return g;}
        GLfloat getB(){return b;}

};

#endif