    // ===============================================================
    // Computer Graphics Homework Solutions
    // Copyright (C) 2022 by George Wolberg
    //
    // HW1b.cpp - HW1b class
    //
    // Written by: George Wolberg, 2022
    // ===============================================================
    #include "HW1b.h"
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::HW1b:
    //
    // HW1b constructor.
    //
    HW1b::HW1b(const QGLFormat &glf, QWidget *parent)
        : HW(glf, parent)
    {
        // init vars
        m_theta		= 0;
        m_subdivisions	= 4;
        m_updateColor	= 1;
        m_twist		= 1;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::initializeGL:
    //
    // Initialization routine before display loop.
    // Gets called once before the first time resizeGL() or paintGL() is called.
    //
    void
    HW1b::initializeGL()
    {
        // init vertex and color buffers
        // specifically, marks out vertices & colors to begin drawing in paintGL() 
        initBuffers();

        // init state variables
        glClearColor(0.0, 0.0, 0.0, 1.0);	// set background color
        glColor3f   (1.0, 1.0, 1.0);		// set foreground color
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::resizeGL:
    //
    // Resize event handler.
    // The input parameters are the window width (w) and height (h).
    //
    void
    HW1b::resizeGL(int w, int h)
    {
        m_winW = w;
        m_winH = h;
        if(h == 0) h = 1;  // prevent divide by zero

        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float ar = (float)w / h;
        if (w >= h)
            glOrtho(-ar, ar, -1.0, 1.0, -1.0, 1.0);
        else
            glOrtho(-1.0, 1.0, -1.0/ar, 1.0/ar, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::paintGL:
    //
    // Update GL scene.
    //
    void
    HW1b::paintGL()
    {
        // clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // draw all triangles
        glBegin(GL_TRIANGLES);
        for(size_t i = 0; i < m_points.size(); ++i) {
            const vec3 &color = m_colors[i / 3];   // same color per triangle
            glColor3f(color.x(), color.y(), color.z());
            glVertex2f(m_points[i].x(), m_points[i].y());
        }
        glEnd();
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::controlPanel:
    //
    // Create control panel groupbox.
    //
    // **FOR STUDYING PURPOSES, I THINK WE CAN MAINLY IGNORE THIS**
    // **AS THESE ARE JUST SETTING THE UI SETTINGS AVAILABLE ON QTCREATOR**
    QGroupBox*
    HW1b::controlPanel()
    { 
        // init group box
        QGroupBox *groupBox = new QGroupBox("Homework 1b");
        groupBox->setStyleSheet(GroupBoxStyle);
        // create labels
        QLabel *label[2];
        label[0] = new QLabel("Theta");
        label[1] = new QLabel("Subdivide");

        // create sliders
        m_sliderTheta  = new QSlider(Qt::Horizontal);
        m_sliderSubdiv = new QSlider(Qt::Horizontal);

        // init sliders
        m_sliderTheta ->setRange(0, 360);
        m_sliderTheta ->setValue(0);
        m_sliderSubdiv->setRange(0, 6);
        m_sliderSubdiv->setValue(m_subdivisions);

        // create spinBoxes
        m_spinBoxTheta = new QSpinBox;
        m_spinBoxTheta->setRange(0, 360);
        m_spinBoxTheta->setValue(0);
        m_spinBoxSubdiv = new QSpinBox;
        m_spinBoxSubdiv->setRange(0, 6);
        m_spinBoxSubdiv->setValue(m_subdivisions);

        // init checkbox
        m_checkBoxTwist = new QCheckBox("Twist");
        m_checkBoxTwist->setChecked(m_twist);

        // layout for assembling widgets
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(label[0],	   0, 0);
        layout->addWidget(m_sliderTheta,   0, 1);
        layout->addWidget(m_spinBoxTheta,  0, 2);
        layout->addWidget(label[1],	   1, 0);
        layout->addWidget(m_sliderSubdiv,  1, 1);
        layout->addWidget(m_spinBoxSubdiv, 1, 2);
        layout->addWidget(m_checkBoxTwist, 2, 0);

        // assign layout to group box
        groupBox->setLayout(layout);

        // init signal/slot connections
        connect(m_sliderTheta  , SIGNAL(valueChanged(int)), this, SLOT(changeTheta (int)));
        connect(m_sliderSubdiv , SIGNAL(valueChanged(int)), this, SLOT(changeSubdiv(int)));
        connect(m_spinBoxTheta,  SIGNAL(valueChanged(int)), this, SLOT(changeTheta (int)));
        connect(m_spinBoxSubdiv, SIGNAL(valueChanged(int)), this, SLOT(changeSubdiv(int)));
        connect(m_checkBoxTwist, SIGNAL(stateChanged(int)), this, SLOT(changeTwist (int)));

        return(groupBox);
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::reset:
    //
    // Reset parameters.
    //
    // **FOR STUDYING PURPOSES, I THINK WE CAN MAINLY IGNORE THIS**
    // **AS THESE ARE JUST SETTING THE UI SETTINGS AVAILABLE ON QTCREATOR**
    void
    HW1b::reset()
    {
        m_theta = 0;
        m_subdivisions = 4;
        m_updateColor = true;
        m_twist = true;

        // update UI controls without triggering signals
        m_sliderTheta->blockSignals(true);
        m_sliderTheta->setValue(0);
        m_sliderTheta->blockSignals(false);
        m_spinBoxTheta->blockSignals(true);
        m_spinBoxTheta->setValue(0);
        m_spinBoxTheta->blockSignals(false);
        m_sliderSubdiv->blockSignals(true);
        m_sliderSubdiv->setValue(m_subdivisions);
        m_sliderSubdiv->blockSignals(false);
        m_spinBoxSubdiv->blockSignals(true);
        m_spinBoxSubdiv->setValue(m_subdivisions);
        m_spinBoxSubdiv->blockSignals(false);
        m_checkBoxTwist->setChecked(m_twist);

        // redraw
        m_points.clear();
        m_colors.clear();
        initBuffers();
        updateGL();
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::initBuffers:
    //
    // Initialize vertex buffer.
    //
    void
    HW1b::initBuffers()
    {
        const QVector2D vertices[] = {
             QVector2D( 0.0f ,  0.75f),
             QVector2D( 0.65f, -0.375f),
             QVector2D(-0.65f, -0.375f)
        };

        // recursively subdivide triangle into triangular facets;
        // store vertex positions and colors in m_points and m_colors, respectively
        divideTriangle(vertices[0], vertices[1], vertices[2], m_subdivisions);
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::divideTriangle:
    //
    // Recursive subdivision of triangle (a,b,c). Recurse count times.
    //
    void
    HW1b::divideTriangle(vec2 a, vec2 b, vec2 c, int count)
    {
        if(count > 0) {
            // midpoints
            vec2 ab = (a + b) / 2.0f;
            vec2 ac = (a + c) / 2.0f;
            vec2 bc = (b + c) / 2.0f;

            // recurse on 4 smaller triangles
            divideTriangle(a, ab, ac, count-1);
            divideTriangle(b, bc, ab, count-1);
            divideTriangle(c, ac, bc, count-1);
            divideTriangle(ab, bc, ac, count-1);
        } else {
            // base case: save triangle
            triangle(a, b, c);
        }
    }



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::triangle:
    //
    // Push positions and colors of the three triangle vertices.
    //
    void
    HW1b::triangle(vec2 a, vec2 b, vec2 c)
    {
        // sets random color
        // note rand()/RAND_MAX just results in a random float between 0 and 1
        if(m_updateColor) {
            m_colors.push_back(vec3((float) rand()/RAND_MAX,
                        (float) rand()/RAND_MAX,
                        (float) rand()/RAND_MAX));
        }
        // init geometry
        m_points.push_back(rotTwist(a));
        m_points.push_back(rotTwist(b));
        m_points.push_back(rotTwist(c));
    }



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::rotTwist:
    //
    // Rotate point p based on rotation angle Theta and distance from origin (for Twist = true)
    //
    vec2
    HW1b::rotTwist(vec2 p)
    {
        // d = Euclidean distance from origin
        // or
        // d = sqrt{p.x^2 + p.y^2}
        // sinθ = sin(d*m_θ); cosθ = cos(d*m_θ) (m_θ is user input)
        // returns the rotation matrix for 2D rotation!
        // p.x*cosθ - p.y*sinθ
        // p.x*sinθ + p.y*cosθ
        float d = m_twist ? sqrt(p[0]*p[0] + p[1]*p[1]) : 1;
        float sinTheta = sin(d*m_theta);
        float cosTheta = cos(d*m_theta);
        return vec2(p[0]*cosTheta - p[1]*sinTheta, p[0]*sinTheta + p[1]*cosTheta);
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::changeTheta:
    //
    // Slot function to change rotation angle.
    //
    void
    HW1b::changeTheta(int angle)
    {
        // update slider and spinbox without triggering signals
        m_sliderTheta->blockSignals(true);
        m_sliderTheta->setValue(angle);
        m_sliderTheta->blockSignals(false);
        m_spinBoxTheta->blockSignals(true);
        m_spinBoxTheta->setValue(angle);
        m_spinBoxTheta->blockSignals(false);

        m_theta = angle * (M_PI / 180.0);  // convert to radians
        m_updateColor = 0;  // don't update color during rotation

        // redraw
        m_points.clear();
        initBuffers();
        updateGL();
    }



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::changeSubdiv:
    //
    // Slot function to change number of recursive subdivisions.
    //
    void
    HW1b::changeSubdiv(int subdivisions)
    {
        // update slider and spinbox without triggering signals
        m_sliderSubdiv->blockSignals(true);
        m_sliderSubdiv->setValue(subdivisions);
        m_sliderSubdiv->blockSignals(false);
        m_spinBoxSubdiv->blockSignals(true);
        m_spinBoxSubdiv->setValue(subdivisions);
        m_spinBoxSubdiv->blockSignals(false);

        m_subdivisions = subdivisions;
        m_updateColor = 1;

        // redraw
        m_points.clear();
        m_colors.clear();
        initBuffers();
        updateGL();
    }



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // HW1b::changeTwist:
    //
    // Slot function to turn on/off m_twist;
    //
    void
    HW1b::changeTwist(int twist)
    {
        m_twist = twist;
        m_updateColor = 0;

        // redraw
        m_points.clear();
        initBuffers();
        updateGL();
    }
