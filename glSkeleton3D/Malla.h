//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef MallaH
#define MallaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "PV3D.h"
#include "Cara.h"
#include "Lista.h"
#include "Objeto3D.h"
#include "TAfin.h"
#include "Color.h"
#include "Pixmap.h"
//---------------------------------------------------------------------------
class Malla : public Objeto3D
{
   protected:
    
        int numVertices;
        Lista<PV3D*>* vertices;
        int numNormales;
        Lista<PV3D*>* normales;
        int numCaras;
        Lista<Cara*>* caras;

        GLdouble anguloX, anguloY, anguloZ;

        Pixmap* pixmap;
        GLuint texName;

   public:
        
        Malla();
        Malla(TAfin* a):Objeto3D(a){};
        Malla(Color* color, int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c, TAfin* a):Objeto3D(a){
            numVertices = inumV; vertices = v;
            numNormales = numN;  normales = n;
            numCaras = numC;     caras = c;
            anguloX = 0.0f; anguloY = 0.0f; anguloZ = 0.0f;

            this->color = color;
            initTextura("icono.bmp");

        };

        Malla(Color* color, int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c, TAfin* a, int m):Objeto3D(a){
            numVertices = inumV; vertices = v;
            numNormales = numN;  normales = n;
            numCaras = numC;     caras = c;
            anguloX = 0.0f; anguloY = 0.0f; anguloZ = 0.0f;

            this->color = color;
            if(m==1)
                initTextura("icono.bmp");

        };
        
        ~Malla(){
            
            delete vertices;
            delete normales;
            delete caras;
            //delete pixmap;

            numVertices = 0;
            numNormales = 0;
            numCaras = 0;

            anguloX = 0;
            anguloY = 0;
            anguloZ = 0;

            
        }

//------------------------------------------------------------------------------
                        /***** RellenaVectorNormalPorNewell *****/
//------------------------------------------------------------------------------

        void RellenaVectorNormalPorNewell(){
        
            Cara* c; GLdouble x; GLdouble y; GLdouble z;
            PV3D* vertActual; PV3D* vertSiguiente;

            for(int pos = 0; pos < numCaras; pos++){

                c = caras->iesimo(pos);
                x = 0; y = 0; z = 0;
                
                for(int i = 0; i < c->getNumVertices(); i++){

                    GLdouble a = c->getIndiceVertice(i);
                    GLdouble b = c->getIndiceVertice((i+1) % c->getNumVertices());
                    vertActual = vertices->iesimo(a);
                    vertSiguiente = vertices->iesimo(b);
                    x += (vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ());
                    y += (vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX());
                    z += (vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY());

                }

                PV3D* n = new PV3D(x,y,z);
                n->normaliza();
                normales->ponElem(n);
            }

        }// CalculoVectorNormalPorNewell                    

//------------------------------------------------------------------------------
                        /***** dibuja *****/
//------------------------------------------------------------------------------
        
        void dibuja(){
            //dibuja(0,1);  // vacio
            dibuja(0,0);    // relleno
        }

        void dibuja(int modoN, int modoT){

            GLdouble normalX, normalY, normalZ;
            GLdouble verticeX, verticeY, verticeZ;
            
            // Dibuja con la rotacion dada por los angulos
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glRotatef(anguloX, 1.0, 0.0, 0.0);
            glRotatef(anguloY, 0.0, 1.0, 0.0);
            glRotatef(anguloZ, 0.0, 0.0, 1.0);


            for (int i = 0; i < numCaras; i++){
                                     
                    glLineWidth(1.0); 

                    //Texturas
                    glEnable(GL_TEXTURE_2D);
                    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                    glBindTexture(GL_TEXTURE_2D, texName);

                    if(modoT == 0)
                        glBegin(GL_QUADS);
                    else
                        glBegin(GL_QUADS);

                    Cara* cara = caras->iesimo(i);
                    for (int j = 0; j < cara->getNumVertices(); j++) {

                        int iN = cara->getIndiceNormal(j);
                        int iV = cara->getIndiceVertice(j);

                        PV3D* normal = normales->iesimo(iN);
                        normalX = normal->getX();
                        normalY = normal->getY();
                        normalZ = normal->getZ();
                        
                        // Le asignamos una normal a cada vertice
                        glNormal3d(normalX,normalY,normalZ);
                             
                        //Si hubiera coordenadas de textura, aqui se suministrarian
                        //las coordenadas de textura del vertice j con glTexCoor2f(...);

                        PV3D* vertice = vertices->iesimo(iV);
                        verticeX = vertice->getX();
                        verticeY = vertice->getY();
                        verticeZ = vertice->getZ();

                        // Pintamos cada vertice
                        glColor3f(color->getR(),color->getG(),color->getB());
                        coordTextura(j);
                        glVertex3d(verticeX,verticeY,verticeZ);

                    } // for 2

                    glEnd();
                    glDisable(GL_TEXTURE_2D);

                    // Dibujamos las normales
                    if(modoN == 1){
                        glBegin(GL_LINES);
                            glColor3f(3,3,3);
                            glVertex3d(verticeX,verticeY,verticeZ);
                            glVertex3d(verticeX-normalX,verticeY-normalY,verticeZ-normalZ);
                        glEnd();
                    }

            }// for 1
            
            glPopMatrix();


        }// Dibuja


//------------------------------------------------------------------------------
                        /***** calculaCaras *****/
//------------------------------------------------------------------------------

        void calculaCaras(int numRodajas, int numLados){

            int indiceCara = 0; int indAux = 0;

            // añadimos las caras pertenecientes a los lados:
            for(int indiceRodaja = 0, lado = 0; indiceRodaja < numRodajas-1; indiceRodaja++, lado = lado+numLados){
                
                for(indiceCara = lado, indAux = 0; indiceCara < (lado+numLados); indiceCara++, indAux++){ 

                    Lista<VerticeNormal*>* arrayVN = new Lista<VerticeNormal*>();

                    // Rellenamos arrayVN de la clase Cara
                    arrayVN->ponElem(new VerticeNormal(indiceCara % numVertices ,indiceCara));
                    
                    if(indAux == numLados-1){ // estamos en el ultimo lado de la rodaja actual
                        arrayVN->ponElem(new VerticeNormal(lado % numVertices ,indiceCara));
                        arrayVN->ponElem(new VerticeNormal((lado+numLados) % numVertices ,indiceCara));
                    }else{
                        arrayVN->ponElem(new VerticeNormal((indiceCara+1) % numVertices ,indiceCara));
                        arrayVN->ponElem(new VerticeNormal((indiceCara+numLados+1) % numVertices ,indiceCara));
                    }
                    
                    arrayVN->ponElem(new VerticeNormal((indiceCara+numLados) % numVertices ,indiceCara));

                    caras->ponElem(new Cara(4,arrayVN)); // Siempre una cara va a estar compuesta de 4 vertices, 2 a 2

                }
            }

            // añadimos la tapa delantera:
            Lista<VerticeNormal*>* arrayVN1 = new Lista<VerticeNormal*>();
            arrayVN1->ponElem(new VerticeNormal(0,indiceCara));
            arrayVN1->ponElem(new VerticeNormal(1,indiceCara));
            arrayVN1->ponElem(new VerticeNormal(2,indiceCara));
            arrayVN1->ponElem(new VerticeNormal(3,indiceCara));

            caras->ponElem(new Cara(4,arrayVN1));

            // añadimos la tapa trasera:
            Lista<VerticeNormal*>* arrayVN2 = new Lista<VerticeNormal*>();
            arrayVN2->ponElem(new VerticeNormal(4,indiceCara + 1));
            arrayVN2->ponElem(new VerticeNormal(5,indiceCara + 1));
            arrayVN2->ponElem(new VerticeNormal(6,indiceCara + 1));
            arrayVN2->ponElem(new VerticeNormal(7,indiceCara + 1));

            caras->ponElem(new Cara(4,arrayVN2));
        }

//------------------------------------------------------------------------------
                        /***** multiplicaMatrices *****/
//------------------------------------------------------------------------------

        PV3D* multiplicaMatrices(Lista<PV3D*>* m, PV3D* p){

            PV3D* n = m->iesimo(0);
            GLfloat xPrima = n->getX() * p->getX() + n->getY() * p->getY() + n->getZ() * p->getZ() + n->getW() * p->getW();

            PV3D* b = m->iesimo(1);
            GLfloat yPrima = b->getX() * p->getX() + b->getY() * p->getY() + b->getZ() * p->getZ() + b->getW() * p->getW();

            PV3D* t = m->iesimo(2);
            GLfloat zPrima = t->getX() * p->getX() + t->getY() * p->getY() + t->getZ() * p->getZ() + t->getW() * p->getW();

            PV3D* c = m->iesimo(3);
            GLfloat wPrima = c->getX() * p->getX() + c->getY() * p->getY() + c->getZ() * p->getZ() + c->getW() * p->getW();

            return new PV3D(xPrima, yPrima, zPrima, wPrima);

        }
//------------------------------------------------------------------------------
                        /***** hazMatriz *****/
//------------------------------------------------------------------------------

        Lista<PV3D*>* hazMatriz(GLfloat t, GLfloat r){

            Lista<PV3D*>* matriz = new Lista<PV3D*>();

            PV3D* n = new PV3D(-1 * cos(t),0, -sin(t), r* cos(t));
            PV3D* b = new PV3D(0,-1, 0, 0);
            PV3D* tM = new PV3D(-sin(t),0, cos(t),  r*sin(t));
            PV3D* c = new PV3D(0,0,0, 1);

            matriz->ponElem(n); matriz->ponElem(b); matriz->ponElem(tM); matriz->ponElem(c);
            return matriz;
        }
//------------------------------------------------------------------------------
                        /***** setTextura *****/
//------------------------------------------------------------------------------
        void initTextura(String rutaFichero){
           pixmap = new Pixmap();
                pixmap->cargaBMP("./icono.bmp");

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
//------------------------------------------------------------------------------
                        /***** coordTextura *****/
//------------------------------------------------------------------------------

        private: void coordTextura(int verticeCara){

            switch(verticeCara){

                case 0:   
                    glTexCoord2d(0, 0);
                    break;

                case 1:
                    glTexCoord2d(0, 1);
                    break;

                case 2:
                    glTexCoord2d(1 ,1);
                    break;

                case 3:
                    glTexCoord2d(1,0 );
                    break;

                default:
                    break;
             }
        }
            
};

#endif