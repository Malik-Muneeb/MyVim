#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

#define cursorUpward(x) 	printf("\033[%dA", (x))
#define cursorDownward(x) 	printf("\033[%dB", (x))
#define cursorForward(x) 	printf("\033[%dC", (x))
#define cursorBackward(x) 	printf("\033[%dD", (x))

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108
#define KEY_BACKSPACE	0X007f


static struct termios term, oterm;	//used to store and modify terminal settings
static int getch(void);					//these four functions are used to handling arrow keys
static int kbhit(void);
static int kbesc(void);
static int kbget(void);
<<<<<<< HEAD
int commandMode();
void insertMode(int fd,int c);
int showFileData(char* argv[]); //it will return fd
void fileCopy(FILE* inFile);
void synchronization(int fd);
void searching(char *cmd);
void delete();
void copy();
void paste();
void backspace();
char *tempFile="temp111";
char *fileName;
FILE* inFile;
int cols=0;
int rows=1;
int enter=0;
int limitRows=0;
int flag=0;	//
int isAPressed=0;
int temp_col=0;
char copyLine[141];
FILE *copyFile;
int lineCount=1;
=======

int commandMode();					//handling of arrow keys, delete, copy and paste
void insertMode(int fd,int c);	//handling of arrow keys, a,i,o,A,I,O
int showFileData(char* argv[]);  //show given file data on screen
void fileCopy(FILE* inFile);		//make a copy of original file
void synchronization(int fd);		//synchronization between cursor and file offset
void searching(char *cmd);			//search specific string in a file
void delete();							// delete a line by pressing 'd'
void copy();							//copy a line by pressing 'y'
void paste();							//paste a file by pressing 'p'

char *tempFile="temp111"; //contain name of origianl file
char *fileName;				//contain given file name as commandLine argument
FILE* inFile;					//file pointer
int cols=0;						//current column
int rows=1;						//current row
int limitRows=0;				//contains max number of rows. 
int flag=0;						//case handling while executing insert mode like (a,i,o,A,i,O)
int isAPressed=0;				//for 'A' key pressed flag in insert mode
int temp_col=0;				//used to store increament for cols for case 'A' handling in insert mode
char copyLine[141];			//used to as buffer which contains a line to paste
FILE *copyFile;				//temporary copy file pointer used in copy paste function
int lineCount=1;				//used in copy paste function to count how many lines are copied in temporay file

>>>>>>> d0c512f39c92305339fa5510172e671bed898a34

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Must enter one file Name\n");
		exit(1);
	}
	int fd=showFileData(argv);
	int c=commandMode();
	while(c==100 || c==112)
	{	
		rows=1,cols=0,limitRows=0,lineCount=1;
		fd=showFileData(argv);
		c=commandMode();
	}
  	insertMode(fd,c);
	printf("\n");
	return 0;
}

/**********************************************************************************
 Copy a file line
**********************************************************************************/
void copy()
{
	copyFile = fopen("copyFile", "w");
	fseek(inFile,0L,SEEK_SET);	
	while(lineCount<=rows)
	{
		fgets(copyLine, sizeof(copyLine), inFile);
 		fputs(copyLine, copyFile);
		lineCount++;
	}
 	//fclose(copyFile);
}


/**********************************************************************************
 paste a file line
**********************************************************************************/
void paste()
{
	char buf[141];
<<<<<<< HEAD
=======
	//copy from upward to downward
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
	if(lineCount<=rows)
	{
		while(lineCount<=limitRows)
		{
			if(lineCount==rows)
			{		
				fputs(copyLine,copyFile);
				rows--;
			}
			else
			{
				fgets(buf, sizeof(buf), inFile);
		 		fputs(buf, copyFile);
				lineCount++;
			}
		}
	}
<<<<<<< HEAD
=======
	//copy from downward to upward
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
	else
	{
		fclose(copyFile);
		remove("copyFile");
		copyFile = fopen("copyFile", "w");
		if(limitRows+1==lineCount)
			{
				copyLine[strlen(copyLine)]=10;
			}
		fseek(inFile,0L,SEEK_SET);
		int count=1;	
		while(count<=limitRows)
		{
			if(count==rows)
			{
				fputs(copyLine,copyFile);
<<<<<<< HEAD
				//char *ch='\n';
//				fputc(10,copyFile);
=======
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
			}
			fgets(buf, sizeof(buf), inFile);
	 		fputs(buf, copyFile);
			count++;
		}
	}
	remove(fileName);
	rename("copyFile",fileName);
 	fclose(copyFile);
}
<<<<<<< HEAD
=======

>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
/**********************************************************************************
 commandMode => Handles different keys
**********************************************************************************/

int commandMode()
{
	int c;
	fflush(stdin);
	fflush(stdout);
	system("stty -icanon");
	system("stty -echo");
	c=getchar();
<<<<<<< HEAD
	int ndel=0;
=======
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
	while( c!=97 && c!=65 && c!=105 && c!=73 && c!=79 && c!=111)
	{
	 	c=kbget();
		if (c == KEY_ESCAPE ) 
		{
			break;
		}
		else if (c == KEY_UP) 
		{
			if(rows>1)
			{
				rows--;
				cursorUpward(1);
			}
		} 
		else if (c == KEY_DOWN) 
		{
			if(rows<limitRows)
			{
				rows++;
				cursorDownward(1);
			}
		} 
		else if (c == KEY_RIGHT)
		{
			cols++;
			cursorForward(1);
		} 
		else if (c == KEY_LEFT)
		{
			if(cols>0)
				cols--;
			cursorBackward(1);
		}
<<<<<<< HEAD
		else if(c=='d')
		{	
			delete();
			enter=0;
=======
		else if(c=='d')	//delete
		{
			delete();
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
			system("stty icanon");
			system("stty echo");
			return c;	
		}
<<<<<<< HEAD
		else if(c=='y')
		{
			copy();
		}
		else if(c=='p')
=======
		else if(c=='y')	//copy
		{
			copy();
		}
		else if(c=='p')	//paste
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
		{
			paste();
			system("stty icanon");
			system("stty echo");
			return c;	
		}
<<<<<<< HEAD
		else if(c>0)
		{
			enter=c;
			enter-=48;
		}
=======
>>>>>>> d0c512f39c92305339fa5510172e671bed898a34
		//printf("\n%d %d\n",rows,cols);
	}
	system("stty icanon");
	system("stty echo");
	return c;
}

/**************************************************************************
ShowFileData: This function get all data from file and display
on terminal.
***************************************************************************/


int showFileData(char* argv[])
{
	system("clear");
	fileName=argv[1];
	//to get size of file
	inFile=fopen(fileName,"r");
	char *buff;
	long bytes;
	fseek(inFile,0L,SEEK_END);
	bytes=ftell(inFile);
	fseek(inFile,0L,SEEK_SET);
	buff=(char*)calloc(bytes,sizeof(char));

	int ch;
	size_t size=0;
	int fd=open(fileName,O_RDWR | O_CREAT,0664);
	read(fd,buff,bytes);
	int i=0;
	//write data on terminal and count rows and cols
	while(i<bytes)
	{	
		if(buff[i]!=10 && buff[i]!=13)
		{
			printf("%c",buff[i]);
			cols++;
		}
		else
		{
			printf("\n");
			rows++;
			if(buff[i+1]!='\0')
				cols=0;
		}
		i++;
	}
	//rows--;
	cols--;
	//printf("\n%d %d\n",rows,cols);
	limitRows=rows;
	fileCopy(inFile);	
	return fd;
}

/***************************************************************************************
Handle keys(a,i,o,A,I,O),save, quit and search in insertMode
****************************************************************************************/

void insertMode(int fd,int c)
{
	switch(c)
	{
		case 105:	//i
			if(cols>0)
			{
				cursorBackward(1);
				cols--;
//				printf("\n col = %d row = %d\n",cols,rows);
			}
			break;
		case 97:	//a
			break;
		case 73:	//I
			for(int i=140; i>0; i--)
				cursorBackward(1);
			cols=0;
			flag=73; 
			break;
		case 65:	//A
			flag=65;
			synchronization(fd);
			break;
		case 111:		//o
			cursorDownward(1);
			printf("\033[G");
			rows++;
			cols=0;
			flag=111;
			char line='\n';
			write(fd,&line,1);
			break;
		case 79:	//O
			cursorUpward(1);
			printf("\033[G");
			if(rows>0)
				rows--;
			cols=-1;
			break;
	}
	c=0;
	while (1) 
	{
		c = kbget();
		if (c == KEY_ESCAPE ) 
		{
			for(int i=0; i<30; i++)
				cursorDownward(1);
			printf("\033[%dG", 0);
			char *cmd=readline("ExecuteMode:  ");
			while( cmd!="a" && cmd!="A" && cmd!="i" && cmd!="I" && cmd!="O" && cmd!="o")
			{
				if(strcmp(cmd,":q")==0)			//quit
				{
					remove(fileName);
					rename(tempFile,fileName);
					system("clear");
					exit(0);
				}
				else if(strcmp(cmd,":w")==0)	//save and quit
				{
					remove(tempFile);
					system("clear");
					exit(0);
				}			
				else		//searching a string
				{
					searching(cmd);
					cmd=readline("ExecuteMode:  ");
				}
			}
		}
		else if (c == KEY_UP) 
		{
			cursorUpward(1);
			if(rows>0)			
				rows--;
		} 
		else if (c == KEY_DOWN) 
		{
			cursorDownward(1);
			rows++;
		} 
		else if (c == KEY_RIGHT)
		{
			cursorForward(1);
			cols++;			
		} 
		else if (c == KEY_LEFT)
		{
			cursorBackward(1);
			if(cols>=0)
				cols--;
		} 
		else if (c == KEY_BACKSPACE)
		{
			cursorBackward(1);
			printf(" ");
			cursorBackward(1);
			cols--;
		} 
		else if (c == KEY_ENTER)
		{
			cursorDownward(1);
			printf("\033[G");
			char line='\n';
			write(fd,&line,1);
			rows++;
			cols=-1;
		}         
		else
		{
			if(flag!=111)
				synchronization(fd);
			write(fd,&c,1);
			putchar(c);
			cols++;
		}
	}
}

/**********************************************************************************
 Delete Lines From File
**********************************************************************************/

void delete()
{	
	char ch;
	int count=1;
	FILE  *target;
	target = fopen("myFile", "w");
	fseek(inFile,0L,SEEK_SET);	
   while( ( ch = fgetc(inFile) ) != EOF )
	{
		if(enter==20)
		{
			if(ch==10||ch==13)
				count++;
			if(count!=rows)
   				fputc(ch, target);
		}
		else if(enter<=(limitRows-rows))
		{
			if(ch==10||ch==13)
				count++;
			if(count==rows)
			{
				while(enter>0)
				{
					ch = fgetc(inFile);
					if(ch==10||ch==13)
						enter--;
				}
				count++;
				fputc(10, target);
			}
			else
				fputc(ch, target);
		}
		else
		{
			enter=0;
			fclose(target);
			return;
		}
	}
	enter=0;
	fclose(inFile);
	remove(fileName);
	rename("myFile",fileName);
	//system("clear");
 	fclose(target);
}

/**********************************************************************************
 Synchronization: sync of console and file pointer
**********************************************************************************/

void synchronization(int fd)
{
	int new_pos=0;
	char buf[141];
	fseek(inFile,0L,SEEK_SET);	
	for(int i=1;i<=rows;i++)
	{
		fgets(buf, sizeof(buf), inFile);
		//if(strcmp(buf[strlen(buf) - 1],"\n")==0)
			//buf[strlen(buf) - 1] = ' '; // eat the newline fgets() stores // \n py \0 rakhwana h
		//printf("\n%s\n",buf);
		if(i==rows)
		{
			new_pos += cols;
			if(flag==73 && rows==1)
			{
				new_pos=-1;
				flag=0;
				cols--;
			}
			else if(flag==73)
			{
				new_pos-=1;
				flag=0;
				cols=-1;
			}
			else if(flag==65)
			{				
				temp_col=0;
				for(int i=cols; i < strlen(buf); i++)
				{
					cursorForward(1);
					temp_col++;
				}
				flag=0;
				isAPressed=65;
				return;
			}
			else if(isAPressed==65)
			{
				new_pos+=(strlen(buf)-cols);
				cols=temp_col;
				isAPressed=0;
			}
			lseek(fd,new_pos+1,SEEK_SET);
				//printf("\n col = %d new-pos = %d  row = %d\n",cols,new_pos+1,rows);
			return;
		}
		new_pos += strlen(buf);
	}
}

void searching(char *cmd)
{
	char *buff;
	long bytes;
	fseek(inFile,0L,SEEK_END);
	bytes=ftell(inFile);
	fseek(inFile,0L,SEEK_SET);
	buff=(char*)calloc(bytes,sizeof(char));
	char search[50];
	strcpy(search,cmd);
	int total=0;
	int ch;
	size_t size=0;
	int searchCursor=1;
	int countOfSubStr=0;
	int c;
	while((ch=fgetc(inFile))!=EOF)
	{	
		if(ch!=10 && ch!=13)
		{
			buff[size++] = (char) ch;
		}
		else
		{
			while ( (buff=strstr(buff,search)) != NULL )
			{
				total++;
				buff+=strlen(search);
				countOfSubStr++;
			}
			if(total>0)
			{
				printf("\033[%dC", 25);
				printf("\033[7m%i occurences in the line no # %d\033[m",countOfSubStr ,searchCursor);
				printf("\033[%dC", 25);
				printf("\033[7mDo You want to continue search (y/n)?\033[m");
				system("stty -icanon");
				c=getchar();
				if(c!=121)
				{
					system("stty icanon");
					printf("\033[2K");
					break;
				}
				system("stty icanon");		
				printf("\033[2K");
				printf("\033[%dG", 0);
			}
			buff=(char*)calloc(bytes,sizeof(char)); 
			size=0;
			searchCursor++;
			total=0;
			countOfSubStr=0;							
		}										
	}
	printf("\033[%dA", 0);
	printf("\033[2K");
	printf("\033[%dG", 0);
}


/***********************************************************************************
fileCopy: write copy file to maintain backup of original data
************************************************************************************/

void fileCopy(FILE* inFile)
{
	char ch;
   FILE  *target;
   target = fopen(tempFile, "w");
   while( ( ch = fgetc(inFile) ) != EOF )
      fputc(ch, target);
   fclose(target);
}

static int getch(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

static int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

static int kbesc(void)
{
    int c;

    if (!kbhit()) return KEY_ESCAPE;
    c = getch();
    if (c == '[') {
        switch (getch()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_RIGHT;
                break;
            case 'D':
                c = KEY_LEFT;
                break;
            default:
                c = 0;
                break;
        }
    } else {
        c = 0;
    }
    if (c == 0) while (kbhit()) getch();
    return c;
}

static int kbget(void)
{
    int c;
    c = getch();
	if(c == KEY_ESCAPE) 
		return kbesc(); 
	else
		return c;
}
