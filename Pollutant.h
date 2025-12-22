#ifndef POLLUTANT_H
#define POLLUTANT_H

#define NONE "NONE"
#define ODD "ODD"
#define EVEN "EVEN"
#define COM 1
#define TCP 2
#define UDP 3
typedef struct{
	size_t baudrate;
	char* parity;
	size_t stop_bits;
	size_t data_bits;
} ComInfo;

typedef struct{
	char* ip_address;
	size_t port;
} TcpInfo;

typedef struct{
	char* ip_address;
} UdpInfo;

typedef struct{
	///1= COM
	///2= TCP
	///3= UDP
	size_t communication_type;
	union{
		ComInfo comport_information;
		TcpInfo tcp_information;
		UdpInfo udp_information;
	} Connection;
} Pollutant;

Pollutant create_com_pollutant(size_t baudrate,char* parity, size_t stopbits,size_t data_bits);
Pollutant create_tcp_pollutant(char* ip_address,size_t port);
Pollutant create_udp_pollutant(char* ip_address);

#endif
