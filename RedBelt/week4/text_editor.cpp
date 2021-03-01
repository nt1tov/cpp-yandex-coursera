#include <string>
#include "test_runner.h"
#include <deque>
#include <list>
#include <iterator>

using namespace std;

class Editor {
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor();
  void Left();
  void Right();
  void Insert(char token);
  void Cut(size_t tokens = 1);
  void Copy(size_t tokens = 1);
  void Paste();
  string GetText() const;
private:

  list<char> data;
  list<char>::iterator cursor;
  list<char> buff;

};

Editor::Editor():
  cursor(data.end())
{
  ;
}

void Editor::Left(){
  if (cursor != data.begin()){
    cursor = prev(cursor);
  }
}

void Editor::Right(){
  if (cursor != data.end()){
    cursor = next(cursor);
  }
}

void Editor::Insert(char token){
  data.insert(cursor, token);
}

void Editor::Cut(size_t tokens ){
  if(tokens == 0){
    return;
  }
  list<char>::iterator end_iter;
  if(distance(cursor , data.end()) < tokens){
    end_iter = data.end();
  }
  else{
    end_iter = next(cursor, tokens);
  }
  buff.splice(buff.begin(), data, cursor, end_iter);
  cursor = end_iter;

}

void Editor::Copy(size_t tokens){
  if(tokens == 0){
    return;
  }
  list<char>::iterator end_iter;
  if(distance(cursor , data.end()) < tokens){
    end_iter = data.end();
  }
  else{
    end_iter = next(cursor, tokens);
  }
  buff = list<char>(cursor, end_iter);
}

void Editor::Paste(){
  if(buff.begin() == buff.end()){
    return;
  }
  data.insert(cursor, buff.begin(), buff.end());

}

string Editor::GetText() const{
  return string(data.begin(), data.end());
}

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");

    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");

    editor.Paste();


    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestEditing);
//   RUN_TEST(tr, TestReverse);
//   RUN_TEST(tr, TestNoText);
//   RUN_TEST(tr, TestEmptyBuffer);
//   return 0;
// }