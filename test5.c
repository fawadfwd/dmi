#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#include <fcntl.h> 

#include <string.h>

#include <stdlib.h>

#include <stdint.h>

struct structure
{
	uint8_t type;
	uint8_t length;
	uint16_t handle;
};


int count=0;

#define WORD(x) (uint16_t)((x)[0] + ((x)[1] << 8))

static void dmi_slot_segment_bus_func(uint16_t code1, uint8_t code2, uint8_t code3)
{
	/* 7.10.8 */
	if (!(code1 == 0xFFFF && code2 == 0xFF && code3 == 0xFF))
		printf("Bus Address %04x:%02x:%02x.%x\n",
			code1, code2, code3 >> 3, code3 & 0x7);
}
//dmidecode -t 9 | grep "desig | type 9" 
void process_dmi(char *arr,long n,struct structure *my)
{

	int i=0;
	while(i<n)
	{
		struct structure *m=(struct structure *)&arr[i];
		i=i+m->length;
		int j=i;
		if(m->type==9)
		{
		
			char *test1=(char *)m;
			printf("__________________________________________________\n");
			//printf("~~~%d\n",i);
			int j=0;
			int p1=m->length+1000;
			int k=0;

			while(j<(p1))
			{
				if(test1[j]==0 && test1[j+1]==0 && k>17)
				{
					printf("\n");
					k=0;
				}	
				printf("~%x ",test1[j]&0x0F);
				j++;
				k++;
			}
			exit(0);
			//printf("\n");
			//printf("type %d\n",m->type);

			//printf("handle %x\n",m->handle);
			//////printf("length %d\n",m->length);
			//////printf("slot %x\n",arr[i+4]&0b11111111);
			//////printf("slot type %x\n",arr[i+5]&0b11111111);
			//////printf("bus %x\n",arr[i+15]&0b11111111);
			//printf("function %x\n",arr[i+16]&0b11111111);
			//////printf("segment %x\n",arr[i+14]&0b1111111111111111);
			//printf("+%x %x+ \n",arr[i+13]&0b11111111,(arr[i+14]&0b11111111));
			
			char x=0x08;
			
			//////printf("@%d\n",x&0b00001000);

			//////printf("device number %x\n",arr[i+16]&0b00000111);
			//////printf("function number%x\n",arr[i+16]&0b11111000);			
			count++;
	
		}
	
		//printf("%x\n",arr[i]&0b11111111);
		
		while(*(arr+j)!=0 || *(arr+j+1)!=0)
		{
		
			j++;
		}
		
		if(j>i)
		{
			i=j+2;
			//printf("%x\n",arr[i]&0b11111111);
			//exit(0);
		}
		else				
		i++;


		//printf("type %d\n",m->type);
		
		

		
	}
	printf("(( %d ))\n",count);
	
}
#define PCI_DEVFN(slot, func)	((((slot) & 0x1f) << 3) | ((func) & 0x07))
#define PCI_FUNC(devfn)		((devfn) & 0x07)
#define PCI_SLOT(devfn)		(((devfn) >> 3) & 0x1f)
int main()
{


	struct stat stats;
	/*if (stat("/sys/firmware/dmi/tables/smbios_entry_point", &stats) == 0)
	{

		printf("%ld\n",stats.st_size);
		//printFileProperties(stats);
	}*/
	int fd=open("/sys/firmware/dmi/tables/smbios_entry_point",O_RDONLY);
	//int fd=open("/dev/mychardev-0",O_RDONLY);
	if(fd<=0)
	{	
		printf("fd  %d %d\n",fd,errno);
		exit(0);

	}

	char *buffer=malloc(sizeof(char )*1000);
	int x=read(fd,buffer,1000);
	if(x<0)
	exit(0);
	printf("struct SMBIOS entry point\n");
	//printf("+-_%d______________________________\n",x);

		
	int j=0;
	
	while(j<100)
	{
		if(buffer[j]=='_' && buffer[j+1]=='S' && buffer[j+2]=='M' && buffer[j+3]=='_')
		{
			printf("~%d\n",j);
			//buffer=buffer+5;
			int i=j;
			int k=0;	
			while(i<31)
			{			
				//printf("%x\n",buffer[i]&(0b11111111));
              			i++;
			}
			
			//break;
		}
		
		j++;
	}
	printf("~~~~~~~devfn = ~%x\n",PCI_DEVFN(2,3));
	printf("~~~~~~~devfn = ~%x\n",PCI_DEVFN(3,3));
	printf("~~~~~~~devfn = ~%x\n",PCI_DEVFN(1,3));
	printf("~~~~~~~devfn = ~%x\n",PCI_DEVFN(5,3));

	int k=0;

	//printf("+__________________________________________________\n");
	struct stat stats_dmi;
	int ret=0;
	if ((ret=stat("/sys/firmware/dmi/tables/DMI", &stats_dmi)) == 0)
	{

		printf("DMI size %ld\n",stats_dmi.st_size);
		//printFileProperties(stats);
	}
	else
	{
		printf("ret = %d\n",ret);
	}
	

	int fd_dmi=open("/sys/firmware/dmi/tables/DMI",O_RDONLY);
	if(fd_dmi<=0)
	{	
		printf("fd  %d %d\n",fd_dmi,errno);
		exit(0);

	}


	char *buffer_dmi=malloc(sizeof(char )*stats_dmi.st_size);
	read(fd_dmi,buffer_dmi,stats_dmi.st_size+1);
	
	printf("struct DMI entry point\n");
	//printf("+_______________________________\n");
	for(int i=0;i<stats_dmi.st_size;i++)
	{
		
		//printf("%x\n",buffer_dmi[i]&0b11111111);
		
		
	}
	struct structure *my_struct;
	process_dmi(buffer_dmi,stats_dmi.st_size,my_struct);



	


	




	return 0;
}

