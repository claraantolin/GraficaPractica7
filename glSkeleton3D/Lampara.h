//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef LamparaH
#define LamparaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "Objeto3D.h"
#include "TAfin.h"
#include "Lampara.h"
#include "Cilindro.h"

#define PI 3.14159265

//---------------------------------------------------------------------------
class Lampara  : public Cilindro
{
    private:
        GLfloat luzAmbiente[4];
        GLfloat luzDifusa[4];
        GLfloat luzEspecular[4];
        GLfloat posicionLuz[4];
        GLfloat posicionFoco[4];

        bool luzEncendida;

        GLfloat alturaLampara;
        GLfloat baseLampara;
        GLfloat anguloLampara;
        

    public:

        Lampara(TAfin* a):Cilindro(a,0.2,1,3,30,20){
          a->rotacion(90,1,0,0);
          a->escalacion(1,1,1);
          a->traslacion(1.1,9,2);

          baseLampara = 1;
          alturaLampara = 3;
          calculoAnguloLampara();

           //Inicializacion del foco de la lampara
            //luzAmbiente = { 1.0, 0.0, 0.0, 1.0 };
            luzAmbiente[0] = 0.0;
            luzAmbiente[1] = 0.0;
            luzAmbiente[2] = 0.0;
            luzAmbiente[3] = 1.0;
            //luzDifusa = { 1.0, 0.0, 0.0, 1.0 };
            luzDifusa[0] = 1.0 ;
            luzDifusa[1] = 1.0;
            luzDifusa[2] = 1.0;
            luzDifusa[3] = 1.0;
            //luzEspecular = { 1.0, 1.0, 1.0, 1.0 };
            luzEspecular[1] = 0;
            luzEspecular[2] = 0;
            luzEspecular[3] = 0;
            luzEspecular[4] = 1.0;

            posicionLuz[0] = 0;
            posicionLuz[1] = 0;
            posicionLuz[2] = 0;
            posicionLuz[3] = 1.0;

            posicionFoco[0] = 0.0;
            posicionFoco[1] = 0.0;
            posicionFoco[2] = 1.0;

            glLightfv(GL_LIGHT4, GL_AMBIENT, luzAmbiente);
            glLightfv(GL_LIGHT4, GL_DIFFUSE, luzDifusa);
            glLightfv(GL_LIGHT4, GL_SPECULAR, luzEspecular);

            glLightfv(GL_LIGHT4, GL_AMBIENT, luzAmbiente);
            glLightfv(GL_LIGHT4, GL_DIFFUSE, luzDifusa);
            glLightfv(GL_LIGHT4, GL_SPECULAR, luzEspecular);

            glEnable(GL_LIGHT4);
            //luzEncendida = true;
            luzEncendida = false;


          
        };
        ~Lampara(){}

       void dibuja(){
           glPushMatrix();
                glMultMatrixf(tAfin->getMatriz());

                //Luz
                glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
                glLightfv(GL_LIGHT4, GL_POSITION, posicionLuz);
                glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, anguloLampara);
                glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 4.0);
                glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,posicionFoco);

                luzEncendida == true ? glEnable(GL_LIGHT4) : glDisable(GL_LIGHT4);

                //Dibujar lampara
                glColor3f(color->getR(),color->getG(),color->getB());
                gluCylinder(cilindro, base, top,  height, slices, stacks);


           glPopMatrix();

       }

       void sumaAlturaLampara(GLfloat alturaLamparaSumar){
           alturaLampara += alturaLamparaSumar;
           calculoAnguloLampara();
       }

       void toggleLuz(){
           luzEncendida = !luzEncendida;
       }

       private: void calculoAnguloLampara(){
           GLfloat hipotenusa = sqrt(pow (baseLampara, 2.0) + pow (alturaLampara, 2.0));
           anguloLampara = acos (alturaLampara/hipotenusa) * 180.0 / PI;
       }

         

};

#endif
