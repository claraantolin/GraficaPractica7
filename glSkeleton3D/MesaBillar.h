//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef MesaBillarH
#define MesaBillarH

#include <gl\gl.h>
#include <gl\glu.h>

#include "ObjetoCompuesto3D.h"
#include "TAfin.h"
#include "MesaBillar.h"
#include "Color.h"
#include "Tablero.h"
#include "Disco.h"

//---------------------------------------------------------------------------
class MesaBillar  : public ObjetoCompuesto3D                                                                
{                                                             
    private:

    public:

        MesaBillar(TAfin* a):ObjetoCompuesto3D(a){

            color = new Color(1,1,1);

            // tapete Verde
            TAfin* aTapeteVerde = new TAfin(); aTapeteVerde->traslacion(0.3,2.1,0.25);
            Tablero* tapete = new Tablero(0.0,1.0,0.0, 6,3,0.5, 4,3,1, aTapeteVerde, 1, "./iconoTapete.bmp");
            //tapete->initTextura("./icono.bmp");
            Objeto3D* tapeteVerde = tapete;


            // Marcos
            TAfin* aMarco1 = new TAfin(); aMarco1->traslacion(0,2.2,-1.25);
            Objeto3D* marco1 = new Tablero(1.0,0.0,0.0, 0.5,4,0.8, 1,3,1, aMarco1, 2, "./iconoMarcosMesa.bmp");

            TAfin* aMarco2 = new TAfin(); aMarco2->traslacion(-0.4,2.2,0);
            Objeto3D* marco2 = new Tablero(1.0,0.0,0.0, 7,0.5,0.8, 4,1,1, aMarco2, 2, "./iconoMarcosMesa.bmp");

            TAfin* aMarco3 = new TAfin(); aMarco3->traslacion(0,2.2,5.25);
            Objeto3D* marco3 = new Tablero(1.0,0.0,0.0, 0.5,4,0.8, 1,3,1,aMarco3, 2, "./iconoMarcosMesa.bmp");

            TAfin* aMarco4 = new TAfin(); aMarco4->traslacion(3.1,2.2,0);
            Objeto3D* marco4 = new Tablero(1.0,0.0,0.0, 7,0.5,0.8, 4,1,1, aMarco4, 2, "./iconoMarcosMesa.bmp");

            // Patas
            TAfin* aPata1 = new TAfin(); aPata1->traslacion(-0.4,-0.65,-1.25);
            Objeto3D* pata1 = new Tablero(1.0,0.0,0.0, 0.5,0.5,3, 1,1,3, aPata1);

            TAfin* aPata2 = new TAfin(); aPata2->traslacion(-0.4,-0.65,5.25);
            Objeto3D* pata2 = new Tablero(1.0,0.0,0.0, 0.5,0.5,3, 1,1,3, aPata2);

            TAfin* aPata3 = new TAfin(); aPata3->traslacion(3.1,-0.65,5.25);
            Objeto3D* pata3 = new Tablero(1.0,0.0,0.0, 0.5,0.5,3, 1,1,3, aPata3);

            TAfin* aPata4 = new TAfin(); aPata4->traslacion(3.1,-0.65,-1.25);
            Objeto3D* pata4 = new Tablero(1.0,0.0,0.0, 0.5,0.5,3, 1,1,3, aPata4);

            // Troneras
            TAfin* aTronera1 = new TAfin();
            aTronera1->rotacion(90,1,0,0);
            aTronera1->escalacion(0.5,0.5,0.5);
            aTronera1->traslacion(0.1,2.4,-1);
            Objeto3D* tronera1 = new Disco(aTronera1, 0, 0.5, 30, 30);
            tronera1->setColor(0,0,0);

            TAfin* aTronera2 = new TAfin();
            aTronera2->rotacion(90,1,0,0);
            aTronera2->escalacion(0.5,0.5,0.5);
            aTronera2->traslacion(2.6,2.4,-1);
            Objeto3D* tronera2 = new Disco(aTronera2, 0, 0.5, 30, 30);
            tronera2->setColor(0,0,0);

            TAfin* aTronera3 = new TAfin();
            aTronera3->rotacion(90,1,0,0);
            aTronera3->escalacion(0.5,0.5,0.5);
            aTronera3->traslacion(2.6,2.4,4.5);
            Objeto3D* tronera3 = new Disco(aTronera3, 0, 0.5, 30, 30);
            tronera3->setColor(0,0,0);

            TAfin* aTronera4 = new TAfin();
            aTronera4->rotacion(90,1,0,0);
            aTronera4->escalacion(0.5,0.5,0.5);
            aTronera4->traslacion(0.1,2.4,4.5);
            Objeto3D* tronera4 = new Disco(aTronera4, 0, 0.5, 30, 30);
            tronera4->setColor(0,0,0);

            TAfin* aTronera5 = new TAfin();
            aTronera5->rotacion(90,1,0,0);
            aTronera5->escalacion(0.5,0.5,0.5);
            aTronera5->traslacion(2.6,2.4,1.8);
            Objeto3D* tronera5 = new Disco(aTronera5, 0, 0.5, 30, 30);
            tronera5->setColor(0,0,0);

            TAfin* aTronera6 = new TAfin();
            aTronera6->rotacion(90,1,0,0);
            aTronera6->escalacion(0.5,0.5,0.5);
            aTronera6->traslacion(0.1,2.4,1.8);
            Objeto3D* tronera6 = new Disco(aTronera6, 0, 0.5, 30, 30);
            tronera6->setColor(0,0,0);


            objetos->ponElem(tapeteVerde);
            objetos->ponElem(marco1);
            objetos->ponElem(marco2);
            objetos->ponElem(marco3);
            objetos->ponElem(marco4);
            objetos->ponElem(pata1);
            objetos->ponElem(pata2);
            objetos->ponElem(pata3);
            objetos->ponElem(pata4);
            objetos->ponElem(tronera1);
            objetos->ponElem(tronera2);
            objetos->ponElem(tronera3);
            objetos->ponElem(tronera4);
            objetos->ponElem(tronera5);
            objetos->ponElem(tronera6);
        };

        ~MesaBillar(){}

};

#endif