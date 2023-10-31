#include "TextFile.h"

int main(int argc, char* argv[]) {
	TextFile f(argv[1]);
	f.parse_into_tree();

	return 0;
};