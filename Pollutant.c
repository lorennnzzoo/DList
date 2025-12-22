#include <stdio.h>
#include "Pollutant.h"
#include "stdlib.h"
#include "DList.h"

void access_element(void* element)
{
	Pollutant* pollutant=(Pollutant*)element;
	printf("pollutant com type : %zu\n",pollutant->communication_type);
}
int main(){
	DList* p_list=Initialize(sizeof(Pollutant));

	//create pollutants for com,tcp,udp
	Pollutant com_pollutant=create_com_pollutant(9600,NONE,1,8);
	Pollutant tcp_pollutant=create_tcp_pollutant("192.168.1.23",502);
	Pollutant udp_pollutant=create_udp_pollutant("192.168.1.23");


	//append pollutants to p_list
	Append(p_list,&com_pollutant);
	Append(p_list,&tcp_pollutant);
	Append(p_list,&udp_pollutant);

	if(Serialize(p_list,"DList.bin")!=0)
	{
		printf("Unable to serialize the DList");
	}

	// ForEach(p_list,*access_element);
	Delete(&p_list);
	DList* p2_list=Deserialize("DList.bin");
	if(p2_list==NULL)
	{
		printf("Unable to deserialize the DList");
	}
	else
	{
		ForEach(p2_list,&access_element);
	}




}


Pollutant create_com_pollutant(size_t baudrate,char* parity, size_t stop_bits,size_t data_bits){
	ComInfo comport_information;
	comport_information.baudrate=baudrate;
	comport_information.parity=parity;
	comport_information.stop_bits=stop_bits;
	comport_information.data_bits=data_bits;

	Pollutant pollutant;
	pollutant.communication_type=COM;
	pollutant.Connection.comport_information=comport_information;

	return pollutant;
}

Pollutant create_tcp_pollutant(char* ip_address,size_t port){
	TcpInfo tcp_information;
	tcp_information.ip_address=ip_address;
	tcp_information.port=port;


	Pollutant pollutant;
	pollutant.communication_type=TCP;
	pollutant.Connection.tcp_information=tcp_information;

	return pollutant;
}
Pollutant create_udp_pollutant(char* ip_address){
	UdpInfo udp_information;
	udp_information.ip_address=ip_address;


	Pollutant pollutant;
	pollutant.communication_type=UDP;
	pollutant.Connection.udp_information=udp_information;

	return pollutant;
}
