#include "TextFile.h"
#include "../utils/iohelpers.h"

#include <algorithm>

void user_interact(const int argc,  const char* argv[], TextFile& f) {
	if (argc == 2) {
		std::cout << "input file:\n\n";
		f.print_input();
		std::cout << "\noutputting to console...\n\n";
		f.print_words();
	}
	else if (argc == 3) {
		std::cout << "outputting to file..." << std::endl;
		f.print_words(argv[2]);
	}
};

void PrintNode(TextFile::WordInfo* info, int depth, int position, std::vector<int>* also){
	for (int i = 0; i < depth; i++){
		if (std::find(also->begin(), also->end(), i) != also->end()){
			std::cout << "|   ";
		}
		else {
			std::cout << "    ";
		}
	}
	if (position == 1) {std::cout << "/ ";}
	else if (position == -1) { std::cout << "\\ ";}
	std::cout << info->word << std::endl;
}

int main(int argc, const char* argv[]) {
	iohelpers::check_args(argc, 2, 3);

	TextFile f(argv[1]);
	f.parse_into_tree();
	user_interact(argc, argv, f);
	f.PrintStructure(&PrintNode);
};