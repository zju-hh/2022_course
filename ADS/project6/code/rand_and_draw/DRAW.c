/*
 * File: main.c
 * -------------
 * This program verify the basic function of libgraphics
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "imgui.h"
#define BL 12


void Main() {
	double a[10000] = { 0 };
	double b[10000] = { 0 };
	double c[10000] = { 0 };
	double d[10000] = { 0 };
	double width;
	int n = 0;
	FILE* fpRead = fopen("draw.txt", "r");
	if (fpRead == NULL)
	{	
		printf("failed to open file");
		return 0;
	}
	fscanf(fpRead, "%lf", &width);
	fscanf(fpRead, "%d", &n);
	
	for (int i = 0; i < n; i++)
	{
		fscanf(fpRead, "%lf", &a[i]);
		fscanf(fpRead, "%lf", &b[i]);
		fscanf(fpRead, "%lf", &c[i]);
		fscanf(fpRead, "%lf", &d[i]);

	}
	InitGraphics();
	double cx, cy;
	cx = 0.1;
	cy = 0.1;
	/*SetWindowTitle("FILL");
	SetPenColor("Blue");
	drawBox(cx, cy, 20, 10, 1, "", 'f', "blue3");
	DrawBox(cx, cy, 2.0, 3.0);
	
	//SetFillcolor("RED");
	//FillRectanglr(20, 45, 70, 55);
	//setfillcolor("Red");
SetPenColor("Red");
	DrawCenteredCircle(cx, cy, 1.0);
	SetPenColor("Orange");
	DrawTriangle(cx, cy, 2.0, 1.7);*/
	SetPenColor("red");
	MovePen(cx, cy);
	DrawLine(0, 10);
	MovePen(cx, cy);
	DrawLine(width/BL, 0);
	MovePen(cx+ width /BL, cy);
	DrawLine(0, 10);
	for (int j = 0; j < n; j++)
	{
		SetPenColor("gray");
		drawBox(cx + a[j]/BL, cy + b[j]/BL, c[j]/BL, d[j]/BL, 1, "", 'L', "black");
		SetPenColor("black");
		drawBox(cx + a[j] / BL , cy + b[j] / BL, c[j] / BL, d[j] / BL, 0, "", 'L', "red");
	}
	return 0;
}