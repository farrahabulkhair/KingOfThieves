#include <iostream>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

float xaxis = 0;
float yaxis = 0;
float xV = 5;
float yV = 13;
float gravity = 0.5;
bool jump;
bool djump;
bool wall;
bool lvl;
bool won;
bool reverse;
bool die;
int timeElapsed = 0;

void DrawString (std::string s, float x, float y)
{
    unsigned int i;
    glRasterPos2f(x, y);
    
    for (i = 0; i < s.length(); i++)
        glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}
void drawCircle(int x, int y, float r)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}
void drawRect(int x, int y, int w, int h)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void drawCharacter(int x,int y)
{
    glColor3f(0.086, 0.39, 0.88);
    drawCircle(x, y, 40);
    glColor3f(1, 1, 1);
    drawCircle(x+20, y+20, 10);
    glColor3f(1, 1, 1);
    drawCircle(x, y+20, 10);
    glColor3f(0, 0, 0);
    drawCircle(x+20, y+25, 5);
    glColor3f(0, 0, 0);
    drawCircle(x-5, x+20, 5);
    glColor3f(0, 0, 0);
    drawCircle(x+10, x-20, 7);
}
void drawBar()
{
    glColor3f(0.44, 0.15, 0.045);
    drawRect(20, 300, 600, 40);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(20, 320, 600, 3);
    glColor3f(0.6, 0.6, 0.6);
    //top half
    drawRect(70, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(120, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(170, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(220, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(270, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(320, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(370, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(420, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(470, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(520, 320, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(570, 320, 3, 20);
    //bottom half
    glColor3f(0.6, 0.6, 0.6);
    drawRect(40, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(90, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(140, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(190, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(240, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(290, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(340, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(390, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(440, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(490, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(540, 300, 3, 20);
    glColor3f(0.6, 0.6, 0.6);
    drawRect(590, 300, 3, 20);
}
void drawBorders()
{
    //glColor3f(0.64, 0.28, 0.22);
    glColor3f(0.44, 0.15, 0.045);
    drawRect(0, 780, 800, 40);
    glColor3f(0.44, 0.15, 0.045);
    drawRect(0, 0, 800, 20);
    glColor3f(0.44, 0.15, 0.045);
    drawRect(780, 0, 20, 800);
    glColor3f(0.44, 0.15, 0.045);
    drawRect(0, 0, 20, 800);
}
void drawTube(){
    glColor3f(0.95, 0.70, 0.10);
    drawRect(20, 470, 60, 120);
    drawRect(82, 450, 20, 160);
    glColor3f(0.99, 0.65, 0.10);
    drawRect(20, 570, 60, 10);
    drawRect(82, 590, 20, 10);
}
void obstacle()
{
    glColor3f(1, 0, 0);
    drawRect(300, 20, 20, 110);
}
// Keyboard handler function
//   key: the key pressed on the keyboard
//   x  : the X coordinate of the mouse cursor at the moment of pressing the key
//   y  : the Y coordinate of the mouse cursor at the moment of pressing the key
void Key(unsigned char key, int x, int y)
{
    if (key == ' ' && !jump)
    {
        jump = true;
    }
    else if(jump) djump = true;
}
// KeyboardUp handler function
//   similar to the Keyboard handler function except that it is called only when the key is released
void KeyUp(unsigned char key, int x, int y)
{
    //jump = 0;
}


void anim()
{
    // Moves the object
    xaxis+=xV;
    
    // Dies from obstacle
    if (yaxis < 139 && xaxis > 240 && xaxis < 300 && !lvl) {
        xaxis = 300;
        die = true;
    }
    // Changes direction of object when bumbs into wall
    if (xaxis < 0 || xaxis > 680)
    {
        xV *= -1;
    }
    // Jumps if pressed space
    if (jump)
    {
        yaxis += yV;
        yV -= gravity;
    }
    //Double jumps if touched wall
    if (jump && djump && (xaxis > 678 && xaxis <= 680))
    {
        yV = 13;
        djump = false;
    }
    // Stops the jump when touches ground
    if (yaxis <= 0)
    {
        lvl = false;
        reverse = false;
        jump = false;
        yV = 13;
    }
   
    // Stops on the the upper bar
    if (yaxis > 325)
    {
        lvl = true;
        if (xaxis > 0 ) {
            reverse = true;
        }
    }
    
    
    if (yaxis < 320 && lvl && (xaxis >0 && xaxis <680))
    {
        jump = false;
         yV = 13;
        
    }
    
    if (lvl && xaxis > 590 && reverse && !jump )
    {
        
            yaxis -= yV;

        
    }
    
    if (yaxis > 400 && xaxis < 50 )
    {
        won = true;
    }
    
    
    
    glutPostRedisplay();
    
}



void Timer()
{
    int t = glutGet(GLenum(GLUT_ELAPSED_TIME));
    timeElapsed = t/1000;
    char s[100] = "Time: ";
    char seconds[100];
    sprintf(seconds, "%d", timeElapsed);
    strcat(s, seconds);
    DrawString(s, 680, 720);
}
void end()
{
    glColor3f(0.44, 0.15, 0.045);
    drawRect(20, 300, 600, 40);
    drawRect(20, 300, 600, 40);
    drawRect(20, 300, 600, 40);
    drawRect(20, 300, 600, 40);
    
}
void drawDie()
{
    glClearColor(0.9, 0, 0, 0);
    glColor3f(0, 0, 0);
    DrawString("YOU DIED!!", 300 , 500);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    if (won) {
        die = false;
        
        glClearColor(0, 1, 0.7, 0);
        glColor3f(0, 0, 0);
        DrawString("YOU WON!!", 300 , 500);
    }
    if (die) {
        drawDie();
    }
    
    glPushMatrix();
    
    if (!won && !die)
    {
        glTranslatef(xaxis, yaxis, 0);
        drawCharacter(60,60);
        
    }
    glPopMatrix();
    if (!won && !die)
    {
    Timer();
    }
    drawBar();
    drawBorders();
    drawTube();
    obstacle();
    glFlush();
}

int main(int argc, char** argr)
{
    glutInit(&argc, argr);
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 150);
    
    glutCreateWindow("King of Thieves");
    glutDisplayFunc(Display);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.84, 0.50, 0.45, 0);
    gluOrtho2D(0, 800, 0, 800);
    glutDisplayFunc(Display);
    glutIdleFunc(anim);
    
    glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed
   // glutKeyboardUpFunc(KeyUp);  // sets the KeyboardUp handler function; called when a key is released
    
    glutMainLoop();
    return 0;
}
