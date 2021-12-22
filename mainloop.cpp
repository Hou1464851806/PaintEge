#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include"mainloop.h"
#include"initialization.h"
#include"draw.h"

const int buffSize = 128;
char buff[128] = { "" };
int len = 0;
int DlineN = 0;
int IlineN = 1;
int isCorrect = 0;
int isComplete = 0;
//int nc = 0, nl = 0, ns = 0, np = 0;
int shapen = 0;
command cnd;

void mainloop()
{
	
	for (; is_run(); delay_fps(60))
	{
		showCommand();
	}
}

void setCommand(command* const des)
{
	des->n = 0;
	for (int i = 0; i < 20; i++)
	{
		des->data[i] = -1;
	}
}

void createCommand(command * const des, const char* src)
{
	int n = 0;
	char tmps[128];
	char* ptr;
	strcpy(tmps, src);
	ptr = strtok(tmps, " ");
	if (ptr != NULL)
	{
		strcpy(des->name, ptr);
	}
	else
	{
		//strcpy(des->name, "unknown command");
	}
	while (ptr != NULL)
	{
		ptr = strtok(NULL, ",");
		des->n = n;
		if (ptr == NULL)
		{
			break;
		}
		des->data[n++] = atof(ptr);
	}
	len = 0;
	buff[len] = '\0';
	DlineN++;
}

void showCommand()
{
	//setviewport(0, Cheight, Dwidth - 5 * 2, Sheight);
	setfont(fontSize, 0, "Times New Roman");
	//detect keyboard message
	while (kbmsg())
	{
		key_msg keyMsg = getkey();
		//detect whether the message is a char
		if (keyMsg.msg == key_msg_char)
		{
			char ch = keyMsg.key;
			//detect whether the message is not a special char
			if (ch != '\r')
			{
				if (ch != '\b' && len < buffSize - 1)//act like backspace
				{
					buff[len++] = ch;
					buff[len] = '\0';
				}
				else
				{
					if (len > 0)
					{
						buff[len-1] = '\0';
						len--;
					}
					else
					{	
						len = 0;
						buff[len] = '\0';
					}
				}
			}
			else 
			{
				if (len != 0)
				{
					setCommand(&cnd);
					createCommand(&cnd, buff);
					respondCommand(&cnd);
				}
			}
		}
		setviewport(0, Cheight + fontSize * DlineN, Dwidth - 5 * 2, Cheight + fontSize * (DlineN + 1));
		clearviewport();
		outtextrect(0, 0, Dwidth - 5 * 2, fontSize, buff);//show the command immediately
		
	}
}

void respondCommand(command* const des)
{
	isCorrect = 0;
	isComplete = 1;
	if (!strcmp(des->name, "circle"))
	{
		isCorrect = 1;
		if (cnd.data[0] != -1 && cnd.data[1] != -1 && cnd.data[2] != -1 && cnd.data[3] != -1 && cnd.data[4] == -1)
		{
			
			isComplete = 1;
			setviewport(Dwidth, Cheight, Swidth, Sheight);
			xyprintf(0, fontSize * IlineN, "You have just drawn a %s!", cnd.name);
			IlineN++;
			circles_set(&shape[shapen++], cnd.data[0], cnd.data[1], cnd.data[2], cnd.data[3]);
			circles_draw(&shape[shapen - 1]);
		}
		else
		{
			isComplete = 0;
		}
	}
	if (!strcmp(des->name, "line"))
	{
		isCorrect = 1;
		if (cnd.data[0] != -1 && cnd.data[1] != -1 && cnd.data[2] != -1 && cnd.data[3] != -1 && cnd.data[4] == -1)
		{
			setviewport(Dwidth, Cheight, Swidth, Sheight);
			xyprintf(0, fontSize * IlineN, "You have just drawn a %s!", cnd.name);
			IlineN++;
			lines_set(&shape[shapen++], cnd.data[0], cnd.data[1], cnd.data[2], cnd.data[3]);
			lines_draw(&shape[shapen - 1]);
		}
		else
		{
			isComplete = 0;
		}
	}
	if (!strcmp(des->name, "square"))
	{
		isCorrect = 1;
		if (cnd.data[0] != -1 && cnd.data[1] != -1 && cnd.data[2] != -1 && cnd.data[3] != -1 && cnd.data[4] == -1)
		{
			setviewport(Dwidth, Cheight, Swidth, Sheight);
			xyprintf(0, fontSize * IlineN, "You have just drawn a %s!", cnd.name);
			IlineN++;
			squares_set(&shape[shapen++], cnd.data[0], cnd.data[1], cnd.data[2], cnd.data[3]);
			squares_draw(&shape[shapen - 1]);
		}
		else
		{
			isComplete = 0;
		}
	}
	if (!strcmp(des->name, "poly"))
	{
		isCorrect = 1;
		if (cnd.n % 2 == 0)
		{
			setviewport(Dwidth, Cheight, Swidth, Sheight);
			xyprintf(0, fontSize * IlineN, "You have just drawn a %s!", cnd.name);
			IlineN++;
			polys_set(&shape[shapen++], cnd.n, cnd.data);
			polys_draw(&shape[shapen - 1]);
		}
		else
		{
			isComplete = 0;
		}
	}
	if (!strcmp(des->name, "clear"))
	{
		isCorrect = 1;
		setviewport(Dwidth, Cheight, Swidth, Sheight);
		xyprintf(0, fontSize * IlineN, "You have just cleared the canvas!");
		IlineN++;
		clear();
	}
	if (!strcmp(des->name, "exit"))
	{
		isCorrect = 1;
		exit(EXIT_SUCCESS);
	}

	if (!strcmp(des->name, "undo"))
	{
		isCorrect = 1;
		setviewport(Dwidth, Cheight, Swidth, Sheight);
		xyprintf(0, fontSize * IlineN, "You have undid a command!");
		IlineN++;
		undo();
	}

	if (!strcmp(des->name, "redo"))
	{
		isCorrect = 1;
		setviewport(Dwidth, Cheight, Swidth, Sheight);
		xyprintf(0, fontSize * IlineN, "You have redid a command!");
		IlineN++;
		redo();
	}

	if (!isCorrect)
	{
		setviewport(Dwidth, Cheight, Swidth, Sheight);
		xyprintf(0, fontSize * IlineN, "Unknown Command!");
		IlineN++;
		//not show the unknown command
		DlineN--;
		buff[0] = '\0';
	}

	if (isCorrect == 1 && isComplete == 0)
	{
		setviewport(Dwidth, Cheight, Swidth, Sheight);
		xyprintf(0, fontSize * IlineN, "Incorrect parameters!");
		IlineN++;
		DlineN--;
		buff[0] = '\0';
	}
}
