#pragma once

#include <utility>
#include <string>
#include <vector>
#include "std_lib_facilities.h"

enum class Jewel
{
	NONE=-1, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE
};

class Puzzle
{
public:

	struct Chain
	{
		Jewel jewel;
		std::pair<int, int> start;
		std::pair<int, int> end;
	};

	Puzzle(int num_rows, int num_columns);
	//초기화
	bool initialize(const std::string& jewel_list);
	void randomize();
	//진행
	bool update();
	//위치검사
	bool valid_pos(std::pair<int, int> loc) const;
	//바꾸기
	bool swapJewels(std::pair<int, int> prev_loc, std::pair<int, int> next_loc);
	//가져오기
	bool setJewel(std::pair<int, int> loc, Jewel jewel);
	Jewel getJewel(std::pair<int, int> loc) const;
	//게터
	inline int getNumRows() const { return num_rows; }
	inline int getNumColumns() const { return num_columns; }
	int getcombo() const { return combo; }
	int getscore() const { return score; }
	//변환
	static Jewel getJewelType(char letter);
	static char getJewelLetter(Jewel jewel);

private:
	//사이즈
	int num_rows;
	int num_columns;
	//퍼즐
	vector<vector<Jewel>> puzzle;
	//체인
	vector<Chain> chain_arr;
	//진행정보
	bool update_status{ true };
	//업데이트 내부함수
	void horizon_check();
	void vertical_check();
	void setnone();
	bool update_A();
	void bubbleup();
	bool update_B();
	//점수 변수
	int combo{ 0 };
	int score{ 0 };

};


