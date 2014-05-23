//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef PiezaH
#define PiezaH

#include <gl\gl.h>
#include <gl\glu.h>

#define PI 3.14159265

#include "Malla.h"
#include "Lista.h"
#include "Cara.h"
#include "Objeto3D.h"
#include "TAfin.h"
#include "Color.h"
//---------------------------------------------------------------------------
class Pieza : public Malla
{
   private:

        int numLados;
        int numRodajas;
        int pos;

   public:

        Pieza();
        Pieza(GLdouble r, GLdouble g, GLdouble b, int nlados, int nRodajas, GLdouble ancho, GLdouble alto, GLdouble largo, GLdouble x, GLdouble y, GLdouble z, TAfin* a, int m, String nombre):Malla(new Color(r,g,b),0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, new Lista<Cara*>(), a, m, nombre){

            // Damos valor a nuestros atributos
            numLados = nlados;
            numRodajas = nRodajas;

            // Damos valor a los atributos de la malla
            numVertices = nlados * nRodajas;
            calculaVertices(ancho, alto, largo, x, y, z);
            //numNormales = numVertices; //=numCaras, frecuentemente
            //numCaras = numVertices;
            numNormales = 6;    // Siempre va a haber 6 normales en un cubo
            numCaras = 6;       // Siempre va a haber 6 caras en un cubo
            calculaCaras(numRodajas, numLados);

            //Llamamos a newell para calcular las normales
            RellenaVectorNormalPorNewell();

            pos =0;
        }
        
        ~Pieza(){};

        GLdouble getAnguloX(){ return anguloX;}
        GLdouble getAnguloY(){ return anguloY;}
        GLdouble getAnguloZ(){ return anguloZ;}

        void setAnguloX(GLdouble angX){ anguloX = angX;}
        void setAnguloY(GLdouble angY){ anguloY = angY;}
        void setAnguloZ(GLdouble angZ){ anguloZ = angZ;}

//------------------------------------------------------------------------------
                        /***** calculaVertices *****/
//------------------------------------------------------------------------------

        void calculaVertices(GLdouble ancho, GLdouble alto, GLdouble largo, GLdouble x, GLdouble y, GLdouble z){

            GLdouble t = (2* M_PI * pos) / 60;
            double inc=(2*PI/numLados);
            GLdouble ang = 95.033;

            GLdouble radioX = 0.7*ancho;
            GLdouble radioY = 0.7*alto;

            for(int i=0; i<numLados; i++){

                GLdouble coseno = cos(ang-i*inc)*radioX;
                GLdouble seno = sin(ang-i*inc)*radioY;

                PV3D* nodo = new PV3D(coseno + (x)*ancho, seno + (y )*alto, 0 + (z )*largo, 1);
                vertices->ponElem(nodo);
            }

            for(int i=0; i<numLados; i++){

                GLdouble coseno = cos(ang-i*inc)*radioX;
                GLdouble seno = sin(ang-i*inc)*radioY;

                PV3D* nodo = new PV3D(coseno + (x)*ancho, seno + (y)*alto, -largo + (z)*largo, 1);
                vertices->ponElem(nodo);
            }

        }

//------------------------------------------------------------------------------
                        /***** dibujaPieza *****/
//------------------------------------------------------------------------------

        void dibujaPieza(){
            dibuja();
        }
};

#endif