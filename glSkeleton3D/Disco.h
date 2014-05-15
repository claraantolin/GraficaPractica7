//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef DiscoH
#define DiscoH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCuadrico.h"
#include "TAfin.h"

//---------------------------------------------------------------------------
class Disco  : public ObjetoCuadrico                                                                     
{                                                             
    private:

        GLUquadric*  	disco;
    	GLdouble  	inner;
 	GLdouble  	outer;
 	GLint  	        slices;
 	GLint  	        loops;

    public:

        Disco(TAfin* a,GLdouble inner,GLdouble outer,GLint slices,GLint loops ):ObjetoCuadrico(a){

        	disco = gluNewQuadric();
            gluQuadricDrawStyle(disco, GLU_FILL);
            color = new Color(1,1,1);

        	this->inner= inner;
        	this->outer = outer;
        	this->slices = slices;
        	this->loops = loops;


        };

        Disco(TAfin* a):ObjetoCuadrico(a){}
        ~Disco(){ }

        void dibuja(){
            glPushMatrix();
                glMultMatrixf(tAfin->getMatriz());

                glColor3f(color->getR(),color->getG(),color->getB());
                gluDisk(disco, inner, outer, slices, loops);
            glPopMatrix();
        }

};

#endif