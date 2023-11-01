#include "TextFile.h"
#include "iohelpers.h"

int main(int argc, char* argv[]) {
	iohelpers::check_args(argc, 2, 2);

	TextFile f(argv[1]);
	f.parse_into_tree();
	f.print_words();

	return 0;
};