#include <GL/gl.h>       // Core OpenGL functions
#include <GL/glu.h>      // Utility functions for OpenGL
#include <GL/glut.h>     // GLUT functions for window management and input handling

#include <stdio.h>       // Standard I/O functions
#include <stdbool.h>
#include <stdlib.h>      // Standard library functions
#include <math.h>        // Mathematical functions


//globalvariable
float horsePositionX = 500.0f;  // Initial position of the horse
float horseSpeed = 5.0f;        // Speed at which the horse moves

float tailRotationAngle = 0.0f;  // Initial rotation angle for the horse's tail
float tailRotationSpeed = 2.0f;  // Speed at which the tail rotates

bool isHorseRotated = false;  // Flag to track if the horse is rotated 180 degrees
bool isMovingLeftToRight = false;  // Flag to track if the horse is moving left to right
bool isRotating = false;  // Flag to check if the tail is rotating continuously






void setup() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glMatrixMode(GL_PROJECTION);       // Switch to the projection matrix
    glLoadIdentity();                  // Reset the projection matrix

    // Set the coordinate system (left, right, bottom, top)
    gluOrtho2D(0.0, 1200.0, 0.0, 600.0);
}


void river() {
    glColor3f(0.53, 0.81, 0.98);  // Set color to a light blue for the sky
    glBegin(GL_QUADS);            // Start drawing a rectangle
        glVertex2f(0.0, 0.0);   // Bottom left corner
        glVertex2f(1200.0, 0.0); // Bottom right corner
        glVertex2f(1200.0, 150.0); // Top right corner
        glVertex2f(0.0, 150.0);   // Top left corner
    glEnd();
}

void sky() {
    glBegin(GL_QUADS);  // Start drawing a quadrilateral (rectangle)

    // Top part of the sky (yellow)
    glColor3f(1.0, 1.0, 0.0);  // Yellow
    glVertex2f(0.0, 600.0);    // Top left corner
    glVertex2f(1200.0, 600.0); // Top right corner

    // Bottom part of the sky (white)
    glColor3f(1.0, 1.0, 1.0);  // White
    glVertex2f(1200.0, 200.0); // Bottom right corner of the sky
    glVertex2f(0.0, 200.0);    // Bottom left corner of the sky

    glEnd();
}

void grass() {
    glColor3f(0.0, 0.5, 0.0); // Set color to a shade of green for the grass
    glBegin(GL_POLYGON);       // Start drawing a polygon
        glVertex2f(0.0, 150.0);  // Bottom left corner
        glVertex2f(1200.0, 150.0); // Bottom right corner
        glVertex2f(1200.0, 230.0); // Top right corner (adjusted)
        glVertex2f(400.0, 293.0);  // Top right corner (adjusted)
        glVertex2f(395.0, 293.0);
        glVertex2f(390.0, 290.0);
        glVertex2f(380.0, 290.0);
        glVertex2f(370.0, 285.0);
        glVertex2f(360.0, 280.0);
        glVertex2f(350.0, 275.0);
        glVertex2f(300.0, 270.0);
        glVertex2f(250.0, 260.0);
        glVertex2f(0.0, 230.0);    // Top left corner
    glEnd();
}



void circle(float CX, float CY, float r) {
    float x, y;
    int triangleAmount = 200; // Number of triangles to form the circle
    float twicePi = 2.0f * 3.1416;

    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i <= triangleAmount; i++) {
        x = r * cos(i * twicePi / triangleAmount);
        y = r * sin(i * twicePi / triangleAmount);
        glVertex2f(x + CX, y + CY);
    }

    glEnd();
}


void trees(float x, float y){


    //body
    glBegin(GL_QUADS);
    glColor3f(0.65, 0.33, 0.13);
    glVertex2f(x, y);
    glVertex2f(x+20.0f,y);
    glVertex2f(x+20.0f, y+100.0f);
    glVertex2f(x, y+100.0f);
    glEnd();

    //leaves
    glBegin(GL_POLYGON);
    glColor3f(0.13f, 0.55f, 0.13f);
    glVertex2f(x-60.0f, y+100.0f);
    glVertex2f(x+80.0f,y+100.0f);
    glVertex2f(x+10.0f, y+200.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.13f, 0.55f, 0.13f);
    glVertex2f(x-50.0f, y+150.0f);
    glVertex2f(x+70.0f,y+150.0f);
    glVertex2f(x+10.0f, y+230.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.13f, 0.55f, 0.13f);
    glVertex2f(x-35.0f, y+200.0f);
    glVertex2f(x+55.0f,y+200.0f);
    glVertex2f(x+10.0f, y+300.0f);
    glEnd();
}

void hangingballs(float x, float y){

    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(x-31.0f, y+50.0f);
    glVertex2f(x-29.0f,y+50.0f);
    glVertex2f(x-29.0f,y+100.0f);
    glVertex2f(x-31.0f,y+100.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(x+49.0f, y+50.0f);
    glVertex2f(x+51.0f,y+50.0f);
    glVertex2f(x+51.0f,y+100.0f);
    glVertex2f(x+49.0f,y+100.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    circle(x-30,y+40,10);
    circle(x+50,y+40,10);
}


void house(float x, float y){

    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x+150.0f,y);
        glVertex2f(x+150.0f,y+150.0f);
        glVertex2f(x,y+150.0f);
    glEnd();
}

void doorandroof(float x, float y){

    glBegin(GL_POLYGON);
        glColor3f(0.8f, 0.7f, 0.5f); // Sets the color to a dark cream shade
        glVertex2f(x+50.0f,y);
        glVertex2f(x+100.0f,y);
        glVertex2f(x+100.0f,y+80.0f);
        glVertex2f(x+50.0f,y+80.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x-10.0f,y+150.0f);
        glVertex2f(x+160.0f,y+150.0f);
        glVertex2f(x+130.0f,y+180.0f);
        glVertex2f(x+20.0f,y+180.0f);
    glEnd();


}


void fishwithlines(float x, float y){

    //BODY
    glBegin(GL_POLYGON);

        glVertex2f(x-30.0f, y);
        glVertex2f(x, y-15.0f);
        glVertex2f(x+30.0f, y);
        glVertex2f(x, y+15.0f);
    glEnd();


    //line
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x, y+15.0f);
        glVertex2f(x, y-15.0f);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x+10.0f, y+10.0f);
        glVertex2f(x+10.0f, y-10.0f);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x+20.0f, y+5.0f);
        glVertex2f(x+20.0f, y-5.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    circle(x-15,y,2);
}

void fishtail(float x, float y){

    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x+20,y-15);
        glVertex2f(x+20,y+15);
    glEnd();
}

void horse(){

    float x = horsePositionX;

     glPushMatrix();  // Save the current transformation

    // Apply rotation if the horse is rotated 180 degrees
    if (isHorseRotated) {
    glTranslatef(x + 50.0f, 225.0f, 0.0f);  // Move to the horse's center
    glRotatef(0.0f, 180.0f, 0.0f, 1.0f);    // Rotate 180 degrees along the x-axis (change this)
    glTranslatef(-(x + 50.0f), -225.0f, 0.0f);  // Move back to original position
}

    //rectangle
    glBegin(GL_POLYGON);
        glColor3f(0.65f, 0.16f, 0.16f); // Sets the color to a standard brown shade
        glVertex2f(x,200.0);
        glVertex2f(x+100.0,200.0);
        glVertex2f(x+100.0,250.0);
        glVertex2f(x,250.0);
    glEnd();

    //neck
   glBegin(GL_POLYGON);
        glColor3f(0.65f, 0.16f, 0.16f); // Sets the color to a standard brown shade
        glVertex2f(x-30.0, 280.0);
        glVertex2f(x, 250.0);
        glVertex2f(x+20.0, 250.0);
        glVertex2f(x-10.0, 320.0);
    glEnd();

    //nose
     glBegin(GL_POLYGON);
        glColor3f(0.65f, 0.16f, 0.16f); // Sets the color to a standard brown shade
        glVertex2f(x-40.0, 270.0);
        glVertex2f(x-20.0, 270.0);
        glVertex2f(x-20.0, 290.0);
        glVertex2f(x-40.0, 290.0);
    glEnd();

    //lining
    glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(x-24.0, 270.0);
        glVertex2f(x-23.0, 270.0);
        glVertex2f(x-23.0, 290.0);
        glVertex2f(x-24.0, 290.0);
    glEnd();


    //fur
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(x+20.0, 250.0);
        glVertex2f(x+40.0, 250.0);
        glVertex2f(x-10.0, 320.0);
    glEnd();

    // Tail with rotation
    glPushMatrix();  // Save the current transformation
    glTranslatef(x + 100.0f, 250.0f, 0.0f);  // Move to the tail's position
    glRotatef(tailRotationAngle, 0.0f, 0.0f, 1.0f);  // Rotate the tail
    glTranslatef(-(x + 100.0f), -250.0f, 0.0f);  // Move back to original position

    //tail
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(x+110.0, 200.0);
        glVertex2f(x+120.0, 250.0);
        glVertex2f(x+100.0, 250.0);
    glEnd();

    glPopMatrix();  // Restore the previous transformation

    //legs
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(x, 170.0);
        glVertex2f(x+10.0, 170.0);
        glVertex2f(x+10.0, 200.0);
        glVertex2f(x, 200.0);
    glEnd();

    //legs
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(x+90.0, 170.0);
        glVertex2f(x+100.0, 170.0);
        glVertex2f(x+100.0, 200.0);
        glVertex2f(x+90.0, 200.0);
    glEnd();

    //eye
    glColor3f(0.0,0.0,0.0);
    circle(x-10,295,2);

    glPopMatrix();  // Restore the previous transformation

}



float boatX = 0.0f;
float paddleAngle = 0.0f; // Initial rotation angle of the paddle
void manWithBoat(){

    glPushMatrix();  // Save the current state of transformations

    // Apply translation to move the boat
    glTranslatef(boatX, 0.0f, 0.0f);


    //boat
    glBegin(GL_POLYGON);
        glColor3f(0.82f, 0.71f, 0.55f); // Sets the color to a light brown shade
        glVertex2f(300.0, 50.0);
        glVertex2f(500.0, 50.0);
        glVertex2f(530.0, 100.0);
        glVertex2f(280.0, 100.0);
    glEnd();



    //body
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(330.0, 100.0);
        glVertex2f(370.0, 100.0);
        glVertex2f(350.0, 130.0);
        glVertex2f(330.0, 130.0);
    glEnd();

    //upbody
    glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(330.0, 130.0);
        glVertex2f(340.0, 130.0);
        glVertex2f(360.0, 160.0);
        glVertex2f(330.0, 160.0);
    glEnd();

    //head
    glBegin(GL_POLYGON);
        glColor3f(0.83f, 0.69f, 0.75f); // Sets the color to a rose gold shade
        glVertex2f(333.0, 160.0);
        glVertex2f(353.0, 160.0);
        glVertex2f(353.0, 190.0);
        glVertex2f(333.0, 190.0);
    glEnd();

    //hair
    glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(333.0, 190.0);
        glVertex2f(353.0, 190.0);
        glVertex2f(357.0, 210.0);
        glVertex2f(333.0, 200.0);
    glEnd();

    //nose
    glBegin(GL_POLYGON);
        glColor3f(0.83f, 0.69f, 0.75f); // Sets the color to a rose gold shade
        glVertex2f(353.0, 170.0);
        glVertex2f(358.0, 170.0);
        glVertex2f(353.0, 180.0);
    glEnd();


    //paddle

    glPushMatrix();
    glTranslatef(347.0f, 130.0f, 0.0f);  // Move to the paddle's pivot point
    glRotatef(paddleAngle, 0.0f, 0.0f, 1.0f);  // Rotate the paddle
    glTranslatef(-347.0f, -130.0f, 0.0f);  // Move back after rotation

    glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(320.0, 40.0);
        glVertex2f(335.0, 40.0);
        glVertex2f(350.0, 130.0);
        glVertex2f(347.0, 130.0);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}




void fingsofleftfishes(){

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); // Sets the color to pure red
        glVertex2f(150.0, 135.0);
        glVertex2f(158.0, 130.0);
        glVertex2f(170.0, 140.0);
    glEnd();

}


float sunX = 0.0f;
void sun(void) {

     glPushMatrix();  // Save the current state of transformations

    // Apply translation to move the sun
    glTranslatef(sunX, 0.0f, 0.0f);

    glColor3f(1.0, 0.5, 0.0); // Orange color for the sun
    circle(1125,525,50);

    glPopMatrix();
}

void fingsofrightfishes(float x, float y){

    glBegin(GL_POLYGON);
    glColor3f(0.75f, 0.0f, 0.75f); // Sets the color to a bright purple shade
    glVertex2f(x,y);
    glVertex2f(x+5,y+10);
    glVertex2f(x-5,y+10);
    glEnd();
}

void vase(float x,float y){

    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.4f, 0.3f); // Sets the color to a darker light brown shade
        glVertex2f(x,y);
        glVertex2f(x+20,y);
        glVertex2f(x+25,y+20);
        glVertex2f(x-5,y+20);
    glEnd();
}

// Function to draw a circle


void plant(float x, float y){

    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.4f, 0.3f); // Sets the color to a darker light brown shade
        glVertex2f(x,y);
        glVertex2f(x+2,y);
        glVertex2f(x+2,y+30);
        glVertex2f(x,y+30);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.4f, 0.3f); // Sets the color to a darker light brown shade
        glVertex2f(x+2,y+20);
        glVertex2f(x+20,y+25);
        glVertex2f(x+20,y+27);
        glVertex2f(x+2,y+22);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.4f, 0.3f); // Sets the color to a darker light brown shade
        glVertex2f(x-20,y+15);
        glVertex2f(x,y+10);
        glVertex2f(x,y+12);
        glVertex2f(x-20,y+17);
    glEnd();

    glColor3f(0.75f, 0.55f, 0.85f); // Sets the color to a light purple shade
    circle(x+25,y+26,10);

    glColor3f(1.0f, 0.75f, 0.8f); // Sets the color to a shade of pink
    circle(x+1,y+40,10);

    glColor3f(1.0f, 0.0f, 0.0f); // Sets the color to pure red
    circle(x-30,y+16,10);

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen with the background color


    river();
    sky();
    sun();
    grass();

    //tree1
    glPushMatrix();
    glTranslatef(50.0f, 190.0f, 0.0f);
    glColor3f(0.50, 0.32, 0.13);
    trees(0.0f, 0.0f);
    glPopMatrix();

     //tree2
    glPushMatrix();
    glTranslatef(560.0f, 270.0f, 0.0f);
    glColor3f(0.50, 0.32, 0.13);
    trees(0.0f, 0.0f);
    glPopMatrix();
    hangingballs(560,270);

    //tree3
    glPushMatrix();
    glTranslatef(890.0f, 250.0f, 0.0f);
    glColor3f(0.50, 0.32, 0.13);
    trees(0.0f, 0.0f);
    glPopMatrix();
    hangingballs(890,250);

    //house1
    glPushMatrix();
    glTranslatef(300.0f, 270.0f, 0.0f);
    glColor3f(0.5f, 0.0f, 0.5f); // Sets the color to a shade of purple
    house(0.0f, 0.0f);
    glPopMatrix();

     //house2
    glPushMatrix();
    glColor3f(0.8f, 0.4f, 0.6f); // Sets the color to a darker pink
    glTranslatef(700.0f, 255.0f, 0.0f);
    house(0.0f, 0.0f);
    glPopMatrix();

    //doorroof1
    glPushMatrix();
    glTranslatef(300.0f, 270.0f, 0.0f);
    glColor3f(0.75, 0.32, 0.13);
    doorandroof(0.0f, 0.0f);
    glPopMatrix();

    //doorroof2
    glPushMatrix();
    glTranslatef(700.0f, 255.0f, 0.0f);
    glColor3f(0.50, 0.32, 0.13);
    doorandroof(0.0f, 0.0f);
    glPopMatrix();

    vase(100,180);
    vase(190,190);
    plant(109,200);
    plant(200,210);

    //vase3
    glPushMatrix();
    glTranslatef(950.0f, 200.0f, 0.0f);
    glScalef(0.8f,0.8f,1.0f);
    plant(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(943.0f, 184.0f, 0.0f);
    glScalef(0.8f,0.8f,1.0f);
    vase(0,0);
    glPopMatrix();

    //vase4
    glPushMatrix();
    glTranslatef(1038.0f, 177.0f, 0.0f);
    glScalef(1.3f,1.3f,1.3f);
    vase(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1050.0f, 200.0f, 0.0f);
    glScalef(1.3f,1.3f,1.3f);
    plant(0.0f, 0.0f);
    glPopMatrix();

    // First Fish
    glPushMatrix();              // Save the current transformation
    glColor3f(1.0f, 1.0f, 0.0f); // Sets the color to pure yellow
    glTranslatef(90.0f, 70.0f, 0.0f);  // Move to the desired position
    glScalef(-1.0f, 1.0f, 1.0f);  // Flip vertically
    fishwithlines(0.0f, 0.0f);
    glPopMatrix();

    // Second Fish
    glPushMatrix();
    glTranslatef(150.0f, 120.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f); // Sets the color to pure yellow
    fishwithlines(0.0f, 0.0f);
    glPopMatrix();

     // FOURTH Fish
    glPushMatrix();
    glTranslatef(900.0f, 80.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.5f);
    fishwithlines(0.0f, 0.0f);
    glPopMatrix();

    //tail1
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Sets the color to pure red
    glScalef(-1.0f,1.0f,1.0f);
    glTranslatef(-65.0f, 70.0f, 0.0f);
    fishtail(0.0f, 0.0f);
    glPopMatrix();

    //tail2
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Sets the color to pure red
    glTranslatef(178.0f, 120.0f, 0.0f);
    fishtail(0.0f, 0.0f);
    glPopMatrix();

    //tail4
    glPushMatrix();
    glColor3f(0.75f, 0.0f, 0.75f); // Sets the color to a bright purple shade
    glTranslatef(928.0f, 80.0f, 0.0f);
    fishtail(0.0f, 0.0f);
    glPopMatrix();

    //upfingoffish2
    fingsofleftfishes();

    //fingdownfish2
    glPushMatrix();
    glScalef(1.0f,-1.0f,1.0f);
    glTranslatef(0.8f, -240.0f, 0.0f);
    fingsofleftfishes();
    glPopMatrix();

    //firstfishfingup
    glPushMatrix();
    glTranslatef(241.0f, -49.0f, 0.0f);
    glScalef(-1.0f,1.0f,1.0f);
    fingsofleftfishes();
    glPopMatrix();

    //firstfishfingdown
    glPushMatrix();
    glScalef(1.0f,-1.0f,1.0f);
    glScalef(-1.0f,1.0f,1.0f);
    glTranslatef(-240.0f, -188.0f, 0.0f);
    fingsofleftfishes();
    glPopMatrix();

    //4thfishupfing
    glPushMatrix();
    glTranslatef(900.0f, 96.0f, 0.0f);
    glColor3f(0.75, 0.32, 0.13);
    fingsofrightfishes(0.0f, 0.0f);
    glPopMatrix();

    //4thfishdownfing
    glPushMatrix();
    glTranslatef(900.0f, 65.0f, 0.0f);
    glScalef(1.0f,-1.0f,1.0f);
    glColor3f(0.75, 0.32, 0.13);
    fingsofrightfishes(0.0f, 0.0f);
    glPopMatrix();

    horse();
    manWithBoat();

    // Third Fish
    glPushMatrix();
    glTranslatef(750.0f, 40.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.5f); // Sets the color to a dark blue shade
    fishwithlines(0.0f, 0.0f);
    glPopMatrix();

     //3rdfishupfing
    glPushMatrix();
    glTranslatef(750.0f, 55.0f, 0.0f);
    glColor3f(0.75, 0.32, 0.13);
    fingsofrightfishes(0.0f, 0.0f);
    glPopMatrix();

    //3rdfishdownfing
    glPushMatrix();
    glTranslatef(750.0f, 25.0f, 0.0f);
    glScalef(1.0f,1.0f,1.0f);
    glColor3f(0.75, 0.32, 0.13);
    fingsofrightfishes(0.0f, 0.0f);
    glPopMatrix();

    //tail3
    glPushMatrix();
    glColor3f(0.75f, 0.0f, 0.75f);
    glTranslatef(778.0f, 40.0f, 0.0f);
    fishtail(0.0f, 0.0f);
    glPopMatrix();



    glFlush();  // Render the drawing

}
void updateHorsePosition(int value) {
    if (isMovingLeftToRight) {
        horsePositionX += horseSpeed;  // Move the horse right

        if (horsePositionX > 1200.0f) {  // If the horse goes off-screen, reset
            horsePositionX = -100.0f;
        }
    } else {
        horsePositionX -= horseSpeed;  // Move the horse left

        if (horsePositionX < -100.0f) {  // If the horse goes off-screen, reset
            horsePositionX = 1200.0f;
        }
    }

    glutPostRedisplay();  // Request to render the screen again
    glutTimerFunc(16, updateHorsePosition, 0);  // Set the timer for the next update
}


void updateTailRotation(int value) {
    if (isRotating) {
        tailRotationAngle -= tailRotationSpeed;  // Rotate the tail clockwise
        if (tailRotationAngle < -360.0f) {
            tailRotationAngle += 360.0f;  // Keep the angle within a full rotation
        }
        glutPostRedisplay();  // Request to render the screen again
        glutTimerFunc(16, updateTailRotation, 0);  // Set the timer for the next update (approx 60 FPS)
    }
}



void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'F' || key == 'f') {
        isMovingLeftToRight = false;  // Move from right to left
        glutTimerFunc(0, updateHorsePosition, 0);  // Start moving the horse
    } else if (key == 'R' || key == 'r') {
        if (!isRotating) {
            isRotating = true;  // Start rotation
            glutTimerFunc(0, updateTailRotation, 0);  // Start the tail rotation
        }
    } else if (key == 'Q' || key == 'q') {
        isHorseRotated = true;  // Rotate the horse 180 degrees
        isMovingLeftToRight = true;  // Move from left to right
        glutTimerFunc(0, updateHorsePosition, 0);  // Start moving the horse
    }
     if (key == ' ') {  // Move the sun left when the space bar is pressed
        sunX -= 10.0f;  // Move the sun left by 10 units
        if (sunX < -1200.0f) {  // Reset the sun if it moves off the screen
            sunX = 100.0f;  // Start again from the right side
        }
    }

    if (key == 'B' || key == 'b') {  // Move the boat right when the "B" key is pressed
        boatX += 10.0f;  // Move the boat right by 10 units
        if (boatX > 1200.0f) {  // Reset the boat if it moves off the screen
            boatX = -300.0f;  // Start again from the left side
        }

    }

    if (key == 'W' || key == 'w') {  // Rotate the paddle backward when "W" is pressed
        paddleAngle -= 10.0f;  // Rotate the paddle backward by 10 degrees
         boatX += 10.0f;  // Move the boat right by 10 units
            if (boatX > 1200.0f) {  // Reset the boat if it moves off the screen
            boatX = -260.0f;  // Start again from the left side
        }

        if (paddleAngle <= -45.0f) {  // Reset the angle after a full rotation
            paddleAngle += 150.0f;

        }
    }
     glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);                         // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode: single buffer, RGB color
    glutInitWindowSize(1200, 600);                  // Set the window size to 800x600 pixels
    glutInitWindowPosition(50, 50);                // Position the window on the screen
    glutCreateWindow("Village Scene");             // Create the window with a title
    setup();                                       // Call setup to set up the coordinate system
    glutDisplayFunc(display);                      // Register display callback handler
    glutKeyboardFunc(handleKeypress);  // Register the keyboard callback
    glutMainLoop();                                // Enter the event-processing loop
    return 0;
}
