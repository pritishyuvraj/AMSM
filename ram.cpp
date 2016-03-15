#include<iostream>
#include<sys/sysinfo.h>
#include<fstream>
using namespace std;

int main(){
	struct sysinfo p;
	unsigned long total;

ofstream myfile;
myfile.open("temp2.txt",ios::trunc);

	if (sysinfo(&p) != 0){
	    cout<<"sysinfo: error reading system statistics";
		}
	else {
	
		//	cout<<"Total Ram\t"<<p.totalram/1024/1024<<" MB"<<endl;
			myfile<<"("<<p.totalram/1024/1024<<"%";
		//	cout<<"Free Ram\t"<<p.freeram/1024/1024<<" MB"<<endl;
		myfile<<p.freeram/1024/1024<<"%";
		//	cout<<"Shared Ram\t"<<p.sharedram<<endl;
			myfile<<p.sharedram<<"%";
		//	cout<<"No of Procs\t"<<p.procs<<endl;
			myfile<<p.procs<<"%";
		//	cout<<"Avg Load on Ram\t"<<p.loads[2]<<endl;	
			myfile<<p.loads[0];
		}
	return 0;
}	
