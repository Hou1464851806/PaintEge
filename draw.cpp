#include<graphics.h>
#include"draw.h"
#include"initialization.h"

//circles c[10];
//lines l[10];
//squares s[10];
//polys p[10];
shapes shape[20];
extern int shapen;
int is_undo = 0;

void circles_set(shapes* const me, float x, float y, float w, float h)
{
	me->c.x = x;
	me->c.y = y;
	me->c.width = w;
	me->c.height = h;
	//me->n++;
}

void lines_set(shapes* const me, float x1, float y1, float x2, float y2)
{
	me->l.x1 = x1;
	me->l.x2 = x2;
	me->l.y1 = y1;
	me->l.y2 = y2;
	//me->n++;
}

void squares_set(shapes* const me, float x, float y, float w, float h)
{
	me->s.x = x;
	me->s.y = y;
	me->s.width = w;
	me->s.height = h;
	//me->n++;
}

void polys_set(shapes* const me, int pts, float points[])
{
	me->p.pts = pts;
	for (int i = 0; i < pts; i++)
	{
		me->p.points[i] = points[i];
	}
	//me->n++;
}

void circles_draw(shapes* const me)
{
	setviewport(0, 0, Swidth, Cheight - 5 * 2);
	ege_ellipse(me->c.x, me->c.y, me->c.width, me->c.height);
}

void lines_draw(shapes* const me)
{
	setviewport(0, 0, Swidth, Cheight - 5 * 2);
	ege_line(me->l.x1, me->l.y1, me->l.x2, me->l.y2);
}

void squares_draw(shapes* const me)
{
	setviewport(0, 0, Swidth, Cheight - 5 * 2);
	ege_rectangle(me->s.x, me->s.y, me->s.width, me->s.height);
}

void polys_draw(shapes* const me)
{
	setviewport(0, 0, Swidth, Cheight - 5 * 2);
	ege_drawpoly(me->p.pts / 2, (ege_point*)me->p.points);
	ege_line(me->p.points[0], me->p.points[1], me->p.points[me->p.pts - 2], me->p.points[me->p.pts - 1]);
}

void clear()
{
	setviewport(0, 0, Swidth, Cheight - 5 * 2);
	clearviewport();
}

void undo()
{
	is_undo = 1;
	clear();
	for (int i = 0; i < shapen - 1; i++)
	{
		if (shape[i].c.x != -1)
		{
			circles_draw(&shape[i]);
		}
		if (shape[i].l.x1 != -1)
		{
			lines_draw(&shape[i]);
		}
		if (shape[i].s.x != -1)
		{
			squares_draw(&shape[i]);
		}
		if (shape[i].p.pts != -1)
		{
			polys_draw(&shape[i]);
		}
	}
	if(shapen > 0) shapen--;
}

void redo()
{
	if (is_undo)
	{
		clear();
		for (int i = 0; i < shapen + 1; i++)
		{
			if (shape[i].c.x != -1)
			{
				circles_draw(&shape[i]);
			}
			if (shape[i].l.x1 != -1)
			{
				lines_draw(&shape[i]);
			}
			if (shape[i].s.x != -1)
			{
				squares_draw(&shape[i]);
			}
			if (shape[i].p.pts != -1)
			{
				polys_draw(&shape[i]);
			}
		}
		if (shapen >= 0) shapen++;
	}
}