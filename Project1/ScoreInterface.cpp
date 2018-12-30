#include<msclr\marshal_cppstd.h>
#include"ScoreInterface.h"

using namespace std;
using namespace msclr::interop;

String^ ToCsString(char* str) {//c�ַ���תC#�ַ���
	return gcnew String(str);
}

char* ToCString(String^ str) {//C#�ַ���תc�ַ���
	return const_cast<char*>((new string(marshal_as<string>(str->ToString())))->c_str());
}
Score::Score() {

}
Score::Score(Mark mark) {//���캯��
	id=mark.id;
	name=ToCsString(mark.name);
	sex= mark.sex;//0�У�1Ů
	weight= mark.weight;
	lung_capacity= mark.lung_capacity;
	total= 0;
	CArray<int>* rates = cgetRates();
	if (mark.sex) {
		up_body_situp = mark.situp;
		//���ط���
		if (mark.weight >= 17.2&&mark.weight <= 23.9)total += (sc_weight=100 * rates->data[0] / 100);
		else if ((mark.weight >= 0 && mark.weight <= 17.1) || (mark.weight >= 24 && mark.weight <= 27.9))total += (sc_weight = 80 * rates->data[0] / 100);
		else if (mark.weight >= 28)total += (sc_weight = 60 * rates->data[0] / 100);
		//�λ�������
		if (mark.lung_capacity >= 2051 && mark.lung_capacity <= 3000)total += (sc_lung_capacity=60 * rates->data[1] / 100);
		else if (mark.lung_capacity >= 3001 && mark.lung_capacity <= 3400)total += (sc_lung_capacity = 80 * rates->data[1] / 100);
		else if (mark.lung_capacity > 3400)total += (sc_lung_capacity = 100 * rates->data[1] / 100);
		else if (mark.lung_capacity >= 0 && mark.lung_capacity <= 2050)total += (sc_lung_capacity = 30 * rates->data[1] / 100);
		//������������
		if (mark.situp >= 25 && mark.situp <= 52)total += (sc_up_body_situp=60 * rates->data[2] / 100);
		else if (mark.situp >= 53 && mark.situp <= 56)total += (sc_up_body_situp = 80 * rates->data[2] / 100);
		else if (mark.situp > 56)total += (sc_up_body_situp = 100 * rates->data[2] / 100);
		else if (mark.situp >= 0 && mark.situp <= 16)total += (sc_up_body_situp = 30 * rates->data[2] / 100);

	}
	else
	{
		up_body_situp = mark.up_body;
		//���ط���
		if (mark.weight >= 17.9&&mark.weight <= 23.9)total += (sc_weight = 100 * rates->data[0] / 100);
		else if ((mark.weight >= 0 && mark.weight <= 17.8) || (mark.weight >= 24 && mark.weight <= 27.9))total += (sc_weight = 80 * rates->data[0] / 100);
		else if (mark.weight >= 28)total += (sc_weight = 60 * rates->data[0] / 100);
		//�λ�������
		if (mark.lung_capacity >= 3101 && mark.lung_capacity <= 4180)total += (sc_lung_capacity = 60 * rates->data[1] / 100);
		else if (mark.lung_capacity >= 4181 && mark.lung_capacity <= 4800)total += (sc_lung_capacity = 80 * rates->data[1] / 100);
		else if (mark.lung_capacity > 4800)total += (sc_lung_capacity = 100 * rates->data[1] / 100);
		else if (mark.lung_capacity >= 0 && mark.lung_capacity <= 3100)total += (sc_lung_capacity = 30 * rates->data[1] / 100);
		//�������Ϸ���
		if (mark.up_body >= 10 && mark.up_body <= 15)total += (sc_up_body_situp = 60 * rates->data[2] / 100);
		else if (mark.up_body >= 16 && mark.up_body <= 19)total += (sc_up_body_situp = 80 * rates->data[2] / 100);
		else if (mark.up_body > 19)total += (sc_up_body_situp = 100 * rates->data[2] / 100);
		else if (mark.up_body >= 0 && mark.up_body <= 9)total += (sc_up_body_situp = 30 * rates->data[2] / 100);

	}
}

ScoreInterface::ScoreInterface() {
	initialization();//��ʼ����������
}
bool ScoreInterface::insert(Score^ sc) {//����һ��Score��¼��Score^Ϊ.net����µ�һ����ָ��
	return c_insert({sc->id,ToCString(sc->name),sc->sex,sc->weight,sc->lung_capacity ,sc->sex?NULL:sc->up_body_situp,!sc->sex ? NULL : sc->up_body_situp });
}
List<Score^>^ ScoreInterface::getMark() {//��ȡ�������ݣ�����һ��������
	List<Score^>^ list = gcnew List<Score^>(10000);//�½�һ��List����
	CArray<Mark>* marks = c_getMark();
	for (int i = 0; i < marks->length; i++) {//��CArray�е����ݿ�����list��
		list->Add(gcnew Score(marks->data[i]));
	}
	return list;
}
List<Score^>^ ScoreInterface::getSorted(int type) {//��ȡ�����������
	List<Score^>^ list = gcnew List<Score^>(10000);
	CArray<Mark>* marks = c_getSorted(0);
	for (int i = 0; i < marks->length; i++) {
		list->Add(gcnew Score(marks->data[i]));
	}
	return list;
}
Score^ ScoreInterface::getMark(String^ name) {//�������ֻ�ȡ����
	return gcnew Score(*c_getMark(ToCString(name)));
}
bool ScoreInterface::update(Score^ sc) {//��������
	return c_update({ sc->id,ToCString(sc->name),sc->sex,sc->weight,sc->lung_capacity ,sc->sex ? NULL : sc->up_body_situp,!sc->sex ? NULL : sc->up_body_situp });
}
bool ScoreInterface::setAll(List<Score^>^ sc_list) {//����������������
	CArray<Mark>* marks = newMarkArray(sc_list->Count);
	int i = 0;
	for (auto en = sc_list->GetEnumerator(); en.MoveNext();i++)//ʹ�õ�������������List��autoΪ�Զ�����
	{
		Score^ sc = en.Current;
		marks->data[i] = { sc->id,ToCString(sc->name),sc->sex,sc->weight,sc->lung_capacity ,sc->sex ? NULL : sc->up_body_situp,!sc->sex ? NULL : sc->up_body_situp };
	}
	return c_setAll(*marks);
}
bool ScoreInterface::remove(Score^ sc) {//ɾ��һ������
	return c_remove({ sc->id,ToCString(sc->name),sc->sex,sc->weight,sc->lung_capacity ,sc->sex ? NULL : sc->up_body_situp,!sc->sex ? NULL : sc->up_body_situp });
}
bool ScoreInterface::setRates(List<int>^ rates) {
	CArray<int> rate;
	rate.data = new int[3];
	rate.length = 3;
	int i = 0;
	for (auto en = rates->GetEnumerator(); en.MoveNext(); i++)//ʹ�õ�������������List��autoΪ�Զ�����
	{
		rate.data[i] = en.Current;
	}
	return csetRates(rate);
}
List<int>^ ScoreInterface::getRates() {
	CArray<int>* arr = cgetRates();
	List<int>^ list = gcnew List<int>(10);
	for (int i = 0; i < 3; i++)list->Add(arr->data[i]);
	return list;
}