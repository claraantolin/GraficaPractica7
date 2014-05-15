//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef Objeto3DH
#define Objeto3DH

#include <gl\gl.h>
#include <gl\glu.h>

#include "TAfin.h"
#include "Color.h"

//---------------------------------------------------------------------------
class Objeto3D
{                                                             
    protected:

      TAfin* tAfin;
      Color* color;

    public:

        Objeto3D(TAfin* a){
            tAfin = a;
        };

        virtual ~Objeto3D(){ delete color; delete tAfin;}

        virtual void dibuja() = 0;

        void setColor(GLfloat r, GLfloat g, GLfloat b){
                color->setColor(r,g,b);
        }

        TAfin* getTAfin(){return tAfin;}


};

#endif