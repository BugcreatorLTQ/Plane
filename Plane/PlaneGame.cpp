#include"Units.h"

///Main
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
  srand((unsigned int)time(NULL));
	Window::InitWindow();
	glLineWidth(4.0);
	glutDisplayFunc(Plane::Display);
	glutMouseFunc(Plane::MouseButton);
	glutPassiveMotionFunc(Plane::MouseMove);
  glutMotionFunc(Plane::MouseButtonMove);
	Window::InitColor();
	glutMainLoop();
	return 0;
}