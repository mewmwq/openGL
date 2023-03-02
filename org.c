#include <GL/glut.h>

GLdouble cx = 0, cy = 0, l = 0.5;

void idle(void) { glutPostRedisplay(); }

void display(void) {
  int i, j;
  GLdouble cube_vertex[8][3] = {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
                                {0.5, 0.5, -0.5},   {-0.5, 0.5, -0.5},
                                {-0.5, -0.5, 0.5},  {0.5, -0.5, 0.5},
                                {0.5, 0.5, 0.5},    {-0.5, 0.5, 0.5}};
  int face[6][4] = {{0, 3, 2, 1}, {1, 2, 6, 5}, {4, 5, 6, 7},
                    {0, 4, 7, 3}, {0, 1, 5, 4}, {2, 3, 7, 6}};
  GLdouble normal[6][3] = {{0.0, 0.0, -1.0}, {1.0, 0.0, 0.0},  {0.0, 0.0, 1.0},
                           {-1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
  GLdouble floor_vertex[4][3] = {{-1.5, -1.0, -1.5},
                                 {-1.5, -1.0, 1.5},
                                 {1.5, -1.0, 1.5},
                                 {1.5, -1.0, -1.5}};
  GLfloat light0_position[4] = {1000.0, 0.0, 1000.0, 1.0};
  GLfloat light0_diffuse[4] = {0.0, 0.0, l, 1.0};
  GLfloat light1_position[4] = {-1000.0, 0.0, -1000.0, 1.0};
  GLfloat light1_diffuse[4] = {l, 0.0, 0.0, 1.0};
  GLfloat light2_position[4] = {0.0, 5000.0, 0.0, 1.0};
  GLfloat light2_diffuse[4] = {l, l, l, 1.0};
  GLfloat m_ambient[4] = {0, 0.5, 0, 1.0};
  GLfloat m_diffuse[4] = {0.5, 0.5, 0.5, 1.0};
  GLfloat m_specular[4] = {0.75, 0.75, 0.75, 1.0};
  GLfloat m_shinness = 50;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shinness);

  glLoadIdentity();
  gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotated(cx, 0.0, 1.0, 0.0);
  glRotated(cy, 1.0, 0.0, 0.0);

  glBegin(GL_QUADS);
  for (j = 0; j < 6; j++) {
    glNormal3dv(normal[j]);
    for (i = 0; i < 4; i++) {
      glVertex3dv(cube_vertex[face[j][i]]);
    }
  }
  glEnd();

  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  for (i = 0; i < 4; i++) {
    glVertex3dv(floor_vertex[i]);
  }
  glEnd();

  glFlush();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glutSwapBuffers();

  if (cx >= 360 || cx <= -360)
    cx = 0;
  else if (cy >= 360 || cy <= -360)
    cy = 0;
  if (l > 1.0) l = 0;
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, 1.0, 1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
  if (key == '\033')
    exit(0);
  else if (key == 'a') {
    cx -= 1;
  } else if (key == 'd') {
    cx += 1;
  } else if (key == 'w') {
    cy -= 1;
  } else if (key == 's') {
    cy += 1;
  } else if (key == 'q') {
    cx -= 1;
    cy -= 1;
  } else if (key == 'e') {
    cx += 1;
    cy -= 1;
  } else if (key == 'z') {
    cx -= 1;
    cy += 1;
  } else if (key == 'c') {
    cx += 1;
    cy += 1;
  } else if (key == 'x') {
    l += 0.1;
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutReshapeFunc(resize);
  glutMainLoop();
}