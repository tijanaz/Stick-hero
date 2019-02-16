#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "hero.h"
#include "colors.h"
#include "image.h"

#define FILENAME1 "water.bmp"

/* Identifikatori tekstura. */
static GLuint names[2];

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int id);
static void on_timer_2(int id);
static void initialize(void);


float z = 1.5, x = -3.5; //koordinate lopte
float y_stick = 0;  //duzina stapa
float r = 0;
int animation_ongoing = 0;
int num_build = 1; //redni broj zgrade
float y_ball = 1.1;
int ind = 0;  //indikator da li loptica treba da pada
float r_c = 0; //ugao rotacije kamere
int pause = 0;

void draw_text(char text[], float x, float y, float z){
  //funkcija za iscrtavanj 2D teksta
  glRasterPos3f(x, y, z);
  for (int i=0; text[i]; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  }
}

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(1000, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);


    /* Ukljucujemo normalizaciju vektora normala */
    glEnable(GL_NORMALIZE);

     /* Obavlja se OpenGL inicijalizacija. */
    initialize();
    
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}


/*Kod za funckiju 'initialize' je preuzet iz primera "32_texture" sa vezbi */
static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME1);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            /* Zavrsava se program. */
            exit(0);
            break;
            
        case 'd':
        case 'D':
            /*komanda kojom se dobija pokretanja programa,
             tj. rotiranje stapa i kretanje loptice*/
            pause = 0;
            if(!animation_ongoing) {
                animation_ongoing = 1;
                r=0;
            
                glutTimerFunc(100, on_timer, 0);
            }
            break;
        
        case 'w':
        case 'W':
            /*komanda kojom se dobija rast stapa*/
            if(!animation_ongoing) {
            y_stick+=0.1;
            glutTimerFunc(60, on_timer_2, 0);
            }
            
            break;
            
        case 'z':
        case 'Z':
            //komanda kojom se kamera okrece ulevo
            r_c+=1;
            on_display();
            break;
            
        case 'x':
        case 'X':
            //komanda kojom se kamera okrece udesno
            r_c-=1;
            on_display();
            break;
            
        case 's':
        case 'S':
            //stopiranje igre
            pause = 1;
            animation_ongoing = 0;
            break;
    }
}

static void on_display(void)
{   
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW); 
  
  glLoadIdentity();
  
  glTranslatef(0,-2, -8);
  glRotatef(r_c,0,1,0);
  glTranslatef(0,2,8);
  
  gluLookAt(0, 2, 8,
            0, 2, 0,
            0, 2, 0);
  
  // Podesava se osvetljenje.
  set_lighting();
    
  glPushMatrix();
  //iscrtavanje platforme
  glBindTexture(GL_TEXTURE_2D, names[0]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(4, 0, 2);

        glTexCoord2f(0,1);
        glVertex3f(4, 0, -2);

        glTexCoord2f(1,1);
        glVertex3f(-4, 0, -2);

        glTexCoord2f(1, 0);
        glVertex3f(-4, 0, 2);
    glEnd();
    
  /* Iskljucujemo aktivnu teksturu */
  glBindTexture(GL_TEXTURE_2D, 0);

  //iscratavanje zgrada
  all_buildings();
  
  //iscrtavanje lopte
  glPushMatrix();
  glTranslatef(x, y_ball, z);
  ball();
  glPopMatrix(); 
    
  //iscrtavanje stapa
  stick();
  glPopMatrix();

  //tekst za ispisivanje
  char points[256];
  if(!pause)
  {
      if(num_build-1 == 10) {
          draw_text("YOU WIN! \\o/", 0, 3, 0);
      }
      else {
          sprintf(points, "Score: %02d/10", num_build-1);
          draw_text(points, 0, 3, 0);
      }
  }
  else
      draw_text("Pause! Press D to continue", 0, 3, 0);
  
  
  glutSwapBuffers();
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 10);
}

static void on_timer_2(int id)
{
    /*tajmer za stap, njegov rast i resetovanje rotacije*/
    if(id != 0)
        return;
    
    y_stick+=0.1;
    r=0;
    
    if (animation_ongoing) {
        glutTimerFunc(60, on_timer_2, 0);
    }
      
    glutPostRedisplay();
    
}

static void on_timer(int id)
{
    /* tajmer za rotaciju stapa i kretanje loptice
     u zavisnosti od broja zgrade u tom trenutku*/
    if(id != 0)
        return;
    
    switch(num_build) {
            case 1:
                if(r>-90) {
                    r_c+=5;
                    r-=10;
                }
                else {
                    if(z>1.5-y_stick/2)
                        z-=0.1;
                    
                    if(z<=1.5-y_stick/2) {
                    
                        if(z<=-0.25 && z>=-0.75) {
                            /*loptica i stap su dostigli zgradu
                            loptica dalje nastavlja od centra zgrade*/
                            z = -0.5;
                        }
                        else
                        {
                            //loptica nije stiglo do zgrade, pad loptice 
                            ind = 1;
                            if(y_ball >=-0.1) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        /*ind = 0, znaci da se igra nastavlja
                        * loptica nastavlja da se krece do naredne zgrade*/
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                        else
                        {
                            num_build = 1;
                            ind = 0;
                        }
                    }
                }
                break;
            
            case 2:
                if(r>-90) {
                    r_c+=5;
                    r-=10;
                }
                else {
                    if(z>-0.5-y_stick/2)
                        z-=0.1;
                    if(z<=-0.5-y_stick/2) {
                        
                        if(z<=-1.25 && z>=-1.75) {
                            z = -1.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                               z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                    
                }
                break;
            
            case 3:
                if(r>-90) {
                    r_c+=5;
                    r-=10;
                }
                else {
                    if(x<-3.5+y_stick/2)
                        x+=0.1;
                    if(x>=-3.5+y_stick/2){
                        
                        if(x<=-0.25 && x>=-0.75) {
                            x = -0.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                    
                }
                break;
                
                   
            case 4:
                
                if(r<90) {
                    r_c+=7;
                    r+=10;
                }
                
                else {
                    if(z<-1.5+y_stick/2)
                        z+=0.1;
                    if(z>=-1.5+y_stick/2) {
                        
                        if(z<=0.75 && z>=0.25) {
                            z = 0.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                }
                break;
            
            
            case 5:
                if(r>-90) {
                    r_c+=5;
                    r-=10;
                }
                else {
                    if(x<-0.5+y_stick/2)
                        x+=0.1;
                    if(x>=-0.5+y_stick/2){
                        
                        if(x<=0.75 && x>=0.25) {
                            x = 0.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                    
                }
                break;
                
            
            case 6:
                if(r<90) {
                    r_c+=5;
                    r+=10;
                }
                
                else {
                    if(z<0.5+y_stick/2)
                        z+=0.1;
                    if(z>=0.5+y_stick/2) {
                        
                        if(z<=1.75 && z>=1.25) {
                            z = 1.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                }
                break;
                
                
            case 7:
                if(r>-90) {
                    r_c+=5;
                    r-=10;
                }
                else {
                    if(x<0.5+y_stick/2)
                        x+=0.1;
                    if(x>=0.5+y_stick/2){
                        
                        if(x<=2.75 && x>=2.25) {
                            x = 2.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                    
                }
                break;
                
                
            case 8:
                if(r>-90) {
                    r_c-=5;
                r-=10;
                }
                else {
                    if(z>1.5-y_stick/2)
                        z-=0.1;
                    
                    if(z<=1.5-y_stick/2) {
                    
                        if(z<=-0.25 && z>=-0.75) {
                            z = -0.5;
                        }
                        else
                        {
                            ind = 1;
                            if(y_ball >=-0.1) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                }
                break;
                
                
            case 9:
                if(r>-90) {
                    r_c-=5;
                    r-=10;
                }
                else {
                    if(x<2.5+y_stick/2)
                        x+=0.1;
                    if(x>=2.5+y_stick/2){
                        
                        if(x<=3.75 && x>= 3.25) {
                            x = 3.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                    
                }
                break;
                
            case 10:
                if(r<90) {
                    r_c+=5;
                    r+=10;
                }
                
                else {
                    if(z<-0.5+y_stick/2)
                        z+=0.1;
                    if(z>=-0.5+y_stick/2) {
                        
                        if(z<=1.75 && z>=1.25) {
                            z = 1.5;
                        }
                        else {
                            ind = 1;
                            if(y_ball >=-0.3) {
                                y_ball -=0.1;
                                break;
                            }
                            else
                            {
                                y_stick = 0;
                                r_c = 0;
                                z = 1.5;
                                x = -3.5;
                                y_ball = 1.1;
                                num_build = 1;
                                animation_ongoing = 0;
                                
                            }
                        }
                        
                        if(!ind) {
                            animation_ongoing = 0;
                            y_stick = 0;
                            num_build++;
                        }
                    }
                }
                break;
        }
  
    if (animation_ongoing) {
        glutTimerFunc(60, on_timer, 0);
    }
      
    glutPostRedisplay();
}
