
#include <cmath>  // عشان اقدر ارسم الدائرة فيها الحسابات الخاصة   
#include <GL\glew.h>  // A cross-platform open-source C/C++ extension loading library
#include <GL\freeglut.h>   // handle the window-managing operations
#include <string>

using namespace std;


float Rangle = 0.0; // قيمه الدوران 


// اعطي قيمه للدوران على حسب المحاور اللي اباه يدور فيها 
float RX = 0.0;
float RY = 1.0;
float RZ = 0.0;


//الالوان اللي اباها وتنحط في الرسمه

float red_R = 0.86;
float red_G = 0.08;
float red_B = 0.07;

float green_R = 0.52;
float green_G = 0.79;
float green_B = 0.19;

float rose_R = 0.99;
float rose_G = 0.52;
float rose_B = 0.49;


// draw the circle 
void circle_drawing( float r, float x, float y, float colorred, float colorgreen, float colorblue , float sx, float sy){

    // for the angle
    float currentA = 1.0;

 
    glPushMatrix();

    glTranslatef(x, y, 0);
    glScalef(sx, sy, 0);
    glColor3f(colorred, colorgreen, colorblue);

    glBegin(GL_POLYGON);

    //هنا سوينا لووب عشان نرسم كل نقطة لين 360 وكذا اطتملت الدائرة 
     while (true){  
        if (currentA <= 360){
            glVertex2f(cos(currentA) * r, sin(currentA) * r);// معادلة عشان احاثيات النقطة 
        }
        else {//اذا كانت الزاوية اكبر من 360 يوقف 
             
            break;
        }
        //اذا انتهت اكتمال الدورة نزيده بواحد 
        currentA += 1;
    }
     
    glEnd();

    glPopMatrix();

}

//يحدد حالة الوجه 
string state = "happy";


// for the strawberry 
void s_leaves(float rotateangle, float x , float y , int flip) {

    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(rotateangle, 0, 0,1);

    glBegin(GL_POLYGON);

    glColor3f(green_R, green_G, green_B);

    glVertex2f(flip * 0.16, 0.59);
    glVertex2f(flip * 0.20, 0.61);
    glVertex2f(flip * 0.23, 0.62);
    glVertex2f(flip * 0.29, 0.62);
    glVertex2f(flip * 0.36, 0.60);
    glVertex2f(flip * 0.4, 0.6);
    glVertex2f(flip * 0.44, 0.60);
    glVertex2f(flip * 0.47, 0.60);
    glVertex2f(flip * 0.45, 0.55);
    glVertex2f(flip * 0.41, 0.50);
    glVertex2f(flip * 0.36, 0.46);
    glVertex2f(flip * 0.34, 0.45);
    glVertex2f(flip * 0.27, 0.45);
    glVertex2f(flip * 0.23, 0.47);
    glVertex2f(flip * 0.20, 0.48);
 
    glEnd();

    
    glPopMatrix();
}

void eye(float x, float y) {
    
    glPushMatrix();
    glTranslatef(x, y, 0);

    //رسم العين
    circle_drawing(0.07, -0.2, 0, 0, 0, 0, 1, 1);

   // اللي في نص العين 
    circle_drawing(0.023, -0.225, 0.02, 1, 1, 1, 1, 1);
    circle_drawing(0.015, -0.165, 0.03, 1, 1, 1, 1, 1);
    circle_drawing(0.015, -0.205, -0.03, 1, 1, 1, 1, 1);


    if (state == "happy") {

        circle_drawing(0.05, -0.2, -0.07, red_R, red_G, red_B, 2, 0.5);//اذا كان سعيد نغير شكل العين
    }
    else if (state == "sad"){

        circle_drawing(0.05, -0.2, 0.07, red_R, red_G, red_B, 2, 0.5);  //اذا كان حزين نغير شكل العين


    }


    glPopMatrix();
}

void mouth(float x, float y) {
    glPushMatrix();

    glTranslatef(x, y, 0);
    
    if (state == "happy") {

        //اذا كان سعيد نغير شكل الفم
        circle_drawing(0.15, 0, -0.065, 0, 0, 0, 1, 1);
        circle_drawing(0.1, 0, 0, red_R, red_G, red_B, 2, 1);

    }
    else if (state == "sad")
    {
        //زي الهبي 
        circle_drawing(0.15, 0,-0.135, 0, 0, 0, 1, 1);
        circle_drawing(0.1, 0, -0.2, red_R, red_G, red_B, 2, 1);

    }
    else if (state == "surprised")
    {
        //كمان هنا اذا كان متفاجئ        
        circle_drawing(0.08, 0, -0.1, 0, 0, 0, 1, 1);
    }

    glPopMatrix();
}

//  هنا طريقة ثانيه يخليني اعيد الرسم كل 5 ميلي غير ال play
void newframe(int) {
    glutPostRedisplay();
   glutTimerFunc(10, newframe, 0); 
}

static void play(void) {

    glutPostRedisplay();

}


void Keyboard(unsigned char key, int x, int y) {
   
    switch (key){
        
    case 'h':
        state = "happy";

        RX = 0.0;
        RY = 1.0; //عشان يدور حول واي 
        RZ = 0.0;

        break;
       
    case 's':
        state = "sad";

        RX = 1.0;//عشان يدور حول اكس 
        RY = 0.0;
        RZ = 0.0;

        break;
       
    case 'o':
        state = "surprised";

        RX = 0.0;
        RY = 0.0;
        RZ =1.0; // يدور حول زد

        break;
    }
}


//عشان اطبعها كلها سوا 
void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9f, 0.9f, 0.8f, 1.0f);

    glLoadIdentity();

    glRotatef(Rangle, RX, RY, RZ);


    //البداية جسم الفراولة ك اساس 
    circle_drawing(0.42, 0.10, 0.10, red_R, red_G, red_B, 1, 1);
    circle_drawing(0.42, -0.14, 0.10, red_R, red_G, red_B, 1, 1);
    circle_drawing(0.20, -0.01, -0.52, red_R, red_G, red_B, 1, 1);

    glBegin(GL_POLYGON);
    glColor3f(red_R, red_G, red_B);
    glVertex2f(-0.18, -0.63);
    glVertex2f(-0.50, -0.12);
    glVertex2f(0.46, -0.12);
    glVertex2f(0.16, -0.63);
    glEnd();
    


    // الاوراق الخضراء حقت الفراولة
    glPushMatrix();

    glScalef(1.25, 1.1, 1.2);
    glTranslatef(0, -0.1, 0);
    circle_drawing(0.1, 0, 0.57, green_R, green_G, green_B, 1.3, 1.1);
    s_leaves(0,-0.12,0 ,1);
    s_leaves(-55 , -0.53, 0.32 ,1);
    s_leaves(55, 0.53, 0.32, -1);
    s_leaves(0, 0.12, 0 , -1);


    //ساق الاوراق
    glBegin(GL_POLYGON);
    glColor3f(green_R, green_G, green_B);
    glVertex2f(-0.01, 0.65);
    glVertex2f(-0.05, 0.74);
    glVertex2f(-0.08, 0.80);
    glVertex2f(0, 0.83);
    glVertex2f(0.01, 0.79);
    glVertex2f(0.03, 0.73);
    glVertex2f(0.03, 0.66);
    glEnd();


    glPopMatrix();
   


    //رسم الفم 
    mouth(0, -0.1);
  
    //رسم العيون 
    eye(0,0);
    eye(0.4, 0);
  
    //رسم الخدود
    circle_drawing(0.035,-0.28,-0.1,rose_R,rose_G,rose_B,1.5,1);
    circle_drawing(0.035, 0.28, -0.1, rose_R, rose_G, rose_B, 1.5, 1);
   

    glutSwapBuffers();

    
    Rangle += 0.11; //نزيد قيمة الدوران كل ما كان الرقم صغير راح يمشي بطئ

  
}


int main(int argc, char* argv[]){
  
    glutInit(&argc, argv); 
    glutInitWindowSize(500, 500);
    glutCreateWindow("Assignment #1 (strawberry) made by Alaa :)"); 

    glutIdleFunc(play);
    glutDisplayFunc(display);  
    glutKeyboardFunc(Keyboard);
 
   // glutTimerFunc(0, newframe, 0); //هذي طريقة ثانيه يقعد يعيد الرسمة كل شوي ب وقت معين   

    
    glutMainLoop(); 

    return 0;
}

