#include "TuringMachine.h"

using namespace Turing;

Move Turing::chartoMove(char a) {
	switch (a) {
	case 'l':
		return Move::LEFT;
	case 'r':
		return Move::RIGHT;
	case WILDCARD_SYMBOL:
		return Move::NONE;
	}
}

Transition::Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s)
	: curr_state{ curr_s }, read_symbol{ read_s }, write_symbol{ write_s }, move{ m }, next_state{ next_s }
{
}

void Transition::print(std::ostream& os) const
{
	os << curr_state << " ";
	os << read_symbol << " ";
	os << write_symbol << " ";
	os << (move == Move::LEFT ? 'l' : (move == Move::RIGHT ? 'r' : '*')) << " ";
	os << next_state;
}

Table::Table() {}

Table::~Table() {
	for (Transition* const& x : table) delete x;
}

void Table::addTransition(const std::string& curr_s, char read_s, char write_s,
						  Move move, const std::string& next_s)
{
	Transition* temp = new Transition{ curr_s, read_s, write_s, move, next_s };
	table.push_back(temp);
}

void Table::clear() {
	for (Transition* const& x : table) delete x;
	table.clear();
}

void Table::print(ostream& os) const {
	for (Transition* const& x : table) {
		x->print(os);
		os << '\n';
	}
}

Transition* Table::findTransition(const std::string& curr_s, char read_s) {
	bool wild = true;
	Transition* result = nullptr;
	for (Transition* const& x : table) {
		if (x->getCurrState() == curr_s && x->getReadSymbol() == read_s) {
			return x;
		}
		if (wild && (x->getCurrState() == curr_s) &&
			((read_s == WILDCARD_SYMBOL) || (x->getReadSymbol() == WILDCARD_SYMBOL))) {
			result = x;
			wild = false;
		}
	}
	return result;
}

void Table::initialize(const std::string& rule_script) {
	this->clear();
	vector<string> temp1 = split(rule_script, '\n');
	for (const string& x : temp1) {
		vector<string> temp2 = split(x, ' ');
		if (temp2[0] == ";" || temp2[0] == "") continue;
		this->addTransition(temp2[0], (char)temp2[1][0], (char)temp2[2][0], 
							chartoMove((char)temp2[3][0]), temp2[4]);
	}
}

bool Table::load(const std::string& path) {
	ifstream ist{ path };
	string rule_script, temp;
	while (getline(ist, temp)) {
		rule_script += temp;
		rule_script += "\n";
	}
	if (!ist.eof()) return false;

	this->initialize(rule_script);
	return true;
}

Tape::Tape()
	:sz{ 0 }, space{ 0 }, elem{nullptr}
{
}

Tape::Tape(const Tape& t)
	:sz{ t.sz }, space{ t.sz }, elem{new char[t.sz]}
{
	for (int i = 0; i < t.sz; i += 1) elem[i] = t.elem[i];
}

Tape& Tape::operator=(const Tape& t) {
	if (t.sz <= space) {
		for (int i = 0; i < t.sz; i += 1) elem[i] = t.elem[i];
		sz = t.sz;
		return *this;
	}
	char* temp = new char[t.sz];
	for (int i = 0; i < t.sz; i += 1) temp[i] = t.elem[i];
	delete[] elem;
	elem = temp;
	sz = t.sz;
	space = sz;
	return *this;
}

Tape::Tape(Tape&& t)
	:sz{ t.sz }, space{ t.space }, elem{t.elem}
{
	t.sz = 0;
	t.space = 0;
	t.elem = nullptr;
}

Tape& Tape::operator=(Tape&& t){
	delete[] elem;
	elem = t.elem;
	sz = t.sz;
	space = sz;
	t.sz = 0;
	t.space = 0;
	t.elem = nullptr;
	return *this;
}

Tape::~Tape() {
	delete[] elem;
}

bool Tape::read(int i, char& c) const {
	if (i < 0 || i >= sz) return false;
	c = elem[i];
	return true;
}

bool Tape::write(int i, char c) {
	if (i < 0 || i >= sz) return false;
	elem[i] = c;
	return true;
}

void Tape::initialize(const std::string& s) {
	delete[] elem;
	sz = s.size();
	space = sz;
	elem = new char[space];
	for (int i = 0; i < sz; i += 1) elem[i] = s[i];
}

void Tape::clear() {
	sz = 0;
}

void Tape::print(std::ostream& os) const {
	for (int i = 0; i < sz; i += 1) os << elem[i];
}

void Tape::reserve(int newalloc) {
	if (space >= newalloc) return;
	char* temp = new char[newalloc];
	for (int i = 0; i < sz; i += 1) temp[i] = elem[i];
	delete[] elem;
	elem = temp;
	space = newalloc;
}

void Tape::resize(int newsize) {
	reserve(newsize);
	for (int i = sz; i < space; i += 1) elem[i] = EMPTY_SYMBOL;
	sz = space;
}

void Tape::push_back(char c) {
	if (space == 0) {
		initialize(string(1,c));
		return;
	}
	else if (sz == space) reserve(2 * space);
	elem[sz] = c;
	sz += 1;
}

void Tape::push_front(char c) {
	if (space == 0) {
		initialize(string(1, c));
		return;
	}
	else if (sz == space) reserve(2 * space);
	for (int i = sz; i > 0; i -= 1) elem[i] = elem[i - 1];
	elem[0] = c;
	sz += 1;
}

void Machine::initTape(const std::string& initial_symbols) {
	tape.initialize(initial_symbols);
}

void Machine::initTable(const std::string& initial_symbols) {
	table.initialize(initial_symbols);
}

bool Machine::loadTable(const std::string& path) {
	return table.load(path);
}

void Machine::start(const std::string& start_state,
				    const std::string& accept_state,
					const std::string& reject_state) {
	this->current_pos   = 0;
	this->current_state = start_state;
	this->accept_state  = accept_state;
	this->reject_state  = reject_state;
	this->current_mode  = Mode::NORMAL;
}

bool Machine::step() {
	if (current_state == accept_state || current_state == reject_state) return false;

	char read_s; tape.read(current_pos, read_s);
	Transition* trans = table.findTransition(current_state, read_s);

	if (trans->getWriteSymbol() != WILDCARD_SYMBOL) tape.write(current_pos, trans->getWriteSymbol());

	current_pos += (int)trans->getMove();
	if (current_pos < 0) { 
		tape.push_front(EMPTY_SYMBOL);
		current_pos = 0;
	}
	else if (current_pos >= tape.size()) tape.push_back(EMPTY_SYMBOL);

	current_state = trans->getNextState();
	if (current_state == accept_state) current_mode = Mode::ACCEPT;
	else if (current_state == reject_state) current_mode = Mode::REJECT;
	
	return true;
}


