#include <string>
#include <fstream>
#include <queue>
using namespace std;
#include <music/combine.h>

string combine::do_combine(string file1,string file2,string dest)
{
	ifstream in1,in2;
	int timer1,timer2,prev;
	prev=timer1=timer2=0;
	ofstream out;
	out.open(dest.c_str(),ios::trunc|ios::binary|ios::out);
	in1.open(file1.c_str(),ios::binary);
	in2.open(file2.c_str(),ios::binary);
	char* tmp1=(char*)malloc(sizeof(monoRecord));
	char* tmp2=(char*)malloc(sizeof(monoRecord));
	in1.read(tmp1,sizeof(monoRecord));
	in2.read(tmp2,sizeof(monoRecord));
	monoRecord* record1=reinterpret_cast<monoRecord*>(tmp1);
	monoRecord* record2=reinterpret_cast<monoRecord*>(tmp2);
		timer1+=record1->interval;
		timer2+=record2->interval;

	while(!in1.eof()&&!in2.eof())
	{
		record1=reinterpret_cast<monoRecord*>(tmp1);
		record2=reinterpret_cast<monoRecord*>(tmp2);
		
		if(timer1 <= timer2)
		{
			record1->interval=timer1-prev;
			prev=timer1;
			out.write(reinterpret_cast<char*>(record1),sizeof(monoRecord));
			in1.read(tmp1,sizeof(monoRecord));
			timer1+=record1->interval;
			continue;
		}
		else
		{
			record2->interval=timer2-prev;
			prev=timer2;
			out.write(reinterpret_cast<char*>(record2),sizeof(monoRecord));
			in2.read(tmp2,sizeof(monoRecord));
			timer2+=record2->interval;
			continue;
		}
	}
	if(in1.eof())//2µÄÊ£Óà²¿·Ö
	{
			char* tmp=(char*)malloc(sizeof(monoRecord));

			while(!in2.eof())
			{
				in2.read(tmp,sizeof(monoRecord));
				
				monoRecord* record=reinterpret_cast<monoRecord*>(tmp);
				out.write(reinterpret_cast<char*>(record),sizeof(monoRecord));
			}
	}
	else
	{
			char* tmp=(char*)malloc(sizeof(monoRecord));

			while(!in1.eof())
			{
				in1.read(tmp,sizeof(monoRecord));
				
				monoRecord* record=reinterpret_cast<monoRecord*>(tmp);
				out.write(reinterpret_cast<char*>(record),sizeof(monoRecord));
			}
	}
	out.close();
	return dest;
}