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
    protected:
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

         Cilindro(TAfin* a, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks,const string& rutaTextura):ObjetoCuadrico(a,rutaTextura){
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

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                gluQuadricTexture(cilindro, true);
                glBindTexture(GL_TEXTURE_2D, texName);
                glColor3f(color->getR(),color->getG(),color->getB());
                gluCylinder(cilindro, base, top,  height, slices, stacks);

                glDisable(GL_TEXTURE_2D);

                //
                //gluCylinder(cilindro, base, top,  height, slices, stacks);
            glPopMatrix();
        }

};

#endif