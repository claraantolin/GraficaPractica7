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

#include "ObjetoCompuesto3D.h"
#include "TAfin.h"
#include "Lampara.h"
#include "Cilindro.h"

//---------------------------------------------------------------------------
class Lampara  : public ObjetoCompuesto3D                                                                     
{                                                             
    private:

    public:

        Lampara(TAfin* a):ObjetoCompuesto3D(a){

            color = new Color(1,1,1);

            TAfin* aLampara = new TAfin();
            aLampara->rotacion(90,1,0,0);
            aLampara->escalacion(1,1,1);
            aLampara->traslacion(1.1,7,2);
            Objeto3D* lamp = new Cilindro(aLampara,0.2,1,3,30,20);
            lamp->setColor(0.8,0.8,0.8);

            objetos->ponElem(lamp);

        };
        ~Lampara(){}

};

#endif