//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef TizaH
#define TizaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCompuesto3D.h"
#include "TAfin.h"
#include "Tiza.h"
#include "Color.h"
#include "Tablero.h"

//---------------------------------------------------------------------------
class Tiza  : public ObjetoCompuesto3D                                                                
{                                                             
    private:

    public:

        Tiza(TAfin* a):ObjetoCompuesto3D(a){

            color = new Color(1,1,1);

            TAfin* aTiza = new TAfin(); aTiza->traslacion(3,2.7,5);
            Objeto3D* tizaBlanca = new Tablero(1.0,1.0,1.0, 0.2,0.2,0.2, 1,1,1, aTiza);

            TAfin* aTizaAzul = new TAfin(); aTizaAzul->traslacion(3,2.7,5);
            Objeto3D* tizaAzul = new Tablero(0.0,0.0,1.0, 0.05,0.2,0.2, 1,1,1, aTizaAzul);

            objetos->ponElem(tizaAzul);
            objetos->ponElem(tizaBlanca);
        };

        ~Tiza(){}

};

#endif