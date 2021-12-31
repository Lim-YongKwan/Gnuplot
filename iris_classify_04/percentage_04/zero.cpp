#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<math.h>

using namespace std;


double norm_seto[5][10];
double norm_veri[5][10];
double norm_virgin[5][10];

double iris_setosa[100][4];
double iris_virginica[100][4];
double iris_versicolor[100][4];

double avr_seto[5] = { 0, };
double ver_seto[5] = { 0, };
double avr_veri[5] = { 0, };
double ver_veri[5] = { 0, };
double avr_virgin[5] = { 0, };
double ver_virgin[5] = { 0, };

double assessment_sl[5] = { 0, };
double assessment_sw[5] = { 0, };
double assessment_pl[5] = { 0, };
double assessment_pw[5] = { 0, };

int num_min_pl = 0;
int num_min_pw = 0;
int num_min_sw = 0;
int num_min_sl = 0;

int min_pl = 0;
int min_pw = 0;
int min_sw = 0;
int min_sl = 0;

void setosa_input() {//iris_setosa를 배열에 넣는 함수

	fstream setosa("iris_setosa.txt");
	string sin;
	int num = 0;

	while (true) {

		string sin_2;
		sin_2 = sin;
		setosa >> sin;
		if (sin_2 == sin)
			break;


		char temp[50];//strtok는 string에서 바로 지원이 안되므로 선언
		strcpy_s(temp, sin.c_str());
		char* tok = strtok(temp, ",");//,를 기준으로 자름
		for (int i = 0; i < 4; i++) {
			//cout << tok << endl;
			iris_setosa[num][i] = atof(tok);

			//cout << "iris_setosa[" << num << "]" << "[" << i << "]" << " : " << iris_setosa[num][i] << endl;
			tok = strtok(NULL, ",");
		}
		num++;
	}
}

void virginicia_input() {//iris_virginica를 배열에 넣는 함수

	fstream virginicia("iris_virginica.txt");
	string sin;
	int num = 0;

	while (true) {

		string sin_2;
		sin_2 = sin;
		virginicia >> sin;
		if (sin_2 == sin)
			break;


		char temp[50];//strtok는 string에서 바로 지원이 안되므로 선언
		strcpy_s(temp, sin.c_str());
		char* tok = strtok(temp, ",");//,를 기준으로 자름
		for (int i = 0; i < 4; i++) {
			//cout << tok << endl;
			iris_virginica[num][i] = atof(tok);

			//cout << "iris_virginicia[" << num << "]" << "[" << i << "]" << " : " << iris_virginica[num][i] << endl;
			tok = strtok(NULL, ",");
		}
		num++;
	}
}

void versicolor_input() { //iris_versicolor를 배열에 넣는 함수

	fstream versicolor("iris_versicolor.txt");
	string sin;
	int num = 0;

	while (true) {

		string sin_2;
		sin_2 = sin;
		versicolor >> sin;
		if (sin_2 == sin)
			break;


		char temp[50];//strtok는 string에서 바로 지원이 안되므로 선언
		strcpy_s(temp, sin.c_str());
		char* tok = strtok(temp, ",");//,를 기준으로 자름
		for (int i = 0; i < 4; i++) {
			//cout << tok << endl;
			iris_versicolor[num][i] = atof(tok);

			//cout << "iris_versicolor[" << num << "]" << "[" << i << "]" << " : " << iris_versicolor[num][i] << endl;
			tok = strtok(NULL, ",");
		}
		num++;
	}

}


void train_sl(int p) {

	memset(avr_seto, 0, sizeof(avr_seto));
	memset(avr_veri, 0, sizeof(avr_veri));
	memset(avr_virgin, 0, sizeof(avr_virgin));
	memset(ver_seto, 0, sizeof(ver_seto));
	memset(ver_veri, 0, sizeof(ver_veri));
	memset(ver_virgin, 0, sizeof(ver_virgin));
	//평균 구하기
	for (int i = 0; i < 50; i++) {
		if (i / 10 == p)
			continue;
		avr_seto[p] += iris_setosa[i][0];
		avr_virgin[p] += iris_virginica[i][0];
		avr_veri[p] += iris_versicolor[i][0];
	}

	avr_seto[p] /= 40;
	avr_veri[p] /= 40;
	avr_virgin[p] /= 40;

	//분산 구하기
	for (int i = 0; i < 50; i++) {
		
		ver_seto[p] += pow(iris_setosa[i][0] - avr_seto[p],2);
		ver_veri[p] += pow(iris_versicolor[i][0] - avr_veri[p], 2);
		ver_virgin[p] += pow(iris_virginica[i][0] - avr_virgin[p], 2);
	}

	ver_seto[p] /= 40;
	ver_veri[p] /= 40;
	ver_virgin[p] /= 40;

	double max_seto = 0;
	double max_veri = 0;
	double max_virgin = 0;

	for (int i = 0; i < 10; i++) {

		norm_seto[p][i] = 1 / ver_seto[p] * exp(-pow((iris_setosa[p*10+i][0] - avr_seto[p]), 2) / (2 * pow(ver_seto[p], 2)));
		
		norm_veri[p][i] = 1 / ver_veri[p] * exp(-pow((iris_setosa[p*10+i][0] - avr_veri[p]), 2) / (2 * pow(ver_veri[p], 2)));

		norm_virgin[p][i] = 1 / ver_virgin[p] * exp(-pow((iris_setosa[p*10+i][0] - avr_virgin[p]), 2) / (2 * pow(ver_virgin[p], 2)));

		max_seto += norm_seto[p][i];
		max_veri += norm_veri[p][i];
		max_virgin += norm_virgin[p][i];
	}
	assessment_sl[p] = max_seto+max_veri+max_virgin;

}

void train_sw(int p) {

	memset(avr_seto, 0, sizeof(avr_seto));
	memset(avr_veri, 0, sizeof(avr_veri));
	memset(avr_virgin, 0, sizeof(avr_virgin));
	memset(ver_seto, 0, sizeof(ver_seto));
	memset(ver_veri, 0, sizeof(ver_veri));
	memset(ver_virgin, 0, sizeof(ver_virgin));

	//평균 구하기
	for (int i = 0; i < 50; i++) {
		if (i / 10 == p)
			continue;
		avr_seto[p] += iris_setosa[i][1];
		avr_virgin[p] += iris_virginica[i][1];
		avr_veri[p] += iris_versicolor[i][1];
	}

	avr_seto[p] /= 40;
	avr_veri[p] /= 40;
	avr_virgin[p] /= 40;

	//분산 구하기
	for (int i = 0; i < 50; i++) {

		ver_seto[p] += pow(iris_setosa[i][1] - avr_seto[p], 2);
		ver_veri[p] += pow(iris_versicolor[i][1] - avr_veri[p], 2);
		ver_virgin[p] += pow(iris_virginica[i][1] - avr_virgin[p], 2);
	}

	ver_seto[p] /= 40;
	ver_veri[p] /= 40;
	ver_virgin[p] /= 40;

	double max_seto = 0;
	double max_veri = 0;
	double max_virgin = 0;

	for (int i = 0; i < 10; i++) {

		norm_seto[p][i] = 1 / ver_seto[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_seto[p]), 2) / (2 * pow(ver_seto[p], 2)));

		norm_veri[p][i] = 1 / ver_veri[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_veri[p]), 2) / (2 * pow(ver_veri[p], 2)));

		norm_virgin[p][i] = 1 / ver_virgin[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_virgin[p]), 2) / (2 * pow(ver_virgin[p], 2)));

		max_seto += norm_seto[p][i];
		max_veri += norm_veri[p][i];
		max_virgin += norm_virgin[p][i];
	}


	assessment_sw[p] = max_seto + max_veri + max_virgin;
}

void train_pl(int p) {

	memset(avr_seto, 0, sizeof(avr_seto));
	memset(avr_veri, 0, sizeof(avr_veri));
	memset(avr_virgin, 0, sizeof(avr_virgin));
	memset(ver_seto, 0, sizeof(ver_seto));
	memset(ver_veri, 0, sizeof(ver_veri));
	memset(ver_virgin, 0, sizeof(ver_virgin));

	//평균 구하기
	for (int i = 0; i < 50; i++) {
		if (i / 10 == p)
			continue;
		avr_seto[p] += iris_setosa[i][2];
		avr_virgin[p] += iris_virginica[i][2];
		avr_veri[p] += iris_versicolor[i][2];
	}

	avr_seto[p] /= 40;
	avr_veri[p] /= 40;
	avr_virgin[p] /= 40;

	//분산 구하기
	for (int i = 0; i < 50; i++) {

		ver_seto[p] += pow(iris_setosa[i][2] - avr_seto[p], 2);
		ver_veri[p] += pow(iris_versicolor[i][2] - avr_veri[p], 2);
		ver_virgin[p] += pow(iris_virginica[i][2] - avr_virgin[p], 2);
	}

	ver_seto[p] /= 40;
	ver_veri[p] /= 40;
	ver_virgin[p] /= 40;

	double max_seto = 0;
	double max_veri = 0;
	double max_virgin = 0;

	for (int i = 0; i < 10; i++) {

		norm_seto[p][i] = 1 / ver_seto[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_seto[p]), 2) / (2 * pow(ver_seto[p], 2)));

		norm_veri[p][i] = 1 / ver_veri[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_veri[p]), 2) / (2 * pow(ver_veri[p], 2)));

		norm_virgin[p][i] = 1 / ver_virgin[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_virgin[p]), 2) / (2 * pow(ver_virgin[p], 2)));


		max_seto += norm_seto[p][i];
		max_veri += norm_veri[p][i];
		max_virgin += norm_virgin[p][i];
	}

	assessment_pl[p] = max_seto + max_veri + max_virgin;

}

void train_pw(int p) {

	memset(avr_seto, 0, sizeof(avr_seto));
	memset(avr_veri, 0, sizeof(avr_veri));
	memset(avr_virgin, 0, sizeof(avr_virgin));
	memset(ver_seto, 0, sizeof(ver_seto));
	memset(ver_veri, 0, sizeof(ver_veri));
	memset(ver_virgin, 0, sizeof(ver_virgin));

	//평균 구하기
	for (int i = 0; i < 50; i++) {
		if (i / 10 == p)
			continue;
		avr_seto[p] += iris_setosa[i][3];
		avr_virgin[p] += iris_virginica[i][3];
		avr_veri[p] += iris_versicolor[i][3];
	}

	avr_seto[p] /= 40;
	avr_veri[p] /= 40;
	avr_virgin[p] /= 40;

	//분산 구하기
	for (int i = 0; i < 50; i++) {

		ver_seto[p] += pow(iris_setosa[i][3] - avr_seto[p], 2);
		ver_veri[p] += pow(iris_versicolor[i][3] - avr_veri[p], 2);
		ver_virgin[p] += pow(iris_virginica[i][3] - avr_virgin[p], 2);
	}

	ver_seto[p] /= 40;
	ver_veri[p] /= 40;
	ver_virgin[p] /= 40;

	double max_seto = 0;
	double max_veri = 0;
	double max_virgin = 0;

	for (int i = 0; i < 10; i++) {

		norm_seto[p][i] = 1 / ver_seto[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_seto[p]), 2) / (2 * pow(ver_seto[p], 2)));

		norm_veri[p][i] = 1 / ver_veri[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_veri[p]), 2) / (2 * pow(ver_veri[p], 2)));

		norm_virgin[p][i] = 1 / ver_virgin[p] * exp(-pow((iris_setosa[p * 10 + i][0] - avr_virgin[p]), 2) / (2 * pow(ver_virgin[p], 2)));

		max_seto += norm_seto[p][i];
		max_veri += norm_veri[p][i];
		max_virgin += norm_virgin[p][i];
	}


	assessment_pw[p] = max_seto + max_veri + max_virgin;

}



void iris_test() {

	for (int i = 0; i < 5; i++) {
		if (i == 0)
			min_pl = assessment_pl[i];
		else
		{
			if (assessment_pl[i] > min_pl) {
				min_pl = assessment_pl[i];
				num_min_pl = i;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (i == 0)
			min_pw = assessment_pw[i];
		else
		{
			if (assessment_pw[i] > min_pw) {
				min_pw = assessment_pw[i];
				num_min_pw = i;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (i == 0)
			min_sl = assessment_sl[i];
		else
		{
			if (assessment_sl[i] > min_sl) {
				min_sl = assessment_sl[i];
				num_min_sl = i;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (i == 0)
			min_sw = assessment_sw[i];
		else
		{
			if (assessment_sw[i] > min_sw) {
				min_sw = assessment_sw[i];
				num_min_sw = i;
			}
		}
	}

	train_pl(num_min_pl);
	train_pw(num_min_pw);
	train_sl(num_min_sl);
	train_sw(num_min_sw);
	
}

void k_fold(int p) {

	while (p--) {
		train_sl(p);
	//	train_sw(p);
	//	train_pl(p);
	//	train_pw(p);
	}
	//iris_test();
}

double iris_train_seto(int num_sl, int num_sw, int num_pl, int num_pw) {
	
	double lov = 1 / ver_seto[num_min_sl] * exp(-pow((iris_setosa[num_sl][0] - avr_seto[num_min_sl]), 2) / (2 * pow(ver_seto[num_min_sl], 2)));
	lov += 1 / ver_seto[num_min_sw] * exp(-pow((iris_setosa[num_sw][0] - avr_seto[num_min_sw]), 2) / (2 * pow(ver_seto[num_min_sw], 2)));
	lov += 1 / ver_seto[num_min_pl] * exp(-pow((iris_setosa[num_pl][0] - avr_seto[num_min_pl]), 2) / (2 * pow(ver_seto[num_min_pl], 2)));
	lov += 1 / ver_seto[num_min_pw] * exp(-pow((iris_setosa[num_pw][0] - avr_seto[num_min_pw]), 2) / (2 * pow(ver_seto[num_min_pw], 2)));
	return lov;
}

double iris_train_veri(int num_sl, int num_sw, int num_pl, int num_pw) {

	double lov = 1 / ver_veri[num_min_sl] * exp(-pow((iris_setosa[num_sl][0] - avr_veri[num_min_sl]), 2) / (2 * pow(ver_veri[num_min_sl], 2)));
	lov += 1 / ver_veri[num_min_sw] * exp(-pow((iris_setosa[num_sw][0] - avr_veri[num_min_sw]), 2) / (2 * pow(ver_veri[num_min_sw], 2)));
	lov += 1 / ver_veri[num_min_pl] * exp(-pow((iris_setosa[num_pl][0] - avr_veri[num_min_pl]), 2) / (2 * pow(ver_veri[num_min_pl], 2)));
	lov += 1 / ver_veri[num_min_pw] * exp(-pow((iris_setosa[num_pw][0] - avr_veri[num_min_pw]), 2) / (2 * pow(ver_veri[num_min_pw], 2)));
	return lov;
}

double iris_train_virgin(int num_sl, int num_sw, int num_pl, int num_pw) {

	double lov = 1 / ver_virgin[num_min_sl] * exp(-pow((iris_setosa[num_sl][0] - avr_virgin[num_min_sl]), 2) / (2 * pow(ver_virgin[num_min_sl], 2)));
	lov += 1 / ver_virgin[num_min_sw] * exp(-pow((iris_setosa[num_sw][0] - avr_virgin[num_min_sw]), 2) / (2 * pow(ver_virgin[num_min_sw], 2)));
	lov += 1 / ver_virgin[num_min_pl] * exp(-pow((iris_setosa[num_pl][0] - avr_virgin[num_min_pl]), 2) / (2 * pow(ver_virgin[num_min_pl], 2)));
	lov += 1 / ver_virgin[num_min_pw] * exp(-pow((iris_setosa[num_pw][0] - avr_virgin[num_min_pw]), 2) / (2 * pow(ver_virgin[num_min_pw], 2)));
	return lov;
}

void bayesian(double sl, double sw, double pl, double pw) {

	double setosa = 0;
	double virgincia = 0;
	double versicolor = 0;

	int num_sl = int(sl * 10.0);
	int num_sw = int(sw * 10.0);
	int num_pl = int(pl * 10.0);
	int num_pw = int(pw * 10.0);

	setosa = iris_train_seto(num_sl, num_sw, num_pl, num_pw);

	virgincia = iris_train_virgin(num_sl, num_sw, num_pl, num_pw);

	versicolor = iris_train_veri(num_sl, num_sw, num_pl, num_pw);

	if (setosa > virgincia) {
		if (setosa > versicolor)
			cout << " 이 꽃은 setosa 일 확률이 가장 높습니다." << endl;
		else if (setosa = versicolor)
			cout << " 이 꽃은 setosa 이거나 versicolor 일 겁니다. " << endl;
		else
			cout << " 이 꽃은 versicolor 일 확률이 가장 높습니다. " << endl;
	}
	else if (virgincia > setosa) {
		if (virgincia > versicolor)
			cout << " 이 꽃은 virgincia일 확률이 가장 높습니다. " << endl;
		else if (virgincia = versicolor)
			cout << " 이 꽃은 virgincia 이거나 versicolor 일 겁니다. " << endl;
		else
			cout << " 이 꽃은 versicolor 일 확률이 가장 높습니다. " << endl;
	}
	else {
		if (virgincia > versicolor) {
			cout << " 이 꽃은 setosa이거나 virgincia일 겁니다. " << endl;
		}
		else if (versicolor > virgincia)
			cout << "이 꽃은 versicolor일 확률이 가장 높습니다. " << endl;
		else
			cout << " 이 꽃은 setosa, versicolor, virginicia일 확률이 같습니다. " << endl;
	}

}

void test(double sl, double sw, double pl,double pw) {
	bayesian(sl, sw, pl, pw);
}

int main() {

	double sepal_length, sepal_width, petal_length, petal_width;

	setosa_input();
	virginicia_input();
	versicolor_input();

	k_fold(5);

	cout << " 숫자 4개를 입력하세요 : " << endl;
	cin >> sepal_length >> sepal_width >> petal_length >> petal_width;

	test(sepal_length, sepal_width, petal_length, petal_width);

}