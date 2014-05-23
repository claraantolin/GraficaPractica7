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

#define checkImageWidth 64
#define checkImageHeight 64

//---------------------------------------------------------------------------
class Textura                                                                     
{                                                             
    private:
        GLubyte checkImage[checkImageHeight][checkImageWidth][4];
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
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, checkImageWidth,
                                checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
                                imagen);
        };
        ~Textura(){delete pixmap;}

        GLuint getTextName(){ return texName;}

        void display()
        {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBindTexture(GL_TEXTURE_2D, texName);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
                glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
                glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
                glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

                glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
                glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
                glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
                glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
                glEnd();
                glFlush();
                glDisable(GL_TEXTURE_2D);
        }




};

#endif