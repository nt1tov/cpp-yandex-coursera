#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <queue>
#include <list>
#include <set>
using namespace std;

template <typename T>
class PriorityCollection {
public:
  /* тип, используемый для идентификаторов */;
  using Id = size_t;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
    data.push_back(move(object));
    auto obj_iter = prev(data.end());
    Id id;
    if(id2obj.empty()){
      id = 0;
    }
    else{
      id = id2obj.rbegin()->first + 1;
    }
    id2obj[id] = obj_iter;
    id2prior[id] = 0;
    prior2id[0].insert(id);


    return id;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
                                    IdOutputIt ids_begin){
    vector<Id> tmp;
    for(auto it = range_begin; it != range_end; ++it){
      tmp.emplace_back(Add(move(*it)));
    }
    move(make_move_iterator(tmp.begin()), make_move_iterator(tmp.end()), ids_begin);
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
    return id2obj.find(id) != id2obj.end();
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
    return *id2obj.at(id);
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
    auto old_prior = id2prior[id];
    id2prior[id]++;
    prior2id[old_prior].erase(id);
    if(prior2id[old_prior].empty()){
      prior2id.erase(old_prior);
    }
    prior2id[old_prior+1].insert(id);


  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    auto id_set = prior2id.rbegin()->second;
    auto prior = prior2id.rbegin()->first;
    auto id = *(id_set.rbegin());

    auto obj_it = id2obj.at(id);

    return {(*obj_it), prior};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
    auto id_set = prior2id.rbegin()->second;
    auto prior = prior2id.rbegin()->first;
    auto id = *(prior2id[prior].rbegin());

    prior2id[prior].erase(id);
    if(prior2id[prior].empty()){
      prior2id.erase(prior);
    }
    auto obj_it = id2obj[id];

    id2obj.erase(id);
    id2prior.erase(id);
    auto obj = move(*obj_it);
    data.erase(obj_it);

    return  pair<T, int>{move(obj), prior};
  }

private:
  list<T> data;
  map<Id, typename list<T>::iterator> id2obj;
  map<Id, int> id2prior;
  map<int, set<Id>> prior2id;
  // Приватные поля и методы
};



class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    auto tt = strings.GetMax();
    strings.Get(0);
    strings.IsValid(1);
    strings.IsValid(111);
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestNoCopy);
//   return 0;
// }
