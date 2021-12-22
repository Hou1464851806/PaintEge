#pragma once

struct circles
{
	//int n = 0;
	float x = -1, y = -1, width = -1, height = -1;
};

struct lines
{
	//int n = 0;
	float x1 = -1, y1 = -1, x2 = -1, y2 = -1;
};

struct squares
{
	//int n = 0;
	float x = -1, y = -1, width = -1, height = -1;
};

struct polys
{
	//int n = 0;
	int pts = -1;
	float points[20] = { 0 };
};

struct shapes
{
	circles c;
	lines l;
	squares s;
	polys p;
};

//extern circles c[10];
//extern lines l[10];
//extern squares s[10];
//extern polys p[10];
extern shapes shape[20];

void circles_set(shapes* const me, float x, float y, float w, float h);
void lines_set(shapes* const me, float x1, float y1, float x2, float y2);
void squares_set(shapes* const me, float x, float y, float w, float h);
void polys_set(shapes* const me, int pts, float points[]);
void circles_draw(shapes* const me);
void lines_draw(shapes* const me);
void squares_draw(shapes* const me);
void polys_draw(shapes* const me);
void clear();
void undo();
void redo();