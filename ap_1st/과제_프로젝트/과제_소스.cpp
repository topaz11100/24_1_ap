#include "std_lib_facilities.h"

//프롬프트 모음 -------------------------------
void promft_hello() {
	cout << "-----\n하노이탑 퍼즐에 오신 것을 환영합니다.\n-----\n";
}
void promft_mode_select() {
	cout << "\n문제를 풀겠습니까?  (H)\n오리지널 하노이탑의 답을 보겠습니까?  (A)\n종료하겠습니까?  (Q)\n>>> ";
}
void promft_mode_selected(string mode) {
	if (mode == "H" || mode == "h") {//퍼즐 풀기
		cout << "\n-----\n문제 풀기 선택\n-----\n\n";
	}
	else if (mode == "A" || mode == "a") {//정답 보기
		cout << "\n-----\n정답 보기 선택\n-----\n\n";
	}
	else if (mode == "Q" || mode == "q") {//종료
		cout << "\n-----\n수고하셨습니다!\n2020203090 한용옥 제작\n-----\n\n";
	}
}
void promft_disk() {
	cout << "원반의 개수를 선택해 주세요. (1개 ~ 9개) : ";
}
void promft_rod() {
	cout << "기둥의 개수를 선택해 주세요. (3개 ~ 6개) : ";
}
void promft_position(int len) {
	cout << len << "개의 기둥 중 1번에서 시작합니다\n몇 번 기둥으로 옮기겠습니까? (2번 ~ " << len << "번) : ";
}
void promft_input_fail() {
	cout << "틀린 입력 // 정확한 값을 입력하세요.  :  ";
}
void promft_move_success() {
	cout << "=> 이동 성공!\n";
}
void promft_move_fail(string fail_message) {
	cout << "=> 이동 실패! // "<< fail_message <<" // 다시 입력하세요.  :  ";
}
void promft_try(int tried, int len) {
	cout << "시도 횟수 : " << tried << "번\n"
		 << "원반을 어떻게 옮기겠습니까? (" << 1 << "~" << len << "번 -> " << 1 << "~" << len << "번) :  ";
}
void promft_complete(int tried) {
	cout << "축하합니다! " << tried << "번 만에 성공했습니다!\n\n"
		 << "다시 하겠습니까?  ( Y / N ) : ";
}
//--------------------------------------------

//문자에 대한 입력, 입력예외처리 ---------------------------------------
//cin 초기화 cin에 남아있는 입력을 지우고 변수에 잘 들어갔는지 여부도 초기화한다.
void clear_cin() {
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}
// 문자가 배열에 있는지 : 검사기에서 범위검사를 할때 쓰임
bool isStrinarr(string str, vector<string>& filter_list) {
	for (string x : filter_list) {
		if (str == x) {
			return true;
		}
	}
	return false;
}
// 문자입력 예외검사기
string str_filter(vector<string> filter_list) {
	string answer;
	while (!(cin >> answer) || !isStrinarr(answer, filter_list)) {
		promft_input_fail();
		clear_cin();
	}
	//입력이 여러개 들어와 다음 입력에 영향 미치는것 방지
	clear_cin();

	return answer;
}
//--------------------------------------------------------

//타워 초기화 관련--------------------------------------------
//초기 숫자 설정 : 디스크, 원반 개수, 어디에 놓을지에 대한 정수를 반환
int init_set(string mode, int len = 0) {

	int temp = 0;
	int up = 0, down = 0;
	//모드에따라 상하한, 프롬프트 변경
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
	//예외 검사
	while (!(cin >> temp) || !(down <= temp && temp <= up)) {
		promft_input_fail();
		clear_cin();
	}
	//입력이 여러개 들어와 다음 입력에 영향 미치는것 방지
	clear_cin();

	return temp;
}
//초기 상태 벡터(타워) 반환
vector<vector<int>> init_tower(int disk, int rod) {
	vector<vector<int>> result = {};
	//기둥 생성
	for (int i = 0; i < rod; i += 1) {
		result.push_back({});
	}
	//0번이 제일 밑, 원반 채워넣기
	for (int i = disk; i > 0; i -= 1) {
		result[0].push_back(i);
	}
	return result;
}
//----------------------------------------------------------

//타워 조작 관련--------------------------------------------
//하노이탑 세로로 표시
void show_tower(int position, vector<vector<int>>& tower) {
	cout << '\n';
	//가장 긴 벡터의 요소개수 구함
	int max = 0;
	for (vector<int> x : tower) {
		if (max < x.size()) {
			max = x.size();
		}
	}
	//벡터 끝에서부터 읽음 원소가 없으면 간격조정용 공백 출력
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
	//기둥 번호 표시, 목표 기둥은 특별 표시
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
//하노이 탑 규칙에 맞는 입력인지 검사
bool isAllowinput(int from, int to, vector<vector<int>>& tower) {
	//범위에 안맞는 입력
	if (from < 1 || from > tower.size() || to < 1 || to > tower.size()) {
		promft_move_fail("없는 번호");
		return false;
	}
	//같은 곳에 옮김
	if (from == to) {
		promft_move_fail("같은 위치에 옮김");
		return false;
	}
	//비어있는 곳에서 뺄려고 함
	if (tower[from - 1].size() == 0) {
		promft_move_fail("비어있는 곳에서 뺌");
		return false;
	}
	//놓을 곳이 비어있음 true조건을 검사하는 이유는 밑 조건에서 배열에 접근하기 위함
	if (tower[to - 1].size() == 0) {
		return true;
	}
	//놓을 곳에 있는 디스크가 놓으려는 디스크보다 작은 경우
	else if (tower[from - 1][tower[from - 1].size() - 1] > tower[to - 1][tower[to - 1].size() - 1]) {
		promft_move_fail("하노이탑 규칙에 어긋남\n(큰 원반이 밑에 있어야 함!)");
		return false;
	}
	//안되는건 위에서 다 거름
	return true;
}
//디스크 옮기기
void move_disk(int from, int to, vector<vector<int>>& tower) {
	//뺄 원판 저장, 실제로 빼서, 옮김
	int temp = tower[from - 1][tower[from - 1].size() - 1];
	tower[from - 1].pop_back();
	tower[to - 1].push_back(temp);
}
//정답검사
bool isComplete(int disk, vector<int>& tower) {
	//개수 안맞음
	if (tower.size() != disk) {
		return false;
	}
	//순서대로 검사 하나라도 틀리면 틀림,
	//정답인 경우 큰거부터 맨 앞에 저장되므로 인덱스 + 디스크 크기 = 벡터 요소 개수이다
	for (int i = 0; i < disk; i += 1) {
		if (tower[i] != disk - i) {
			return false;
		}
	}
	return true;
}
//---------------------------------------------------------

//자동 모드 코드 -------------------------------------------
//자동 풀이
void hano(int disk, int start, int re, int end, int position, int& tried, vector<vector<int>>& tower) {
	if (disk == 1) {
		//옮기고, 시행횟수늘리고, 타워 보여주기
		//타워 배열을 건드리며 동작 따라서 답을 다 보여준 후 타워 초기화 필요
		tried += 1;
		move_disk(start, end, tower);
		cout << "시도 횟수 : " << tried << "\n";
		show_tower(position, tower);
		return;
	}
	//재귀
	hano(disk - 1, start, end, re, position, tried, tower);
	hano(1, start, re, end, position, tried, tower);
	hano(disk - 1, re, start, end, position, tried, tower);
}
//정답 초기화
void answer_init(int& tried, int& disk, int& position, vector<vector<int>>& tower) {
	//정답 설정 : 정답은 막대의 개수가 3으로 고정되어있다.
	tried = 0;
	disk = init_set("disk");
	position = init_set("position", 3);
	tower = init_tower(disk, 3);
}
//정답 루프
void answer_loop(int& tried, int& disk, int& position, vector<vector<int>>& tower) {
	//정답 루프
	while (true) {
		//초기화된상태 보여주기
		show_tower(position, tower);
		//정답 보여주기
		hano(disk, 1, 6 - position - 1, position, position, tried, tower);
		promft_complete(tried);
		//다시하기 검사
		string auto_answer = str_filter({ "Y","y","N","n" });
		if (auto_answer == "N" || auto_answer == "n") {//종료
			return;
		}
		else if (auto_answer == "Y" || auto_answer == "y") {//초기화
			answer_init(tried, disk, position, tower);
		}
	}
}
//---------------------------------------------------------

//수동 모드 코드 -------------------------------------------
//플레이 모드 초기화
void game_init(int& tried, int& from, int& to, int& disk, int& rod, int& position, vector<vector<int>>& tower) {
	tried = 0, from = 0, to = 0;
	disk = init_set("disk"), rod = init_set("rod");
	position = init_set("position", rod);
	tower = init_tower(disk, rod);
}
//플레이 루프
void game_loop(int& tried, int& from, int& to, int& disk, int& rod, int& position, vector<vector<int>>& tower) {

	//플레이 과정 루프, 맞추고 종료 누를 때까지 무한루프
	while (true) {
		//보여주기
		show_tower(position, tower);
		tried += 1;
		promft_try(tried, rod);

		//정수가 들어왔는지, 하노이탑 규칙에 맞는 입력인지 검사
		while (!(cin >> from >> to) || !(isAllowinput(from, to, tower))) {
			clear_cin();
		}
		//과입력 방지
		clear_cin();

		//디스크 옮김
		move_disk(from, to, tower);
		promft_move_success();

		//정답검사 타워 인덱스는 초기 설정한 위치
		if (isComplete(disk, tower[position - 1])) {

			show_tower(position, tower);
			promft_complete(tried);

			//다시하기 검사
			string end_answer = str_filter({"Y","y","N","n"});
			if (end_answer == "N" || end_answer == "n") {//종료
				return;
			}
			else if (end_answer == "Y" || end_answer == "y") {//초기화
				game_init(tried, from, to, disk, rod, position, tower);
			}
		}
	}
}
//---------------------------------------------------------

//메인 함수
int main() {

	//환영 문구
	promft_hello();

	//변수 선언
	int tried, from, to, disk, rod, position;
	vector<vector<int>> tower;	

	//q들어올때까지 무한반복
	while (true) {
		promft_mode_select();
		string temp = str_filter({"H","h","A","a","Q","q"});
		
		//유저 입력값에 따라 모드 변경
		promft_mode_selected(temp);
		if (temp == "H" || temp == "h") {//퍼즐 풀기
			game_init(tried, from, to, disk, rod, position, tower);
			game_loop(tried, from, to, disk, rod, position, tower);
		}
		else if (temp == "A" || temp == "a") {//정답 보기
			answer_init(tried, disk, position, tower);
			answer_loop(tried, disk, position, tower);
		}
		else if (temp == "Q" || temp == "q") {//종료
			//창 유지
			keep_window_open();
			return 0;
		}
	}
}