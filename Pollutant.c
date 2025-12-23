#include <modbus.h>
#include <stdio.h>
#include "Pollutant.h"
#include "DList.h"

void read_modbus_rtu(Pollutant* element)
{
	uint16_t tab_reg[REG32];

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
	int rc=modbus_read_input_registers(mb,cominfo.address,REG32,tab_reg);
	if(rc==-1)
	{
		printf("unable to read\n");
		goto error;
	}

	float value;
	switch(element->type_settings.byte_order)
	{
		case ABCD:
			value=modbus_get_float_abcd(tab_reg);
			break;
		case BADC:
			value=modbus_get_float_badc(tab_reg);
			break;
		case CDAB:
			value=modbus_get_float_cdab(tab_reg);
			break;
		case DCBA:
			value=modbus_get_float_dcba(tab_reg);
			break;
	}
	printf("value generated : %f\n",value);
error:

	modbus_close(mb);
	modbus_free(mb);
}
void read_modbus_tcp(Pollutant* element)
{
	uint16_t tab_reg[REG32];

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
	int rc=modbus_read_input_registers(mb,tcpinfo.address,REG32,tab_reg);
	if(rc==-1)
	{
		printf("unable to read\n");
		goto error;
	}

	float value;
	switch(element->type_settings.byte_order)
	{
		case ABCD:
			value=modbus_get_float_abcd(tab_reg);
			break;
		case BADC:
			value=modbus_get_float_badc(tab_reg);
			break;
		case CDAB:
			value=modbus_get_float_cdab(tab_reg);
			break;
		case DCBA:
			value=modbus_get_float_dcba(tab_reg);
			break;
	}
	printf("value generated : %f\n",value);

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
void Run(DList* p_list){
	ForEach(p_list,&access_element);
}


Pollutant create_com_pollutant(char* comport,size_t baudrate,char parity, size_t stop_bits,size_t data_bits,uint8_t slaveid,uint16_t address,char* datatype,enum ByteOrder byte_order){
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

	DataTypeSettings typesettings;
	typesettings.type=datatype;
	typesettings.byte_order=byte_order;

	pollutant.type_settings=typesettings;

	return pollutant;
}

Pollutant create_tcp_pollutant(char* ip_address,size_t port,uint8_t slaveid,uint16_t address,char* datatype,enum ByteOrder byte_order){
	TcpInfo tcp_information;
	tcp_information.ip_address=ip_address;
	tcp_information.port=port;
	tcp_information.slaveid=slaveid;
	tcp_information.address=address;


	Pollutant pollutant;
	pollutant.communication_type=TCP;
	pollutant.Connection.tcp_information=tcp_information;

	DataTypeSettings typesettings;
	typesettings.type=datatype;
	typesettings.byte_order=byte_order;

	pollutant.type_settings=typesettings;


	return pollutant;
}
// Pollutant create_udp_pollutant(char* ip_address){
// 	UdpInfo udp_information;
// 	udp_information.ip_address=ip_address;
//
//
// 	Pollutant pollutant;
// 	pollutant.communication_type=UDP;
// 	pollutant.Connection.udp_information=udp_information;
//
// 	return pollutant;
// }
