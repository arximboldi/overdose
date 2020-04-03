//**************************************************************************
// Prática 1
// Ejemplo de las distintas primitivas
//
// Domingo Martin Perandres 2008
//
// GPL
//**************************************************************************
#include <cstdlib>
#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <ctype.h>
//#include "point.h"

// tipos
GLint Draw_type;


// tamao de los ejes
const int AXIS_SIZE=5000;

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


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
  
  GLfloat Vertices[8][3]= {{5,0,0},{4,4,0},{0,5,0},{-4,4,0},{-5,0,0},{-4,-4,0},{0,-5,0},{4,-4,0}};

  GLfloat Vertices2[8][3] = {{4,-4,0},{4,4,0},{0,-2,0},{0,4,0},{-4,-4,0},{-4,4,0}};
  int i;

  glColor3f(0,0,0.8);
  glPointSize(6);

  switch (Draw_type){
  case GL_POINTS:
    glColor3f(0,0,0.8);
    glBegin(GL_POINTS);
    break;
  case GL_LINES:
    glColor3f(0.75,0.75,0.75);
    glPointSize(7);
    glLineWidth(2);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_LINES);
    break;
  case GL_LINE_STRIP:
    glColor3f(0,1,1);
    glPointSize(7);
    glLineWidth(2);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();

    glColor3f(1,1,0);
    glBegin(GL_LINE_STRIP);
    break;
  case GL_LINE_LOOP:
    glColor3f(0,1,0);
    glPointSize(7);
    glLineWidth(2);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();

    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    break;
  case GL_POLYGON:
    glColor3f(0,1,0);
    glPointSize(7);
    glLineWidth(3);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glColor3f(0,0,1);

    glBegin(GL_POLYGON);
    break;
  case GL_QUADS:
    glColor3f(0,0.5,0);
    glBegin(GL_POINTS); 
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glColor3f(0,0.7,0);
    glPointSize(7);
    glLineWidth(3);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();

    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    for (i=0;i<4;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();

    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    for (i=4;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    break;
  case GL_QUAD_STRIP:
    glColor3f(0,1,1);
    glBegin(GL_POINTS); 
    for (i=0;i<6;i++){
      glVertex3fv((GLfloat *) &Vertices2[i]);
    }
    glEnd();
    glLineWidth(3);
    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(4,-4,0);
    glVertex3f(4,4,0);
    glVertex3f(0,4,0);
    glVertex3f(0,-2,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,-2,0);
    glVertex3f(0,4,0);
    glVertex3f(-4,4,0);
    glVertex3f(-4,-4,0);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (i=0;i<6;i++){
      glVertex3fv((GLfloat *) &Vertices2[i]);
    }  
  glEnd();
    break;
  case GL_TRIANGLES:
    glColor3f(0,1,1);
    glPointSize(7);
    glLineWidth(2);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glColor3f(1,0,1);
    glPointSize(7);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (i=0;i<3;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (i=3;i<6;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glColor3f(0,0,0.8);
    glBegin(GL_TRIANGLES);
    break;
  case GL_TRIANGLE_STRIP: 
    glColor3f(0,0,0.6);
    glBegin(GL_POINTS); 
    for (i=0;i<6;i++){
      glVertex3fv((GLfloat *) &Vertices2[i]);
    }
    glEnd();
    glLineWidth(3);
    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    for (i=0;i<3;i++){
      glVertex3fv((GLfloat *) &Vertices2[i]);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (i=1;i<4;i++){
      glVertex3fv((GLfloat *) &Vertices2[i]);
    }
    glEnd(); 
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,-2,0);
    glVertex3f(0,4,0);
    glVertex3f(-4,4,0);
    glEnd(); 
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,-2,0);
    glVertex3f(-4,4,0);
    glVertex3f(-4,-4,0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP); 
    glColor3f(0,0,1);
    for (i=0;i<6;i++){
      glVertex3fv((GLfloat *) &Vertices2[i]);
    }
    glEnd();
    break;
  case GL_TRIANGLE_FAN:
    glColor3f(0,1,1);
    glPointSize(7);
    glLineWidth(2);
    glBegin(GL_POINTS);
    for (i=0;i<8;i++){
      glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    glLineWidth(3);
    glColor3f(1,0,1);

    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(5,0,0);
    glVertex3f(4,4,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(4,4,0);
    glVertex3f(0,5,0);
    glEnd(); 
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,5,0);
    glVertex3f(-4,4,0);
    glEnd(); 
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(-4,4,0);
    glVertex3f(-5,0,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(-5,0,0);
    glVertex3f(-4,-4,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(-4,-4,0);
    glVertex3f(0,-5,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,-5,0);
    glVertex3f(4,-4,0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    break;
  }
  for (i=0;i<8;i++){
    glVertex3fv((GLfloat *) &Vertices[i]);
  }
  glEnd();
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
  case 282:Draw_type=GL_POINTS;break;// F1
  case 283:Draw_type=GL_LINES;break;
  case 284:Draw_type=GL_LINE_STRIP;break;
  case 285:Draw_type=GL_LINE_LOOP;break;
  case 286:Draw_type=GL_POLYGON;break;
  case 287:Draw_type=GL_QUADS;break;
  case 288:Draw_type=GL_QUAD_STRIP;break;
  case 289:Draw_type=GL_TRIANGLES;break;
  case 290:Draw_type=GL_TRIANGLE_STRIP;break;
  case 291:Draw_type=GL_TRIANGLE_FAN;break;

  case 292:
    screen=SDL_GetVideoSurface();
    SDL_SetVideoMode(screen->w,screen->h,8,SDL_OPENGL|SDL_RESIZABLE);
    SDL_WM_ToggleFullScreen(screen);
    break;
  }
  draw_scene();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
  // se inicalizan la ventana y los planos de corte
  Window_width=5;
  Window_height=5;
  Front_plane=10;
  Back_plane=1000;

  // se inicia la posicion del observador, en el eje z
  Observer_distance=2*Front_plane;
  Observer_angle_x=0;
  Observer_angle_y=0;

  // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
  // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
  glClearColor(1,1,1,1);

  // se habilita el z-bufer
  glEnable(GL_DEPTH_TEST);
  //
  change_projection();
  //
  glViewport(0,0,UI_window_width,UI_window_height);
  //
  Draw_type=GL_POINTS;
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

  // Se inicializa SDL
  if( SDL_Init(SDL_INIT_VIDEO)<0) {
    printf("No se puede inicializar SDL");
    exit(1);
  }

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8);
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8);
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8);
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,24);
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);

  if (SDL_SetVideoMode(500,500,8,SDL_OPENGL|SDL_RESIZABLE)==NULL){
    printf("No se puede inciacializar OpenGL\n");
    SDL_Quit();
    exit(1);
  }

  initialize();

  SDL_EnableKeyRepeat(300,50);
  // se indica el nombre de la ventana
  SDL_WM_SetCaption( "Practica 1", "Practica 1" );

  draw_scene();
  // el bucle de enventos
  while(!Done) {
    SDL_WaitEvent(&Evento);
    switch (Evento.type) {
    case SDL_VIDEOEXPOSE:
      draw_scene();
      break;
    case SDL_VIDEORESIZE:
      change_window_size(Evento.resize.w,Evento.resize.h);
      break;
    case SDL_KEYDOWN:
      keys(&Evento.key.keysym);
      break;
    case SDL_QUIT:
      Done=true;
      break;
    default:
      break;
    }
  }

  //
  SDL_Quit( );

  return 0;
}
