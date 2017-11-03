/**
	* 作者：邹致超
	* 17S103251
	* 2017/10/25 创建
	* 2017/11/1  最后修改
*/
#include "drawLine.h"

using namespace std;

/*在"drawLine.cpp"中定义的全局变量*/
extern GLint startX;
extern GLint startY;
extern GLint endX;
extern GLint endY;
extern int drawMethon;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	cout << "请选择绘图方法：DDA(0)或者Bresenham(1)：" 	/* 提示用户选择绘图算法*/
		<< "(之后可以在画图窗口点击鼠标右键切换)" << endl;
	cin >> drawMethon;
	if (drawMethon == 0) {
		drawMethon = -1;	// DDA算法
		cout << "【当前算法为DDA】" << endl;
	}
	else {
		drawMethon = 1;		/* Bresenham算法*/
		cout << "【当前算法为Bresenham】" << endl;
	}
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOWS_RANGE, WINDOWS_RANGE);
	glutCreateWindow("DrawLine");
	glutDisplayFunc(&myDisplay);
	glutMouseFunc(&myOnMouse);	/*注册鼠标响应函数*/
	myInit();					/*初始化各种全局变量、显示参数等*/
	glutMainLoop();
	return 0;
}