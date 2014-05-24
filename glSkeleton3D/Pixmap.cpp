#include <vcl.h>
#pragma hdrstop

#include "Pixmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Pixmap::Pixmap(const string& arch){
        pixmap=NULL; nCols=0; nRows=0;
        cargaBMP(arch);
}

bool Pixmap::cargaBMP(const string& arch){
        drawLuminancia = false;
        Graphics::TBitmap* AuxBMP = new Graphics::TBitmap();
        AuxBMP->LoadFromFile(arch.c_str());
        if (AuxBMP->Empty) {
                delete AuxBMP;
                return false;
        }
        else {
                recoloca(AuxBMP);
                delete AuxBMP;
                return true;
        }
}

void Pixmap::recoloca(Graphics::TBitmap* AuxBMP){
        delete[] pixmap; delete[] luminanciaPixmap;
        pixmap = new colorRGBA[AuxBMP->Width * AuxBMP->Height];
        luminanciaPixmap = new colorY[AuxBMP->Width * AuxBMP->Height];
        nCols=AuxBMP->Width;
        nRows=AuxBMP->Height;
        int count;
        unsigned int i, j;
        for (i=0; i < nRows; i++)
                for (j=0; j < nCols; j++) {
                        count=i*nCols + j;
                        pixmap[count][0]=GetRValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
                        pixmap[count][1]=GetGValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
                        pixmap[count][2]=GetBValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
                        //pixmap[count][3]=255;
                        GLubyte valorLuminancia = 0.299 * GetRValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]) + 0.587 * GetGValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]) + 0.114 *  GetBValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
                        luminanciaPixmap[count][0]=valorLuminancia;
                        luminanciaPixmap[count][1]=valorLuminancia;
                        luminanciaPixmap[count][2]=valorLuminancia;
                }

        pixmap[20 * nCols + 20][0]= 255;
        pixmap[20 * nCols + 20][1]= 0;
        pixmap[20 * nCols + 20][2]= 0;
}


//Dibujar pieles en el frame buffer desde la matriz pixmap
void Pixmap::drawBMP(GLfloat x, GLfloat y){

        if(drawLuminancia){
                glPixelStorei(GL_UNPACK_ALIGNMENT, //como escribir los pixeles
                                1); //sin padding entre filas
                glRasterPos2i(x, y); //esquina inferior-izquerda donde escribiremos el bloque, usando coordenadas OpenGL de la ventana
                glDrawPixels(nCols, nRows, //tamaño del bloque
                                GL_RGB, //datos a escribir: buffer de color, de profundidad, componente alpha...
                                GL_UNSIGNED_BYTE, //tipo de los datos
                                luminanciaPixmap); //origen
        }else{
                glPixelStorei(GL_UNPACK_ALIGNMENT, //como escribir los pixeles
                                1); //sin padding entre filas
                glRasterPos2i(x, y); //esquina inferior-izquerda donde escribiremos el bloque, usando coordenadas OpenGL de la ventana
                glDrawPixels(nCols, nRows, //tamaño del bloque
                                GL_RGB, //datos a escribir: buffer de color, de profundidad, componente alpha...
                                GL_UNSIGNED_BYTE, //tipo de los datos
                                pixmap); //origen
        }

        //Si una de las operaciones devuelve en escala de grises, pixmap es más pequeño. Pasarle a drawPixels GL_LUMINANCE
}



