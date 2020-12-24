#include <iostream>

using namespace std;



void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}


class INotifier {
public:
    INotifier() {}
    virtual void Notify(const string &message) = 0;
};

class SmsNotifier: public INotifier {
    string number;
public:
    SmsNotifier(const std::string &_number): number(_number) {} 
    void Notify(const string &message){
        SendSms(number, message);
    }
    
};

class EmailNotifier: public INotifier {
    string addr;
public:
    EmailNotifier(const std::string &_addr): addr(_addr) {} 
    void Notify(const string &message){
        SendEmail(addr, message);
    }
    
};

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}


int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}