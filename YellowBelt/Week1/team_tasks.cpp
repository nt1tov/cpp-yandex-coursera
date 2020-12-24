#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>

using namespace std;

// Перечислимый тип для статуса задачи

/*
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;
*/
class TeamTasks {
	map<string, TasksInfo> person_tasks;
public:

  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& 
  GetPersonTasksInfo(const string& person) const;
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> 
  PerformPersonTasks(const string& person, int task_count);
};


//не можем использовать оператор [] для функции const
const TasksInfo& 
TeamTasks::GetPersonTasksInfo(const string& person) const {
	return person_tasks.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
	if(person_tasks.count(person) == 0){
		TasksInfo tasks = person_tasks[person];
		tasks[TaskStatus::NEW] = 1;
		//tasks[TaskStatus::IN_PROGRESS] = 0;
		//tasks[TaskStatus::TESTING] = 0;
		//tasks[TaskStatus::DONE] = 0;
		person_tasks[person] = tasks;
		//person_tasks[person]
	}
	else{
		TasksInfo tasks = person_tasks[person];
		tasks[TaskStatus::NEW] += 1;
		person_tasks[person] = tasks;
	}
}

tuple<TasksInfo, TasksInfo> 
TeamTasks::PerformPersonTasks(const string& person, int task_count) {
	TasksInfo updated_tasks, untouched_tasks;
	TasksInfo name_tasks = person_tasks[person];
	TasksInfo new_name_tasks = person_tasks[person];
	int count = task_count, buf = 0;

	//cout<<person<<endl;

	auto enum_array = {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE};
	for(const auto& item: enum_array){
		if(name_tasks.count(item) == 0)
			 name_tasks[item] = 0;
	}


	for(const auto& [key, value]: name_tasks){
/*
		cout<<static_cast<int>(TaskStatus::NEW)<<" "<<new_name_tasks[TaskStatus::NEW]<<endl;
		cout<<static_cast<int>(TaskStatus::IN_PROGRESS)<<" "<<new_name_tasks[TaskStatus::IN_PROGRESS]<<endl;
		cout<<static_cast<int>(TaskStatus::TESTING)<<" "<<new_name_tasks[TaskStatus::TESTING]<<endl;
		cout<<static_cast<int>(TaskStatus::DONE)<<" "<<new_name_tasks[TaskStatus::DONE]<<endl<<endl;
*/

		if(key == TaskStatus::DONE){
			if(buf != 0)
				updated_tasks[key] = buf;
			new_name_tasks[key] += buf;
		}
		else{
			if(buf != 0)
				updated_tasks[key] = buf;
			if(count == 0){
				if(value != 0)
					untouched_tasks[key] = value;
				new_name_tasks[key] += buf;
				buf = 0;
			}
			else{
				if(value < count){
					if(buf != 0){
						new_name_tasks[key] = buf;
					}
					else{
						new_name_tasks.erase(key);
					}

					count -= value;
					buf = value;
				}	
				else{
					if((value - count) != 0)
						untouched_tasks[key] = value - count;
					if((value - count + buf) != 0){
						new_name_tasks[key] = value - count + buf;
					}
					else{
						new_name_tasks.erase(key);
					}
					buf = count;
					count = 0;

				}
			}
		}
 

	}
	person_tasks[person] = new_name_tasks;
	
	return {updated_tasks, untouched_tasks};
}


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь

void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

ostream& operator <<(ostream& out, const TaskStatus& status) {
    string statusName;
    switch (status) {
        case TaskStatus::NEW:
            statusName = "\"NEW\"";
            break;
        case TaskStatus::IN_PROGRESS:
            statusName = "\"IN_PROGRESS\"";
            break;
        case TaskStatus::TESTING:
            statusName = "\"TESTING\"";
            break;
        case TaskStatus::DONE:
            statusName = "\"DONE\"";
            break;
    }
    return out << statusName;
}
/*
######## ВАША РЕАЛИЗАЦИЯ #########
*/

template <typename Collection>
string Join(const Collection& c, const string& d) {
    stringstream ss;
    bool isFirst = true;
    for (const auto& i : c) {
        if(!isFirst) {
            ss << d;
        }
        isFirst = false;
        ss << i;
    }
    return ss.str();
}
template <typename F, typename S>
ostream& operator <<(ostream& out, const pair<F,S>& p) {
    return out << p.first << ": " << p.second;
}
template <typename K, typename V>
ostream& operator <<(ostream& out, const map<K,V>& m){
    return out << '{' << Join(m, ", ") << '}';
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& v) {
   return out << '['  << Join(v, ", ") << ']';
}
int main() {
    TeamTasks tasks;
    while(cin) {
        string command, person;
        int num;
        cin >> command >> person;
        if (command == "AddNewTasks") {
            cin >> num;
            while (num--)
                tasks.AddNewTask(person);
            cout << "[]" << endl;
        } 
        else if (command == "PerformPersonTasks") {
            cin >> num;
            TasksInfo updated_tasks, untouched_tasks;
            tie(updated_tasks, untouched_tasks) =
                    tasks.PerformPersonTasks(person, num);
            cout << vector<TasksInfo>{updated_tasks, untouched_tasks } << endl;
        } 
        else if (command == "GetPersonTasksInfo") {
            cout << tasks.GetPersonTasksInfo(person) << endl;
        } 
        else if (command.size() && command[0] != '#'){
            throw invalid_argument("wrong command: " + command);
        }
    }
}