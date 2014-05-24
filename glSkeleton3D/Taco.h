//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef TacoH
#define TacoH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCompuesto3D.h"
#include "TAfin.h"
#include "Taco.h"
#include "Cilindro.h"

//---------------------------------------------------------------------------
class Taco  : public ObjetoCompuesto3D                                                                     
{                                                             
    private:

    public:

        Taco(TAfin* a):ObjetoCompuesto3D(a){

            color = new Color(1,1,1);

            TAfin* aPalo = new TAfin();
            Objeto3D* paloBillar = new Cilindro(aPalo,0.1,0.5,7,30,20,"./iconoMaderaTaco.bmp" );
            aPalo->traslacion(10,6,0);
            aPalo->escalacion(0.5,0.5,0.5);
            paloBillar->setColor(1,1,1);

            TAfin* aMangoPalo = new TAfin();
            Objeto3D* mangoPaloBillar = new Cilindro(aMangoPalo,0.5,0.7,5,30,20);
            aMangoPalo->traslacion(10,6,7);
            aMangoPalo->escalacion(0.5,0.5,0.5);
            mangoPaloBillar->setColor(0,0,0);

            TAfin* aTizaPalo = new TAfin();
            Objeto3D* tizaPaloBillar = new Cilindro(aTizaPalo,0.1,0.1,0.1,30,20);
            aTizaPalo->traslacion(10,6,-0.1);
            aTizaPalo->escalacion(0.5,0.5,0.5);
            tizaPaloBillar->setColor(0,0,8.0);

            objetos->ponElem(paloBillar);
            objetos->ponElem(mangoPaloBillar);
            objetos->ponElem(tizaPaloBillar);
        };

        ~Taco(){}

};

#endif