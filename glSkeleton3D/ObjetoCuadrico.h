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
#include "Pixmap.h"

//---------------------------------------------------------------------------
class ObjetoCuadrico : public Objeto3D
{                                                             
    protected:

        //Textura
        Pixmap* pixmap;
        GLuint texName;

        int modoTextura;

        

    public:

        ObjetoCuadrico(TAfin* a):Objeto3D(a){};
        ObjetoCuadrico(TAfin* a, int modoTex):Objeto3D(a){
                modoTextura = modoTex;
                if(modoTextura  != 0)
                        initTextura("./icono.bmp");

        };
        ~ObjetoCuadrico(){}


//------------------------------------------------------------------------------
                        /***** initTextura *****/
//------------------------------------------------------------------------------
        void initTextura(String rutaFichero){
            pixmap = new Pixmap();

            if(modoTextura == 1)
                pixmap->cargaBMP("./iconoMaderaTaco.bmp");

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &texName);
            glBindTexture(GL_TEXTURE_2D, texName);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                            GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                            GL_NEAREST);

            GLuint rows = pixmap->getRows();
            GLuint cols = pixmap->getCols();
            colorRGBA* imagen = pixmap->getBMP();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cols,
                            rows, 0, GL_RGB, GL_UNSIGNED_BYTE,
                            imagen);
        }

        
};

#endif