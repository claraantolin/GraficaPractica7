//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef EscenaH
#define EscenaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCompuesto3D.h"
#include "TAfin.h"
#include "Color.h"
#include "BolasTriangulo.h"
#include "Objeto3D.h"
#include "Tablero.h"
#include "Tiza.h"
#include "Taco.h"
#include "Tablero.h"
#include "MesaBillar.h"

//---------------------------------------------------------------------------
class Escena  : public ObjetoCompuesto3D                                                                     
{                                                             
    private:

    public:

        Escena(TAfin* a):ObjetoCompuesto3D(a){

            color = new Color(1,1,1);

            // Bolas
            Objeto3D* bolas = new BolasTriangulo(new TAfin());

            // Tiza
            Objeto3D* tiza = new Tiza(new TAfin());

            // Taco
            Objeto3D* taco = new Taco(new TAfin());

            // Mesa
            Objeto3D* mesaBillar = new MesaBillar(new TAfin());


            objetos->ponElem(taco);
            objetos->ponElem(bolas);
            objetos->ponElem(tiza);
            objetos->ponElem(mesaBillar);


        };
        ~Escena(){}

};

#endif