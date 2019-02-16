#include<GL/glut.h>
#include"colors.h"

// Zelena boja
GLfloat ambient_coeffs_green[]  = { 0.0, 0.5, 0.0, 1 };   // ambijentalna
GLfloat diffuse_coeffs_green[]  = { 0, 0.8, 0.8, 1 };  // difuzna
GLfloat specular_coeffs_green[] = { 0.7, 1.0, 0.7, 1 }; // spekularna

// Plava boja
GLfloat ambient_coeffs_blue[]  = { 0.1, 0.1, 0.1, 1 };      
GLfloat diffuse_coeffs_blue[]  = {0, 0, 1, 1 };       
GLfloat specular_coeffs_blue[] = { 0.4, 0.4, 0.4, 1 };

// Plava boja 2
GLfloat ambient_coeffs_blue2[]  = { 0.1, 0.1, 0.1, 1 };      
GLfloat diffuse_coeffs_blue2[]  = {0, 0.8, 1, 1 };       
GLfloat specular_coeffs_blue2[] = { 0.4, 0.4, 0.4, 1 };


// Ljubicasta boja
GLfloat ambient_coeffs_purple[]  = { 0.4, 0.0, 0.4, 1 };        
GLfloat diffuse_coeffs_purple[]  = { 0.5, 0.0, 0.5, 1 };  
GLfloat specular_coeffs_purple[] = { 0.6, 0.0, 0.6, 1 }; 

// Roze boja
GLfloat ambient_coeffs_pink[]  = { 0.917647, 0.678431, 0.917647, 1 };        
GLfloat diffuse_coeffs_pink[]  = { 1.0, 0.0, 0.0, 1 };        
GLfloat specular_coeffs_pink[] = { 1.0, 0.1, 0.1, 1 }; 


void green(){

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_green);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_green);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_green);

}

void blue(){

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_blue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_blue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_blue);

}

void blue2(){

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_blue2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_blue2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_blue2);

}


void purple(){
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_purple);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_purple);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_purple);
}

void pink(){
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_pink);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_pink);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_pink);
    glPopMatrix();
}


void set_lighting(){

  glPushMatrix();
  glLoadIdentity();

  GLfloat light_position[] = { 10, 30, 0, 1 }; // pozicija svetla

  GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1 }; // ambijentalna boja
  GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 }; // difuzna boja
  GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 }; // spekularna boja
  GLfloat shininess = 50; // koeficijent glatkosti materijala

  //Ukljucuje se osvjetljenje.
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  glShadeModel(GL_SMOOTH);

  //Podesava se pozicija svetla.
  glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
  //Podesavaju se boje svetla.
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  // Koeficijent glatkosti materijala.
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glPopMatrix();
}