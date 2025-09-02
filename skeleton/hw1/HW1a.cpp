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
// this is a flat array with 32 values, but visually, it functions as
// as 2D array of 16 values (each value paired with each other)
// indexing will have to be by 0...31 though
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
	// these below are actually all the OpenGL primitives that can be found
	// here: https://www.dgp.toronto.edu/~ah/csc418/fall_2001/tut/ogl_draw.html
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
	glColor3f(1.0F, 1.0f, 1.0f);
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
	m_winW = w;
	m_winH = h;
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
	// so this actually means that the (0,0) origin is right in the center.
	
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
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	// modelview here because we're setting up the objects, not where our "camera lens" is located
	// we use projection view earlier because that's where we set up the said camera lens
	float xmax, ymax;
	float ar = (float) m_winW/m_winH;
	if (ar>1.0) {
		xmax=ar;
		ymax=1.;
	} else {
		xmax=1.;
		ymax=1/ar;
	}
	// this will be handy: https://docs.gl/gl3/glTranslate
	for (int i=0; i<9; i++) {
		glLoadIdentity();
		
		int row = i / 3;
		int col = i % 3;
		
		// the window size is like this:
		// far left = -xmax, far right = xmax, so the center is 0
		// doubling xmax will be the full size of the horizontal range
		// then we divide by 3. same goes for ymax.
		float cellWidth = (2.0f * xmax) / 3.0f;
		float cellHeight = (2.0f * ymax) / 3.0f;

		// kinda gotta sketch it out, but you move forward from the left
		// half of the cellwidth or cellheight. and further than that
		// you stack up cellwidths or cellheights depending on the grid.
		float x = -xmax + (cellWidth/2) + (cellWidth * col);
		float y = -ymax + (cellHeight/2) + (cellHeight * row);
		
		glTranslatef(x, y, 0.0f);
		float scale = 0.3f;
		glScalef(scale, scale, 1.0f);
		glColor3f(1.0F, 1.0f, 1.0f);
		glBegin(DrawModes[i]);
			for (int j=0; j<16; j++) {
				glVertex2f(Vertices[2*j], Vertices[(2*j)+1]);
			}
		glEnd();
	}
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
