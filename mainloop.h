#pragma once

extern int DlineN;
extern int IlineN;

struct command
{
	char name[128] = { "" };
	float data[20];
	int n;
};

void mainloop();
void showCommand();
void createCommand(command* const des, const char* src);
void respondCommand(command* const des);
void setCommand(command* const des);