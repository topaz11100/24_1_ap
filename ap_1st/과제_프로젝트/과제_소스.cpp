#include "std_lib_facilities.h"

//������Ʈ ���� -------------------------------
void promft_hello() {
	cout << "-----\n�ϳ���ž ���� ���� ���� ȯ���մϴ�.\n-----\n";
}
void promft_mode_select() {
	cout << "\n������ Ǯ�ڽ��ϱ�?  (H)\n�������� �ϳ���ž�� ���� ���ڽ��ϱ�?  (A)\n�����ϰڽ��ϱ�?  (Q)\n>>> ";
}
void promft_mode_selected(string mode) {
	if (mode == "H" || mode == "h") {//���� Ǯ��
		cout << "\n-----\n���� Ǯ�� ����\n-----\n\n";
	}
	else if (mode == "A" || mode == "a") {//���� ����
		cout << "\n-----\n���� ���� ����\n-----\n\n";
	}
	else if (mode == "Q" || mode == "q") {//����
		cout << "\n-----\n�����ϼ̽��ϴ�!\n2020203090 �ѿ�� ����\n-----\n\n";
	}
}
void promft_disk() {
	cout << "������ ������ ������ �ּ���. (1�� ~ 9��) : ";
}
void promft_rod() {
	cout << "����� ������ ������ �ּ���. (3�� ~ 6��) : ";
}
void promft_position(int len) {
	cout << len << "���� ��� �� 1������ �����մϴ�\n�� �� ������� �ű�ڽ��ϱ�? (2�� ~ " << len << "��) : ";
}
void promft_input_fail() {
	cout << "Ʋ�� �Է� // ��Ȯ�� ���� �Է��ϼ���.  :  ";
}
void promft_move_success() {
	cout << "=> �̵� ����!\n";
}
void promft_move_fail(string fail_message) {
	cout << "=> �̵� ����! // "<< fail_message <<" // �ٽ� �Է��ϼ���.  :  ";
}
void promft_try(int tried, int len) {
	cout << "�õ� Ƚ�� : " << tried << "��\n"
		 << "������ ��� �ű�ڽ��ϱ�? (" << 1 << "~" << len << "�� -> " << 1 << "~" << len << "��) :  ";
}
void promft_complete(int tried) {
	cout << "�����մϴ�! " << tried << "�� ���� �����߽��ϴ�!\n\n"
		 << "�ٽ� �ϰڽ��ϱ�?  ( Y / N ) : ";
}
//--------------------------------------------

//���ڿ� ���� �Է�, �Է¿���ó�� ---------------------------------------
//cin �ʱ�ȭ cin�� �����ִ� �Է��� ����� ������ �� ������ ���ε� �ʱ�ȭ�Ѵ�.
void clear_cin() {
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}
// ���ڰ� �迭�� �ִ��� : �˻�⿡�� �����˻縦 �Ҷ� ����
bool isStrinarr(string str, vector<string>& filter_list) {
	for (string x : filter_list) {
		if (str == x) {
			return true;
		}
	}
	return false;
}
// �����Է� ���ܰ˻��
string str_filter(vector<string> filter_list) {
	string answer;
	while (!(cin >> answer) || !isStrinarr(answer, filter_list)) {
		promft_input_fail();
		clear_cin();
	}
	//�Է��� ������ ���� ���� �Է¿� ���� ��ġ�°� ����
	clear_cin();

	return answer;
}
//--------------------------------------------------------

//Ÿ�� �ʱ�ȭ ����--------------------------------------------
//�ʱ� ���� ���� : ��ũ, ���� ����, ��� �������� ���� ������ ��ȯ
int init_set(string mode, int len = 0) {

	int temp = 0;
	int up = 0, down = 0;
	//��忡���� ������, ������Ʈ ����
	if (mode == "disk") {
		promft_disk();
		up = 9, down = 1;
	}
	else if (mode == "rod") {
		promft_rod();
		up = 6, down = 3;
	}
	else if (mode == "position") {
		promft_position(len);
		up = len, down = 2;
	}
	//���� �˻�
	while (!(cin >> temp) || !(down <= temp && temp <= up)) {
		promft_input_fail();
		clear_cin();
	}
	//�Է��� ������ ���� ���� �Է¿� ���� ��ġ�°� ����
	clear_cin();

	return temp;
}
//�ʱ� ���� ����(Ÿ��) ��ȯ
vector<vector<int>> init_tower(int disk, int rod) {
	vector<vector<int>> result = {};
	//��� ����
	for (int i = 0; i < rod; i += 1) {
		result.push_back({});
	}
	//0���� ���� ��, ���� ä���ֱ�
	for (int i = disk; i > 0; i -= 1) {
		result[0].push_back(i);
	}
	return result;
}
//----------------------------------------------------------

//Ÿ�� ���� ����--------------------------------------------
//�ϳ���ž ���η� ǥ��
void show_tower(int position, vector<vector<int>>& tower) {
	cout << '\n';
	//���� �� ������ ��Ұ��� ����
	int max = 0;
	for (vector<int> x : tower) {
		if (max < x.size()) {
			max = x.size();
		}
	}
	//���� ���������� ���� ���Ұ� ������ ���������� ���� ���
	for (int i = max; i > 0; i -= 1) {
		for (int j = 0; j < tower.size(); j += 1) {
			if (i <= tower[j].size()) {
				cout << " " << tower[j][i - 1] << " ";
			}
			else {
				cout << "   ";
			}
		}
		cout << '\n';
	}
	//��� ��ȣ ǥ��, ��ǥ ����� Ư�� ǥ��
	for (int i = 0; i < tower.size(); i += 1) {
		if (i + 1 == position) {
			cout << "[" << i + 1 << "]";
		}
		else {
			cout << "-" << i + 1 << "-";
		}
	}
	cout << "\n\n";
}
//�ϳ��� ž ��Ģ�� �´� �Է����� �˻�
bool isAllowinput(int from, int to, vector<vector<int>>& tower) {
	//������ �ȸ´� �Է�
	if (from < 1 || from > tower.size() || to < 1 || to > tower.size()) {
		promft_move_fail("���� ��ȣ");
		return false;
	}
	//���� ���� �ű�
	if (from == to) {
		promft_move_fail("���� ��ġ�� �ű�");
		return false;
	}
	//����ִ� ������ ������ ��
	if (tower[from - 1].size() == 0) {
		promft_move_fail("����ִ� ������ ��");
		return false;
	}
	//���� ���� ������� true������ �˻��ϴ� ������ �� ���ǿ��� �迭�� �����ϱ� ����
	if (tower[to - 1].size() == 0) {
		return true;
	}
	//���� ���� �ִ� ��ũ�� �������� ��ũ���� ���� ���
	else if (tower[from - 1][tower[from - 1].size() - 1] > tower[to - 1][tower[to - 1].size() - 1]) {
		promft_move_fail("�ϳ���ž ��Ģ�� ��߳�\n(ū ������ �ؿ� �־�� ��!)");
		return false;
	}
	//�ȵǴ°� ������ �� �Ÿ�
	return true;
}
//��ũ �ű��
void move_disk(int from, int to, vector<vector<int>>& tower) {
	//�� ���� ����, ������ ����, �ű�
	int temp = tower[from - 1][tower[from - 1].size() - 1];
	tower[from - 1].pop_back();
	tower[to - 1].push_back(temp);
}
//����˻�
bool isComplete(int disk, vector<int>& tower) {
	//���� �ȸ���
	if (tower.size() != disk) {
		return false;
	}
	//������� �˻� �ϳ��� Ʋ���� Ʋ��,
	//������ ��� ū�ź��� �� �տ� ����ǹǷ� �ε��� + ��ũ ũ�� = ���� ��� �����̴�
	for (int i = 0; i < disk; i += 1) {
		if (tower[i] != disk - i) {
			return false;
		}
	}
	return true;
}
//---------------------------------------------------------

//�ڵ� ��� �ڵ� -------------------------------------------
//�ڵ� Ǯ��
void hano(int disk, int start, int re, int end, int position, int& tried, vector<vector<int>>& tower) {
	if (disk == 1) {
		//�ű��, ����Ƚ���ø���, Ÿ�� �����ֱ�
		//Ÿ�� �迭�� �ǵ帮�� ���� ���� ���� �� ������ �� Ÿ�� �ʱ�ȭ �ʿ�
		tried += 1;
		move_disk(start, end, tower);
		cout << "�õ� Ƚ�� : " << tried << "\n";
		show_tower(position, tower);
		return;
	}
	//���
	hano(disk - 1, start, end, re, position, tried, tower);
	hano(1, start, re, end, position, tried, tower);
	hano(disk - 1, re, start, end, position, tried, tower);
}
//���� �ʱ�ȭ
void answer_init(int& tried, int& disk, int& position, vector<vector<int>>& tower) {
	//���� ���� : ������ ������ ������ 3���� �����Ǿ��ִ�.
	tried = 0;
	disk = init_set("disk");
	position = init_set("position", 3);
	tower = init_tower(disk, 3);
}
//���� ����
void answer_loop(int& tried, int& disk, int& position, vector<vector<int>>& tower) {
	//���� ����
	while (true) {
		//�ʱ�ȭ�Ȼ��� �����ֱ�
		show_tower(position, tower);
		//���� �����ֱ�
		hano(disk, 1, 6 - position - 1, position, position, tried, tower);
		promft_complete(tried);
		//�ٽ��ϱ� �˻�
		string auto_answer = str_filter({ "Y","y","N","n" });
		if (auto_answer == "N" || auto_answer == "n") {//����
			return;
		}
		else if (auto_answer == "Y" || auto_answer == "y") {//�ʱ�ȭ
			answer_init(tried, disk, position, tower);
		}
	}
}
//---------------------------------------------------------

//���� ��� �ڵ� -------------------------------------------
//�÷��� ��� �ʱ�ȭ
void game_init(int& tried, int& from, int& to, int& disk, int& rod, int& position, vector<vector<int>>& tower) {
	tried = 0, from = 0, to = 0;
	disk = init_set("disk"), rod = init_set("rod");
	position = init_set("position", rod);
	tower = init_tower(disk, rod);
}
//�÷��� ����
void game_loop(int& tried, int& from, int& to, int& disk, int& rod, int& position, vector<vector<int>>& tower) {

	//�÷��� ���� ����, ���߰� ���� ���� ������ ���ѷ���
	while (true) {
		//�����ֱ�
		show_tower(position, tower);
		tried += 1;
		promft_try(tried, rod);

		//������ ���Դ���, �ϳ���ž ��Ģ�� �´� �Է����� �˻�
		while (!(cin >> from >> to) || !(isAllowinput(from, to, tower))) {
			clear_cin();
		}
		//���Է� ����
		clear_cin();

		//��ũ �ű�
		move_disk(from, to, tower);
		promft_move_success();

		//����˻� Ÿ�� �ε����� �ʱ� ������ ��ġ
		if (isComplete(disk, tower[position - 1])) {

			show_tower(position, tower);
			promft_complete(tried);

			//�ٽ��ϱ� �˻�
			string end_answer = str_filter({"Y","y","N","n"});
			if (end_answer == "N" || end_answer == "n") {//����
				return;
			}
			else if (end_answer == "Y" || end_answer == "y") {//�ʱ�ȭ
				game_init(tried, from, to, disk, rod, position, tower);
			}
		}
	}
}
//---------------------------------------------------------

//���� �Լ�
int main() {

	//ȯ�� ����
	promft_hello();

	//���� ����
	int tried, from, to, disk, rod, position;
	vector<vector<int>> tower;	

	//q���ö����� ���ѹݺ�
	while (true) {
		promft_mode_select();
		string temp = str_filter({"H","h","A","a","Q","q"});
		
		//���� �Է°��� ���� ��� ����
		promft_mode_selected(temp);
		if (temp == "H" || temp == "h") {//���� Ǯ��
			game_init(tried, from, to, disk, rod, position, tower);
			game_loop(tried, from, to, disk, rod, position, tower);
		}
		else if (temp == "A" || temp == "a") {//���� ����
			answer_init(tried, disk, position, tower);
			answer_loop(tried, disk, position, tower);
		}
		else if (temp == "Q" || temp == "q") {//����
			//â ����
			keep_window_open();
			return 0;
		}
	}
}