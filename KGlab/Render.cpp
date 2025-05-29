#include "Render.h"
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "GUItextRectangle.h"
#include "MyShaders.h"

#define PI 3.14159265358979323846

struct Vector3 {
	double x, y, z;

	Vector3 operator-(const Vector3& v) const {
		return { x - v.x, y - v.y, z - v.z };
	}

	Vector3 cross(const Vector3& v) const {
		return {
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		};
	}

	double length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3 normalize() const {
		double len = length();
		return { x / len, y / len, z / len };
	}
};

Vector3 calculateNormalVector(const Vector3& A, const Vector3& B, const Vector3& C) {
	Vector3 AB = B - A;
	Vector3 AC = C - A;
	Vector3 N = AC.cross(AB); // Изменили порядок векторов
	return N.normalize();
}

Vector3 calculateTopFaceNormal(const double* A, const double* B, const double* C) {
	Vector3 AB = { B[0] - A[0], B[1] - A[1], B[2] - A[2] };
	Vector3 AC = { C[0] - A[0], C[1] - A[1], C[2] - A[2] };
	Vector3 N = AB.cross(AC);
	return N.normalize();
}

Vector3 calculateBottomFaceNormal(const double* A, const double* B, const double* C) {
	Vector3 AB = { B[0] - A[0], B[1] - A[1], B[2] - A[2] };
	Vector3 AC = { C[0] - A[0], C[1] - A[1], C[2] - A[2] };
	Vector3 N = AC.cross(AB);
	return N.normalize();
}

Vector3 calculateSideFaceNormal(const double* A, const double* B, const double* C) {
	Vector3 AB = { B[0] - A[0], B[1] - A[1], B[2] - A[2] };
	Vector3 AC = { C[0] - A[0], C[1] - A[1], C[2] - A[2] };
	Vector3 N = AC.cross(AB);
	return N.normalize();
}

void drawFigure(GLuint texId)
{
	Vector3 A = { 1.0, 0.0, 0.0 };
	Vector3 B = { 6.0, 3.0, 0.0 };
	Vector3 C = { 4.0, 7.0, 0.0 };
	Vector3 D = { 0.0, 2.0, 0.0 };
	Vector3 E = { -4.0, 3.0, 0.0 };
	Vector3 F = { -7.0, -2.0, 0.0 };
	Vector3 G = { -2.0, -6.0, 0.0 };
	Vector3 H = { 3.0, -4.0, 0.0 };

	double height = 1.0;

	Vector3 A1 = { 1.0, 0.0, height };
	Vector3 B1 = { 6.0, 3.0, height };
	Vector3 C1 = { 4.0, 7.0, height };
	Vector3 D1 = { 0.0, 2.0, height };
	Vector3 E1 = { -4.0, 3.0, height };
	Vector3 F1 = { -7.0, -2.0, height };
	Vector3 G1 = { -2.0, -6.0, height };
	Vector3 H1 = { 3.0, -4.0, height };

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);

	Vector3 normal = calculateNormalVector(A, B, C);

	glBegin(GL_QUADS);

	glNormal3d(0, 0, -1);
	glColor3d(1, 0.213, 0.2);
	glVertex3dv((double*)&A);
	glVertex3dv((double*)&B);
	glVertex3dv((double*)&C);
	glVertex3dv((double*)&D);

	glNormal3d(0, 0, -1);
	glColor3d(0.8, 1.0, 0.3);
	glVertex3dv((double*)&A);
	glVertex3dv((double*)&D);
	glVertex3dv((double*)&E);
	glVertex3dv((double*)&H);

	glNormal3d(0, 0, -1);
	glColor3d(0.9, 0.32, 0.4);
	glVertex3dv((double*)&E);
	glVertex3dv((double*)&F);
	glVertex3dv((double*)&G);
	glVertex3dv((double*)&H);

	normal = calculateNormalVector(A, A1, B1);
	glNormal3dv((double*)&normal);
	glColor3d(0.1, 0.0, 0.5);
	glVertex3dv((double*)&A);
	glVertex3dv((double*)&A1);
	glVertex3dv((double*)&B1);
	glVertex3dv((double*)&B);

	normal = calculateNormalVector(B, B1, C1);
	glNormal3dv((double*)&normal);
	glColor3d(0.76, 0.2, 0.6);
	glVertex3dv((double*)&B);
	glVertex3dv((double*)&B1);
	glVertex3dv((double*)&C1);
	glVertex3dv((double*)&C);

	normal = calculateNormalVector(C, C1, D1);
	glNormal3dv((double*)&normal);
	glColor3d(0, 0.3, 0.7);
	glVertex3dv((double*)&C);
	glVertex3dv((double*)&C1);
	glVertex3dv((double*)&D1);
	glVertex3dv((double*)&D);

	normal = calculateNormalVector(D, D1, E1);
	glNormal3dv((double*)&normal);
	glColor3d(0.3, 0.4, 0.8);
	glVertex3dv((double*)&D);
	glVertex3dv((double*)&D1);
	glVertex3dv((double*)&E1);
	glVertex3dv((double*)&E);

	normal = calculateNormalVector(F, F1, G1);
	glNormal3dv((double*)&normal);
	glColor3d(0.3, 0.6, 1.0);
	glVertex3dv((double*)&F);
	glVertex3dv((double*)&F1);
	glVertex3dv((double*)&G1);
	glVertex3dv((double*)&G);

	normal = calculateNormalVector(G, G1, H1);
	glNormal3dv((double*)&normal);
	glColor3d(0.3, 0.7, 0.9);
	glVertex3dv((double*)&G);
	glVertex3dv((double*)&G1);
	glVertex3dv((double*)&H1);
	glVertex3dv((double*)&H);

	normal = calculateNormalVector(H, H1, A1);
	glNormal3dv((double*)&normal);
	glColor3d(0.3, 0.6, 0.8);
	glVertex3dv((double*)&H);
	glVertex3dv((double*)&H1);
	glVertex3dv((double*)&A1);
	glVertex3dv((double*)&A);

	double VectorFE[] = { F.x - E.x, F.y - E.y, F.z - E.z };
	double startfaza = PI + atan2(VectorFE[1], VectorFE[0]);
	double MID[] = { (E.x + F.x) / 2, (E.y + F.y) / 2, (E.z + F.z) / 2 };
	double radius = sqrt(VectorFE[0] * VectorFE[0] + VectorFE[1] * VectorFE[1]) / 2;
	int i = 0;
	glColor3d(0.3, 0.5, 0.1);
	while (i < 90)
	{
		double x = MID[0] + radius * cos(2 * PI * i / 180 + startfaza);
		double y = MID[1] + radius * sin(2 * PI * i / 180 + startfaza);
		double z = MID[2];
		double x1 = MID[0] + radius * cos(2 * PI * (i + 1) / 180 + startfaza);
		double y1 = MID[1] + radius * sin(2 * PI * (i + 1) / 180 + startfaza);
		double z1 = MID[2];

		Vector3 normalBot = calculateBottomFaceNormal(MID, new double[3] {x, y, z}, new double[3] {x1, y1, z1});
		glNormal3dv((double*)&normalBot);
		glColor3d(0.3, 0.5, 0.1);
		glVertex3d(MID[0], MID[1], MID[2]);
		glVertex3d(x, y, z);

		glNormal3dv((double*)&normalBot);
		glVertex3d(x1, y1, z1);
		glVertex3d(MID[0], MID[1], MID[2]);

		Vector3 normalSide = calculateSideFaceNormal(new double[3] {x, y, z}, new double[3] {x, y, z + height}, new double[3] {x1, y1, z1 + height});
		glNormal3dv((double*)&normalSide);
		glColor3d(1, 0.5, 0.1);
		glVertex3d(x, y, z);
		glVertex3d(x, y, z + height);
		glVertex3d(x1, y1, z1 + height);
		glVertex3d(x1, y1, z1);

		i++;
	}

	i = 0;
	glColor3d(0.3, 0.5, 0.1);

	while (i < 90)
	{
		double x = MID[0] + radius * cos(2 * PI * i / 180 + startfaza);
		double y = MID[1] + radius * sin(2 * PI * i / 180 + startfaza);
		double z = MID[2];
		double x1 = MID[0] + radius * cos(2 * PI * (i + 1) / 180 + startfaza);
		double y1 = MID[1] + radius * sin(2 * PI * (i + 1) / 180 + startfaza);
		double z1 = MID[2];
		Vector3 normal = calculateTopFaceNormal(MID, new double[3] {x, y, z}, new double[3] {x1, y1, z1});
		glNormal3dv((double*)&normal);
		glColor4d(0.3, 0.5, 0.1, 0.5);
		glVertex3d(MID[0], MID[1], MID[2] + height);
		glVertex3d(x, y, z + height);
		glVertex3d(x1, y1, z1 + height);
		glVertex3d(MID[0], MID[1], MID[2] + height);
		i++;
	}

	glNormal3d(0, 0, 1);
	glColor4d(0.3, 0.5, 0.1, 0.5);
	glVertex3dv((double*)&A1);
	glVertex3dv((double*)&B1);
	glVertex3dv((double*)&C1);
	glVertex3dv((double*)&D1);

	glNormal3d(0, 0, 1);
	glColor4d(0.3, 0.5, 0.1, 0.5);
	glVertex3dv((double*)&A1);
	glVertex3dv((double*)&D1);
	glVertex3dv((double*)&E1);
	glVertex3dv((double*)&H1);

	glNormal3d(0, 0, 1);
	glColor4d(0.3, 0.5, 0.1, 0.5);
	glVertex3dv((double*)&E1);
	glVertex3dv((double*)&F1);
	glVertex3dv((double*)&G1);
	glVertex3dv((double*)&H1);

	glEnd();
}

#include "MyOGL.h"
extern OpenGL gl;
#include "Light.h"
Light light;
#include "Camera.h"
Camera camera;

bool texturing = true;
bool lightning = true;
bool alpha = false;

void switchModes(OpenGL *sender, KeyEventArg arg)
{
	//конвертируем код клавиши в букву
	auto key = LOWORD(MapVirtualKeyA(arg.key, MAPVK_VK_TO_CHAR));

	switch (key)
	{
	case 'L':
		lightning = !lightning;
		break;
	case 'T':
		texturing = !texturing;
		break;
	case 'A':
		alpha = !alpha;
		break;
	}
}

GuiTextRectangle text;

GLuint texId;

void initRender()
{
	//==============НАСТРОЙКА ТЕКСТУР================
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	//================НАСТРОЙКА КАМЕРЫ======================
	camera.caclulateCameraPos();

	gl.WheelEvent.reaction(&camera, &Camera::Zoom);
	gl.MouseMovieEvent.reaction(&camera, &Camera::MouseMovie);
	gl.MouseLeaveEvent.reaction(&camera, &Camera::MouseLeave);
	gl.MouseLdownEvent.reaction(&camera, &Camera::MouseStartDrag);
	gl.MouseLupEvent.reaction(&camera, &Camera::MouseStopDrag);
	//==============НАСТРОЙКА СВЕТА===========================
	gl.MouseMovieEvent.reaction(&light, &Light::MoveLight);
	gl.KeyDownEvent.reaction(&light, &Light::StartDrug);
	gl.KeyUpEvent.reaction(&light, &Light::StopDrug);
	//========================================================
	//====================Прочее==============================
	gl.KeyDownEvent.reaction(switchModes);
	text.setSize(512, 180);
	//========================================================
	camera.setPosition(2, 1.5, 1.5);
}

float view_matrix[16];
double full_time = 0;
void Render(double delta_time)
{    
	full_time += delta_time;

	if (gl.isKeyPressed('F')) //если нажата F - свет из камеры
	{
		light.SetPosition(camera.x(), camera.y(), camera.z());
	}
	camera.SetUpCamera();

	glGetFloatv(GL_MODELVIEW_MATRIX,view_matrix);

	light.SetUpLight();

	gl.DrawAxes();

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_NORMALIZE);  
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	if (lightning)
		glEnable(GL_LIGHTING);
	if (texturing)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0); //сбрасываем текущую текстуру
	}
		
	if (alpha)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
		
	//=============НАСТРОЙКА МАТЕРИАЛА==============-

	float  amb[] = { 0.2, 0.2, 0.1, 1. };
	float dif[] = { 0.4, 0.65, 0.5, 1. };
	float spec[] = { 0.9, 0.8, 0.3, 1. };
	float sh = 0.2f * 256;

	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec); 

	glMaterialf(GL_FRONT, GL_SHININESS, sh);

	glShadeModel(GL_SMOOTH);     

	//============ РИСОВАТЬ ТУТ ==============

	drawFigure(texId);

	//===============================================

	//================Сообщение в верхнем левом углу=======================
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, gl.getWidth() - 1, 0, gl.getHeight() - 1, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	std::wstringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << "T - " << (texturing ? L"[вкл]выкл  " : L" вкл[выкл] ") << L"текстур" << std::endl;
	ss << "L - " << (lightning ? L"[вкл]выкл  " : L" вкл[выкл] ") << L"освещение" << std::endl;
	ss << "A - " << (alpha ? L"[вкл]выкл  " : L" вкл[выкл] ") << L"альфа-наложение" << std::endl;
	ss << L"F - Свет из камеры" << std::endl;
	ss << L"G - двигать свет по горизонтали" << std::endl;
	ss << L"G+ЛКМ двигать свет по вертекали" << std::endl;
	ss << L"Коорд. света: (" << std::setw(7) <<  light.x() << "," << std::setw(7) << light.y() << "," << std::setw(7) << light.z() << ")" << std::endl;
	ss << L"Коорд. камеры: (" << std::setw(7) << camera.x() << "," << std::setw(7) << camera.y() << "," << std::setw(7) << camera.z() << ")" << std::endl;
	ss << L"Параметры камеры: R=" << std::setw(7) << camera.distance() << ",fi1=" << std::setw(7) << camera.fi1() << ",fi2=" << std::setw(7) << camera.fi2() << std::endl;
	ss << L"delta_time: " << std::setprecision(5)<< delta_time << std::endl;
	ss << L"full_time: " << std::setprecision(2) << full_time << std::endl;

	text.setPosition(10, gl.getHeight() - 10 - 180);
	text.setText(ss.str().c_str());
	
	text.Draw();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}   