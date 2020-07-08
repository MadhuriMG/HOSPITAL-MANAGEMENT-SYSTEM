#include<stdio.h>
#include<conio.h>
#include<iomanip.h>
#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<dir.h>
#include<bios.h>
#include<dos.h>
#define datafile "dafile1.txt"
#define indexfile "infile1.txt"
#define sindexfile "sinfile1.txt"
void screen();
void normal();
void screen1();
fstream stdfile,indfile,sindfile,lfile;
int i,indsize,sindsize,lsize;
char buffer[100],skey[20];

void opener(fstream &file,char *fn,int mode)
{
	file.open(fn,mode);
	if(!file)
	{
		printf("file doesn't exist\n");
		getch();
		exit(1);
	}
}

class patient
{
	char PID[10],CONTACT[15],ADDRESS[15],SEX[8],PNAME[20],DCT[15];
	public:void read();
	       void pack();
	       friend int search(char *);
	       void remove();
	       void datadisp();
	       void indexdisplay(int );
	       void unpack();
	       void modify();

}m;

class index
{
	public:char mid[10],addr[5];
	       void initial();
	       void write();
}id[50],in;

class sindex
{
	public:char sPNAME[20],smid[10];
	       void sinitial();
	       void swrite();
}sid[50],sin;

void index::initial()
{
	indfile.open(indexfile,ios::in);
	if(!indfile)
	{
		indsize=0;
		return;
	}
	for(indsize=0;;indsize++)
	{
		indfile.getline(id[indsize].mid,10,'|');
		indfile.getline(id[indsize].addr,5,'\n');
		if(indfile.eof())
		break;
	}
	indfile.close();
}

void sindex::sinitial()
{
	sindfile.open(sindexfile,ios::in);
	if(!sindfile)
	{
		sindsize=0;
		return;
	}
	for(sindsize=0;;sindsize++)
	{
		sindfile.getline(sid[sindsize].sPNAME,20,'|');
		sindfile.getline(sid[sindsize].smid,10,'\n');
		if(sindfile.eof())
		break;
	}
	sindfile.close();
}


void index::write()
{
	opener(indfile,indexfile,ios::out);
	for(i=0;i<indsize;i++)
		indfile<<id[i].mid<<'|'<<id[i].addr<<"\n";

}

void sindex::swrite()
{
	opener(sindfile,sindexfile,ios::out);
	for(i=0;i<sindsize;i++)
		sindfile<<sid[i].sPNAME<<'|'<<sid[i].smid<<"\n";

}

void patient::read()
{

	int k;
	clrscr();
	cout<<"\n\n"<<"\t\t.....Enter patient records...\n";

	cout<<"\t\t"<<"enter patient id\t:";
	gets(PID);
	if(search(PID)>=0)
	{
		cout<<"PATIENT ID IS ALREADY PRESENT!!!!\n";
		delay(1500);
		return;
	}
	for(i=indsize;i>0;i--)
	{
		if(strcmp(PID,id[i-1].mid)<0)
		id[i]=id[i-1];
		else
		break;
	}
	opener(stdfile,datafile,ios::app);
	cout<<"\n"<<"\t\t"<<"enter PNAME\t:";
	gets(PNAME);
	cout<<"\n"<<"\t\t"<<"enter ADDRESS\t:";
	gets(ADDRESS);
	cout<<"\n"<<"\t\t"<<"enter SEX\t:";
	gets(SEX);
	cout<<"\n"<<"\t\t"<<"enter CONTACT NO\t:";
	gets(CONTACT);
	cout<<"\n"<<"\t\t"<<"enter the CON_DCT\t:";
	gets(DCT);

	pack();

	stdfile.seekg(0,ios::end);
	k=stdfile.tellg();
	stdfile<<buffer<<endl;
	strcpy(id[i].mid,PID);
	itoa(k,id[i].addr,10);
	indsize++;
	for(i=sindsize;i>0;i--)
	{
		if(strcmp(PNAME,sid[i-1].sPNAME)<0)
			sid[i]=sid[i-1];
		else if((strcmp(PNAME,sid[i-1].sPNAME)==0)&&(strcmp(PID,sid[i-1].smid)<0))
			sid[i]=sid[i-1];
		else
			break;
	}
	strcpy(sid[i].sPNAME,PNAME);
	strcpy(sid[i].smid,PID);
	sindsize++;

}

void patient::pack()
{
	strcpy(buffer,PID);strcat(buffer,"|");
	strcat(buffer,PNAME);strcat(buffer,"|");
	strcat(buffer,ADDRESS);strcat(buffer,"|");
	strcat(buffer,SEX);strcat(buffer,"|");
	strcat(buffer,CONTACT);strcat(buffer,"|");
	strcat(buffer,DCT);strcat(buffer,"|");
}

int search(char *fid)
{
	int low=0,high=indsize-1;
	int middle;
	while(low<=high)
	{
		middle=(low+high)/2;
		if(strcmp(fid,id[middle].mid)==0)
			return  middle;
		else if(strcmp(fid,id[middle].mid)>0)
			low=middle+1;
		else
			high=middle-1;
	}
	return -1;
}

int sec_search()
{
	int pos,j,flag=-1,count=0;
	cout<<"\n\t\tENTER THE PNAME ....... :\t";
	gets(skey);
	clrscr();
	cout<<setiosflags(ios::left);
	cout<<"\n"<<"\t\tTHE SEARCHED RECORD DETAILS ARE...:";
	cout<<"\n"<<"\t\t"<<"SL NO."<<"\t\t"<<setw(15)<<"PATIENT ID"<<setw(15)<<"NAME"<<endl;
	opener(stdfile,datafile,ios::in|ios::out);
	for(j=0;j<sindsize;j++)
	if(strcmp(skey,sid[j].sPNAME)==0)
	{
		count=count+1;
		cout<<"\n"<<"\t\t"<<count<<"\t\t"<<setw(15)<<sid[j].smid<<setw(15)<<sid[j].sPNAME<<endl;
		flag=j;
	}

	return flag;

}

void patient::remove()
{
	char rmid[10];
	int pos,spos;
	cout<<"\nENTER THE PATIENT ID LISTED ABOVE TO DELETE..:\t";
	cin>>rmid;
	for(i=0;i<sindsize;i++)
	{
	       if(strcmp(sid[i].smid,rmid)==0)
		{
			spos=i;
			break;
		}
	}
	if(strcmp(sid[spos].sPNAME,skey)==0)
	{
		pos=search(rmid);
		stdfile.seekp(atoi(id[pos].addr),ios::beg);
		stdfile.put('$');
		for(i=pos;i<indsize;i++)
		id[i]=id[i+1];
		indsize--;
		for(i=spos;i<sindsize;i++)
		sid[i]=sid[i+1];
		sindsize--;
		cout<<"\n\n\n"<<"RECORD DELETED SUCCESSFULLY\n";
	}
	else
	cout<<"\nPATIENT ID AND NAME DOES NOT MATCH\n";
}
void patient::datadisp()
{
	opener(stdfile,datafile,ios::in);
	stdfile.seekg(0,ios::beg);
	cout<<setiosflags(ios::left);
	clrscr();
	cout<<"\n";
	cout<<setw(10)<<"PATIENT ID"<<setw(15)<<"PNAME"<<setw(15)<<"ADDRESS"<<setw(8)<<"SEX"<<setw(13)<<"CONTACT"<<setw(13)<<"CON_DCT"<<endl;
	while(1)
	{
		unpack();
		if(stdfile.eof())
		break;
		if(PID[0]!='$')
		cout<<setw(10)<<PID<<setw(15)<<PNAME<<setw(15)<<ADDRESS<<setw(8)<<SEX<<setw(13)<<CONTACT<<setw(13)<<DCT<<endl;
		getch();
	}
}
void patient::indexdisplay(int pos)
{
	opener(stdfile,datafile,ios::in);
	stdfile.seekg(atoi(id[pos].addr),ios::beg);
	   clrscr();
	   cout<<endl<<endl<<endl;
	   cout<<setw(25)<<" "<<"DISPLAYING RECORDS"<<endl<<endl<<endl<<endl;

	   for(int i=0;i<80;i++)   cout<<'*';   cout<<endl<<endl<<endl;
	   unpack();
	   cout<<setw(20)<<" "<<" PATIENT ID  :  "<<PID<<endl<<endl<<endl;
	   cout<<setw(20)<<" "<<" PNAME  :  "<<PNAME<<endl<<endl<<endl;
	   cout<<setw(20)<<" "<<" ADDRESS      :  "<<ADDRESS<<endl<<endl<<endl;
	   cout<<setw(20)<<" "<<" SEX      :  "<<SEX<<endl<<endl<<endl;
	   cout<<setw(20)<<" "<<" CONTACT    :  "<<CONTACT<<endl<<endl<<endl<<endl;
	   for(i=0;i<80;i++) cout<<'*';
	   cout<<endl<<endl<<setw(39)<<" ";
	   getch();
    stdfile.clear();
    stdfile.close();
}
int secondary()
{
	int j,flag=-1;
	cout<<"\n\n"<<"\t\tENTER THE PNAME TO SEARCH :----->";
	gets(skey);
	cout<<"\n\t\t"<<skey<<":";
	opener(sindfile,sindexfile,ios::in);
	for(j=0;j<sindsize;j++)
	if(strcmp(skey,sid[j].sPNAME)==0)
	{
		cout<<sid[j].smid<<":";
		flag=j;
	}
	sindfile.close();
	return flag;

}

void patient::modify()
{
	int spos,i,flag;
	char key[15];
	cout<<"\nENTER THE PRIMARY KEY..:\t";
	cin>>key;
	flag=search(key);
	if(flag==-1)
	cout<<"NO RECORD FOUND..!!!";
	else
	{
	   opener(stdfile,datafile,ios::in|ios::out);
	   stdfile.seekp(atoi(id[flag].addr),ios::beg);
	    stdfile.put('$');
		for(i=flag;i<indsize;i++)
		id[i]=id[i+1];
		indsize--;
		for(i=0;i<sindsize;i++)
		if(strcmp(key,sid[i].smid)==0)
		{
			spos=i;
	break;
		}



		for(i=spos;i<sindsize;i++)
		sid[i]=sid[i+1];
		sindsize--;

		stdfile.close();

	}

}

void patient::unpack()
{
	char dummy[75];
	stdfile.getline(PID,10,'|');
	stdfile.getline(PNAME,15,'|');
	stdfile.getline(ADDRESS,15,'|');
	stdfile.getline(SEX,8,'|');
	stdfile.getline(CONTACT,15,'|');
	stdfile.getline(DCT,15,'|');
	stdfile.getline(dummy,75,'\n');

}
void drawdoublelinebox(int x,int y,int len,int bdt)
{
	gotoxy(x,y);


	cprintf("ษ");
		gotoxy(x,y+bdt);
	cprintf("ศ");
	gotoxy(x+len,y);
	cprintf("ป");
	gotoxy(x+len,y+bdt);
	cprintf("ผ");
	for(int i=x+1;i<x+len;i++)
	{
		gotoxy(i,y);
		cprintf("อ");
		gotoxy(i,y+bdt);
		cprintf("อ");
	}
	for(int j=y+1;j<y+bdt;j++)
	{
		gotoxy(x,j);
		cprintf("บ");
		gotoxy(x+len,j);
		cprintf("บ");
			}
}

/*Double box design*/

void drawsinglelinebox(int x,int y,int len,int bdt)
{                                            // (x,y) : co.ord. of 1st tip
	gotoxy(x,y);                         // len : length of box
	cprintf("ฺ");                        // bdt : breadth of box
	gotoxy(x,y+bdt);
	cprintf("ภ");
	gotoxy(x+len,y);
	cprintf("ฟ");
	gotoxy(x+len,y+bdt);
	cprintf("ู");

	for(int i=x+1;i<x+len;i++)
	{
		gotoxy(i,y);
		cprintf("ฤ");
		gotoxy(i,y+bdt);
		cprintf("ฤ");
	}
	for(int j=y+1;j<y+bdt;j++)
	{
		gotoxy(x,j);
		cprintf("ณ");
		gotoxy(x+len,j);
		cprintf("ณ");
	}
}



void main()
{
	int ch,flag,choice,a,pos,spos,cho;
	char key[15];
	in.initial();
	sin.sinitial();
	clrscr();
	do
	{
		 screen();

		cout<<"     PLEASE ENTER YOUR CHOICE [1-3]  :   ";
		cin>>ch;
		switch(ch)
		{
		case 1:do
			{
				clrscr();
				drawdoublelinebox(17,7,44,14);
				textcolor(WHITE);
				textbackground(LIGHTBLUE);
				clrscr();
				textbackground(WHITE);
				gotoxy(25,3);
				textcolor(YELLOW);
				cprintf("       PATIENT RECORDS       ");
				gotoxy(25,4);
				cprintf(" ออออออออออออออออออออออออออออ ");
				int z=19,q=10;
				textcolor(YELLOW);
				drawdoublelinebox(17,7,44,14);
				gotoxy(28,7);
				textbackground(RED);
				textcolor(YELLOW);
				cprintf("Û  M A I N    M E N U Û" );
				normal();
				textcolor(WHITE);
				gotoxy(z,q++);
				cout<<"1.>  INSERT";
				gotoxy(z,q++);
				cout<<"2.>  UPDATE";
				gotoxy(z,q++);
				cout<<"3.>  DISPLAY ALL";
				gotoxy(z,q++);
				cout<<"4.>  DELETE";
				gotoxy(z,q++);
				cout<<"5.>  QUIT";
				gotoxy(z,q++);
				gotoxy(z,q++);
				gotoxy(z,q++);
				cout<<"      ENTER YOUR CHOICE [1-5] :-->";
				cin>>choice;

				 switch(choice)
				{
					 case 1:m.read();
						in.write();
						sin.swrite();
						break;

					 case 2:clrscr();
						m.modify();
						m.read();
						in.write();
						sin.swrite();
						break;

					case 3: m.datadisp();
						break;

					case 4: clrscr();
						flag=sec_search();
						if(flag==-1)
						cout<<"NO RECORD FOUND..!!!";
						else
						{
							m.remove();

							in.write();
							sin.swrite();
						}
						break;

					case 5:clrscr();
						screen();
						break;

					default:break;
				}
					stdfile.close();
					indfile.close();
					sindfile.close();
		   }while(choice!=5);break;

		case 2:
			 //int g=19,h=10;

			do
			{
				screen1();
				cout<<"     PLEASE ENTER YOUR CHOICE [1-4]  : ";
				cin>>cho;

				switch(cho)
				{
					case 1:clrscr();

					label1:
						cout<<"\n\n\n"<<"Enter the Primary key: \t";
						cin>>key;
						a=search(key);
						if(a==-1)
						{
							gotoxy(25,40);
							cout<<"Record not found....!";}
							else
						{
							m.indexdisplay(a);
							cout<<"\n\n\nSuccessfull search......  :";
						}
						getch();
						break;



					case 2: clrscr();

						flag=sec_search();
						if(flag==-1)

						{
							gotoxy(25,40);
							cout<<"Record not found....!";
						}

						getch();
						break;



					case 3: clrscr();
						cout<<"\n"<<"\t\t\INVERTED LIST\n";
						flag=secondary();
						if(flag==-1)
						cout<<"N0 RECORD FOUND....!!!!\n";
						else
						{
							goto label1;
						}
						break;

					case 4: clrscr();
				}
				stdfile.close();
				indfile.close();
				sindfile.close();
			}while(cho!=4);
			screen();
			break;

		case 3:exit(0);

		default:break;
	}
		stdfile.close();
		indfile.close();
		sindfile.close();
	}while(ch!=3);
}

void screen()
{
 int g=19,h=10;

     textbackground(LIGHTCYAN);
     gotoxy(25,3);
     textcolor(BLACK);
     cprintf("      PATIENT RECORD DETAILS      ");
     gotoxy(25,4);
     cprintf(" =================================== ");
     drawdoublelinebox(17,7,44,14);
     gotoxy(28,7);
     textbackground(LIGHTBLUE);
	 textcolor(WHITE);
	 cprintf("Û  M A I N    M E N U Û" );
     normal();
     textcolor(WHITE);
     gotoxy(g,h++);
     cout<<"   þ PATIENT RECORD";
     gotoxy(g,h++);
     cout<<"   þ INDEXING";
     gotoxy(g,h++);
     cout<<"   þ EXIT";
     gotoxy(g,h++);
     gotoxy(g,h++);
     gotoxy(g,h++);
     normal();
}

void normal()  // to obtain normal background
{
	textattr(WHITE); // textattr sets text attributes for text-window functions
	textcolor(WHITE);// textcolor selects a new character color in text mode
	textbackground(BLACK);//textbackground selects a new text background color
	_setcursortype(_NORMALCURSOR); /* sets cursor ADDRESS to normal underscore
						 ADDRESS cursor  */
}

void screen1()
{
     int b,g=19,h=10;
     clrscr();
     textbackground(BLUE);
     gotoxy(25,3);
     textcolor(YELLOW);
     cprintf("        INDEXING      ");
     gotoxy(25,4);
     cprintf(" ออออออออออออออออออออออออออออ ");
	 drawdoublelinebox(17,7,44,14);
	 gotoxy(28,7);
	 textbackground(RED);
	 textcolor(YELLOW);
	 cprintf("Û  M A I N    M E N U Û" );
	 normal();
	 textcolor(WHITE);
	 gotoxy(g,h++);
	 cout<<"þ SIMPLE INDEX";
	 gotoxy(g,h++);
	 cout<<"þ SECONDARY KEY";
	 gotoxy(g,h++);
	 cout<<"þ INVERTED LIST";
	 gotoxy(g,h++);
	 cout<<"þ QUIT";
	 gotoxy(g,h++);
	 gotoxy(g,h++);
	 gotoxy(g,h++);
}







