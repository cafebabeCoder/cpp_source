#include <iostream>
#include <string>
#include "student.pb.h"
#include <unordered_map>
using namespace std;

int main(int argc, char* argv[]){
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	tutorial::Student student;
	// student.set_id(201421031059);
	// cout<<student.id()<<endl;
	cout<<"---"<<student.phone_size()<<"---"<<endl;
	cout<<"---"<<student.id()<<"---"<<endl;
	cout<<"---"<<student.name()<<"---"<<endl;
	tutorial::Student::PhoneNumber* pn = student.add_phone();
	// auto s =  student.mutable_phone(0)->mutable_number();
	auto s =  student.phone(0).ip().s_size();
	cout<<"---"<<s<<"---"<<endl;

	// std::unordered_map<int, string> optimal_rule4pos; //
	// if(!optimal_rule4pos)
	// 	cout<<"------"<<endl;
	// else
	// 	cout<<"---"<<endl;
	


}