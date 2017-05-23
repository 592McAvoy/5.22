#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<fstream>

using namespace std;

vector<vector<char>> MG;
vector<vector<char>> WAY;
int best = 99;
int hh;
int ll;

struct Point{
public:
	int h;
	int l;
};

void read(string fn);
void find(Point begin,vector<vector<char>>& mg,int n);
bool dire(Point& begin, char dd, vector<vector<char>>& mg);

const char north = '0';
const char east = '1';
const char south = '2';
const char west = '3';

Point END{0,0};


int main() {
	cout << "Enter the filename:";
	string fn;
	getline(cin,fn);
	read(fn);
	Point begin{ 0,0 };
	MG[0][0] = '2';
	find(begin, MG,0);
	for (int i = 0; i < WAY.size(); i++) {
		for (int j = 0; j < WAY[i].size(); j++)
			cout << WAY[i][j];
		cout << endl;
	}
	cin.get();
	cin.get();
	
}

void read(string fn) {
	ifstream ff;
	ff.open(fn);
	stringstream ss;
	string temp;
	getline(ff, temp);
	ss << temp;
	ss >> hh;
	ss >> ll;
	END.h = hh - 1;
	END.l = ll - 1;
	ss.str("");
	vector<char> tt;
	int i = 0;
	while (i < ll) {
		tt.push_back('0');
		i++;
	}
	i = 0;
	while (i < hh) {
		MG.push_back(tt);
		i++;
	}

	int n = 0;
	while (n<hh) {
		getline(ff,temp);
		ss.clear();//多次转换之前要调用clear，不然可能会报错
		ss << temp;
		char ch;
		for (int i = 0; i < ll; i++) {
			ss >> ch;			
			if (ch == ' ')
				ss >> ch;
			MG[n][i] = ch;
		}
		ss.str("");
		n++;
	}
	return;
}

bool dire(Point& begin, char dd, vector<vector<char>>& mg) {
	switch (dd) {
	case north: {
		int t = begin.h - 1;
		if (t >= 0&&t<hh) {
			if (mg[t][begin.l] == '0') {
				begin.h = t;
				return true;
			}				
		}
		return false;
	}
	case east: {
		int t = begin.l+1;
		if (t >= 0 && t<ll) {
			if (mg[begin.h][t] == '0') {
				begin.l = t;
				return true;
			}
		}
		return false;
	}
	case south: {
		int t = begin.h + 1;
		if (t >= 0 && t<hh) {
			if (mg[t][begin.l] == '0') {
				begin.h = t;
				return true;
			}
		}
		return false;
	}
	case west: {
		int t = begin.l - 1;
		if (t >= 0 && t<ll) {
			if (mg[begin.h][t] == '0') {
				begin.l = t;
				return true;
			}
		}
		return false;
	}
	}
}
void find(Point begin, vector<vector<char>>& mg,int n) {	
	if (begin.h == END.h&&begin.l == END.l) {
		if (n < best)
			best=n;
			WAY = mg;
		return;
	}
	for (char i = north; i <= west; i++) {
		Point temp = begin;
		vector<vector<char>> mm = mg;
		if (dire(temp, i, mm)) {
			mm[temp.h][temp.l] = '2';
			find(temp, mm, n + 1);
		}
	}
	return;
}
