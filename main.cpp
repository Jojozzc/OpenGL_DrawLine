/**
	* ���ߣ����³�
	* 17S103251
	* 2017/10/25 ����
	* 2017/11/1  ����޸�
*/
#include "drawLine.h"

using namespace std;

/*��"drawLine.cpp"�ж����ȫ�ֱ���*/
extern GLint startX;
extern GLint startY;
extern GLint endX;
extern GLint endY;
extern int drawMethon;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	cout << "��ѡ���ͼ������DDA(0)����Bresenham(1)��" 	/* ��ʾ�û�ѡ���ͼ�㷨*/
		<< "(֮������ڻ�ͼ���ڵ������Ҽ��л�)" << endl;
	cin >> drawMethon;
	if (drawMethon == 0) {
		drawMethon = -1;	// DDA�㷨
		cout << "����ǰ�㷨ΪDDA��" << endl;
	}
	else {
		drawMethon = 1;		/* Bresenham�㷨*/
		cout << "����ǰ�㷨ΪBresenham��" << endl;
	}
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOWS_RANGE, WINDOWS_RANGE);
	glutCreateWindow("DrawLine");
	glutDisplayFunc(&myDisplay);
	glutMouseFunc(&myOnMouse);	/*ע�������Ӧ����*/
	myInit();					/*��ʼ������ȫ�ֱ�������ʾ������*/
	glutMainLoop();
	return 0;
}