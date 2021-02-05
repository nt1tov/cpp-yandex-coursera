#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table

template<class T>
class Table{
private:
	size_t rows_cnt = 0;
	size_t cols_cnt = 0;
	vector<vector<T>> data;
public:
	Table(const size_t& rcnt, const size_t& ccnt){
		Resize(rcnt, ccnt);
	}

	auto& operator[](const size_t& idx){
		return data[idx];
	}

	const auto& operator[](const size_t& idx) const{
		return data[idx];
	}

	void Resize(const size_t& rcnt, const size_t& ccnt){
		rows_cnt = rcnt;
		cols_cnt = ccnt;
		data.resize(rcnt);
		for(auto i = 0; i < data.size(); ++i){
			data[i].resize(ccnt);
		}
	}

	pair<size_t, size_t> Size() const{
		if(rows_cnt != 0 && cols_cnt != 0) return {rows_cnt, cols_cnt};
		return {0, 0};
	}
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

// int main() {
// 	TestRunner tr;
// 	RUN_TEST(tr, TestTable);
// 	return 0;
// }

//  binding value of type 'const vector<...>' to reference to type 'vector<...>' drops 'const' qualifier\n                return data[idx];\n
//  \n/tmp/submission7t4vezev/tmpmybnjbst.cpp:38:3: note: in instantiation of member function 'Table<int>::operator[]' requested here\n
//  t[0][0] = 42;\n         ^\n1 error generated.\n"