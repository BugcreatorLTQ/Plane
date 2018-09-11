#include"Units.h"

///Main
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
	Window::InitWindow();
	glutDisplayFunc(Plane::Display);
	glutMouseFunc(Plane::MouseButton);
	glutPassiveMotionFunc(Plane::MouseMove);
	Window::InitColor();
	glutMainLoop();
	return 0;
}