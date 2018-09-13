#ifndef UNITS_H
#define UNITS_H
#include<GL/glut.h>
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"MyTool.h"

typedef GLfloat Type;
typedef point<Type> PT;

//------------------Windows-------------
namespace Window {
	point<GLint> size(600, 1000);
	point<GLint> position(1200, 20);
	const char name[] = "PlaneGame";
	void InitWindow(void);
	void InitColor(void);
}
 
void Window::InitWindow(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(size.x, size.y);
	glutInitWindowPosition(position.x, position.y);
	glutCreateWindow(name);
}

void Window::InitColor(void)
{
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
	GLboolean IsOk(void);
};
const Type Bullet::size = 0.1f;

void Bullet::Display(void)
{
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();
	glFlush();
}

GLboolean Bullet::IsOk(void)
{
	if (end.y <= -1.0f)
		throw"Bullet Error";
	if (end.y >= 1.0f)
		return false;
	else
		return true;
}

//------------------Enemy-----------------
struct Enrmy {
	PT Center;
	static const Type width, high;
  Enrmy() { Center = PT(0.0f, 0.0f); };
  Enrmy(const PT center) :Center(center) {};
	void Display(void);
  GLboolean IsSafe(const Bullet & bullet);
  GLboolean IsSafe();
};
const Type Enrmy::width = 0.2f;
const Type Enrmy::high = 0.05f;

void Enrmy::Display(void)
{
	PT Pt = Center;
  glRectf(Pt.x - width / 2, Pt.y + high / 2, Pt.x + width / 2, Pt.y - high / 2);
	glFlush();
}

GLboolean Enrmy::IsSafe(const Bullet & bullet)
{
  PT start(bullet.start - Center);
  if (abs(start.x) < width / 2 && abs(start.y) < high / 2)
    return false;
  else
    return true;
}

GLboolean Enrmy::IsSafe()
{
  if (Center.y <= -1.0f)
    return false;
  else
    return true;
}

//------------------Plane---------------
namespace Plane {
	PT Center(0.0f, -0.9f);
	Type ago(0.1f), after(0.03f), side(0.05f);
	std::vector<Bullet> bullets;
  std::vector<Enrmy> enrmys;
	void DisplayPlane(void);
	void Display(void);
	void MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y);
	void MouseMove(GLint mouse_x, GLint mouse_y);
  void MouseButtonMove(GLint mouse_x, GLint mouse_y);
}

void Plane::DisplayPlane(void)
{
	PT Pt = Center;
	glBegin(GL_TRIANGLES);
	glVertex2f(Pt.x - side, Pt.y - after);
	glVertex2f(Pt.x, Pt.y + ago);
	glVertex2f(Pt.x + side, Pt.y - after);
	glEnd();
	glFlush();
}

void Plane::Display(void)
{
	Window::InitColor();
  //Display Plane
	DisplayPlane();
	Sleep(20);
  //Create Enrmys
  if (rand() % 20 == 0) {
    Enrmy NewEnrmy;
    Type temp = rand() % 20 * 0.1f - 1.0f;
    NewEnrmy.Center = PT(temp, 1.0f); 
    enrmys.push_back(NewEnrmy);
  }
  //Display Enrmys
  auto enrmy = enrmys.begin();
  while (enrmy != enrmys.end()) {
    enrmy->Display();
    enrmy->Center.y -= Enrmy::high / 10;
    if (enrmy->IsSafe() == false)
      enrmy = enrmys.erase(enrmy);
    else
      enrmy++;
  }
  //Display Bullets
	auto bullet = bullets.begin();
	while (bullet!=bullets.end()) {
    
    //Attack Enrmy
    auto enrmy = enrmys.begin();
    while (enrmy != enrmys.end()) {
      if (enrmy->IsSafe(*bullet) == false) {
        enrmy = enrmys.erase(enrmy);
        break;
      }
      else
        enrmy++;
    }
    
		bullet->Display();
		bullet->start.y += Bullet::size*0.1f;
		bullet->end.y += Bullet::size*0.1f;
		if (bullet->IsOk())
			bullet++;
		else
			bullet = bullets.erase(bullet);
	}
	glutPostRedisplay();
  glutSwapBuffers();
}

void Plane::MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y)
{
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
    //Create Bullets
		Bullet NewBullet(Center, Center);
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
	Center = NewCenter;
}

void Plane::MouseButtonMove(GLint mouse_x, GLint mouse_y)
{
  static unsigned int count = 0;
  MouseMove(mouse_x, mouse_y);
  //Create Bullets
  count++;
  if ((count %= 5) == 4)
    MouseButton(GLUT_LEFT_BUTTON, GLUT_DOWN, mouse_x, mouse_y);
}

//-----------------Message-----------------
namespace Message {
	std::string str;
}
#endif // !UNITS_H

