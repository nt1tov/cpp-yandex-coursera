#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }
  bool CheckIfLine() const {return log_line;}
  bool CheckIfFile() const {return log_file;}

  void Log(const string& message) {os << message;}

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) {    		\
    std::ostringstream os;        		\
    if(logger.CheckIfFile()){       		\
      os << __FILE__;             		\
      if(logger.CheckIfLine()){     		\
        os <<":"<<__LINE__;       		\
      }                           		\
      os <<" ";                   		\
    }                             		\
    else if(logger.CheckIfLine()){		\
		os <<"Line "<<__LINE__ <<" ";	\
    }									\
	os << message << "\n";				\
    logger.Log(os.str());				\
}

void TestLog() {
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestLog);
// }
