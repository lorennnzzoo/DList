#ifndef POLLUTANT_H
#define POLLUTANT_H

#define REG32 2
#define REG64 4
#define NONE 'N'
#define ODD 'O'
#define EVEN 'E'
#define COM 1
#define TCP 2
#define UDP 3


#define INT16 "INT16"
#define INT32 "INT32"
#define INT64 "INT64"
#define UINT16 "UINT16"
#define UINT32 "UINT32"
#define UINT64 "UINT64"

#define FLOAT "FLOAT"
// #define DOUBLE "DOUBLE"

enum ByteOrder{
	ABCD,
	BADC,
	CDAB,
	DCBA,
};

typedef struct{
	char* type;
	enum ByteOrder byte_order;
} DataTypeSettings;

typedef struct{
	uint8_t slaveid;
	uint16_t address;
	size_t baudrate;
	char parity;
	size_t stop_bits;
	size_t data_bits;
	char* comport;
} ComInfo;

typedef struct{
	uint8_t slaveid;
	uint16_t address;
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
	DataTypeSettings type_settings;
} Pollutant;

Pollutant create_com_pollutant(char* comport,size_t baudrate,char parity, size_t stopbits,size_t data_bits,uint8_t slaveid,uint16_t address,char* datatype,enum ByteOrder byte_order);
Pollutant create_tcp_pollutant(char* ip_address,size_t port,uint8_t slaveid,uint16_t address,char* datatype,enum ByteOrder byte_order);
// Pollutant create_udp_pollutant(char* ip_address,char* datatype,char* byte_order);

#endif
