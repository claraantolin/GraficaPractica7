//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef CamaraH
#define CamaraH

#include <gl\gl.h>
#include <gl\glu.h>

#include<math.h>
#define PI 3.14159265

#include "PV3D.h"

//---------------------------------------------------------------------------
class Camara                                                                     
{                                                             
    private:

        PV3D* eye;
        PV3D* look;
        PV3D* up;
        
        PV3D* u;
        PV3D* v;
        PV3D* n;

        GLfloat left, right, top, bottom, cerca, lejos, fovy, aspect;

    public:

        Camara(PV3D* eye, PV3D* look, PV3D* up, GLfloat left, GLfloat right,
                GLfloat bottom, GLfloat top, GLfloat cerca, GLfloat lejos){

            this->eye = eye;
            this->look = look;
            this->up = up;

            this->left = left;
            this->right = right;
            this->top = top;
            this->bottom = bottom;
            this->cerca = cerca;
            this->lejos = lejos;

            //Calculo del vector n
            GLdouble nX = eye->getX() - look->getX();
            GLdouble nY = eye->getY() - look->getY();
            GLdouble nZ = eye->getZ() - look->getZ();
            n = new PV3D(nX, nY, nZ);
            n->normaliza();

            //Calculo del vector u
            u = up->productoVectorial(n);
            u->normaliza();

            //Calculo del vector n
            v = n->productoVectorial(u);

            //Inizializacion de la camara
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
                      look->getX(), look->getY(), look ->getZ(),
                      up->getX(), up->getY(), up->getZ());

        };

        ~Camara(){
            delete eye; delete look; delete up;
            delete n; delete u; delete v;
        }

        void mueveCamara(GLfloat eX, GLfloat eY, GLfloat eZ, GLfloat lX, GLfloat lY, GLfloat lZ, GLfloat uX, GLfloat uY, GLfloat uZ){

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();


            eye->set3Coor(eye->getX()+eX,eye->getY()+eY, eye->getZ()+eZ );
            look->set3Coor(look->getX()+lX,look->getY()+lY, look->getZ()+lZ );
            up->set3Coor(up->getX()+uX,up->getY()+uY, up->getZ()+uZ );

            gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
                      look->getX(), look->getY(), look->getZ(),
                      up->getX(), up->getY(), up->getZ());
        }


        void vistas(GLfloat eX, GLfloat eY, GLfloat eZ, GLfloat lX, GLfloat lY, GLfloat lZ, GLfloat uX, GLfloat uY, GLfloat uZ){

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            eye->set3Coor(eX,eY,eZ );
            look->set3Coor(lX,lY,lZ );
            up->set3Coor(uX,uY,uZ );

            gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
                      look->getX(), look->getY(), look->getZ(),
                      up->getX(), up->getY(), up->getZ());
        }

        void girosCamara(PV3D* punto){
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            gluLookAt( punto->getX() * eye->getX(), punto->getY() * eye->getY(), eye->getZ() * punto->getZ(),
                       look->getX(), look->getY(), look->getZ(),
                       up->getX(), up->getY(), up->getZ());
        }

        void setModelViewMatrix() {

            glMatrixMode(GL_MODELVIEW);

            GLdouble m[16];
            m[0]=u->getX(); m[4]=u->getY(); m[8]=u->getZ(); m[12]=-eye->productoEscalar(u);
            m[1]=v->getX(); m[5]=v->getY(); m[9]=v->getZ(); m[13]=-eye->productoEscalar(v);
            m[2]=n->getX(); m[6]=n->getY(); m[10]=n->getZ(); m[14]=-eye->productoEscalar(n);
            m[3]=0; m[7]=0; m[11]=0; m[15]=1;

            glLoadMatrixd(m);                
        }

        void roll(GLfloat angulo){
            
            // Hacemos una copia de u y la ponemos en t, ya que para calcular v necesitamos la u antigua
            PV3D* t = new PV3D(u->getX(), u->getY(), u->getZ(), u->getW());

            GLfloat coseno = cos(angulo / 180 * PI);
            GLfloat seno = sin(angulo / 180 * PI);

            // u = t * cos(a) - v * sen(a)
            u->set3Coor(t->getX() * coseno - v->getX() * seno, t->getY() * coseno - v->getY() * seno, t->getZ() * coseno - v->getZ() * seno);

            // v = t * cos(a) - v * sen(a)
            v->set3Coor(t->getX() * seno + v->getX() * coseno, t->getY() * seno + v->getY() * coseno, t->getZ() * seno + v->getZ() * coseno);

            delete t;
            setModelViewMatrix();

        }

        void yaw(GLfloat angulo){

            // Hacemos una copia de u y la ponemos en t, ya que para calcular v necesitamos la u antigua
            PV3D* t = new PV3D(u->getX(), u->getY(), u->getZ(), u->getW());

            GLfloat coseno = cos(angulo / 180 * PI);
            GLfloat seno = sin(angulo / 180 * PI);

            // u = t * cos(a) + n * sen(a)
            u->set3Coor(t->getX() * coseno + n->getX() * seno, t->getY() * coseno + n->getY() * seno, t->getZ() * coseno + n->getZ() * seno);

            // n = - t * sen(a) + n * cosen(a)
            n->set3Coor((-1) * t->getX() * seno + n->getX() * coseno, (-1) * t->getY() * seno + n->getY() * coseno, (-1) * t->getZ() * seno + n->getZ() * coseno);
            
            delete t;
            setModelViewMatrix();

        }

        void pitch(GLfloat angulo){

            // Hacemos una copia de u y la ponemos en t, ya que para calcular v necesitamos la u antigua
            PV3D* t = new PV3D(n->getX(), n->getY(), n->getZ(), n->getW());

            GLfloat coseno = cos(angulo / 180 * PI);
            GLfloat seno = sin(angulo / 180 * PI);

            // n = t * cos(a) + v * sen(a)
            n->set3Coor(t->getX() * coseno + v->getX() * seno, t->getY() * coseno + v->getY() * seno, t->getZ() * coseno + v->getZ() * seno);

            // v = - t * sen(a) + v * cosen(a)
            v->set3Coor((-1) * t->getX() * seno + v->getX() * coseno, (-1) * t->getY() * seno + v->getY() * coseno, (-1) * t->getZ() * seno + v->getZ() * coseno);
            
            delete t;
            setModelViewMatrix();

        }

        void proyecOblicua(PV3D* d){

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                
                d->normaliza();

                if(d->getZ() != 0 && (d->getX() != 0 || d->getY() != 0   || d->getZ() != 1)){

                        GLfloat m[16];
                        m[0]=1; m[4]=0; m[8]=0;  m[12]=0;
                        m[1]=0; m[5]=1; m[9]=0;  m[13]=0;
                        m[2]=0; m[6]=0; m[10]=1; m[14]=0;
                        m[3]=0; m[7]=0; m[11]=0; m[15]=1;

                        m[8] = - d->getX() / d->getZ();
                        m[9] = - d->getY() / d->getZ();
                        m[12] = - cerca * (d->getX() / d->getZ());
                        m[13] = - cerca * (d->getY() / d->getZ());

                        //m[0]=1; m[4]=0; m[8]=0;  m[12]=0;
                        //m[1]=0; m[5]=1; m[9]=0;  m[13]=0;
                        //m[2]=-0.5; m[6]=-0.5; m[10]=1; m[14]=0;
                        //m[3]=0; m[7]=0; m[11]=0; m[15]=1;

                        glOrtho(left,right,bottom,top,cerca,lejos);
                        //glLoadMatrixf(m);
                        glMultMatrixf(m);
                }

        }

};

#endif