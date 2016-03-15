#include<iostream>
#include<libusb-1.0/libusb.h>
#include<map>
#include<fstream>
using namespace std;

map<string,int> usb_device;
map<string,int> unrecognized;

int count;
int unrec;
void printdev(libusb_device *dev){
	libusb_device_descriptor desc;
	int r=libusb_get_device_descriptor(dev,&desc);
	if(r<0){
		cout<<"failed to get device descriptor"<<endl;
		return;
	}
	
	libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev,0,&config);
		
	//cout<<"\nInterfaces"<<(int)config->bNumInterfaces<<endl;

	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;

	for(int i=0;i<(int)config->bNumInterfaces;i++){
		inter=&config->interface[i];
		//cout<<"\nNo of alternate settings:\t"<<inter->num_altsettings<<endl;
		//for(int j=0;j<inter->num_altsetting;j++){
			interdesc=&inter->altsetting[i];
			 if((int)interdesc->bInterfaceClass==3&&(int)interdesc->bInterfaceProtocol==2){
				usb_device.insert(pair<string,int>("Mouse",inter->num_altsetting));
				count++;
			}
			 else if((int)interdesc->bInterfaceClass==3&&(int)interdesc->bInterfaceProtocol==1){			
				usb_device.insert(pair<string,int>("KeyBoard",inter->num_altsetting));
				count++;
			}
			 else if((int)interdesc->bInterfaceClass==8&&(int)interdesc->bInterfaceProtocol==80){			
				usb_device.insert(pair<string,int>("Pendrive",inter->num_altsetting));
				count++;
			}
			 else if((int)interdesc->bInterfaceClass==3&&(int)interdesc->bInterfaceProtocol==4){
				usb_device.insert(pair<string,int>("Scanner",inter->num_altsetting));	
				count++;
			}
			else{		
				unrecognized.insert(pair<string,int>("UnrecognizedDevice",inter->num_altsetting));
				unrec++;
			}
			
		//}
	
	}
libusb_free_config_descriptor(config);
}
			
void display(){

//
ofstream myfile;
	
	myfile.open("temp2.txt",ios::trunc);

	
	
//
map<string,int>::iterator p;
p=usb_device.begin();
//cout<<"\nTotal no of recognized devices are:\t"<<count<<"\nNo of unrecognized devices are\t:"<<unrec;
//cout<<"\nAlternate Settings"<<"\tDevice\n";
myfile<<"*";
	while(p!=usb_device.end()){
//		cout<<p->second<<"\t\t\t";		
		//cout<<p->first<<" ";
		string abc(p->first);
			myfile<<abc;
			myfile<<"%";
		p++;
	}

myfile.close();

}



int main(){	
	libusb_device **devs;
	libusb_context *ctx=NULL;
	int r;
	ssize_t cnt;
	r=libusb_init(&ctx);
	
	if(r<0){
		cout<<"\nInitialization Error"<<r<<endl;
		return 1;
	}
	
	libusb_set_debug(ctx,3);
	cnt=libusb_get_device_list(ctx,&devs);
	
	if(cnt<0){
		cout<<"\nGet device Error"<<endl;
	}
		
//	cout<<cnt<<"\tDevices in the list"<<endl;
	ssize_t i;
	
	for(i=0;i<cnt;i++){
		printdev(devs[i]);
	}
	
	libusb_free_device_list(devs,1);
	libusb_exit(ctx);
display();
	cout<<endl<<endl;
	return 0;
}


