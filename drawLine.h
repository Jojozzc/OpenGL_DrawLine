/***
	* Author :	Zou Zhichao
	* StuID	 :  17S103251
	* Date	 :	2017-10-25

	* 声明了需要使用的函数
	* 声明了画直线的两种算法DDA和Bresenham
	* Bresenham画斜率为0-1的直线，DAA画线的斜率不受限制
***************************************************/
#pragma once

#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define VIEW_RANGE 600		/* 显示范围*/
#define WINDOWS_RANGE 600	/* 窗口范围*/
#define DDA_Methon -1		/* 使用DDA算法*/
#define Bresenham_Methon 1  /* 使用Bresenham算法*/
void myInit();														/*初始化函数*/
void myDrawLine_DDA(GLint x0, GLint y0, GLint x1, GLint y1);		/*DDA方法*/
void myDrawLine_bresenham(GLint x, GLint y, GLint x1, GLint y1);	/*bresenham方法*/
void myDisplay();													/*显示函数*/
void myOnMouse(int button, int state, int x, int y);				/*鼠标事件处理函数*/

void mySwap2i(int &a, int &b);										/*交换两个变量*/
