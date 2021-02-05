#include "test_runner.h"
#include <iomanip>
#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) (out) << (x) << "\n" << (y) << endl

int main() {
	TestRunner tr;
	tr.RunTest([] {
	ostringstream output;
	PRINT_VALUES(output, 5, "red belt");
	// output.clear();

	ASSERT_EQUAL(output.str(), "5\nred belt\n");
	output.str("");

	}, "PRINT_VALUES usage example");
	ostringstream output;
	// if(true)
	// 	PRINT_VALUES(output, "", 4);
	// else
	// 	PRINT_VALUES(output, 2, "");

	// for(auto i = 0; i < 5; ++i)
	// 	PRINT_VALUES(output, "i=", i);
  	// cout << output.str();

	int a=2,b=3;
    PRINT_VALUES(output, 5, 6);
	cout << output.str();
}
