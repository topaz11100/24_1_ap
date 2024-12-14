#include "Puzzle.h"

Puzzle::Puzzle(int num_rows, int num_columns) {
	if (num_rows <= 0 || num_columns <= 0) error("invalid size");
	this->num_rows = num_rows;
	this->num_columns = num_columns;
	for (int i = 0; i < num_rows; i += 1) {
		vector<Jewel> temp;
		for (int j = 0; j < num_columns; j += 1) {
			temp.push_back(Jewel::NONE);
		}
		puzzle.push_back(temp);
	}
	srand((int)time(NULL));
}

bool Puzzle::initialize(const std::string& jewel_list) {
	if (jewel_list.size() != num_rows * num_columns) return false;

	for (int i = 0; i < num_rows; i += 1) {
		for (int j = 0; j < num_columns; j += 1) {
			puzzle[i][j] = getJewelType(jewel_list[i * num_rows + j]);
		}
	}
	return true;
}

void Puzzle::randomize() {
	for (int i = 0; i < num_rows; i += 1) {
		for (int j = 0; j < num_columns; j += 1) {
			int temp = rand();
			puzzle[i][j] = (Jewel)(temp % 7);
		}
	}
}

//가로 필터
void Puzzle::horizon_check() {
	for (int i = 0; i < getNumRows(); i += 1) {
		for (int j = 0; j < getNumColumns() - 2; j += 1) {
			if (puzzle[i][j] == puzzle[i][j + 1] && puzzle[i][j + 1] == puzzle[i][j + 2]) {
				Jewel J = getJewel(make_pair(i, j));
				int temp = 3;
				while (j + temp < getNumColumns() && puzzle[i][j + temp] == J) temp += 1;
				chain_arr.push_back(Chain{ J, make_pair(i, j), make_pair(i, j + temp - 1) });
				j += temp - 1;
			}
		}
	}
}
//세로필터
void Puzzle::vertical_check() {
	for (int j = 0; j < getNumColumns(); j += 1) {
		for (int i = 0; i < getNumRows() - 2; i += 1) {
			if (puzzle[i][j] == puzzle[i + 1][j] && puzzle[i + 1][j] == puzzle[i + 2][j]) {
				Jewel J = getJewel(make_pair(i, j));
				int temp = 3;
				while (i + temp < getNumRows() && puzzle[i + temp][j] == J) temp += 1;
				chain_arr.push_back(Chain{ J, make_pair(i, j), make_pair(i + temp - 1, j) });
				i += temp - 1;
			}
		}
	}
}
//none변환
void Puzzle::setnone() {
	for (const Chain& c : chain_arr) {
		for (int i = 0; i <= c.end.first - c.start.first; i += 1) {
			puzzle[c.start.first + i][c.start.second] = Jewel::NONE;
		}
		for (int j = 0; j <= c.end.second - c.start.second; j += 1) {
			puzzle[c.start.first][c.start.second + j] = Jewel::NONE;
		}
	}
}
//역할A
bool Puzzle::update_A() {
	horizon_check();
	vertical_check();
	if (chain_arr.size() == 0) {
		combo = 0;
		return false;
	}
	setnone();
	chain_arr.clear();
	combo += 1;
	return true;
}
//none위로 띄우기
void Puzzle::bubbleup() {
	for (int i = 0; i < getNumRows(); i += 1) {
		for (int j = 0; j < getNumColumns(); j += 1) {
			if (puzzle[i][j] == Jewel::NONE) {
				for (int k = i; k > 0; k -= 1) {
					swapJewels(make_pair(k, j), make_pair(k - 1, j));
				}
			}
		}
	}
}
//역할 B
bool Puzzle::update_B() {
	bubbleup();
	int temp_score = 0;
	for (int i = 0; i < getNumRows(); i += 1) {
		for (int j = 0; j < getNumColumns(); j += 1) {
			if (puzzle[i][j] == Jewel::NONE) {
				puzzle[i][j] = (Jewel)(rand() % 7);
				temp_score += 1;
			}
		}
	}
	score += temp_score * combo;
	return true;
}
//업데이트
bool Puzzle::update() {
	if (update_status) {
		update_status = false;
		if (!update_A()) return false;
		else return true;
	}
	else {
		update_status = true;
		return update_B();
	}
}
//위치검사
bool Puzzle::valid_pos(std::pair<int, int> loc) const {
	if (loc.first < 0 || loc.second < 0) return false;
	if (loc.first >= getNumRows() || loc.second >= getNumColumns()) return false;
	return true;
}
//바꾸기
bool Puzzle::swapJewels(std::pair<int, int> prev_loc, std::pair<int, int> next_loc) {
	if (!(valid_pos(prev_loc) && valid_pos(next_loc))) return false;
	if (!((prev_loc.first == next_loc.first && abs(prev_loc.second - next_loc.second) == 1)
		|| (prev_loc.second == next_loc.second && abs(prev_loc.first - next_loc.first) == 1)))
		return false;
	Jewel temp = puzzle[prev_loc.first][prev_loc.second];
	puzzle[prev_loc.first][prev_loc.second] = puzzle[next_loc.first][next_loc.second];
	puzzle[next_loc.first][next_loc.second] = temp;
	return true;
}

Jewel Puzzle::getJewel(std::pair<int, int> loc) const{
	if (!valid_pos(loc)) return Jewel::NONE;
	return puzzle[loc.first][loc.second];
}

bool Puzzle::setJewel(std::pair<int, int> loc, Jewel jewel) {
	if (!valid_pos(loc)) return false;
	puzzle[loc.first][loc.second] = jewel;
	return true;
}

Jewel Puzzle::getJewelType(char letter) {
	Jewel jewel = Jewel::NONE;

	switch (letter) {
	case ' ': jewel = Jewel::NONE; break;
	case '@': jewel = Jewel::RED; break;
	case '#': jewel = Jewel::ORANGE; break;
	case '*': jewel = Jewel::YELLOW; break;
	case '%': jewel = Jewel::GREEN; break;
	case '$': jewel = Jewel::BLUE; break;
	case '&': jewel = Jewel::PURPLE; break;
	case '!': jewel = Jewel::WHITE; break;
	}

	return jewel;
}

char Puzzle::getJewelLetter(Jewel jewel) {
	char letter = ' ';

	switch (jewel) {
	case Jewel::NONE: letter = ' '; break;
	case Jewel::RED: letter = '@'; break;
	case Jewel::ORANGE: letter = '#'; break;
	case Jewel::YELLOW: letter = '*'; break;
	case Jewel::GREEN: letter = '%'; break;
	case Jewel::BLUE: letter = '$'; break;
	case Jewel::PURPLE: letter = '&'; break;
	case Jewel::WHITE: letter = '!'; break;
	}

	return letter;
}

