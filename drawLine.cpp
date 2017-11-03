#include "drawLine.h"
/**
	* 作者 邹致超
	* 17S103251 
	* 定义了"drawLine.h"里的函数
	  define function of "drawLine.h"
*/

using namespace std;

/*定义全局变量 表示起点和终点坐标*/
GLint startX;
GLint startY;
GLint endX;
GLint endY;

int drawMethon = DDA_Methon; /* 画图模式变量*/
bool isFirstDown = true;	 /* 判断鼠标是否第一次按下*/
/*****************************/

void myDrawLine_DDA(GLint x0, GLint y0, GLint x1, GLint y1) {
	/*DDA方法画线*/
	int deltaX = x1 - x0;	/* x总变化量*/
	int deltaY = y1 - y0;	/* y总变化量*/
	int steps;				/* 步长	*/
	float incX;				/* x的增量*/
	float incY;				/* y的增量*/
	float x = x0;			/* x为变化量*/
	float y = y0;			/* y为变化量*/

	/*x和y变化量大的作为步长*/
	if (abs(deltaX) > abs(deltaY)) {
		steps = abs(deltaX);
	}
	else {
		steps = abs(deltaY);
	}
	cout << "steps = " << steps << endl;	/* 显示步长，测试时用 */
	incX = (float)deltaX / (float)steps;	/* 计算x和y每一步的变化量*/
	incY = (float)deltaY / (float)steps;	/* 计算x和y每一步的变化量*/

	glBegin(GL_POINTS);		/* openGL画点模式*/
	glVertex3d(x, y, 0);	/*画起点*/
	for (int i = 0; i <= steps; i++) {
		x += incX;		/* 每次递增incX的量*/
		y += incY;		/* 每次递增incY的量*/
		glVertex3f(x, y, 0);	/*画点*/
	}
	glEnd();
	glFlush();
}
void myDrawLine_bresenham(GLint x0, GLint y0, GLint x1, GLint y1) {
	// Bresenham算法画斜率为0-1的直线
	int dx;	/*x的变化量*/
	int dy; /*y的变化量*/
	int p;	/*决策参数，判断是否应该在y轴增长*/
	int x;	/*绘制点坐标*/
	int y;		

	if (x0 > x1) {
		/*让终点的横坐标始终大于起点*/
		mySwap2i(x0, x1);
		mySwap2i(y0, y1);
	}
	x = x0;			/*x，y从起点开始*/
	y = y0;			
	dx = x1 - x0;	/*计算x变化量*/
	dy = y1 - y0;	/*计算y变化量*/
	const int upInc = 2 * dx - 2 * dy;		/*决策判断常量*/
	const int downInc = -2 * dy;			/*决策判断常量*/
	p = dx - 2 * dy;	/*初始p*/
	glBegin(GL_POINTS);
	while (x <= x1){/*从起点画到终点*/
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, y);
		x++;			/*每次都在x方向上增加一个像素*/
		if (p < 0){	/*y更靠近上面一个像素*/
			y++;		/*在y方向上增长一个像素*/
			p += upInc;	/*决策参数向上偏移*/
		}
		else			/*更靠近下面一个参数*/
			p += downInc;/*决策参数向下偏移*/
	}
	glEnd();
	glFlush();
}
void myInit() {
	/* 初始化起点和终点 
	   以左下角为起点 */
	startX = 0;
	startY = VIEW_RANGE - 10;
	endX = 260;
	endY = VIEW_RANGE - 300;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, VIEW_RANGE, 0.0, VIEW_RANGE);	/* 设置显示范围 */
	glMatrixMode(GL_MODELVIEW);
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if(drawMethon == DDA_Methon)	/*判断绘线方法*/
		myDrawLine_DDA(startX, startY, endX, endY);/* 使用DDA方法 */
	else {
		myDrawLine_bresenham(startX, startY, endX, endY);/* 使用Bresenham方法 */
	}
	glFlush();
}
void myOnMouse(int button, int state, int x, int y) {
	/* 一开始遇到bug 坐标原点应该是左上角*/
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		/*鼠标左键按下，记录起点或者终点位置*/
		if (isFirstDown) { /* 第一次按下*/
			isFirstDown = false;		/*设置为第一次已经按下*/
			startX = x;					/*设置起点横纵坐标*/
			startY = VIEW_RANGE - y;	/* 以左下角为起点 */
			cout << "当前起点位置：" << startX << "," << startY << endl;
 		}
		else {
			isFirstDown = true;		/* 不是第一次按下，说明起点已经设置好*/
			endX = x;				/*设置终点横纵坐标*/
			endY = VIEW_RANGE - y;	/* 鼠标坐标与绘图坐标的y轴不一致，需进行变换*/
			cout << "当前终点位置：" << endX << "," << endY << endl;
			glClear(GL_COLOR_BUFFER_BIT);	/* 清空窗口*/
			glColor3f(1.0, 0.0, 0.0);

			if(drawMethon == DDA_Methon) 	/* 判断当前绘图算法*/
				myDrawLine_DDA(startX, startY, endX, endY);
			else {
				myDrawLine_bresenham(startX, startY, endX, endY);
			}
			glFlush();
		}
	}
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		drawMethon = -drawMethon;	/* 右键按下时改变使用的算法 */
		if (drawMethon == DDA_Methon)
			cout << "【当前算法为DDA】" << endl;
		else
			cout << "【当前算法为Bresenham】" << endl;
	}
	
}

void mySwap2i(int &a, int &b) {
	/*交换两个变量的值*/
	int temp = a;
	a = b;
	b = temp;
}