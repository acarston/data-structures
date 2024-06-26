#include "TextFile.h"
#include "../../utils/iohelpers.h"

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
}

int main(int argc, const char* argv[]) {
	iohelpers::check_args(argc, 2, 3);

	TextFile f(argv[1]);
	f.parse_into_tree();
	user_interact(argc, argv, f);
}