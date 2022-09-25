#include <iostream>
#include <fstream>
#include <regex>
#include <utility>
using namespace std;


class regexValue{
public:
    const regex regFrom = regex("[\\s\\S]+from=<(.*@.*)>[\\s\\S]+");
    const regex reTo = regex("[\\s\\S]+to=<(.*)>.*status=([a-z]+).*");
    const regex time = regex("([\\s\\S]+[0-9][0-9]:[0-9][0-9]:[0-9][0-9])[\\s\\S]+");
    regex getFrom(){
        return regFrom;
    }
    regex getTo(){
        return reTo;
    }
    regex getTime(){
        return time;
    }
};


class Value{
private:
    string fromUser;
    string toUser;
    string status;
    string time;
public:
    Value(string From, string To, string Status ): fromUser(std::move(From)), toUser(std::move(To)), status(std::move(Status)){};
    void setFromUser(string str){
        this->fromUser = std::move(str);
    }
    void setToUser(string str){
        this->toUser = std::move(str);
    }
    void setStatus(string str){
        this->status = std::move(str);
    }
    void setTime(string str){
        this->time = std::move(str);
    }
    string getFromUser(){
        return this->fromUser;
    }
    string getToUser(){
        return this->toUser;
    }
    string getStatus(){
        return this->status;
    }
    string getTime(){
        return this->time;
    }
};


bool matchValue(Value* value, string& input, regexValue regValus){

    //getline(cin, input);
    smatch sms;

    if( regex_match(input, sms, regValus.getTime()) ){
        //   cout << "Match!" << endl;
        int i=0;
        //  cout << "The matches are:\n";
        for(string sm:sms ){

           // cout << sm << endl;
            if(i==1) {
               // cout << sm << endl;
                value->setTime(sm);
            }
            i++;
        }
         //cout <<  value->getFromUser();
    }

    if( regex_match(input, sms, regValus.getFrom()) ){
     //   cout << "Match!" << endl;
        int i=0;
      //  cout << "The matches are:\n";
        for(string sm:sms ){
            i++;
            if(i==2) {
             //   cout << sm << endl;
                value->setFromUser(sm);
            }
        }
       // cout <<  value->getFromUser();
    }
    if( regex_match(input, sms, regValus.getTo()) ){
   //     cout << "Match!" << endl;

        int i=0;
    //    cout << "The matches are:\n";
        for(string sm:sms ){
            i++;
            if(i==2) {
           //     cout << sm << endl;
                value->setToUser(sm);
            }
            if(i==3){
                value->setStatus(sm);
            }
        }

        // cout <<  value->getFromUser();
        return true;
    }
    else{
       // cout << "to Not Match!" << endl;
    }
   // cout << "Not Match!" << endl;
    return false;
}


int main() {
    Value object{"","",""};
    string input;
    ifstream myfile("mail.log");
    if(myfile.is_open()){
        while (getline(myfile,input)){
            regexValue regObject;
            if(matchValue(&object, input, regObject)){
                cout << "time: " <<object.getTime();
                cout << " from: " << object.getFromUser();
                cout << " user: " << object.getToUser();
                cout << " status: " << object.getStatus() <<endl;
            }
        }
    }
    return 0;
}
