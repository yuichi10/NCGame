/*
 *  GL_routines.cpp
 *
 *  Created by Alan Dorin on Fri May 24 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include "GL_routines.h"

extern void cleanQuit( );
extern void drawCircleXZWire(const double, const double, const double);

void myInitializeOpenGL(void)
{
	// Set the background/clear-the-screen colour
	glClearColor (0.02, 0.02, 0.02, 0.0);
   
	// These routines ensure that objects further away from
	// the viewpoint will be drawn on top of by closer objects (using a "depth-buffer" or "z-buffer")   
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    
    std::cerr << "\nIn myInitializeOpenGL(void)";
}

void displayWorld(void)
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear the screen and clear the depth-buffer
	glLoadIdentity ();						      		// load the identity matrix
    
    // Display your gYourCreatureCollectionDataStruct here
    // for example call gYourCreatureCollectionDataStruct->display()
    // for example call gYourPlayerCharacterDataStruct->display()
	
    // for this example, just draw some circles...
    drawCircleXZWire(10, 100, 10);
	drawCircleXZWire(0, 20, 5);
	drawCircleXZWire(-10, -10 , 20);
    
    // What does this routine do?
	glFlush ();
	
    // This routine "swaps buffers"
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    std::cerr << "\nIn reshape(w,h)";

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   
   // lookAt from, to, up
  /* gluLookAt (0, -10, 0,
					0, 0, 0,
						0, 0, 1);
      */                  
   gluOrtho2D(-100, +100, -100, 100);
   
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    // extern gYourCreatureCollectionDataStruct here
    
	switch (key) {
        // character 27 is the escape key. Use this or Q/q to quit the program
        case 27:
        case 'q':
        case 'Q':
            // Call your cleanQuit routine to quit neatly
            cleanQuit( );
        break;

        // Assign keys to do different things in you code. For example you might like to....
        case 'a':
            // Do stuff here when the 'a' key is pressed
            // E.g. update your gYourCreatureCollectionDataStruct maybe?
            // or maybe gYourPlayerCharacterDataStruct->update()?
            
            // After that, you may want to tell OpenGL to redraw the screen like this...
        	glutPostRedisplay();
      	break;
        
        case 'A':
            // Do other stuff here when 'A' key is pressed...
            // E.g. update your gYourCreatureCollectionDataStruct differently maybe?
            // or maybe gYourPlayerCharacterDataStruct->update()?
            // Or adjust the view? Its up to you!
            
            // Remember that if you make a change which requires the screen to redrawn,
            // post a "display" message...
            glutPostRedisplay();
        break;
        
      	default:
            // Do something or nothing by default when a key you haven't used is pressed here...
      	break;
   }
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
         {
            // Do something e.g. gYourPlayerCharacterDataStruct->update()
            
            // and maybe redisplay...
            glutPostRedisplay();
         }
      break;
      
      default:
      
      break;
   }
}

void mouseMove(int x, int y)
{
    // Sometimes its useful to keep track of the old mouse
    // position so that you can compare it to new mouse positions.
    // You'll need static variables to do this... why?
	static int oldX=0;
	static int oldY=0;
	static bool firstCall = true;
    
    // What is the use of this if statement?
	if(firstCall==true)
	{
		oldX=x;
		oldY=y;
		firstCall = false;
		return;
	}
    
    // Do things in here with the difference b/n the new mouse x,y and oldX,oldY
    // to make your program's behaviour respond to mouse movements.
    
    // Then set the old mouse position to the current mouse position
    // for next time around...
    oldX=x;
	oldY=y;
}

void mousePassiveMove(int x, int y)
{
    // What might you write in here?
    // What is this event handler for?
}

void visible(int vis)
{
	if (vis == GLUT_VISIBLE)	glutIdleFunc(updateWorld);
	else						glutIdleFunc(NULL);
}

void updateWorld(void)
{
    // Update your gYourCreatureCollectionDataStruct here
    // for example call gYourCreatureCollectionDataStruct->update() and
    // maybe call gYourPlayerCharacterDataStruct->update() if any non-player controlled aspects need to be updated
    
	// then request a redraw of the display by posting a "redraw" event
	glutPostRedisplay();
}

void null_select(int mode)
{	/* nothing */ }

void menu_select(int mode)
{
	switch (mode)
	{
		case 1:
			// Put code in here to handle the first menu item
		break;

		case 2:
            // Code to handle the menu quit...
			{ cleanQuit( ); }
		break;
		default:
			return;
		break;
	}
}

void glutMenu(void)
{
	int glut_menu;
	
	glut_menu = glutCreateMenu(menu_select);
	
	glutAddMenuEntry("Do Nothing", 1);
	glutAddMenuEntry("Quit", 2);
	
	glutAttachMenu(GLUT_LEFT_BUTTON);
  	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
