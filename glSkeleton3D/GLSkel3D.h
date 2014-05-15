//---------------------------------------------------------------------------
#ifndef GLSkel3DH
#define GLSkel3DH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Malla.h"
#include "VerticeNormal.h"
#include "PV3D.h"
#include "Cara.h"
#include "Lista.h"
#include "Camara.h"
#include "Tablero.h"
#include "Esfera.h"
#include "Cilindro.h"
#include "TAfin.h"
#include "ObjetoCompuesto3D.h"
#include "Disco.h"
#include "BolasTriangulo.h"
#include "Escena.h"
#include "Lampara.h"


//---------------------------------------------------------------------------
class TGLForm3D : public TForm
{
__published:    //IDE-managed Components
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);

private:        //User declarations
    HDC hdc;
    HGLRC hrc;
    GLfloat eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ; //Cámara
    GLdouble RatioViewPort, xLeft, xRight, yBot, yTop, N, F;  //Volumen de vista
    Camara* camara;
    Escena* escena;

    int modoNormales;   // si es 0 no se dibujan las normales, si es 1 se dibujan las normales
    int modoTransparencia;   // si es 0 no se dibujan el armazón, si es 1 se dibuja las rayas

    //Para los giros sobre los ejes
    int ladosGiros;
    int indY;
    int indZ;
    int indX;
    Lista<PV3D*>* curvaX;
    Lista<PV3D*>* curvaY;
    Lista<PV3D*>* curvaZ;

    // Modos iluminación
    bool luzAmbiente;
    bool luzLampara;
    bool luzRemota;
    bool niebla;

    void __fastcall SetPixelFormatDescriptor();
    void __fastcall GLScene();
    void crearObjetosEscena();
    void creaBolas(ObjetoCompuesto3D* objetoCompuesto);
    void liberarObjetosEscena();
    void actDesLuzAmbiente();
    void actDesLuzLampara();
    void actDesLuzRemota();
    void actDesNiebla();


public:     //User declarations
    __fastcall TGLForm3D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm3D *GLForm3D;
//---------------------------------------------------------------------------
#endif
