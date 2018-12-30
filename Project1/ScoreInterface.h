#pragma once

using namespace System;
using namespace System::Collections::Generic;
#include"ScoreJudger.h"

public ref class Score {//����.net����µ�һ����
	public:
		int id;
		String^ name;
		bool sex;//0�У�1Ů
		float weight;
		int sc_weight;
		int lung_capacity;
		int sc_lung_capacity;
		int up_body_situp;
		int sc_up_body_situp;
		int total;
		Score();
		Score(Mark mark);
};

public ref class ScoreInterface {//������C#�����Ľӿ���
	public:
		ScoreInterface();
		bool insert(Score^ sc);
		List<Score^>^ getMark();
		List<Score^>^ getSorted(int type);
		Score^ getMark(String^ name);
		bool update(Score^ sc);
		bool remove(Score^ sc);
		bool setAll(List<Score^>^ sc);
		bool setRates(List<int>^ rates);
		List<int>^ getRates();
};