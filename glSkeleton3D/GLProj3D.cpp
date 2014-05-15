//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GLProj3D.res");
USEFORM("GLSkel3D.cpp", GLForm3D);
USEUNIT("Cara.cpp");
USEUNIT("Lista.cpp");
USEUNIT("Malla.cpp");
USEUNIT("PV3D.cpp");
USEUNIT("VerticeNormal.cpp");
USEUNIT("Camara.cpp");
USEUNIT("TAfin.cpp");
USEUNIT("Color.cpp");
USEUNIT("Objeto3D.cpp");
USEUNIT("ObjetoCompuesto3D.cpp");
USEUNIT("ObjetoCuadrico.cpp");
USEUNIT("Esfera.cpp");
USEUNIT("Cilindro.cpp");
USEUNIT("Disco.cpp");
USEUNIT("Tablero.cpp");
USEUNIT("Pieza.cpp");
USEUNIT("Escena.cpp");
USEUNIT("BolasTriangulo.cpp");
USEUNIT("Taco.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm3D), &GLForm3D);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
