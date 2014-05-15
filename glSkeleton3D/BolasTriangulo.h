//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef BolasTrianguloH
#define BolasTrianguloH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCompuesto3D.h"
#include "TAfin.h"
#include "Color.h"
#include "Esfera.h"


//---------------------------------------------------------------------------
class BolasTriangulo  : public ObjetoCompuesto3D
{                                                             
    private:

    public:

        BolasTriangulo(TAfin* a):ObjetoCompuesto3D(a){
            color = new Color(1,1,1);
            creaBolas();
        };
        ~BolasTriangulo(){}


        void creaBolas(){

            int numBolasFila = 5;
            int posBola = 0;
            int fila = 0;

            // Pos primera bola
            GLdouble x = 1;
            GLdouble y = 2.6;
            GLdouble z = 0.5;

            GLdouble diametro = 0.3;

            for(int i = 0, p = numBolasFila; i < 15; i++, p--){

                if(p == 0) {
                    numBolasFila --;
                    fila++;
                    posBola = 0;
                    p = numBolasFila;
                }

                Objeto3D* bolaBillar;
                TAfin* a = new TAfin();
                a->escalacion(diametro/2,diametro/2,diametro/2);
                a->traslacion(x+diametro*posBola+diametro*fila/2,y,z+diametro*fila);
                bolaBillar = new Esfera(a);
                if(i == 10) bolaBillar->setColor(0.0,0.0,0.0);
                else bolaBillar->setColor(0.4,0.0,1);
                objetos->ponElem(bolaBillar);

                if(i == 14){
                    Objeto3D* bolaBillarBlanca;
                    TAfin* a = new TAfin();
                    a->escalacion(diametro/2,diametro/2,diametro/2);
                    a->traslacion(x+diametro*posBola+diametro*fila/2,y,z+diametro*fila + 2);
                    bolaBillarBlanca = new Esfera(a);
                    if(i == 10) bolaBillarBlanca->setColor(1.0,1.0,1.0);
                    objetos->ponElem(bolaBillarBlanca);
                }
                posBola++;
            }
        }

};

#endif