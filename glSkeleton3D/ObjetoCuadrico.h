//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ObjetoCuadricoH
#define ObjetoCuadricoH

#include <gl\gl.h>
#include <gl\glu.h>

#include "Objeto3D.h"
#include "TAfin.h"
#include "Color.h"

//---------------------------------------------------------------------------
class ObjetoCuadrico : public Objeto3D
{                                                             
    protected:
        

    public:

        ObjetoCuadrico(TAfin* a):Objeto3D(a){};
        ~ObjetoCuadrico(){}

        
};

#endif