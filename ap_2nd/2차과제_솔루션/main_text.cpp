#include "Puzzle.h"

#include <iostream>
#include <vector>
#include <string>

//만들어진 배열
std::vector<std::string> predefined_puzzles = {
	"!#!&%*&@&!@&!!@#!@$$**%!&!&&!##&#*@$&@$%%$$*&*@$##$#@$%@#$&#%$@#",
	"#!%%@%!&@*%!&@&!#*$$%%%&#*$#@$@!$%$@%@&!%$&%&@*%*$&&*&#!$$&*$#*!",
	"*@&*@#%%&%%&!$!*%#%*!*##*$$###*$$!#&&@*$$@#&#$&$$#!!!**@##@@@!!!",
	"$#@!%@$#$&$&!!*@@!$$@$!&*@**&$&@$!#*@&*@&###!@@%&@&!%&&%##$#@@&$",
};

//프롬프트
void promft_input_error() {
	cout << "잘못된 입력입니다. 다시 입력하세요 : ";
}
void promft_game_title() {
	cout << "<< BEJEWELED >>" << "\n";
}
void promft_game_menu() {
	cout << "\n"
		 << "[1] 랜덤 퍼즐" << "\n"
		 << "[2] 정해진 퍼즐" << "\n"
		 << "[3] 등수 보기" << "\n"
		 << "[4] 종료" << "\n"
		 << ">> 메뉴를 선택하세요 (1~4) : ";
}
void promft_game_info() {
	cout << "\n***\n두 위치 모두 (0, 0)일 경우 게임이 종료됩니다\n***\n";
}
void promft_menu_error() {
	cout << "없는 메뉴입니다 다시 선택하세요 : ";
}
void promft_psize() {
	cout << "퍼즐의 크기를 입력하세요 3<=크기<=20 인 (행, 열) : ";
}
void promft_psize_error() {
	cout << "잘못된 크기입니다 다시 입력하세요 : ";
}
void promft_choose_pre() {
	cout << "몇 번 배열로 시작하겠습니까? (0~3) : ";
}
void promft_choose_error() {
	cout << "없는 번호입니다 다시 선택하세요 : ";
}
void promft_choose_gem_1() {
	cout << "어느 위치에 있는 보석을 바꾸겠습니까? (행, 열) : ";
}
void promft_choose_gem_2() {
	cout << "어느 위치에 있는 보석과 바꾸겠습니까? (행, 열) : ";
}
void promft_choose_gem_error() {
	cout << "잘못된 위치 입력입니다 다시 입력하세요 : ";
}
void promft_goodbye() {
	cout << "\n감사합니다\n2020203090 한용옥 제작\n";
}
void promft_score(int n) {
	cout << "Score : " << n << '\n';
}
void promft_combo(int n) {
	if (n > 1) {
		cout << n << " COMBO";
		for (int i = 1; i < n; i += 1) {
			cout << "!";
		}
		cout << '\n';
	}
}
void promft_ask_name() {
	cout << "점수를 등록합니다 이름을 입력하세요 : ";
}
void promft_check_score(int score) {
	cout << "\n당신의 점수는 " << score << "점 입니다" << '\n';
}
void promft_check_rank(int rank) {
	cout << "당신은 " << rank << "등 입니다" << '\n';
}

//크기 상수
const int presize = 8;
const int rand_down = 3;
const int rand_up = 20;

//입력부
int input() {
	int result;
	while (!(cin >> result)) {
		promft_input_error();
		cin.clear();
		cin.ignore(INT_MAX,'\n');
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return result;
}
std::pair<int, int> loc_input() {
	int a, b;
	while (!(cin >> a >>b)) {
		promft_input_error();
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return make_pair(a, b);
}
string str_input() {
	string result;
	while (!(cin >> result)) {
		promft_input_error();
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return result;
}

//점수 벡터, 관리부
vector<std::pair<int, string>> score_board;
int what_rank(const std::pair<int, string>& x, const vector<std::pair<int, string>>& s) {
	for (int i = 0; i < s.size(); i += 1) {
		if (x.first == s[i].first && x.second == s[i].second) {
			return s.size() - i;
		}
	}
}
void game_score(int score) {
	promft_check_score(score);
	promft_ask_name();
	string name = str_input();
	score_board.push_back(make_pair(score, name));
	sort(score_board);
	promft_check_rank(what_rank(make_pair(score, name), score_board));
}

//퍼즐 표시
void print_puzzle(const Puzzle& p) {
	cout << "\n";

	cout << "    ";
	for (int j = 0; j < p.getNumColumns(); j += 1) {
		cout << j << ((j >= 9) ? "" : " ");
	}
	cout << '\n';

	cout << "  +";
	for (int j = 0; j < p.getNumColumns(); j += 1) {
		cout << "--";
	}
	cout << '\n';

	for (int i = 0; i < p.getNumRows(); i += 1) {
		cout << i << ((i >= 10) ? "| " : " | ");
		for (int j = 0; j < p.getNumColumns(); j += 1) {
			std::pair<int, int> loc = make_pair(i, j);
			cout << p.getJewelLetter(p.getJewel(loc)) << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

//보석 바꾸기
bool switchgem(Puzzle& p) {
	while (true) {
		promft_choose_gem_1();
		std::pair<int, int> prev_loc = loc_input();
		promft_choose_gem_2();
		std::pair<int, int> next_loc = loc_input();
		if (prev_loc == make_pair(0, 0) && next_loc == make_pair(0, 0)) return false;
		if (p.swapJewels(prev_loc, next_loc)) return true;
		else promft_choose_gem_error();
	}
}

//게임 루프
void game_main(Puzzle& p) {
	promft_game_info();
	while (true) {
		do{
			print_puzzle(p);
			promft_combo(p.getcombo());
		} while (p.update() == true);
		p.update();
		
		promft_score(p.getscore());
		if (!switchgem(p)) {
			game_score(p.getscore());
			return;
		}
	}
}

//랜덤 시작
void game_random() {
	promft_psize();
	std::pair<int, int> psize = loc_input();
	while (!((rand_down <= psize.first && psize.first <= rand_up)
		   &&(rand_down <= psize.second && psize.second <= rand_up))){
		promft_psize_error();
		psize = loc_input();
	}

	Puzzle p{ psize.first, psize.second };
	p.randomize();
	game_main(p);
}

//만들어진거로시작
void game_pre() {
	promft_choose_pre();
	int temp = input();
	while (!(0 <= temp && temp <= 3)) {
		promft_choose_error();
		temp = input();
	}

	Puzzle p{ presize,presize };
	p.initialize(predefined_puzzles[temp]);
	game_main(p);
}

//등수표시
void print_rank() {
	cout << "\n***** 퍼즐게임 등수 *****\n";
	cout << "플레이어 수 : " << score_board.size() << "명" << '\n';
	cout << "이름   :   점수" << '\n';
	for (int a = score_board.size() - 1; a >= 0; a -= 1) {
		cout << "[" << score_board.size() - a << "등]   ";
		cout << score_board[a].second << "  :  " << score_board[a].first << '\n';
	}
}

//게임 메뉴
void game_menu() {
	while (true) {
		promft_game_menu();
		int temp = input();
		while (!(1 <= temp && temp <= 4)) {
			promft_menu_error();
			temp = input();
		}
		switch (temp) {
		case 1:
			game_random();
			break;
		case 2:
			game_pre();
			break;
		case 3:
			print_rank();
			break;
		case 4:
			return;
		}
	}
}

int main()
try {
	promft_game_title();
	game_menu();

	promft_goodbye();
	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << e.what();
	return 1;
}
catch (...) {
	cerr << "terrible error";
	return 2;
}