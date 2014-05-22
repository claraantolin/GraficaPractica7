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

void Pixmap::mediaPonderada(Pixmap* imagenAuxiliar, GLdouble factorK){

        int countPixmap, countImgAux;
        unsigned int i, j;

        int rows = min(nRows,imagenAuxiliar->getRows());
        int cols = min(nCols,imagenAuxiliar->getCols());

        for (i=0; i < rows; i++)
                for (j=0; j < cols; j++) {
                        countPixmap= i*nCols + j;
                        countImgAux=i*imagenAuxiliar->getCols() + j;

                        pixmap[countPixmap][0] =  factorK * pixmap[countPixmap][0] + (1-factorK) * imagenAuxiliar->pixmap[countImgAux][0];
                        pixmap[countPixmap][1] =  factorK * pixmap[countPixmap][1] + (1-factorK) * imagenAuxiliar->pixmap[countImgAux][1];
                        pixmap[countPixmap][2] =  factorK * pixmap[countPixmap][2] + (1-factorK) * imagenAuxiliar->pixmap[countImgAux][2];
                }
        drawLuminancia = false;
}

void Pixmap::diferencia(Pixmap* imagenAuxiliar){

        int countPixmap, countImgAux;
        unsigned int i, j;

        int rows = min(nRows,imagenAuxiliar->getRows());
        int cols = min(nCols,imagenAuxiliar->getCols());

        for (i=0; i < rows; i++)
                for (j=0; j < cols; j++) {
                        countPixmap= i*nCols + j;
                        countImgAux= i*imagenAuxiliar->getCols() + j;

                        luminanciaPixmap[countPixmap][0] = abs (luminanciaPixmap[countPixmap][0] - imagenAuxiliar->luminanciaPixmap[countImgAux][0])  ;
                        luminanciaPixmap[countPixmap][1] = abs (luminanciaPixmap[countPixmap][1] - imagenAuxiliar->luminanciaPixmap[countImgAux][1])   ;
                        luminanciaPixmap[countPixmap][2] = abs (luminanciaPixmap[countPixmap][2] - imagenAuxiliar->luminanciaPixmap[countImgAux][2])  ;
                }
        drawLuminancia = true;
}


void Pixmap::rotacion(GLdouble angulo, GLdouble puntoOrigenX, GLdouble puntoOrigenY){

        colorRGBA* rotacion = new colorRGBA[nCols * nRows];

        GLdouble auxX, auxY;
        int count;
        unsigned int i, j;
        for (i=0; i < nRows; i++)
                for (j=0; j < nCols; j++) {
                        count=i*nCols + j;

                        auxX = i-puntoOrigenX;
                        auxY = j-puntoOrigenY;

                        //Hallamos la distancia desde el punto actual al ogigen
                        GLdouble dist = sqrt (pow (auxX, 2) +  pow(auxY, 2) );

                        //Hallamos el angulo nuevo
                        if(auxX != 0 || auxY != 0){
                        GLdouble dir = atan2(auxY, auxX);
                        dir +=angulo;

                        int puntoNuevoX = puntoOrigenX + dist * cos(dir);
                        int puntoNuevoY = puntoOrigenY + dist * sin(dir);

                        double x = puntoOrigenX + dist * cos(dir);
                        double y = puntoOrigenY + dist * sin(dir);

                        if(puntoNuevoX < 0 || puntoNuevoX >= nRows || puntoNuevoY < 0 || puntoNuevoY >= nCols){

                             rotacion[count][0] = 255;
                             rotacion[count][1] = 255;
                             rotacion[count][2] = 255;
                        }


                        if(puntoNuevoX < nRows && puntoNuevoY < nCols && puntoNuevoX >= 0 && puntoNuevoY >=0 ){

                                //rotacion[count][0] = pixmap[puntoNuevoX * nCols + puntoNuevoY][0];
                                //rotacion[count][1] = pixmap[puntoNuevoX * nCols + puntoNuevoY][1];
                                //rotacion[count][2] = pixmap[puntoNuevoX * nCols + puntoNuevoY][2];

                                rotacion[count][0] =  interpolacionBilineal(puntoNuevoX, puntoNuevoY, 0);
                                rotacion[count][1] =  interpolacionBilineal(puntoNuevoX, puntoNuevoY, 1);
                                rotacion[count][2] =  interpolacionBilineal(puntoNuevoX, puntoNuevoY, 2);
                        }
                }else { //Estamos en el punto de origen
                        rotacion[count][0] = pixmap[count][0];
                        rotacion[count][1] = pixmap[count][1];
                        rotacion[count][2] = pixmap[count][2];
                }
        }

        delete [] pixmap;
        pixmap = rotacion;

        drawLuminancia = false;
}

GLdouble  Pixmap::interpolacionBilineal(GLdouble x, GLdouble y, int rgb){

        GLdouble incrementoX = x - (int)x;
        GLdouble incrementoY = y - (int)y;

        int count = x * nCols + y;  

        GLdouble color = (1-incrementoX) * (1-incrementoY) * pixmap[count][rgb];

        if(y < nCols-1)
        color += (1-incrementoX) * incrementoY * pixmap[count + 1][rgb];

        if(y < nCols-1 && x < nRows - 1)
        color += incrementoX * incrementoY * pixmap[count + nCols + 1][rgb];

        if(x < nRows - 1)
        color += incrementoX * (1-incrementoY) * pixmap[count + nCols][rgb];

        return color;

}

void Pixmap::sobel(){
        sobelAux = new colorRGBA[nCols * nRows];

        for(int i = 0; i < nRows; i++)
            for(int j = 0; j < nCols; j++)
                calculaSobel(i, j);

        delete[] luminanciaPixmap;
        luminanciaPixmap = sobelAux;
        drawLuminancia = true;

}// suavizadoGaussiano

int Pixmap::sacaValor(int num, int lum){
    if(num > 100)
        return 0;
    else
        return lum;
}

void Pixmap::calculaSobel(int fila, int columna){
    int countPixmap = fila*nCols + columna;

/*  
PRIMERO: 
    Calculamos las posiciones vecinas en el array siendo pos4 el pixel que estamos mirando:
        pos6    pos7    pos8
        pos3    pos4    pos5  
        pos0    pos1    pos2   
*/

    int pos0 = countPixmap - nCols - 1;
    int pos1 = countPixmap - nCols;
    int pos2 = countPixmap - nCols + 1;
    int pos3 = countPixmap - 1;
    int pos4 = countPixmap;
    int pos5 = countPixmap + 1;
    int pos6 = countPixmap + nCols - 1;
    int pos7 = countPixmap + nCols;
    int pos8 = countPixmap + nCols + 1;

/*
SEGUNGO:
    Calculamos los valores Gx y Gy 
    a partir de los valores de los pixeles vecinos:

    Gx = (pos6 + 2*pos3 + pos0) - (pos8 + 2*pos5 + pos2)
    Gy = (pos0 + 2*pos1 + pos2) - (pos6 + 2*pos7 + pos8)

*/
    double gXR; double gYR;
    double gXG; double gYG;
    double gXB; double gYB;

    // POS 0    -> solo tenemos las posiciones: pos5, pos7 y pos8
    if(fila == 0 && columna == 0){
        gXR = - (2*luminanciaPixmap[pos5][0] + luminanciaPixmap[pos8][0]);
        gYR = (2*luminanciaPixmap[pos7][0] + luminanciaPixmap[pos8][0]);

        gXG = - (2*luminanciaPixmap[pos5][1] + luminanciaPixmap[pos8][1]);
        gYG = 2*luminanciaPixmap[pos7][1] + luminanciaPixmap[pos8][1];

        gXB = - (2*luminanciaPixmap[pos5][2] + luminanciaPixmap[pos8][2]);
        gYB = 2*luminanciaPixmap[pos7][2] + luminanciaPixmap[pos8][2];

    }else


    // POS 1  -> solo tenemos las posiciones: pos3, pos5, pos6, pos7 y pos8
    if(fila == 0 && columna > 0 && columna < nCols-1){
        gXR = (2*luminanciaPixmap[pos3][0] + luminanciaPixmap[pos6][0]) -
              (2*luminanciaPixmap[pos5][0] + luminanciaPixmap[pos8][0]);
        gYR = luminanciaPixmap[pos6][0] + 2*luminanciaPixmap[pos7][0] + luminanciaPixmap[pos8][0];

        gXG = (2*luminanciaPixmap[pos3][1] + luminanciaPixmap[pos6][1]) -
              (2*luminanciaPixmap[pos5][1] + luminanciaPixmap[pos8][1]);
        gYG = luminanciaPixmap[pos6][1] + 2*luminanciaPixmap[pos7][1] + luminanciaPixmap[pos8][1];

        gXB = (2*luminanciaPixmap[pos3][2] + luminanciaPixmap[pos6][2]) -
              (2*luminanciaPixmap[pos5][2] + luminanciaPixmap[pos8][2]);
        gYB = luminanciaPixmap[pos6][2] + 2*luminanciaPixmap[pos7][2] + luminanciaPixmap[pos8][2];

    }else

    // POS 2  -> solo tenemos las posiciones: pos3, pos6 y pos7
    if(columna == nCols-1 && fila == 0){
        gXR = 2*luminanciaPixmap[pos3][0] + luminanciaPixmap[pos6][0];
        gYR = luminanciaPixmap[pos6][0] + 2*luminanciaPixmap[pos7][0];

        gXG = 2*luminanciaPixmap[pos3][1] + luminanciaPixmap[pos6][1];
        gYG = luminanciaPixmap[pos6][1] + 2*luminanciaPixmap[pos7][1];

        gXB = 2*luminanciaPixmap[pos3][2] + luminanciaPixmap[pos6][2];
        gYB = luminanciaPixmap[pos6][2] + 2*luminanciaPixmap[pos7][2];

    }else

    // POS 3  -> solo tenemos las posiciones: pos1, pos2, pos5, pos7 y pos8
    if(fila < nRows-1 && fila > 0 && columna == 0){
        gXR = - (luminanciaPixmap[pos2][0] + 2*luminanciaPixmap[pos5][0] + luminanciaPixmap[pos8][0]);
        gYR = (2*luminanciaPixmap[pos7][0] + luminanciaPixmap[pos8][0]) -
              (2*luminanciaPixmap[pos1][0] + luminanciaPixmap[pos2][0]);

        gXG = - (luminanciaPixmap[pos2][1] + 2*luminanciaPixmap[pos5][1] + luminanciaPixmap[pos8][1]);
        gYG = (2*luminanciaPixmap[pos7][1] + luminanciaPixmap[pos8][1]) -
              (2*luminanciaPixmap[pos1][1] + luminanciaPixmap[pos2][1]);

        gXB = - (luminanciaPixmap[pos2][2] + 2*luminanciaPixmap[pos5][2] + luminanciaPixmap[pos8][2]);
        gYB = (2*luminanciaPixmap[pos7][2] + luminanciaPixmap[pos8][2]) -
              (2*luminanciaPixmap[pos1][2] + luminanciaPixmap[pos2][2]);

    }else

    // POS 5  -> solo tenemos las posiciones: pos0, pos1, pos3, pos6 y pos7
    if(fila < nRows-1 && fila > 0 && columna == nCols-1){
        gXR = luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos3][0] + luminanciaPixmap[pos6][0];
        gYR = (luminanciaPixmap[pos6][0] + 2*luminanciaPixmap[pos7][0]) -
              (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos1][0]);

        gXG = luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos3][1] + luminanciaPixmap[pos6][1];
        gYG = (luminanciaPixmap[pos6][1] + 2*luminanciaPixmap[pos7][1]) -
              (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos1][1]);

        gXB = luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos3][2] + luminanciaPixmap[pos6][2];
        gYB = (luminanciaPixmap[pos6][2] + 2*luminanciaPixmap[pos7][2]) -
              (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos1][2]);

    }else

    // POS 6  -> solo tenemos las posiciones: pos1, pos2 y pos5
    if(columna == 0 && fila == nRows-1){
        gXR = - (luminanciaPixmap[pos2][0] + 2*luminanciaPixmap[pos5][0]);
        gYR = - (2*luminanciaPixmap[pos1][0] + luminanciaPixmap[pos2][0]);

        gXG = - (luminanciaPixmap[pos2][1] + 2*luminanciaPixmap[pos5][1]);
        gYG = - (2*luminanciaPixmap[pos1][1] + luminanciaPixmap[pos2][1]);

        gXB = - (luminanciaPixmap[pos2][2] + 2*luminanciaPixmap[pos5][2]);
        gYB = - (2*luminanciaPixmap[pos1][2] + luminanciaPixmap[pos2][2]);

    }else

    // POS 7  -> solo tenemos las posiciones: pos0, pos1, pos2, pos3 y pos5
    if(fila == nRows-1 && columna > 0 && columna < nCols-1){
        gXR = (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos3][0]) -
              (luminanciaPixmap[pos2][0] + 2*luminanciaPixmap[pos5][0]);
        gYR = - (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos1][0] + luminanciaPixmap[pos2][0]);

        gXG = (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos3][1]) -
              (luminanciaPixmap[pos2][1] + 2*luminanciaPixmap[pos5][1]);
        gYG = - (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos1][1] + luminanciaPixmap[pos2][1]);

        gXB = (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos3][2]) -
              (luminanciaPixmap[pos2][2] + 2*luminanciaPixmap[pos5][2]);
        gYB = - (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos1][2] + luminanciaPixmap[pos2][2]);

    }else

    // POS 8  -> solo tenemos las posiciones: pos0, pos1 y pos3
    if(fila == nRows-1 && columna == nCols-1){
        gXR = (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos3][0]);
        gYR = - (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos1][0]);

        gXG = (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos3][1]);
        gYG = - (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos1][1]);

        gXB = (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos3][2]);
        gYB = - (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos1][2]);

    }else{   // POS 4  -> tenemos todas las posiciones

        gXR = (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos3][0] + luminanciaPixmap[pos6][0]) -
              (luminanciaPixmap[pos2][0] + 2*luminanciaPixmap[pos5][0] + luminanciaPixmap[pos8][0]);
        gYR = (luminanciaPixmap[pos6][0] + 2*luminanciaPixmap[pos7][0] + luminanciaPixmap[pos8][0]) -
              (luminanciaPixmap[pos0][0] + 2*luminanciaPixmap[pos1][0] + luminanciaPixmap[pos2][0]);

        gXG = (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos3][1] + luminanciaPixmap[pos6][1]) -
              (luminanciaPixmap[pos2][1] + 2*luminanciaPixmap[pos5][1] + luminanciaPixmap[pos8][1]);
        gYG = (luminanciaPixmap[pos6][1] + 2*luminanciaPixmap[pos7][1] + luminanciaPixmap[pos8][1]) -
              (luminanciaPixmap[pos0][1] + 2*luminanciaPixmap[pos1][1] + luminanciaPixmap[pos2][1]);

        gXB = (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos3][2] + luminanciaPixmap[pos6][2]) -
              (luminanciaPixmap[pos2][2] + 2*luminanciaPixmap[pos5][2] + luminanciaPixmap[pos8][2]);
        gYB = (luminanciaPixmap[pos6][2] + 2*luminanciaPixmap[pos7][2] + luminanciaPixmap[pos8][2]) -
              (luminanciaPixmap[pos0][2] + 2*luminanciaPixmap[pos1][2] + luminanciaPixmap[pos2][2]);

    }

/*
TERCERO:
    · Sumamos los valores en valor absoluto: |Gx| + |Gy|
    · Normalizamos:
        si el valor es mayor que n      // n por ejemplo lo he puesto a 100
            ponemos 1 en la matriz luminanciaPixmap
        si no
            ponemos 0 en la matriz luminanciaPixmap
*/

    sobelAux[pos4][0] = sacaValor(abs(gXR) + abs(gYR), pixmap[pos4][0]);
    sobelAux[pos4][1] = sacaValor(abs(gXG) + abs(gYG), pixmap[pos4][1]);
    sobelAux[pos4][2] = sacaValor(abs(gXB) + abs(gYB), pixmap[pos4][2]);
}


void Pixmap::suavizadoGaussiano(){

        int m = 1; GLdouble sigma = 1.5;
        int countPixmap;
        calculaMatrizGauss();
        for(int i = 0; i < nRows; i++)
            for(int j = 0; j < nCols; j++)
                recalculaColor(i, j);
            
        drawLuminancia = false;
}// suavizadoGaussiano

void Pixmap::calculaMatrizGauss(){

    double sigma = 1.5;
    int m = 1;
    double numerador;
    double denominador = 2*sigma*sigma;
    double exponente;
    double sumaTotal = 0;
    int indice = 0;
    
    for(int j = m; j > -2; j--)
        for(int i = -m; i < 2; i++, indice++){
            numerador = i*i + j*j;
            exponente = exp((-1)*(numerador / denominador));
            matrizGauss[indice] = exponente / (3.14 * denominador);

            sumaTotal += matrizGauss[indice];
        }

    for(int i = 0; i < 9; i++)
        matrizGauss[i] /= sumaTotal;

}// calculaMatrizGauss

void Pixmap::recalculaColor(int fila, int columna){

    int countPixmap = fila*nCols + columna;

/*  
PRIMERO:
    Calculamos las posiciones exactas en el array:

        pos0    pos1    pos2
        pos3    pos4    pos5
        pos6    pos7    pos8    
*/

    int pos0 = countPixmap + nCols - 1;
    int pos1 = countPixmap + nCols;
    int pos2 = countPixmap + nCols + 1;
    int pos3 = countPixmap - 1;
    int pos4 = countPixmap;
    int pos5 = countPixmap + 1;
    int pos6 = countPixmap - nCols - 1;
    int pos7 = countPixmap - nCols;
    int pos8 = countPixmap - nCols + 1;

/*
SEGUNDO:
    Multimplicamos cada posicion del array por su peso
*/
    // Casilla que estamos mirando (centro)
    double r = matrizGauss[4] * pixmap[pos4][0];
    double g = matrizGauss[4] * pixmap[pos4][1];
    double b = matrizGauss[4] * pixmap[pos4][2];

    if(fila < nRows-1 && columna > 0){
        r += matrizGauss[0] * pixmap[pos0][0];
        g += matrizGauss[0] * pixmap[pos0][1];
        b += matrizGauss[0] * pixmap[pos0][2];
    }

    if(columna > 0 && fila < nRows-1){
        r += matrizGauss[1] * pixmap[pos1][0];
        g += matrizGauss[1] * pixmap[pos1][1];
        b += matrizGauss[1] * pixmap[pos1][2];
    }
    if(fila < nRows-1 && columna < nCols-1){
        r += matrizGauss[2] * pixmap[pos2][0];
        g += matrizGauss[2] * pixmap[pos2][1];
        b += matrizGauss[2] * pixmap[pos2][2];
    }
    if(columna > 0){
        r += matrizGauss[3] * pixmap[pos3][0];
        g += matrizGauss[3] * pixmap[pos3][1];
        b += matrizGauss[3] * pixmap[pos3][2];
    }

    if(columna < nCols-1){
        r += matrizGauss[5] * pixmap[pos5][0];
        g += matrizGauss[5] * pixmap[pos5][1];
        b += matrizGauss[5] * pixmap[pos5][2];
    }
    if(fila > 0 && columna > 0){
        r += matrizGauss[6] * pixmap[pos6][0];
        g += matrizGauss[6] * pixmap[pos6][1];
        b += matrizGauss[6] * pixmap[pos6][2];
    }
    if(fila < nRows-1 && fila > 0){
        r += matrizGauss[7] * pixmap[pos7][0];
        g += matrizGauss[7] * pixmap[pos7][1];
        b += matrizGauss[7] * pixmap[pos7][2];
    }
    if(fila > 0 && columna < nCols-1){
        r += matrizGauss[8] * pixmap[pos8][0];
        g += matrizGauss[8] * pixmap[pos8][1];
        b += matrizGauss[8] * pixmap[pos8][2];
    }

/*
TERCERO:
    Sumamos todos los pesos de las posiciones vecinas 
    para sacar el valor del pixel que estamos mirando:
*/
    pixmap[countPixmap][0] = r;
    pixmap[countPixmap][1] = g;
    pixmap[countPixmap][2] = b;

}// recalculaColor

//Leer pixeles del frame buffer y dejarlos en la matriz arbol
void Pixmap::bufferToPixmap(int width, int height, GLfloat x, GLfloat y){
        delete[] pixmap;
        pixmap = new colorRGBA[height*width];

        nRows = height;
        nCols = width;

        glPixelStorei(GL_PACK_ALIGNMENT, //Cómo se leen los pixeles
         1); //sin padding entre filas

        glReadPixels(x, y, //esquina inferior-izquierda del bloque,
                nCols, nRows, // tamaño del bloque
                GL_RGB,  //datos a leer
                GL_UNSIGNED_BYTE, //tipo de los datos
                pixmap); //destino


        //Calculamos la luminancia

        delete[] luminanciaPixmap;
        luminanciaPixmap = new colorY[height*width];

        int count;
        unsigned int i, j; 

        for (i=0; i < nRows; i++)
                for (j=0; j < nCols; j++) {  
                        count= i*nCols + j;

                        GLubyte valorLuminancia = 0.299 * pixmap[count][0] + 0.587 * pixmap[count][1] + 0.114 *  pixmap[count][2];

                        luminanciaPixmap[count][0] = valorLuminancia;
                        luminanciaPixmap[count][1] = valorLuminancia;
                        luminanciaPixmap[count][2] = valorLuminancia;
                }
       drawLuminancia = false;
}

//Leer pixeles del frame buffer y dejarlos en la matriz pixmap
void Pixmap::printPantTree(int width, int height, GLfloat x, GLfloat y){
        /*delete[] pixmap;
        pixmap = new colorRGBA[3*height*width];

        nRows = height;
        nCols = width;

        glPixelStorei(GL_PACK_ALIGNMENT, //Cómo se leen los pixeles
         1); //sin padding entre filas

        glReadPixels(x, y, //esquina inferior-izquierda del bloque,
                nCols, nRows, // tamaño del bloque
                GL_RGB,  //datos a leer
                GL_UNSIGNED_BYTE, //tipo de los datos
                pixmap); //destino

        guardaBMP();
        delete[] pixmap;

        drawLuminancia = false;*/
}                    

void Pixmap::guardaBMP(){
    int width = nCols;
    int height = nRows;                                                    
    int countPixmap;
    bmp = new Graphics::TBitmap();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j ) {
            countPixmap= i*nCols + j;

            TColor red = pixmap[countPixmap][0];
            TColor green = pixmap[countPixmap][1];
            TColor blue = pixmap[countPixmap][2];

            //bmp->Canvas->SetValue(j, nRows-i-1, new Color(red,green,blue));

            
            bmp->Canvas->Pixels[j][nRows-i-1] = red;
            bmp->Canvas->Pixels[j][nRows-i-1] = green;
            bmp->Canvas->Pixels[j][nRows-i-1] = blue;
        }
    }

    char* FileName = "ejemplo.bmp";

    bmp->SaveToFile(FileName);

    drawLuminancia = false;
}


//Dibujar pixeles en el frame buffer desde la matriz arbol
void Pixmap::drawArbol(GLfloat x, GLfloat y){

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