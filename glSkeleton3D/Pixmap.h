//---------------------------------------------------------------------------

#ifndef PixmapH
#define PixmapH
//---------------------------------------------------------------------------
#include <gl\gl.h>
#include <gl\glu.h>
#include <string>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
typedef GLubyte colorRGBA[3];
typedef GLubyte colorY[3];

class Pixmap{
        private:

                GLuint nCols;
                GLuint nRows;
                colorRGBA* pixmap;
                colorY* luminanciaPixmap;
                bool drawLuminancia;
                Graphics::TBitmap* bmp;

                GLdouble matrizGauss[9];
                colorRGBA* sobelAux;
                
                void recoloca(Graphics::TBitmap* AuxBMP);
                GLdouble interpolacionBilineal(GLdouble x, GLdouble y, int rgb);
                void calculaMatrizGauss();
                void recalculaColor(int fila, int columna);
                int sacaValor(int num,int lum);
                void calculaSobel(int fila, int columna);


        public:
                Pixmap(){pixmap=NULL; nCols=0; nRows=0; luminanciaPixmap=NULL;};
                Pixmap(const string& arch);
                ~Pixmap(){delete[] pixmap; delete[] luminanciaPixmap;};
                GLuint getCols(){return nCols;};
                GLuint getRows(){return nRows;};
                colorRGBA* getBMP(){return pixmap;};
                colorY* getLuminancia(){return luminanciaPixmap;};
                void bufferToPixmap(int width, int height, GLfloat x, GLfloat y);
                void guardaBMP();
                bool cargaBMP(const string& arch);
                void drawBMP(GLfloat x, GLfloat y);

};


#endif
 