//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ObjetoCompuesto3DH
#define ObjetoCompuesto3DH

#include <gl\gl.h>
#include <gl\glu.h>

#include "Lista.h"
#include "Objeto3D.h"
#include "TAfin.h"

//---------------------------------------------------------------------------
class ObjetoCompuesto3D  : public Objeto3D                                                                     
{
    protected:

        Lista<Objeto3D*>* objetos;

    public:          

        ObjetoCompuesto3D():Objeto3D(new TAfin()){
            objetos = new Lista<Objeto3D*>();
            color = new Color(1,1,1);
        };
        
        ObjetoCompuesto3D(TAfin* a):Objeto3D(a){ objetos = new Lista<Objeto3D*>();};
        ~ObjetoCompuesto3D(){delete objetos; }

        Lista<Objeto3D*>* getObjetos(){ return objetos;}

        void dibuja(){

            glPushMatrix();
              glMultMatrixf(tAfin->getMatriz());
              for(int i=0; i<objetos->numElem(); i++){
                  Objeto3D* o = objetos->iesimo(i);
                  o->dibuja();
              }
            glPopMatrix();
        };

        void trasladar(GLdouble X, GLdouble Y, GLdouble Z){
            tAfin->traslacion(X,Y,Z);
        }


        void escalar(GLdouble X, GLdouble Y, GLdouble Z){
            tAfin->escalacion(X,Y,Z);
        }


        void rotar(GLdouble angulo, GLdouble X, GLdouble Y, GLdouble Z){
            tAfin->rotacion(angulo,X,Y,Z);
        }
};

#endif