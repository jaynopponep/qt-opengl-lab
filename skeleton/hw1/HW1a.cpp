// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2022 by George Wolberg
//
// HW1a.cpp - HW1a class
//
// Written by: George Wolberg, 2022
// ===============================================================

#include "HW1a.h"
// ** NOTE
// version we're running is 5.14.2, latest will not compile correctly!
// **

// init array of 16 vertices for letter 'P'
float Vertices[] = {
	-0.5f , -0.75f,
	-0.5f , -0.5f,
	-0.5f , -0.25f,
	-0.5f ,  0.0f,
	-0.5f ,  0.25f,
	-0.5f ,  0.5f,
	-0.25f,  0.75f,
	 0.0f ,  0.75f,
	 0.25f,  0.75f,
	 0.5f ,  0.75f,
	 0.75f,  0.5f,
	 0.75f,  0.25f,
	 0.5f ,  0.0f,
	 0.25f,  0.0f,
	 0.0f ,  0.0f,
	-0.25f,  0.0f
};

static int DrawModes[] = {
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_QUADS,
	GL_POLYGON
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::HW1a:
//
// HW1a constructor.
//
HW1a::HW1a(const QGLFormat &glf, QWidget *parent)
	: HW(glf, parent)
{
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW1a::initializeGL()
{
	// https://doc.qt.io/archives/qt-5.15/qglfunctions.html#initializeGLFunctions
	// part of QGLFunctions class (Qt 4.8), now obsolete/deprecated in latest Qt version
	initializeGLFunctions(); // <- this just binds the available GL functions to Qt for us to use

	// the GL functions loaded can be found in: https://docs.gl/gl4/glClearColor
	// black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// we need 3x3 letter P shapes bottom to top, left to right
	// we'll use glColor3f in paintGL() since it's situational
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW1a::resizeGL(int w, int h)
{
	// ar = aspect ratio
	float xmax, ymax;
	float ar = (float) w / h;
	if (ar > 1.0) { // wide screen
		xmax = ar;
		ymax = 1.0;
	} else { // tall screen
		xmax = 1.0;
		ymax = 1.0 / ar;
	}

	// set viewport to occupy full canvas
	glViewport(0, 0, w, h); // 0, 0 = x, y; location of lower left corner of viewport

	// init viewing coordinates for orthographic projection
	glMatrixMode(GL_PROJECTION); // matrix ops to the projection matrix stack
	// (explained in Chapter 3.8 in textbook: Projection Matrices)
	glLoadIdentity(); // init curr matrix = Identity Matrix

	glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0); // curr matrix *= ortho matrix
	// orthographic projection -> is to map 3D to 2D to make the projection matrix
	// view work. parameters in glOrtho() are corners of the coord system
	
	// (btw, pretty much just took the same setting from HW0a.cpp)
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::paintGL:
//
// Update GL scene.
//
void
HW1a::paintGL()
{
	// PUT YOUR CODE HERE
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW1a::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 1a");
	groupBox->setStyleSheet(GroupBoxStyle);

	return(groupBox);
}
