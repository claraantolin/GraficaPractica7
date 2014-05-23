//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef TableroH
#define TableroH

#include <gl\gl.h>
#include <gl\glu.h>

#define PI 3.14159265

#include "Malla.h"
#include "Lista.h"
#include "Cara.h"
#include "Objeto3D.h"
#include "TAfin.h"
#include "Pieza.h"
#include "Color.h"

//---------------------------------------------------------------------------
class Tablero : public Malla
{
   private:

        int largo;
        int ancho;
        int alto;

        int divLargo;
        int divAncho;
        int divAlto;

        Lista<Pieza*>* piezas;

   public:           

        Tablero();
        Tablero(GLdouble r, GLdouble g, GLdouble b, GLdouble largo, GLdouble ancho, GLdouble alto, GLdouble divL, GLdouble divAn, GLdouble divAl, TAfin* a):Malla(new Color(r,g,b),0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, new Lista<Cara*>(), a, 0, ""){
        
            this->largo = largo;
            this->ancho = ancho;
            this->alto = alto;

            divLargo = divL;
            divAncho = divAn;
            divAlto = divAl;                                      

            piezas = new Lista<Pieza*>();

            numVertices = (divLargo+1)*(divAncho+1)*(divAlto+1);
            numCaras = divAncho*divAlto*(divLargo+1) + divLargo*divAlto*(divAncho+1) + divLargo*divAncho*(divAlto+1);
            numNormales = numCaras;

            // vamos calculando todas las piezas ("troncos") que forman parte del tablero
            for(int i = 0; i < divAlto; i++)
                for(int j = 0; j < divLargo; j++)
                    for(int k = 0; k < divAncho; k++){
                        TAfin* aPieza = new TAfin(); aPieza->traslacion(3,2.7,5);
                        piezas->ponElem(new Pieza(r, g, b, 4, 2, ancho/divAncho, alto/divAlto, largo/divLargo, k, i, j, aPieza, 0, ""));
                    }
        };

        // Si queremos indicarle que la pieza es con textura o no
        Tablero(GLdouble r, GLdouble g, GLdouble b, GLdouble largo, GLdouble ancho, GLdouble alto, GLdouble divL, GLdouble divAn, GLdouble divAl, TAfin* a, int m, String nombre):Malla(new Color(r,g,b),0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, new Lista<Cara*>(), a, m, nombre){
            this->largo = largo;
            this->ancho = ancho;
            this->alto = alto;

            divLargo = divL;
            divAncho = divAn;
            divAlto = divAl;                                      

            piezas = new Lista<Pieza*>();

            numVertices = (divLargo+1)*(divAncho+1)*(divAlto+1);
            numCaras = divAncho*divAlto*(divLargo+1) + divLargo*divAlto*(divAncho+1) + divLargo*divAncho*(divAlto+1);
            numNormales = numCaras;

            // vamos calculando todas las piezas ("troncos") que forman parte del tablero
            for(int i = 0; i < divAlto; i++)
                for(int j = 0; j < divLargo; j++)
                    for(int k = 0; k < divAncho; k++){
                        TAfin* aPieza = new TAfin(); aPieza->traslacion(3,2.7,5);
                        piezas->ponElem(new Pieza(r, g, b, 4, 2, ancho/divAncho, alto/divAlto, largo/divLargo, k, i, j, aPieza, m, nombre));
                    }
        }

        
        ~Tablero(){delete piezas;}



//------------------------------------------------------------------------------
                        /***** dibujaTablero *****/
//------------------------------------------------------------------------------

        void dibuja(){

           for(int i = 0; i < piezas->numElem(); i++){
                glPushMatrix();
                        glMultMatrixf(tAfin->getMatriz());
                        Pieza* pieza = piezas->iesimo(i);
                        pieza->dibujaPieza();
                glPopMatrix();
           }
        }



};

#endif