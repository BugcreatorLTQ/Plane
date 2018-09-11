#include"Units.h"

///Main
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
	Window::Init();
	glutDisplayFunc(Plane::DisplayPlane);
	glutMainLoop();
	return 0;
}