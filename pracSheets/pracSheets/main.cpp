//
//  main.m
//  junkproj
//
//  Created by Alan Dorin

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GLUT/glut.h>

#include "GL_routines.h"
using namespace std;

// because OpenGL works using eventHandlers you will need to define
// a few global variables. For example...

// YOUR_CREATURE_TYPE	gYourCreatureCollectionDataStruct;

int	gWinRows=500;
int gWinCols=500;

// Define a function which will always exit your program cleanly

void cleanQuit( )
{
    // put code in here to print out the message and quit the program
    exit(0);
}


// ! UNTESTED Circle code that doesn't use anything other than openGL...
void drawCircleXZWire(const double centX, const double centZ, const double radius)
{
	double	PI = 3.141;
	long	numSteps	= 20;
	double	angle		= 0;
	double	stepSize	= (2*PI)/(double)numSteps;

	double colourRedComponent=1.0;
	double colourGreenComponent=1.0;
	double colourBlueComponent=1.0;

	// set the current colour (white R=G=B=1)
	glColor3d(colourRedComponent, colourGreenComponent , colourBlueComponent );

	double 	curPoint[3];
	double	centY = 0;
	curPoint[1] = centY; // draw the circle in the Y=0 (XZ) plane
	
	// replace this line with: glBegin(GL_POLYGON); in order to draw a filled circle
	glBegin(GL_POLYGON);	

	for (angle=0; angle < (2*PI); angle+=stepSize)
	{
		curPoint[0] = centX+(radius * cos(angle));
		curPoint[2] = centZ+(radius * sin(angle));

		//glVertex3dv(curPoint);
		glVertex2f(curPoint[0], curPoint[2]);
	}
	glEnd();
}

int main(int argc, char **argv)
{
    // Initialize OpenGL/GLUT (only do this once)
    glutInit(&argc, argv);
    
    // Set up OpenGL to use double buffering, RGB mode, and a depth-buffer
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Set up the window and open it
	glutInitWindowSize (gWinCols, gWinRows);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Your Window Name");
    
    // This routine makes the graphics window take up the whole screen
    // for when you want this to work in game mode
	// glutFullScreen();
    
    // Do some of your own initializations in this routine
	myInitializeOpenGL();
    
    // Register all of the event handlers
	glutDisplayFunc(displayWorld);
	glutVisibilityFunc(visible);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mousePassiveMove);
	glutIdleFunc(updateWorld);
    
    // Set the software looking for events in an infinite loop
	glutMainLoop();
	
    // ANSI C requires integer return type from main()
    return 0;
}
