#include<iostream>
#include<fstream>
#include<string>
#include<random>

using namespace std;

int assessment_pl[5] = { 0, };
int assessment_pw[5] = { 0, };
int assessment_sl[5] = { 0, };
int assessment_sw[5] = { 0, };

double iris_setosa[100][4];
double iris_virginica[100][4];
double iris_versicolor[100][4];

int num_min_pl = 0;
int num_min_pw = 0;
int num_min_sw = 0;
int num_min_sl = 0;

int min_pl = 0;
int min_pw = 0;
int min_sw = 0;
int min_sl = 0;

struct pmfs {
	double seto=0;
	double virgin=0;
	double veri=0;
};

pmfs iris_sl[100];
pmfs iris_sw[100];
pmfs iris_pl[100];
pmfs iris_pw[100];


pmfs iris_train_sl[100];
pmfs iris_train_sw[100];
pmfs iris_train_pl[100];
pmfs iris_train_pw[100];


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

	memset(iris_train_sl, 0, sizeof(iris_train_sl));

	for (int i = 0; i < 50; i++) {
		if (i /10 == p)
			continue;
		int n = iris_setosa[i][0] * 10;
		iris_train_sl[n].seto += 1;

		n = iris_versicolor[i][0] * 10;
		iris_train_sl[n].veri += 1;

		n = iris_virginica[i][0] * 10;
		iris_train_sl[n].virgin += 1;
	}

	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = iris_setosa[i][0] * 10;

		if (iris_train_sl[n].seto > iris_train_sl[n].veri) {
			if (iris_train_sl[n].seto > iris_train_sl[n].virgin) {
				assessment_sl[p - 1]++;
			}
		}

	}

	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = iris_virginica[i][0] * 10;

		if (iris_train_sl[n].virgin > iris_train_sl[n].veri) {
			if (iris_train_sl[n].virgin > iris_train_sl[n].seto) {
				assessment_sl[p - 1]++;
			}
		}
	}
	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = iris_versicolor[i][0] * 10;

		if (iris_train_sl[n].veri > iris_train_sl[n].seto) {
			if (iris_train_sl[n].veri > iris_train_sl[n].virgin) {
				assessment_sl[p - 1]++;
			}
		}
	}
}
void train_sw(int p){


	memset(iris_train_sw, 0, sizeof(iris_train_sw));
	for (int i = 0; i < 50; i++) {
		if (i / 10 == p)
			continue;
		int n = iris_setosa[i][1] * 10;
		iris_train_sw[n].seto += 1;

		//cout << " i :" << i;
		//cout <<" "<< n<<"번째 IRIS : "<<iris_train_sw[n].seto << endl;


		n = iris_versicolor[i][1] * 10;
		iris_train_sw[n].veri += 1;

		n = iris_virginica[i][1] * 10;
		iris_train_sw[n].virgin += 1;
	}

	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = iris_setosa[i][1] * 10;

		if (iris_train_sw[n].seto > iris_train_sw[n].veri) {
			if (iris_train_sw[n].seto > iris_train_sw[n].virgin) {
				assessment_sw[p - 1]++;
			}
		}

	}

	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = iris_virginica[i][1] * 10;

		if (iris_train_sw[n].virgin > iris_train_sw[n].veri) {
			if (iris_train_sw[n].virgin > iris_train_sw[n].seto) {
				assessment_sw[p - 1]++;
			}
		}
	}
	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = iris_versicolor[i][1] * 10;

		if (iris_train_sw[n].veri > iris_train_sw[n].seto) {
			if (iris_train_sw[n].veri > iris_train_sw[n].virgin) {
				assessment_sw[p - 1]++;
			}
		}
	}
}


void train_pl(int p) {

	memset(iris_train_pl, 0, sizeof(iris_train_pl));

	for (int i = 0; i < 50; i++) {

		if (i / 10 == p)
			continue;
		int n = 0;
		n = iris_setosa[i][2] * 10;
		iris_train_pl[n].seto += 1;

		//cout << " i :" << i;
		//cout <<" "<< n<<"번째 IRIS : "<<iris_train_pl[n].seto << endl;

		n = iris_versicolor[i][2] * 10;
		iris_train_pl[n].veri += 1;

		n = iris_virginica[i][2] * 10;
		iris_train_pl[n].virgin += 1;

	}



	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = 0;
		n = iris_setosa[i][2] * 10;

		if (iris_train_pl[n].seto > iris_train_pl[n].veri) {
			if (iris_train_pl[n].seto > iris_train_pl[n].virgin) {
				assessment_pl[p]++;
			}
		}

	}

	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = 0;
		n = iris_setosa[i][2] * 10;

		if (iris_train_pl[n].virgin > iris_train_pl[n].veri) {
			if (iris_train_pl[n].virgin > iris_train_pl[n].seto) {
				assessment_pl[p]++;
			}
		}
	}
	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = 0;
		n = iris_setosa[i][2] * 10;
		if (iris_train_pl[n].veri > iris_train_pl[n].seto) {
			if (iris_train_pl[n].veri > iris_train_pl[n].virgin) {
				assessment_pl[p]++;
			}
		}
	}



}


void train_pw(int p) {

	memset(iris_train_pw, 0, sizeof(iris_train_pw));

	for (int i = 0; i < 50; i++) {

		if (i / 10 == p)
			continue;
		int n = 0;
		n = iris_setosa[i][3] * 10;
		iris_train_pw[n].seto += 1;

		//cout << " i :" << i;
		//cout <<" "<< n<<"번째 IRIS : "<<iris_train_pl[n].seto << endl;

		n = iris_versicolor[i][3] * 10;
		iris_train_pw[n].veri += 1;

		n = iris_virginica[i][3] * 10;
		iris_train_pw[n].virgin += 1;

	}



	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = 0;
		n = iris_setosa[i][3] * 10;

		if (iris_train_pw[n].seto > iris_train_pw[n].veri) {
			if (iris_train_pw[n].seto > iris_train_pw[n].virgin) {
				assessment_pw[p]++;
			}
		}

	}

	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = 0;
		n = iris_setosa[i][3] * 10;

		if (iris_train_pw[n].virgin > iris_train_pw[n].veri) {
			if (iris_train_pw[n].virgin > iris_train_pw[n].seto) {
				assessment_pw[p]++;
			}
		}
	}
	for (int i = p * 10 - 1; i >= (p - 1) * 10; i--) {
		int n = 0;
		n = iris_setosa[i][3] * 10;
		if (iris_train_pw[n].veri > iris_train_pw[n].seto) {
			if (iris_train_pw[n].veri > iris_train_pw[n].virgin) {
				assessment_pw[p]++;
			}
		}
	}



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

void k_fold(int i){
	

	while (i--) {
		train_pl(i);
		train_pw(i);
		train_sl(i);
		train_sw(i);
	}

	iris_test();
}

void bayesian(double sl,double sw,double pl,double pw) {
	double setosa = 0;
	double virgincia = 0;
	double versicolor = 0;

	int num_sl = int(sl * 10.0);
	int num_sw = int(sw * 10.0);
	int num_pl = int(pl * 10.0);
	int num_pw = int(pw * 10.0);

	//P(X|B) = P(B|X) *P(X)/P(B)
	//P(setosa|SL) = P(SL|setosa) *P(setosa)/P(SL)

	//cout << "num_sw : " << num_sw << endl;
	//cout << "iris_train_sw[num_sw].seto : " << iris_train_sw[num_sw].seto << endl;
	//cout << "iris_train_sw[num_sw].veri : " << iris_train_sw[num_sw].veri << endl;
	//cout <<"iris_train_sw[num_sw].virgin : "<< iris_train_sw[num_sw].virgin << endl;

	//cout << "example : "<< iris_train_sw[num_sw].seto / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin)) << endl;

	
	setosa = iris_train_sl[num_sl].seto / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin))
		+ iris_train_sw[num_sw].seto / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin))
		+ iris_train_pl[num_pl].seto / (3.0) * (iris_train_pl[num_pl].seto + iris_train_pl[num_pl].veri + iris_train_pl[num_pl].virgin)
		+ iris_train_pw[num_pw].seto / (3.0) * (iris_train_pw[num_pw].seto + iris_train_pw[num_pw].veri + iris_train_pw[num_pw].virgin);

	virgincia = iris_train_sl[num_sl].virgin / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin))
		+ iris_train_sw[num_sw].virgin / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin))
		+ iris_train_pl[num_pl].virgin / (3.0) * (iris_train_pl[num_pl].seto + iris_train_pl[num_pl].veri + iris_train_pl[num_pl].virgin)
		+ iris_train_pw[num_pw].virgin / (3.0) * (iris_train_pw[num_pw].seto + iris_train_pw[num_pw].veri + iris_train_pw[num_pw].virgin);

	versicolor = iris_train_sl[num_sl].veri / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin))
		+ iris_train_sw[num_sw].veri / (3.0 * (iris_train_sw[num_sw].seto + iris_train_sw[num_sw].veri + iris_train_sw[num_sw].virgin))
		+ iris_train_pl[num_pl].veri / (3.0) * (iris_train_pl[num_pl].seto + iris_train_pl[num_pl].veri + iris_train_pl[num_pl].virgin)
		+ iris_train_pw[num_pw].veri / (3.0) * (iris_train_pw[num_pw].seto + iris_train_pw[num_pw].veri + iris_train_pw[num_pw].virgin);

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

void test(double x,double y,double z,double k) {
	bayesian(x,y,z,k);
}


int main()
{

	double sepal_length, sepal_width, petal_length, petal_width;

	setosa_input();
	virginicia_input();
	versicolor_input();


	k_fold(5);

	
	cout << " 숫자 4개를 입력하세요 : " << endl;
	cin >> sepal_length >> sepal_width >> petal_length >> petal_width;

	test(sepal_length,sepal_width,petal_length,petal_width);

}