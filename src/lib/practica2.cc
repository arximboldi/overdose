//**************************************************************************
// Prática 2
// Uso de las clases Cubo, Cilindro y Cono.
//  trapper0707@hotttttt  untrapper@gmail...
// María Carrasco Rodríguez
//
// GPL
//**************************************************************************
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ctype.h>
#include "cube.h"
#include "cone.h"
#include "sphere.h"
#include "cylinder.h"
#include "drawable.h"
#include "scenenode.h"
#include "plymesh.h"
#include "camera.h"
#include <SDL/SDL_mixer.h>


using namespace mge;

Drawable* draw_object = NULL;

// tamaño de los ejes
const int AXIS_SIZE=50000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamao de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformacin de proyeccion
//***************************************************************************

void change_projection()
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)l
  glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformacin de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}


void dibujar_seno(float ancho, float largo, float alto,
		  int veces, int resol)
{
  static float t = 0;
  int i;

  glBegin(GL_QUAD_STRIP);
  glColor3f(0, 1, 0);
  for (i = 0; i < veces * resol; ++i) {
    glVertex3f(-largo/2 + largo * (float)i/(veces * resol),
	       alto * sin(2 * M_PI * (float)i/resol + t),
	       -(float)ancho/2.0);
    glVertex3f(-largo/2 + largo * (float)i/(veces * resol),
	       alto * sin(2 * M_PI * (float)i/resol + t),
	       +(float)ancho/2.0);
  }
  glEnd();

  t += 0.1;
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
  glPolygonMode( GL_BACK, GL_LINE );
  glPolygonMode( GL_FRONT, GL_FILL );
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  if (draw_object)
    draw_object->draw();
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
  clear_window();
  change_observer();
  draw_axis();
  draw_objects();
  SDL_GL_SwapBuffers( );
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamao de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Width,int Height)
{

  //change_projection();
  SDL_SetVideoMode(Width,Height,8,SDL_OPENGL|SDL_RESIZABLE);
  glViewport(0,0,Width,Height);
  draw_scene();
}


Drawable* crear_coche()
{
  SceneNode* car = new SceneNode;

  car->getChild("chasis").attachDrawable(new Cube);
  car->getChild("chasis").setScale(PointF(6,3,2.5));
  car->getChild("dlan").attachDrawable(new Cube);
  car->getChild("dlan").setScale(PointF(4,1,2.5));
  car->getChild("dlan").setPosition(PointF(-1,2,0));
  car->getChild("foco_0").attachDrawable(new Cone);
  car->getChild("foco_0").setPosition(PointF(3.2,0,1));
  car->getChild("foco_0").setRotate(Point4F(90,0,0,1));
  car->getChild("foco_0").setScale(PointF(0.5,0.5,0.5));
  car->getChild("foco_1").attachDrawable(new Cone);
  car->getChild("foco_1").setPosition(PointF(3.2,0,-1));
  car->getChild("foco_1").setRotate(Point4F(90,0,0,1));
  car->getChild("foco_1").setScale(PointF(0.5,0.5,0.5));
  //car->getPath("chasis/foco_0").setScale(PointF(0.5,0.5,0.5));
  //car->getPath("chasis/foco_1").attachDrawable(new Cone);
  car->getChild("rueda_0").attachDrawable(new Cylinder);
  car->getChild("rueda_0").setPosition(PointF(2,-1,1));
  car->getChild("rueda_0").setRotate(Point4F(90,1,0,0));
  car->getChild("rueda_1").attachDrawable(new Cylinder);
  car->getChild("rueda_1").setPosition(PointF(-2,-1,1));
  car->getChild("rueda_1").setRotate(Point4F(90,1,0,0));
  car->getChild("rueda_2").attachDrawable(new Cylinder);
  car->getChild("rueda_2").setPosition(PointF(2,-1,-2));
  car->getChild("rueda_2").setRotate(Point4F(90,1,0,0));
  car->getChild("rueda_3").attachDrawable(new Cylinder);
  car->getChild("rueda_3").setPosition(PointF(-2,-1,-2));
  car->getChild("rueda_3").setRotate(Point4F(90,1,0,0));
  //car->getPath("rueda_0/tornillo").attachDrawable(new Cone);
  //car->getPvoid normalize(Block& b);ath("rueda_0/tornillo").setPosition(PointF(1,0,0));
  car->setPosition(PointF(5,5,5));
  car->setPosition(PointF(-1,-1,-1));
  return car;
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void keys(SDL_keysym *Tecla)
{
  
  SDL_Surface *screen;

  switch (Tecla->sym){
  case 276:Observer_angle_y--;break;// izquierda
  case 275:Observer_angle_y++;break;// derecha
  case 273:Observer_angle_x--;break;// arriba
  case 274:Observer_angle_x++;break;// abajo
  case 280:Observer_distance*=1.2;break;// avance pagina
  case 281:Observer_distance/=1.2;break;// retroceso pagina
    // primitivas graficas
  case 282: delete draw_object; draw_object = new Cube; break;// F1
  case 283: delete draw_object; draw_object = new Cone; break;
  case 284: delete draw_object; draw_object = new Cylinder; break;
  case 285: delete draw_object; draw_object = new Sphere; break;
  case 286: delete draw_object; draw_object = crear_coche(); break;
  case 287: delete draw_object; draw_object = new PlyMesh("models/bsurf.ply"); break;
    /*case 286:Draw_type=GL_POLYGON;break;
      case 287:Draw_type=GL_QUADS;break;
      case 288:Draw_type=GL_QUAD_STRIP;break;
      case 289:Draw_type=GL_TRIANGLES;break;
      case 290:Draw_type=GL_TRIANGLE_STRIP;break;
      case 291:Draw_type=GL_TRIANGLE_FAN;break;

      case 292:
      screen=SDL_GetVideoSurface();
      SDL_SetVideoMode(screen->w,screen->h,8,SDL_OPENGL|SDL_RESIZABLE);
      SDL_WM_ToggleFullScreen(screen); 
      break;*/
  } 
  draw_scene();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
  bool Done;
  SDL_Event Evento;
  Mix_Music *musica;
  int done = 0;
  int canal;

  // Se inicializa SDL

  // Cargamos sonido
  musica = Mix_LoadMUS("./sounds/champ.mid"); 
  if ( musica == NULL ) {
    printf("No pude cargar sonido: %s\n", Mix_GetError());
    exit(1);
  }
  // Reproducción del sonido.
  // Esta función devuelve el canal por el que se reproduce el sonido
  canal = Mix_PlayMusic(musica, -1);

 
  draw_scene();
  // el bucle de enventos
  while(!Done) {
    SDL_WaitEvent(&Evento);
    switch (Evento.type) {

    }
  }
  // paramos la música
  Mix_HaltMusic();

  // liberamos recursos
  Mix_FreeMusic(musica);

  //
  SDL_Quit( );

  return 0;
}

