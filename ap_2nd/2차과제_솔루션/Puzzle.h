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
	//�ʱ�ȭ
	bool initialize(const std::string& jewel_list);
	void randomize();
	//����
	bool update();
	//��ġ�˻�
	bool valid_pos(std::pair<int, int> loc) const;
	//�ٲٱ�
	bool swapJewels(std::pair<int, int> prev_loc, std::pair<int, int> next_loc);
	//��������
	bool setJewel(std::pair<int, int> loc, Jewel jewel);
	Jewel getJewel(std::pair<int, int> loc) const;
	//����
	inline int getNumRows() const { return num_rows; }
	inline int getNumColumns() const { return num_columns; }
	int getcombo() const { return combo; }
	int getscore() const { return score; }
	//��ȯ
	static Jewel getJewelType(char letter);
	static char getJewelLetter(Jewel jewel);

private:
	//������
	int num_rows;
	int num_columns;
	//����
	vector<vector<Jewel>> puzzle;
	//ü��
	vector<Chain> chain_arr;
	//��������
	bool update_status{ true };
	//������Ʈ �����Լ�
	void horizon_check();
	void vertical_check();
	void setnone();
	bool update_A();
	void bubbleup();
	bool update_B();
	//���� ����
	int combo{ 0 };
	int score{ 0 };

};


