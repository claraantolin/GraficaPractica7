//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef TexturaH
#define TexturaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "Pixmap.h"

//---------------------------------------------------------------------------
class Textura                                                                     
{                                                             
    private:
        GLuint texName;
        Pixmap* pixmap;

    public:

        Textura(String rutaFichero, int m){
                pixmap = new Pixmap();                
                if(m == 1)
                    pixmap->cargaBMP("./iconoTapete.bmp");
                else if(m == 2)
                    pixmap->cargaBMP("./iconoMarcosMesa.bmp");

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
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rows,
                                cols, 0, GL_RGB, GL_UNSIGNED_BYTE,
                                imagen);
        };
        ~Textura(){delete pixmap;}

        GLuint getTextName(){ return texName;}


};

#endif