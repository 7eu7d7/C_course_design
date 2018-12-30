#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"./sqlite3.h"//使用sqlite数据库作为数据储存介质
#pragma comment(lib, "sqlite3.lib")


/*
 *结构体声明
*/
struct Mark {
	int id;
	char* name;
	bool sex;//0男，1女
	float weight;
	int lung_capacity;
	int up_body;
	int situp;
};
template<typename T> struct CArray {//定义一个结构体作为带长度记录的数组，便于使用
	T* data;//泛型数组，根据需要替换类型
	int length=0;
};

/*
 *变量声明
*/
static sqlite3* db = NULL; //声明sqlite关键结构指针


/*
 *函数声明
*/
bool initialization();
bool c_insert(Mark sc);
CArray<Mark>* c_getMark();
CArray<Mark>* c_getSorted(int type);
Mark* c_getMark(char* name);
bool c_update(Mark sc);
bool c_setAll(CArray<Mark> sc);
bool c_remove(Mark sc);
CArray<Mark>* newMarkArray(int len);
float cal_Score(Mark mark);
bool dosql(char* zSQL);
void quickSort(CArray<Mark>* arr,int low,int high);
bool csetRates(CArray<int> rates);
CArray<int>* cgetRates();