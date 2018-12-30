#include"ScoreJudger.h"
#include<string.h>//包含字符串操作相关的头文件

int callback_exist_table(void* pHandle, int iRet, char** szSrc, char** szDst)//判断某表是否已存在的回调函数
{
	if (1 == iRet)
	{
		int iTableExist = atoi(*(szSrc));  //此处返回值为查询到同名表的个数，没有则为0，否则大于0
		if (pHandle != nullptr)//若句柄不为空则将其赋值
		{
			int* pRes = (int*)pHandle;
			*pRes = iTableExist;
		}
	}
	return 0;
}

CArray<Mark>* newMarkArray(int len) {//创建一个长度为len的Mark型数组
	CArray<Mark>* array_temp = new CArray<Mark>;//new一个CArray型结构体
	array_temp->data = new Mark[len];//设置其数据
	array_temp->length = len;//记录长度
	return array_temp;
}

bool isTableExist(const char* table)//判断一张表是否存在
{
	char* head = sqlite3_mprintf("SELECT COUNT(*) FROM sqlite_master where type ='table' and name ='%s'",table);//转换sql语句
	
	char* sErrMsg = NULL;//储存如果发生错误的错误信息

	int nTableNums = 0;
	//执行sql语句
	if (sqlite3_exec(db, head, &callback_exist_table, &nTableNums, &sErrMsg) != SQLITE_OK)
	{
		return false;
	}
	//回调函数无返回值，则此处第一次时返回SQLITE_OK， 第n次会返回SQLITE_ABORT

	return nTableNums > 0;
}

bool initialization() {//初始化
	int result;
	//打开数据库
	result = sqlite3_open("score.db", &db );
	if (result != SQLITE_OK)
	{
		//数据库打开失败
		return 0;
	}

	if (!isTableExist("Score")) {//判断Score表是否存在
		//创建Score表的sql语句
		const char* sql = "CREATE TABLE Score("  \
			"id int PRIMARY KEY," \
			"name           text," \
			"sex            text," \
			"weight        float," \
			"lung_capacity         int, "\
			"up_body_or_situp		int, "\
			"total		float"\
			");";

		dosql(sqlite3_mprintf(sql));//执行sql语句
	}
	if (!isTableExist("Rate")) {//判断Rate表是否存在
								 //创建Rate表的sql语句
		const char* sql = "CREATE TABLE Rate("  \
			"weight int PRIMARY KEY," \
			"lung_capacity         int, "\
			"up_body_or_situp		int "\
			");";

		dosql(sqlite3_mprintf(sql));//执行sql语句
		dosql(sqlite3_mprintf("INSERT INTO Rate VALUES(25,35,40)"));
	}

	return 1;
}
bool c_insert(Mark sc) {//插入一条数据
	return dosql(sqlite3_mprintf("INSERT INTO Score VALUES(%d,'%s',%d,%f,%d,%d,%f)", sc.id,sc.name,sc.sex,sc.weight,sc.lung_capacity,sc.sex?sc.situp:sc.up_body,cal_Score(sc)));
}
CArray<Mark>* c_getMark() {//查询所有数据
	int result;
	char * errmsg = NULL;
	char **dbResult; //查到的数据
	int nRow, nColumn;
	int index;

	result = sqlite3_get_table(db, "select * from Score;", &dbResult, &nRow, &nColumn, &errmsg);//执行查询语句

	if (SQLITE_OK == result)
	{
		CArray<Mark>* score_temp = newMarkArray(nRow);//新建一个跟数据条数长度一样的数组
		//查询成功
		index = nColumn; // dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (int i = 0; i < nRow; i++)
		{
			//为各数据赋值
			score_temp->data[i].id = atoi(dbResult[index++]);
			score_temp->data[i].name = dbResult[index++];
			score_temp->data[i].sex = atoi(dbResult[index++]);
			score_temp->data[i].weight = atof(dbResult[index++]);
			score_temp->data[i].lung_capacity = atoi(dbResult[index++]);
			if (score_temp->data[i].sex) {//根据性别判断做了什么项目
				score_temp->data[i].situp = atoi(dbResult[index++]);
			}else{
				score_temp->data[i].up_body = atoi(dbResult[index++]);
			}
			index++;//跳过总分数
		}
		return score_temp;
	}
	return NULL;
}
CArray<Mark>* c_getSorted(int type) {//获取排序过的数据
	CArray<Mark>* marks = c_getMark();
	quickSort(marks, 0, marks->length - 1);
	return marks;
}
Mark* c_getMark(char* name) {//根据姓名获取数据
	int result;
	char * errmsg = NULL;
	char **dbResult; //查到的数据
	int nRow, nColumn;

	char *zSQL = sqlite3_mprintf("select * from Score where name='%s';", name);//带条件的sql语句
	result = sqlite3_get_table(db,zSQL, &dbResult, &nRow, &nColumn, &errmsg);
	int index = nColumn;
	Mark* mark = new Mark;
	mark->id = atoi(dbResult[index++]);
	mark->name = dbResult[index++];
	mark->sex = atoi(dbResult[index++]);
	mark->weight = atof(dbResult[index++]);
	mark->lung_capacity = atoi(dbResult[index++]);
	if (mark->sex) {
		mark->situp = atoi(dbResult[index++]);
	}
	else {
		mark->up_body = atoi(dbResult[index++]);
	}
	return mark;
}
bool c_update(Mark sc) {//更新数据
	return dosql(sqlite3_mprintf("update Score set id='%d',name='%s',sex='%d',weight='%f',lung_capacity='%d',up_body_or_situp='%d',total='%f' where id = '%d'", sc.id, sc.name, sc.sex, sc.weight, sc.lung_capacity, sc.sex ? sc.situp : sc.up_body, cal_Score(sc),sc.id));
}
bool c_setAll(CArray<Mark> sc) {//重新设置所有数据
	dosql(sqlite3_mprintf("delete from Score"));//删除表中全部数据
	for (size_t i = 0; i < sc.length; i++)//把数组中所有数据插入表中
	{
		if (!c_insert(sc.data[i]))return 0;
	}
	return 1;
}
bool c_remove(Mark sc) {//删除一条数据
	return dosql(sqlite3_mprintf("delete from Score where id = '%d'",sc.id));
}
float cal_Score(Mark mark) {//计算得分
	float result = 0;
	CArray<int>* rates = cgetRates();
	if (mark.sex) {
		//体重分数
		if (mark.weight >= 17.2&&mark.weight <= 23.9)result += 100*rates->data[0]/100;
		else if ((mark.weight >= 0 && mark.weight <= 17.1) || (mark.weight >= 24 && mark.weight <= 27.9))result += 80 * rates->data[0] / 100;
		else if (mark.weight >= 28)result += 60 * rates->data[0] / 100;
		//肺活量分数
		if (mark.lung_capacity >= 2051&&mark.lung_capacity <= 3000)result += 60 * rates->data[1] / 100;
		else if (mark.lung_capacity >= 3001 && mark.lung_capacity <=3400)result += 80 * rates->data[1] / 100;
		else if (mark.lung_capacity > 3400)result += 100 * rates->data[1] / 100;
		else if (mark.lung_capacity >= 0 && mark.lung_capacity <= 2050)result += 30 * rates->data[1] / 100;
		//仰卧起坐分数
		if (mark.situp >= 25 && mark.situp <= 52)result += 60 * rates->data[2] / 100;
		else if (mark.situp >= 53 && mark.situp <= 56)result += 80 * rates->data[2] / 100;
		else if (mark.situp > 56)result += 100 * rates->data[2] / 100;
		else if (mark.situp >= 0 && mark.situp <= 16)result += 30 * rates->data[2] / 100;

	}
	else
	{
		//体重分数
		if (mark.weight >= 17.9&&mark.weight <= 23.9)result += 100 * rates->data[0] / 100;
		else if ((mark.weight >= 0 && mark.weight <= 17.8) || (mark.weight >= 24 && mark.weight <= 27.9))result += 80 * rates->data[0] / 100;
		else if (mark.weight >= 28)result += 60 * rates->data[0] / 100;
		//肺活量分数
		if (mark.lung_capacity >= 3101 && mark.lung_capacity <= 4180)result += 60 * rates->data[1] / 100;
		else if (mark.lung_capacity >= 4181 && mark.lung_capacity <= 4800)result += 80 * rates->data[1] / 100;
		else if (mark.lung_capacity > 4800)result += 100 * rates->data[1] / 100;
		else if (mark.lung_capacity >= 0 && mark.lung_capacity <= 3100)result += 30 * rates->data[1] / 100;
		//引体向上分数
		if (mark.up_body >= 10 && mark.up_body <= 15)result += 60 * rates->data[2] / 100;
		else if (mark.up_body >= 16 && mark.up_body <= 19)result += 80 * rates->data[2] / 100;
		else if (mark.up_body > 19)result += 100 * rates->data[2] / 100;
		else if (mark.up_body >= 0 && mark.up_body <= 9)result += 30 * rates->data[2] / 100;

	}
	return result;
}

bool dosql(char* zSQL) {//将执行sql语句的步骤封装，便于使用
	char *zErrMsg = 0;
	if (sqlite3_exec(db, zSQL, NULL, 0, &zErrMsg) != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zSQL);
		return 0;
	}
	sqlite3_free(zSQL);
	return 1;
}

void quickSort(CArray<Mark>* arr, int low, int high) {//快速排序
	Mark temp = arr->data[low];
	int rlow=low, rhigh=high;
	while (low<high)
	{
		while (cal_Score(arr->data[high]) < cal_Score(temp)&&low<high)high--;
		arr->data[low] = arr->data[high];
		while (cal_Score(arr->data[low]) > cal_Score(temp) && low<high)low++;
		arr->data[high] = arr->data[low];
	}
	arr->data[low] = temp;
	quickSort(arr, rlow, low - 1);
	quickSort(arr, rhigh, high + 1);
}

bool csetRates(CArray<int> rates) {
	return dosql(sqlite3_mprintf("update Rate set weight='%d',lung_capacity='%d',up_body_or_situp='%d'",rates.data[0], rates.data[1], rates.data[2]));
}
CArray<int>* cgetRates() {
	int result;
	char * errmsg = NULL;
	char **dbResult; //查到的数据
	int nRow, nColumn;

	char *zSQL = sqlite3_mprintf("select * from Rate");//带条件的sql语句
	result = sqlite3_get_table(db, zSQL, &dbResult, &nRow, &nColumn, &errmsg);
	int index = nColumn;
	CArray<int>* rates=new CArray<int>;
	rates->data = new int[3];
	rates->length = 3;
	for(int i=0;i<3;i++)
	rates->data[i] = atoi(dbResult[index++]);
	return rates;
}