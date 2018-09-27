
#include <exception>
#include <filesystem>
#include <iostream>
#include <system_error>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

// io2d uses its own main(), rather than Catch's, so as to set the running
// process' current working directory to that where input data files are
// located.
//
// Catch2 describes how to do a custom main(), at:
//   https://github.com/catchorg/Catch2/blob/master/docs/own-main.md

int main(int argc, char* argv[])
{
	// For now, set the app's CWD (Current Working Directory) to where the
	// app's executable is, presuming this info is available.
	if (argc >= 1 && argv[0] != nullptr) {
		try {
			using namespace std::filesystem;
			current_path(path(argv[0]).parent_path());
		} catch (const std::exception & ex) {
			std::cerr <<
				"ERROR: Unable to set CWD via current_path(). what()=\"" <<
				ex.what() <<
				"\"\n";
			return 1;	// Return a non-zero integer to indicate failure
		}
	}

	return Catch::Session().run(argc, argv);
}
