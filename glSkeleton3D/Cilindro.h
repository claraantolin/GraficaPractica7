//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef CilindroH
#define CilindroH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCuadrico.h"
#include "TAfin.h"

//---------------------------------------------------------------------------
class Cilindro  : public ObjetoCuadrico                                                                     
{                                                             
    private:
        GLUquadricObj* cilindro;
        GLdouble  	base;
 	    GLdouble  	top;
 	    GLdouble  	height;
 	    GLint  	    slices;
 	    GLint  	    stacks;

    public:

        Cilindro(TAfin* a):ObjetoCuadrico(a){
                cilindro = gluNewQuadric();
                gluQuadricDrawStyle(cilindro, GLU_FILL);
                color = new Color(1,1,1);
        };

        Cilindro(TAfin* a, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks):ObjetoCuadrico(a){
                cilindro = gluNewQuadric();
                gluQuadricDrawStyle(cilindro, GLU_FILL);
                color = new Color(1,1,1);

                this->base = base;
                this->top = top;
                this->height = height;
                this->slices = slices;
                this->stacks = stacks;
        };


        ~Cilindro(){ }

        void dibuja(){
            glPushMatrix();
                glMultMatrixf(tAfin->getMatriz());

                glColor3f(color->getR(),color->getG(),color->getB());
                gluCylinder(cilindro, base, top,  height, slices, stacks);
            glPopMatrix();
        }

};

#endif