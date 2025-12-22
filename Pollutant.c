#include <modbus.h>
#include <stdio.h>
#include "Pollutant.h"
#include "DList.h"

void read_modbus_rtu(Pollutant* element)
{
	uint16_t tab_reg[8];

	ComInfo cominfo=element->Connection.comport_information;
	modbus_t* mb=modbus_new_rtu(cominfo.comport,cominfo.baudrate,cominfo.parity,cominfo.data_bits,cominfo.stop_bits);
	if(mb==NULL)
	{
		printf("unable to create modbus rtu instance\n");
		return;
	}

	if(modbus_set_slave(mb,cominfo.slaveid)==-1)
	{
		printf("Unable to set slave id \n");
		goto error;
	}

	if(modbus_connect(mb)==-1)
	{
		printf("rtu connection failed\n");
		goto error;
	}
	int rc=modbus_read_input_registers(mb,cominfo.address,8,tab_reg);
	if(rc==-1)
	{
		printf("unable to read\n");
		goto error;
	}

	for(int i=0;i<rc;i++)
	{
		printf("reg[%d] = %d\n",i+cominfo.address,tab_reg[i]);
	}

error:

	modbus_close(mb);
	modbus_free(mb);
}
void read_modbus_tcp(Pollutant* element)
{
	uint16_t tab_reg[8];

	TcpInfo tcpinfo=element->Connection.tcp_information;
	modbus_t* mb=modbus_new_tcp(tcpinfo.ip_address,tcpinfo.port);
	if(mb==NULL)
	{
		printf("unable to create modbus tcp instance\n");
		return;
	}

	if(modbus_set_slave(mb,tcpinfo.slaveid)==-1)
	{
		printf("Unable to set slave id \n");
		goto error;
	}

	if(modbus_connect(mb)==-1)
	{
		printf("tcp connection failed\n");
		goto error;
	}
	int rc=modbus_read_input_registers(mb,tcpinfo.address,8,tab_reg);
	if(rc==-1)
	{
		printf("unable to read\n");
		goto error;
	}

	for(int i=0;i<rc;i++)
	{
		printf("reg[%d] = %d\n",i+tcpinfo.address,tab_reg[i]);
	}

error:

	modbus_close(mb);
	modbus_free(mb);
}

void access_element(void* element)
{
	Pollutant* pollutant=(Pollutant*)element;
	if(pollutant->communication_type==TCP)
	{
		read_modbus_tcp(pollutant);
	}
	else if(pollutant->communication_type==COM)
	{
		read_modbus_rtu(pollutant);
	}
}
int main(){
	DList* p_list=Initialize(sizeof(Pollutant));

	//create pollutants for com,tcp,udp
	Pollutant com_pollutant=create_com_pollutant("/dev/ttyAMA1",9600,NONE,1,8,1,31);
	Pollutant tcp_pollutant=create_tcp_pollutant("45.8.248.56",502,10,31);


	//append pollutants to p_list
	Append(p_list,&tcp_pollutant);
	Append(p_list,&com_pollutant);

	ForEach(p_list,&access_element);

	Delete(&p_list);



}


Pollutant create_com_pollutant(char* comport,size_t baudrate,char parity, size_t stop_bits,size_t data_bits,uint8_t slaveid,uint16_t address){
	ComInfo comport_information;
	comport_information.baudrate=baudrate;
	comport_information.parity=parity;
	comport_information.stop_bits=stop_bits;
	comport_information.data_bits=data_bits;
	comport_information.slaveid=slaveid;
	comport_information.address=address;
	comport_information.comport=comport;

	Pollutant pollutant;
	pollutant.communication_type=COM;
	pollutant.Connection.comport_information=comport_information;

	return pollutant;
}

Pollutant create_tcp_pollutant(char* ip_address,size_t port,uint8_t slaveid,uint16_t address){
	TcpInfo tcp_information;
	tcp_information.ip_address=ip_address;
	tcp_information.port=port;
	tcp_information.slaveid=slaveid;
	tcp_information.address=address;


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
