#ifndef UNITS_H
#define UNITS_H
#include<GL/glut.h>
#include<vector>
#include"MyTool.h"

typedef GLfloat Type;
typedef point<Type> PT;

//------------------Windows-------------
namespace Window {
	point<GLint> size(400, 800);
	point<GLint> position(40, 40);
	const char name[] = "PlaneGame";
	void Init(void);
}
 
void Window::Init(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(size.x, size.y);
	glutInitWindowPosition(position.x, position.y);
	glutCreateWindow(name);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
}
//------------------Bullet--------------
struct Bullet {
	static const Type size;
	PT start;
	PT end;
	Bullet(void) {};
	Bullet(const PT start, const PT end) :start(start), end(end) {};
	void Display(void);
};
const Type Bullet::size = 0.2f;

void Bullet::Display(void)
{
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();
	glFlush();
}

//------------------Plane---------------
namespace Plane {
	PT PlaneCenter(0.0f, -0.9f);
	Type ago(0.1f), after(0.03f), side(0.05f);
	std::vector<Bullet> bullets;
	void DisplayPlane(void);
	void Display(void);
	void MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y);
	void MouseMove(GLint mouse_x, GLint mouse_y);
}

void Plane::DisplayPlane(void)
{
	PT Pt = PlaneCenter;
	glBegin(GL_TRIANGLES);
	glVertex2f(Pt.x - side, Pt.y - after);
	glVertex2f(Pt.x, Pt.y + ago);
	glVertex2f(Pt.x - side, Pt.y - after);
	glEnd();
	glFlush();
}

void Plane::Display(void)
{
	DisplayPlane();
	for (auto bullet : bullets)
		bullet.Display();

}

void Plane::MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y)
{
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		Bullet NewBullet(PlaneCenter, PlaneCenter);
		NewBullet.start.y += ago + Bullet::size;
		NewBullet.end.y += ago;
		bullets.push_back(NewBullet);
	}
}

void Plane::MouseMove(GLint mouse_x, GLint mouse_y)
{
	using Window::size;
	PT NewCenter;
	NewCenter.x = 2.0f* mouse_x / size.x - 1.0f;
	NewCenter.y = -2.0f*mouse_y / size.y + 1.0f;
	PlaneCenter = NewCenter;
}

#endif // !UNITS_H
