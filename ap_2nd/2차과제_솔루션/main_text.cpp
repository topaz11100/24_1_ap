#include "Puzzle.h"

#include <iostream>
#include <vector>
#include <string>

//������� �迭
std::vector<std::string> predefined_puzzles = {
	"!#!&%*&@&!@&!!@#!@$$**%!&!&&!##&#*@$&@$%%$$*&*@$##$#@$%@#$&#%$@#",
	"#!%%@%!&@*%!&@&!#*$$%%%&#*$#@$@!$%$@%@&!%$&%&@*%*$&&*&#!$$&*$#*!",
	"*@&*@#%%&%%&!$!*%#%*!*##*$$###*$$!#&&@*$$@#&#$&$$#!!!**@##@@@!!!",
	"$#@!%@$#$&$&!!*@@!$$@$!&*@**&$&@$!#*@&*@&###!@@%&@&!%&&%##$#@@&$",
};

//������Ʈ
void promft_input_error() {
	cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ��� : ";
}
void promft_game_title() {
	cout << "<< BEJEWELED >>" << "\n";
}
void promft_game_menu() {
	cout << "\n"
		 << "[1] ���� ����" << "\n"
		 << "[2] ������ ����" << "\n"
		 << "[3] ��� ����" << "\n"
		 << "[4] ����" << "\n"
		 << ">> �޴��� �����ϼ��� (1~4) : ";
}
void promft_game_info() {
	cout << "\n***\n�� ��ġ ��� (0, 0)�� ��� ������ ����˴ϴ�\n***\n";
}
void promft_menu_error() {
	cout << "���� �޴��Դϴ� �ٽ� �����ϼ��� : ";
}
void promft_psize() {
	cout << "������ ũ�⸦ �Է��ϼ��� 3<=ũ��<=20 �� (��, ��) : ";
}
void promft_psize_error() {
	cout << "�߸��� ũ���Դϴ� �ٽ� �Է��ϼ��� : ";
}
void promft_choose_pre() {
	cout << "�� �� �迭�� �����ϰڽ��ϱ�? (0~3) : ";
}
void promft_choose_error() {
	cout << "���� ��ȣ�Դϴ� �ٽ� �����ϼ��� : ";
}
void promft_choose_gem_1() {
	cout << "��� ��ġ�� �ִ� ������ �ٲٰڽ��ϱ�? (��, ��) : ";
}
void promft_choose_gem_2() {
	cout << "��� ��ġ�� �ִ� ������ �ٲٰڽ��ϱ�? (��, ��) : ";
}
void promft_choose_gem_error() {
	cout << "�߸��� ��ġ �Է��Դϴ� �ٽ� �Է��ϼ��� : ";
}
void promft_goodbye() {
	cout << "\n�����մϴ�\n2020203090 �ѿ�� ����\n";
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
	cout << "������ ����մϴ� �̸��� �Է��ϼ��� : ";
}
void promft_check_score(int score) {
	cout << "\n����� ������ " << score << "�� �Դϴ�" << '\n';
}
void promft_check_rank(int rank) {
	cout << "����� " << rank << "�� �Դϴ�" << '\n';
}

//ũ�� ���
const int presize = 8;
const int rand_down = 3;
const int rand_up = 20;

//�Էº�
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

//���� ����, ������
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

//���� ǥ��
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

//���� �ٲٱ�
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

//���� ����
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

//���� ����
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

//��������ŷν���
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

//���ǥ��
void print_rank() {
	cout << "\n***** ������� ��� *****\n";
	cout << "�÷��̾� �� : " << score_board.size() << "��" << '\n';
	cout << "�̸�   :   ����" << '\n';
	for (int a = score_board.size() - 1; a >= 0; a -= 1) {
		cout << "[" << score_board.size() - a << "��]   ";
		cout << score_board[a].second << "  :  " << score_board[a].first << '\n';
	}
}

//���� �޴�
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