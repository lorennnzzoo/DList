#include <stdio.h>
#include "Pollutant.h"
#include "DList.h"
#include <unistd.h>

int main()
{

	DList* p_list=Initialize(sizeof(Pollutant));

	//create pollutants for com,tcp,udp
	Pollutant tcp_pollutant=create_tcp_pollutant("192.168.1.23",502,2,0,FLOAT,BADC);
	Pollutant tcp_pollutant2=create_tcp_pollutant("192.168.1.23",502,2,0,FLOAT,BADC);
	Pollutant tcp_pollutant3=create_tcp_pollutant("192.168.1.23",502,2,0,FLOAT,BADC);
	Pollutant tcp_pollutant4=create_tcp_pollutant("192.168.1.23",502,2,0,FLOAT,BADC);


	//append pollutants to p_list
	Append(p_list,&tcp_pollutant);
	Append(p_list,&tcp_pollutant2);
	Append(p_list,&tcp_pollutant3);
	Append(p_list,&tcp_pollutant4);

	while(1)
	{
		Run(p_list);
		sleep(5);
	}
	Delete(&p_list);
}
