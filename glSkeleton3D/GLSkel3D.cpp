//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//


#include <vcl.h>
#pragma hdrstop

#include "GLSkel3D.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm3D *GLForm3D;

//---------------------------------------------------------------------------

__fastcall TGLForm3D::TGLForm3D(TComponent* Owner): TForm(Owner) {}
//---------------------------------------------------------------------------


void __fastcall TGLForm3D::FormCreate(TObject *Sender) {
    hdc=GetDC(Handle);
    SetPixelFormatDescriptor(); 
    hrc=wglCreateContext(hdc);
    if(hrc==NULL) ShowMessage("Error CreateContex");
    if(wglMakeCurrent(hdc, hrc)==false) ShowMessage("Error MakeCurrent");

    //Volumen de vista
    N=1; F=1000;
    xRight=10; xLeft=-xRight;
    yTop=10; yBot=-yTop;

    crearObjetosEscena();

    glClearColor(0.6,0.7,0.8,1.0);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);   //Defecto



    //Ratio del volumen de vista =1
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;
    
    //Luz0
    /*glEnable(GL_LIGHT0);
    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    GLfloat PosicionLuz0[]={25.0, 25.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);*/

    // Modos iluminación
    luzAmbiente = false;
    luzRemota = false;
    niebla = false;

    //Para los giros de camara
    indZ = indY = indX = 0; ladosGiros = 75;
    curvaZ = new Lista<PV3D*>();
    curvaY = new Lista<PV3D*>();
    curvaX = new Lista<PV3D*>();
    
    double inc=(2*PI/ladosGiros);
    for(int t=0; t<ladosGiros; t++){
       curvaZ->ponElem(new PV3D(cos(2*PI-t*inc), sin(2*PI-t*inc), 1, 1));
       curvaY->ponElem(new PV3D(cos(2*PI-t*inc), 1 , sin(2*PI-t*inc), 1));
       curvaX->ponElem(new PV3D( 1, cos(2*PI-t*inc) , sin(2*PI-t*inc), 1));
    }

    ventanaCerrada = false;
}

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::SetPixelFormatDescriptor() {
    PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0 };
    int PixelFormat=ChoosePixelFormat(hdc,&pfd);
    SetPixelFormat(hdc,PixelFormat,&pfd);
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::FormResize(TObject *Sender) {
    //Se actualiza puerto de vista y ratio
    if ((ClientHeight<=1.0) || (ClientHeight<=1.0)) {
        ClientWidth=400;
        ClientHeight=400;
        RatioViewPort=1.0;
    }
    else RatioViewPort=(GLfloat)ClientWidth/(GLfloat)ClientHeight;

    glViewport(0,0,ClientWidth,ClientHeight);

    //Se actualiza el volumen de vista
    //para que su ratio coincida con RatioViewPort
    GLfloat RatioVolVista=xRight/yTop;

    if (RatioVolVista>=RatioViewPort) {
     //Aumentamos yTop-yBot
     yTop=xRight/RatioViewPort;
     yBot=-yTop;
     }
    else {
     //Aumentamos xRight-xLeft
     xRight=RatioViewPort*yTop;
     xLeft=-xRight;
     }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xLeft, xRight, yBot, yTop, N, F);

    if(!ventanaCerrada) GLScene();
}

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::GLScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    actDesIluminacion();

    //Dibujo de los ejes
    glBegin(GL_LINES);
        glColor4d(1.0, 0.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(20.0, 0.0, 0.0);

        glColor4d(0.0, 1.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 20.0, 0.0);

        glColor4d(0.0, 0.0, 1.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 20.0);     
    glEnd();
    
    escena->dibuja();
    
    //glFlush();
    SwapBuffers(hdc);
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::FormPaint(TObject *Sender) {
    GLScene();
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::FormDestroy(TObject *Sender) {

    liberarObjetosEscena();
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL,NULL);                                              
    wglDeleteContext(hrc);

}

//---------------------------------------------------------------------------

void TGLForm3D::crearObjetosEscena(){

    escena = new Escena(new TAfin());
    escena->trasladar(0.5,1.25,1.5);
    
    //Clase camara
    PV3D* eye = new PV3D(100.0, 100.0, 100.0, 1);
    PV3D* look = new PV3D(0.0, 0.0, 0.0, 1);
    PV3D* up = new PV3D(0, 1, 0, 1);
    camara = new Camara(eye, look, up, xLeft, xRight, yBot, yTop, N, F);
}



//---------------------------------------------------------------------------

void TGLForm3D::liberarObjetosEscena() {
    delete curvaZ;
    delete curvaY;
    delete curvaX;
    delete camara;
    delete escena;

    ventanaCerrada = true;
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::FormKeyPress(TObject *Sender, char &Key)
{

    switch(Key){

        case 'e':   //Recorre eje X hacia delante
            camara->mueveCamara(3,0,0,0,0,0,0,0,0);
            break;

        case 'r':   //Recorre eje X hacia atras
            camara->mueveCamara(-3,0,0,0,0,0,0,0,0);
            break;

        case 'd':   //Recorre eje Y hacia delante
            camara->mueveCamara(0,3,0,0,0,0,0,0,0);
            break;

        case 'f':   //Recorre eje Y hacia atras
            camara->mueveCamara(0,-3,0,0,0,0,0,0,0);
            break;

        case 'c':   //Recorre eje Z hacia delante
            camara->mueveCamara(0,0,3,0,0,0,0,0,0);
            break;

        case 'v':   //Recorre eje Z hacia atras
            camara->mueveCamara(0,0,-3,0,0,0,0,0,0);
            break;

        case 't':   //desplaza eje X hacia delante
            camara->mueveCamara(0,0,0,1,0,0,0,0,0);
            break;

        case 'y':   //desplaza eje X hacia atras
            camara->mueveCamara(0,0,0,-1,0,0,0,0,0);
            break;

        case 's':   //desplaza eje Y hacia delante
            camara->mueveCamara(0,0,0,0,1,0,0,0,0);
            break;

        case 'x':   //desplaza eje Y hacia atras
            camara->mueveCamara(0,0,0,0,-1,0,0,0,0);
            break;

        case 'g':   //desplaza eje Z hacia delante
            camara->mueveCamara(0,0,0,0,0,1,0,0,0);
            break;

        case 'h':   //desplaza eje Z hacia atras
            camara->mueveCamara(0,0,0,0,0,-1,0,0,0);
            break;

        case '4':   //vista lateral
            camara->vistas(10,0,0,0,0,0,0,1,0);
           break;

        case '5':   //vista frontal
            camara->vistas(0,0,10,0,0,0,0,1,0);
            break;

        case '6':   //vista cenital
            camara->vistas(100,990,100,0,0,0,0,1,0);
            break;

        case '7':   //vista esquina
            camara->vistas(100,100,100,0,0,0,0,1,0);
            break;

        case '3':   //giros sobre el eje Z
            {PV3D* punto = curvaZ->iesimo(indZ);
            camara->girosCamara(punto);
            indZ++; indZ = indZ%ladosGiros;
            break;}
           
        case '2':   //giros sobre el eje Y
            {PV3D* punto = curvaY->iesimo(indY);
            camara->girosCamara(punto);
            indY++; indY = indY%ladosGiros;
            break;}

        case '1':   //giros sobre el eje X
            {PV3D* punto = curvaX->iesimo(indX);
            camara->girosCamara(punto);
            indX++; indX = indX%ladosGiros;
            break;}

        case 'o':   // Proyeccion ortogonal

            //Restauramos la matriz identidad en la matriz de proyecciÃ³n
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(xLeft, xRight, yBot, yTop, N, F);
            escena->escalar(1,1,1);
            break;

        case 'p':   // Proyeccion perspectiva

            //Restauramos la matriz identidad en la matriz de proyecciÃ³n
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective (5, 2, N, F);
            escena->escalar(1,1,1);
            break;

        case 'u':   // Roll hacia la izquierda
            camara->roll(5);   // pasamos el angulo por parametro
            break;

        case 'i':   // Roll hacia la derecha
            camara->roll(-5);   // pasamos el angulo por parametro
            break;

        case 'j':   // Yaw hacia la izquierda
            camara->yaw(1);
            break;

        case 'k':   // Yaw hacia la derecha
            camara->yaw(-1);
            break;

        case 'n':   // Pitch hacia arriba
            camara->pitch(1);
            break;

        case 'm':   // Pitch hacia abajo
            camara->pitch(-1);
            break;

        case 'l':{   // Proyeccion oblicua
            PV3D* d = new PV3D(0.01,0.01,1,0);
            camara->proyecOblicua(d);
            delete d;
            escena->escalar(1,1,1);
            break;
        }

        case '8':{   // Trasladar escena eje Y positivamente
            escena->trasladar(0,1,0);
            break;
        }

        case '9':{   // Trasladar escena eje Y negativamente
            escena->trasladar(0,-1,0);
            break;
        }

        case 'q':{   // Escalar escena positivamente
            escena->escalar(1.5,1.5,1.5);
            break;
        }

        case 'w':{   // Escalar escena negativamente
            escena->escalar(0.5,0.5,0.5);
            break;
        }

        case 'ñ':{   // Rotar escena EjeY positivamente
            escena->rotar(1,0,1,0);
            break;
        }

        case 'ç':{   // Rotar escena EjeY negativamente
            escena->rotar(-1,0,1,0);
            break;
        }

        default:
            break;
    }
    GLScene();
}

//---------------------------------------------------------------------------

void TGLForm3D::actDesIluminacion(){

    if(luzAmbiente) actLuzAmbiente();
    else            desLuzAmbiente();

    // Luz Remota
    if(luzRemota)   actLuzRemota();
    else            glDisable(GL_LIGHT2);
    
    // Niebla
    if(niebla)  actNiebla();
    else        glDisable(GL_FOG);

}

/*  Añadir luz ambiente global (baño de luz) a la escena. Esta luz se debe poder 
    activar o desactivar de manera que, en ausencia de fuentes de luz encendidas, la 
    escena permanezca completamente a oscuras, si esta luz no está activada */
void TGLForm3D::actLuzAmbiente(){
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Activamos y configuramos la luz
    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    GLfloat PosicionLuz0[]={25.0, 25.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, PosicionLuz0);

    // Le damos luz ambiental a la escena
    GLfloat luzAmbiental[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiental);
}

void TGLForm3D::desLuzAmbiente() {

    // ponemos a 0 la luz ambiental
    GLfloat luzAmbiental[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiental);

    // Desactivamos la luz
    glDisable(GL_LIGHT_MODEL_AMBIENT);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
}


/*  Añadir una luz remota que entre en la escena formando un ángulo de 45º con el 
    plano XZ, y que provenga del este. Esta luz direccional se debe poder encender o apagar*/
void TGLForm3D::actLuzRemota() {

    glEnable(GL_LIGHT2);

    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.0,0.0,0.0,1.0};
    glLightfv(GL_LIGHT2, GL_AMBIENT, LuzAmbiente);
    GLfloat lightPos[] = { 2.0f, 2.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
}

/*  Añadir niebla a la escena. */
void TGLForm3D::actNiebla() {
    /* 1. Seleccionamos el modo de niebla: */
    glFogi(GL_FOG_MODE, GL_LINEAR); // lineal: para indicios de profundidad
    //glFogi(GL_FOG_MODE, GL_EXP);  // Exponencial: para niebla espesa o nubes
    //glFogi(GL_FOG_MODE, GL_EXP2); // Gaussiana: para neblina y humo

    /* 2. Una vez que hemos elegido el tipo de niebla, debemos elegir un color para la niebla que se mezclará con nuestra escena */
    GLfloat colorNiebla[3]= {0.1,0.1,0.1};
    glFogfv(GL_FOG_COLOR, colorNiebla);

    /* 3. Configuramos la niebla */
    glFogf(GL_FOG_START, 70.0f);
    glFogf(GL_FOG_END, 400.0f);

    // Si elegimos Exponencial (NO lineal)
    //glFogf(GL_FOG_DENSITY, 0.5f);

    /* 4. Activamos la niebla: */
    glEnable(GL_FOG);
}


//---------------------------------------------------------------------------
//---------------------------- MENU -----------------------------------------
//---------------------------------------------------------------------------


void __fastcall TGLForm3D::Niebla1Click(TObject *Sender)
{
    niebla = !niebla;
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::LuzRemota1Click(TObject *Sender)
{
    luzRemota = !luzRemota;
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::LuzAmbiente1Click(TObject *Sender)
{
    luzAmbiente = !luzAmbiente;
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::LuzLampara1Click(TObject *Sender)
{
    Lampara* l = (Lampara*)escena->getLampara();
    l->toggleLuz(); GLScene(); GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Derecha1Click(TObject *Sender)
{
    escena->getLampara()->getTAfin()->traslacion(0,0,-1);
    GLScene(); GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Izquierda1Click(TObject *Sender)
{
    escena->getLampara()->getTAfin()->traslacion(0,0,1);
    GLScene(); GLScene();
}
//---------------------------------------------------------------------------


void __fastcall TGLForm3D::Msalta1Click(TObject *Sender)
{
    Lampara* l = (Lampara*)escena->getLampara();
    l->getTAfin()->escalacion(1,1.1,1);
    l->getTAfin()->traslacion(0,-0.6,0);
    l->sumaAlturaLampara(0.4);

    GLScene(); GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Menosalta1Click(TObject *Sender)
{
    Lampara* l = (Lampara*)escena->getLampara();
    l->getTAfin()->escalacion(1,0.9,1);
    l->getTAfin()->traslacion(0,0.6,0);
    l->sumaAlturaLampara(-0.4);
    GLScene(); GLScene();
}
//---------------------------------------------------------------------------

