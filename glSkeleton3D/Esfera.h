//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef EsferaH
#define EsferaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCuadrico.h"
#include "TAfin.h"

//---------------------------------------------------------------------------
class Esfera  : public ObjetoCuadrico                                                                     
{                                                             
    private:
        GLUquadricObj* esfera;

    public:

        Esfera(TAfin* a):ObjetoCuadrico(a){
                esfera = gluNewQuadric();
                gluQuadricDrawStyle(esfera, GLU_FILL);
                color = new Color(1,1,1);

        };

        Esfera(TAfin* a, const string& rutaTextura ):ObjetoCuadrico(a, rutaTextura){
                esfera = gluNewQuadric();
                gluQuadricDrawStyle(esfera, GLU_FILL);
                color = new Color(1,1,1);

        };
        ~Esfera(){}

        void dibuja(){
            glPushMatrix();
                glMultMatrixf(tAfin->getMatriz());

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                gluQuadricTexture(esfera, true);
                glBindTexture(GL_TEXTURE_2D, texName);
                glColor3f(color->getR(),color->getG(),color->getB());
                gluSphere(esfera, 1, 30, 30);

                glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }



};

#endif