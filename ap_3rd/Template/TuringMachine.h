#pragma once

#include <vector>
#include <string>
#include <set>
#include <cassert>
#include <iterator>

#include <iostream>

#include <fstream>
#include "util.h"

using namespace std;
using namespace Util;

namespace Turing
{
	const char EMPTY_SYMBOL = '_';
	const char WILDCARD_SYMBOL = '*';

	enum class Move
	{
		LEFT = -1, NONE, RIGHT
	};
	Move chartoMove(char a);

	struct Transition
	{
	public:
		Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s);

		void print(std::ostream& os) const;

		inline const std::string& getCurrState() const { return curr_state; }
		inline const std::string& getNextState() const { return next_state; }

		inline char getReadSymbol() const { return read_symbol; }
		inline char getWriteSymbol() const { return write_symbol; }
		
		inline Move getMove() const { return move; }

	private:
		std::string curr_state, next_state;
		char read_symbol, write_symbol;
		Move move;
	};

	class Table
	{
	public:
		Table();
		~Table();
		void addTransition(const std::string& curr_s, char read_s, char write_s,
						   Move move, const std::string& next_s);
		Transition* findTransition(const std::string& curr_s, char read_s);
		void clear();
		void print(std::ostream& os) const;
		void initialize(const std::string& rule_script);
		bool load(const std::string& path);
		
	private:
		vector<Transition*> table;
	};

	class Tape
	{
	public:
		Tape();
		Tape(const Tape& t);
		Tape(Tape&& t);
		~Tape();

		Tape& operator=(const Tape& t);
		Tape& operator=(Tape&& t);

		bool read(int i, char& c) const;
		bool write(int i, char c);
		void push_back(char c);
		void push_front(char c);

		void reserve(int newalloc);
		void resize(int newsize);

		int size() const { return sz; }
		int capacity() const { return space; }

		void initialize(const std::string& s);
		void clear();
		void print(std::ostream& os) const;

	private:
		int sz;
		int space;
		char* elem;
	};

	class Machine
	{
	public:
		enum class Mode { NONE, NORMAL, ACCEPT, REJECT, ERROR };

		void initTape(const std::string& initial_symbols);
		void initTable(const std::string& rule_script);
		bool loadTable(const std::string& path);

		void start(const std::string& start_state,
				   const std::string& accept_state,
				   const std::string& reject_state);
		bool step();

		const Table& getTable() const { return table; }
		const Tape& getTape() const { return tape; }
		const std::string& getCurrentState() const { return current_state; }
		int getCurrentPos() const { return current_pos; }
		Mode getCurrentMode() const { return current_mode; }

	private:
		Table table;
		Tape tape;

		Mode current_mode = Mode::NONE;
		std::string current_state = "";
		int current_pos = 0;

		std::string accept_state = "";
		std::string reject_state = "";
	};
};
