/***
	* Author :	Zou Zhichao
	* StuID	 :  17S103251
	* Date	 :	2017-10-25

	* ��������Ҫʹ�õĺ���
	* �����˻�ֱ�ߵ������㷨DDA��Bresenham
	* Bresenham��б��Ϊ0-1��ֱ�ߣ�DAA���ߵ�б�ʲ�������
***************************************************/
#pragma once

#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define VIEW_RANGE 600		/* ��ʾ��Χ*/
#define WINDOWS_RANGE 600	/* ���ڷ�Χ*/
#define DDA_Methon -1		/* ʹ��DDA�㷨*/
#define Bresenham_Methon 1  /* ʹ��Bresenham�㷨*/
void myInit();														/*��ʼ������*/
void myDrawLine_DDA(GLint x0, GLint y0, GLint x1, GLint y1);		/*DDA����*/
void myDrawLine_bresenham(GLint x, GLint y, GLint x1, GLint y1);	/*bresenham����*/
void myDisplay();													/*��ʾ����*/
void myOnMouse(int button, int state, int x, int y);				/*����¼�������*/

void mySwap2i(int &a, int &b);										/*������������*/
