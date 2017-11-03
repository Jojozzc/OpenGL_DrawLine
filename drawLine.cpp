#include "drawLine.h"
/**
	* ���� ���³�
	* 17S103251 
	* ������"drawLine.h"��ĺ���
	  define function of "drawLine.h"
*/

using namespace std;

/*����ȫ�ֱ��� ��ʾ�����յ�����*/
GLint startX;
GLint startY;
GLint endX;
GLint endY;

int drawMethon = DDA_Methon; /* ��ͼģʽ����*/
bool isFirstDown = true;	 /* �ж�����Ƿ��һ�ΰ���*/
/*****************************/

void myDrawLine_DDA(GLint x0, GLint y0, GLint x1, GLint y1) {
	/*DDA��������*/
	int deltaX = x1 - x0;	/* x�ܱ仯��*/
	int deltaY = y1 - y0;	/* y�ܱ仯��*/
	int steps;				/* ����	*/
	float incX;				/* x������*/
	float incY;				/* y������*/
	float x = x0;			/* xΪ�仯��*/
	float y = y0;			/* yΪ�仯��*/

	/*x��y�仯�������Ϊ����*/
	if (abs(deltaX) > abs(deltaY)) {
		steps = abs(deltaX);
	}
	else {
		steps = abs(deltaY);
	}
	cout << "steps = " << steps << endl;	/* ��ʾ����������ʱ�� */
	incX = (float)deltaX / (float)steps;	/* ����x��yÿһ���ı仯��*/
	incY = (float)deltaY / (float)steps;	/* ����x��yÿһ���ı仯��*/

	glBegin(GL_POINTS);		/* openGL����ģʽ*/
	glVertex3d(x, y, 0);	/*�����*/
	for (int i = 0; i <= steps; i++) {
		x += incX;		/* ÿ�ε���incX����*/
		y += incY;		/* ÿ�ε���incY����*/
		glVertex3f(x, y, 0);	/*����*/
	}
	glEnd();
	glFlush();
}
void myDrawLine_bresenham(GLint x0, GLint y0, GLint x1, GLint y1) {
	// Bresenham�㷨��б��Ϊ0-1��ֱ��
	int dx;	/*x�ı仯��*/
	int dy; /*y�ı仯��*/
	int p;	/*���߲������ж��Ƿ�Ӧ����y������*/
	int x;	/*���Ƶ�����*/
	int y;		

	if (x0 > x1) {
		/*���յ�ĺ�����ʼ�մ������*/
		mySwap2i(x0, x1);
		mySwap2i(y0, y1);
	}
	x = x0;			/*x��y����㿪ʼ*/
	y = y0;			
	dx = x1 - x0;	/*����x�仯��*/
	dy = y1 - y0;	/*����y�仯��*/
	const int upInc = 2 * dx - 2 * dy;		/*�����жϳ���*/
	const int downInc = -2 * dy;			/*�����жϳ���*/
	p = dx - 2 * dy;	/*��ʼp*/
	glBegin(GL_POINTS);
	while (x <= x1){/*����㻭���յ�*/
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, y);
		x++;			/*ÿ�ζ���x����������һ������*/
		if (p < 0){	/*y����������һ������*/
			y++;		/*��y����������һ������*/
			p += upInc;	/*���߲�������ƫ��*/
		}
		else			/*����������һ������*/
			p += downInc;/*���߲�������ƫ��*/
	}
	glEnd();
	glFlush();
}
void myInit() {
	/* ��ʼ�������յ� 
	   �����½�Ϊ��� */
	startX = 0;
	startY = VIEW_RANGE - 10;
	endX = 260;
	endY = VIEW_RANGE - 300;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, VIEW_RANGE, 0.0, VIEW_RANGE);	/* ������ʾ��Χ */
	glMatrixMode(GL_MODELVIEW);
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if(drawMethon == DDA_Methon)	/*�жϻ��߷���*/
		myDrawLine_DDA(startX, startY, endX, endY);/* ʹ��DDA���� */
	else {
		myDrawLine_bresenham(startX, startY, endX, endY);/* ʹ��Bresenham���� */
	}
	glFlush();
}
void myOnMouse(int button, int state, int x, int y) {
	/* һ��ʼ����bug ����ԭ��Ӧ�������Ͻ�*/
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		/*���������£���¼�������յ�λ��*/
		if (isFirstDown) { /* ��һ�ΰ���*/
			isFirstDown = false;		/*����Ϊ��һ���Ѿ�����*/
			startX = x;					/*��������������*/
			startY = VIEW_RANGE - y;	/* �����½�Ϊ��� */
			cout << "��ǰ���λ�ã�" << startX << "," << startY << endl;
 		}
		else {
			isFirstDown = true;		/* ���ǵ�һ�ΰ��£�˵������Ѿ����ú�*/
			endX = x;				/*�����յ��������*/
			endY = VIEW_RANGE - y;	/* ����������ͼ�����y�᲻һ�£�����б任*/
			cout << "��ǰ�յ�λ�ã�" << endX << "," << endY << endl;
			glClear(GL_COLOR_BUFFER_BIT);	/* ��մ���*/
			glColor3f(1.0, 0.0, 0.0);

			if(drawMethon == DDA_Methon) 	/* �жϵ�ǰ��ͼ�㷨*/
				myDrawLine_DDA(startX, startY, endX, endY);
			else {
				myDrawLine_bresenham(startX, startY, endX, endY);
			}
			glFlush();
		}
	}
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		drawMethon = -drawMethon;	/* �Ҽ�����ʱ�ı�ʹ�õ��㷨 */
		if (drawMethon == DDA_Methon)
			cout << "����ǰ�㷨ΪDDA��" << endl;
		else
			cout << "����ǰ�㷨ΪBresenham��" << endl;
	}
	
}

void mySwap2i(int &a, int &b) {
	/*��������������ֵ*/
	int temp = a;
	a = b;
	b = temp;
}