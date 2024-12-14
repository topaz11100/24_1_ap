#include "Graph.h"
#include "Puzzle_window.h"
using namespace Graph_lib;


int main()
{
	Point tl(0, 0);
	Puzzle_window win(tl, 400, 400, 8, 8, "Bejeweled");

	Fl::redraw();

	return gui_main();
}

