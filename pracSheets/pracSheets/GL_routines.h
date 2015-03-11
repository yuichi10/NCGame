/*
 *  GL_routines.h
 *
 *  Created by Alan Dorin on Fri May 24 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GL_ROUTINES
#define GL_ROUTINES

#include <iostream>
#include <GLUT/glut.h>

// -- GL routines
void myInitializeOpenGL(void);
void displayWorld(void);
void reshape (int w, int h);
void updateWorld(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void mousePassiveMove(int x, int y);
void visible(int vis);
void null_select(int mode);
void menu_select(int mode);
void glutMenu(void);

#endif
