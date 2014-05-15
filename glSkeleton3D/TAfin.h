//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef TAfinH
#define TAfinH

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class TAfin                                                                     
{                                                             
    private:

      GLfloat* matriz;

    public:

        TAfin(){
                matriz = new GLfloat[16];
                glPushMatrix();
                        glLoadIdentity();
                        glGetFloatv(GL_MODELVIEW_MATRIX,matriz);
                glPopMatrix();
        };

        ~TAfin(){ delete [] matriz; }   

        GLfloat* getMatriz(){
                return matriz;
        }

        void traslacion(GLfloat x, GLfloat y, GLfloat z){
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                        glLoadIdentity();
                        glTranslatef(x,y,z);
                        GLfloat* mm = new GLfloat[16];
                        glGetFloatv(GL_MODELVIEW_MATRIX,mm);
                glPopMatrix();
                postMultiplicar(mm);
                delete[] mm;
        }

        void rotacion(GLfloat ang, GLfloat x, GLfloat y, GLfloat z){
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                        glLoadIdentity();
                        glRotatef(ang,x,y,z);
                        GLfloat* mm = new GLfloat[16];
                        glGetFloatv(GL_MODELVIEW_MATRIX,mm);
                glPopMatrix();
                postMultiplicar(mm);
                delete[] mm;
        }

        void escalacion(GLfloat x, GLfloat y, GLfloat z){
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                        glLoadIdentity();
                        glScalef(x,y,z);
                        GLfloat* mm = new GLfloat[16];
                        glGetFloatv(GL_MODELVIEW_MATRIX,mm);
                glPopMatrix();
                postMultiplicar(mm);
                delete[] mm;
        }

        private:

        void postMultiplicar(GLfloat* mm){

           GLfloat* res = new GLfloat[16]; 
           for(int i=0; i<4 ; i++)
                for(int j=0; j<4; j++){
                        res[i*4+j] = 0;
                        for(int k=0; k<4; k++ ){
                            int resAux = i*4+j;
                            int matrixAux = i*4+k;
                            int mmAux = k*4+j;
                            res[i*4+j]+= matriz[i*4+k] * mm[k*4+j];
                        }
                }
           GLfloat* aux = matriz;
           matriz=res;
           delete[]aux;
           res = NULL;
        }

};

#endif
