#include "TextFile.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "cry" << std::endl;
		exit(-1);
	}

	TextFile f(argv[1]);
	f.parse_into_tree();
	f.print_words();

	return 0;
};