#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "hero.h"

#define MAX 11

extern float y_stick;
extern int num_build, ind, animation_ongoing;
extern float r, y_ball, r_c, z, x;


typedef struct{
    float x,y,z;
}Coordinates;

typedef struct{
    float x,y,z;
}Coordinates_low_rise;

Coordinates array_coord[] = {
    {-3.5, 0.5, 1.5},
    {-3.5, 0.5, -0.5},
    {-3.5, 0.5, -1.5},
    {-0.5, 0.5, -1.5},
    {-0.5, 0.5, 0.5},
    {0.5, 0.5, 0.5},
    {0.5, 0.5, 1.5},
    {2.5, 0.5, 1.5},
    {2.5, 0.5, -0.5},
    {3.5, 0.5, -0.5},
    {3.5, 0.5, 1.5}
};

Coordinates_low_rise array_coord_low_rise[] = {
    {-3.5, 0.375, 0.5},
    {-1.5, 0.375, 0.5},
    {-2.5, 0.375, 1.5},
    {0.5, 0.375, -1.5},
    {1.5, 0.375, 0.5},
    {-2.5, 0.375, -1.5},
    {1.5, 0.375, 1.5},
    {3.5, 0.375, 1.5}
};

 void building()
 {
     /*funkcija za iscrtavanje prizme koje predstavljaju zgrade*/
    glScalef(0.5,1,0.5);
    glutSolidCube(1);
 }

 
void all_buildings()
{   
    //visoke zgrade
    for(int i = 0; i<MAX; i++)
    {
        glPushMatrix();
        if(i == num_build)
            purple();
        else
            blue();
        
        glTranslatef(array_coord[i].x, array_coord[i].y, array_coord[i].z);
        building();
        glPopMatrix();
    }
    
    // niske zgrade
    for(int i =0; i<8; i++)
    {
        glPushMatrix();
        
        glScalef(1,0.75,1);
        glTranslatef(array_coord_low_rise[i].x, array_coord_low_rise[i].y, array_coord_low_rise[i].z);
        blue2();
        building();
        glPopMatrix();
    }
   
}

void ball()
{
    /*funkcija za isrtavanje sfere*/
    glPushMatrix();
    glShadeModel(GL_FLAT);
    green();
    glutSolidSphere(0.11, 60, 60);
    glPopMatrix();
    
}

void stick()
{
    /*funckija za iscrtavanje stapa*/
    
    float x_stick = array_coord[num_build-1].x;
    float z_stick = array_coord[num_build-1].z;
    double clip_plane0[] = {0, 1, 0, 0};
    int x_rot, z_rot;
    
    if(num_build == 1 || num_build%2 == 0 || num_build == 1) {
        x_rot = 1;
        z_rot = 0;
    }
    else {
        x_rot = 0;
        z_rot = 1;
    }
     
    glPushMatrix();
          pink();
          glTranslatef(x_stick, 1, z_stick);
          glRotatef(r, x_rot,0,z_rot);
          glTranslatef(-x_stick,-1,-z_stick);
          glTranslatef(x_stick, 1, z_stick);
          
          glClipPlane(GL_CLIP_PLANE0, clip_plane0);
          glEnable(GL_CLIP_PLANE0);
          
          glScalef(0.04,y_stick,0.04);
          glutSolidCube(1);
          
          glDisable(GL_CLIP_PLANE0);
          
    glPopMatrix();
}

