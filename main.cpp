#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <windows.h>
#include <math.h>

// variable for rotation of teapot
 
float zRotated = 0.0;

// variables for mouse and keyboard

float cx, cz, z;
  
// cone function

void cone(){
    glPushMatrix();
    glColor3f(1,0,0);
    glRotatef(-87,1,0,0);
    glRotatef(40,0,0,1);
    glTranslatef(-1.5,-4.4,4);
    glScalef(1.0,0.7,1.0);
    glutSolidCone(2.5,1,4,4);
    glPopMatrix();
}

// teapot function

void drawteapot(){

    glPushMatrix();
    glRotatef(zRotated ,0,1,0);
    glTranslatef(1 + cx,1.6,1 + cz);
    glutSolidTeapot(0.3 + z);
    glPopMatrix();

}

// table function

void table(){

    glPushMatrix();
    glTranslatef(0.5 + cx,0.5,0.5 + cz);
    glScalef(0.2,0.2,0.2);
    //glRotatef(-90,0,1,0);

   glBegin (GL_QUADS) ;



    glColor3f(0.7,0.4,0.1);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(-0.7,-1.0,1.0);
    glVertex3f(-0.7,1.0,1.0);


    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-0.7,-1.0,-1.0);
    glVertex3f(-0.7,1.0,-1.0);


    glVertex3f(-0.7,1.0,-1.0);
    glVertex3f(-0.7,-1.0,-1.0);
    glVertex3f (-1.0,-1.0,-1.0);
    glVertex3f(-1.0,1.0,-1.0);


    glVertex3f(1.0,1.0,-0.7);
    glVertex3f(1.0,-1.0,-0.7);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);




    glVertex3f (-1.0,1.0,-1.0);
    glVertex3f (-1.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);


    glPopMatrix();
    glEnd();

}

// reshape function
 
void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (40.0, (GLdouble)w / (GLdouble)h, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// walls and ground function

void wall (double thickness){
    glPushMatrix();
    glColor3f(1.0,1.0,0.0);
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

// display function

void display (void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glTranslatef(0.0, 0.0, -15.0);
    glScalef(3.5,3.5,3.5);
    glRotatef(25,1,0,0);
    glRotatef(-25,0,1,0);
    wall(0.2);
    glPushMatrix();
    glRotated(-90.0,1.0,0.0,0.0);
    wall(0.02);
    glPopMatrix();
    glPushMatrix();
    glRotated(90.0,0.0,0.0,180.0);
    wall(0.02);
    glPopMatrix();
    table();
    drawteapot();
    cone();




    glutSwapBuffers();
}

// idleFunc function for anticlockwise rotation of teapot

void idleFunc (void)
{
    zRotated += 1;
    glutPostRedisplay();
}

// idleFunc1 function for clockwise rotation of teapot

void idleFunc1 (void)
{
    zRotated -= 1;
    glutPostRedisplay();
}

// idleFunc2 function to stop the rotation of teapot

void idleFunc2 (void)
{
    zRotated = 0;
    glutPostRedisplay();
}

// texture for shadows and light

void texture (void){

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


}

// MouseClick function for right and left click

void onMouseClick(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
    {

        z+=0.1;
    }
    else if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
    {

        z-=0.1;
    }
}

// keyboard function for moving xz plane for teapot and table

void keyboard(unsigned char Key,int x,int y)
    {
    if(Key=='w'){cz-=0.1;} if(Key=='s'){cz+=0.1;}//forward and back
    if(Key=='a'){cx-=0.1;} if(Key=='d'){cx+=0.1;}//left and right
    if(Key== 'h'){glutIdleFunc(idleFunc);} if(Key== 'j'){glutIdleFunc(idleFunc1);} if(Key== 'o'){glutIdleFunc(idleFunc2);}
    glutPostRedisplay();
    }

// main function

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // buffer mode
    glutInitWindowSize     (800, 700);
    glutInitWindowPosition (700, 200);
    glutCreateWindow       ("20102650");

    glClearColor (1.0, 1.0, 1.0, 0.0);

    glutDisplayFunc (display);
    glutReshapeFunc (reshapeFunc);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(onMouseClick);

    glOrtho(-100.0,100,-100.0,100,-100.0,100);
    glClearColor(1,1,1,1);
    texture(); // Lighting and textures
 
    

    glutMainLoop();
}
