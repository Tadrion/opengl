#include <cstdio>
#include <cstdlib>
#include <GL/glfw.h>

const int windowWidth = 800;
const int windowHeight = 600;  

float rotate_y = 0;
float rotate_z = 0;
const float rotations_per_tick = 0.2;

double timer = 0.0;
double old_timer = 0.0;

typedef struct vert{
  int x,y,z;
}VERTEX;

VERTEX v[9];

void Shut_Down(int return_code)
{
  glfwTerminate();
  exit(return_code);
}

void Init() {
  
  if( glfwInit() != GL_TRUE ) {
    Shut_Down(1);
  }

  if (glfwOpenWindow(windowWidth,windowHeight,5,6,5,0,0,0,GLFW_WINDOW) != GL_TRUE)
    Shut_Down(1);
  glfwSetWindowTitle("My Window");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = ((float)windowHeight) / windowWidth;
  glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1,1000);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  //glfwSwapInterval(1);
}

void Draw_Square(float red, float green, float blue){
  glBegin(GL_QUADS);
  {
    glColor3f(red, green, blue);
    glVertex2i(1, 11);
    glColor3f(red * .8, green * .8, blue * .8);
    glVertex2i(-1,11);
    glColor3f(red * .5, green * .5, blue * .5);
    glVertex2i(-1, 9);
    glColor3f(red * .8, green * .8, blue * .8);
    glVertex2i(1, 9); 
  }
  glEnd();
}

void Draw()
{
  glLoadIdentity();
  
  glTranslatef(0,0,-50);

  glRotatef(rotate_y, 0, 1, 0);
  glRotatef(rotate_z, 0, 0, 1);

  int i = 0, squares = 15;
  float red = 0, blue = 1;
  
  for(; i < squares; ++i) {
    glRotatef(360.0/squares, 0, 0, 1);
    red += 1.0 /12;
    blue -= 1.0/12;
    Draw_Square(red, .6, blue);
  }
}

void Main_Loop() {
  double old_time = glfwGetTime();
  int it = 0;
  while(1)
    {
      double current_time = glfwGetTime();
      double delta_rotate = (current_time - old_time) * 
	rotations_per_tick * 360;
      old_time = current_time;

      if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
	break;

      rotate_z += delta_rotate;
      
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      Draw();
      
      glfwSwapBuffers();
      
      it++;
      timer = glfwGetTime();
      
      if(timer - old_timer >= 1.0) {
	printf("%lf\n",it / (timer - old_timer) );
	it = 0;
	old_timer = timer;
      }
    }
}

void DrawSq(VERTEX a1,VERTEX a2, VERTEX a3, VERTEX a4, float r = 1, float g = 1, float b = 1) {
  
    glBegin(GL_QUADS);
    {
      glColor3f(r,g,b);
      glVertex3i(a1.x,a1.y, a1.z);
      
      glColor3f(r,g,b);
      glVertex3i(a2.x,a2.y, a2.z);
      
      glColor3f(r,g,b);
      glVertex3i(a3.x,a3.y, a3.z);
      
      glColor3f(r,g,b);
      glVertex3i(a4.x,a4.y, a4.z);    
    }
  glEnd();
}


void MDraw() {
  glLoadIdentity();

  glTranslatef(0,0,-30);
  
  glRotatef(45.0, 1, 1, 0);

  float r = 1;
  float g = 1;
  float b = 1;

  glBegin(GL_QUADS);
  {
    glColor3f(r,g,b);
    glVertex3i(-5,-5, 0);
    
    glColor3f(r,g,b);
    glVertex3i(-5,5, 0);
    
    glColor3f(r,g,b);
    glVertex3i(5,5, 0);
    
    glColor3f(r,g,b);
    glVertex3i(5,-5, 0);    
  }
  glEnd();

  glBegin(GL_QUADS);
  {
    glColor3f(0.8*r,0.1*g,0.1*b);
    glVertex3i(5,5, 0);
    
    glColor3f(0.8*r,0.1*g,0.1*b);
    glVertex3i(5,5, -5);
    
    glColor3f(0.8*r,0.1*g,0.1*b);
    glVertex3i(5,-5, -5);    
  
    glColor3f(0.8*r,0.1*g,0.1*b);
    glVertex3i(5,-5, 0);
    }
  glEnd();

  


  glfwSwapBuffers();
}
void Loop2() {

  float x = 0.0;
  
  while(1) {
    if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
	break;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1);

    glLoadIdentity();
    
    glTranslatef(0,0,-30);
    
    glRotatef(x, 1, 1, 0);
    //glRotatef(x, 0, 1, 0);
    //glRotatef(x, 0, 1, 2);

    DrawSq(v[1],v[2],v[3],v[4],1,1,1);
    DrawSq(v[1],v[4],v[8],v[5],1,0,0);
    DrawSq(v[1],v[2],v[6],v[5],0,1,0);
    DrawSq(v[4],v[3],v[7],v[8],0,0,1);
    DrawSq(v[2],v[3],v[7],v[6],1,1,0);
    DrawSq(v[5],v[6],v[7],v[8],0,1,1);

    x += 1.0;
    
    glfwSwapBuffers();
  }

}


int main() {
  int w = 4;

  // v[1].x = 0;
  // v[1].y = 0;
  // v[1].z = 0;

  // v[2].x = w;
  // v[2].y = 0;
  // v[2].z = 0;

  // v[3].x = w;
  // v[3].y = w;
  // v[3].z = 0;

  // v[4].x = 0;
  // v[4].y = w;
  // v[4].z = 0;

  // v[5].x = 0;
  // v[5].y = 0;
  // v[5].z = -w;

  // v[6].x = w;
  // v[6].y = 0;
  // v[6].z = -w;

  // v[7].x = w;
  // v[7].y = w;
  // v[7].z = -w;

  // v[8].x = 0;
  // v[8].y = w;
  // v[8].z = -w;


  v[1].x = -w;
  v[1].y = -w;
  v[1].z = w;

  v[2].x = w;
  v[2].y = -w;
  v[2].z = w;

  v[3].x = w;
  v[3].y = w;
  v[3].z = w;

  v[4].x = -w;
  v[4].y = w;
  v[4].z = w;

  v[5].x = -w;
  v[5].y = -w;
  v[5].z = -w;

  v[6].x = w;
  v[6].y = -w;
  v[6].z = -w;

  v[7].x = w;
  v[7].y = w;
  v[7].z = -w;

  v[8].x = -w;
  v[8].y = w;
  v[8].z = -w;

  Init();
  Loop2();
  Shut_Down(0);
}
