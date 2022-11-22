#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<direct.h>
#include <conio.h> 
#include<time.h>
#include<windows.h>
#include<sys/stat.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#pragma warning (disable : 4996);
int percent_pass_str(char pass[256]);
void write_user_file(struct users a);
void creat_user(FILE* users_list);
void pass_star(char pass[256]);
int find_size_of_file(char filename[]);
int time_use(int d, int m, int y);
void shift(char str[], int T);
void shift_wo(char str[], int T);
int check1(char str[]);
int check2(char str[]);
void cut(char str[], char command[]);
void printFileProperties(struct stat file_stat);
void fre(char input[][80]);
int number_of_line(char str[][80]);
int number_of_word(char str[][80], int line);
int number_of_char(char str[][80], int line);



void gotoxy(int line, int colum)
{
	COORD coord;
	coord.X = line;
	coord.Y = colum;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

typedef struct file
{
	char file_name[40];
	char file_creator[64];
}s_file;



typedef struct users
{
	char name[256];
	char username[256];
	char pass[256];
	int pass_str;
	int S_dastresi;
	int fail = 0;
	int year_end;
	int mounth_end;
	int day_end;

}s_user;
int number_of_users = 1;
int number_of_files = 1;

s_user* user;
s_file* fl;


int main()
{
	user = (s_user*)malloc(sizeof(s_user));
	fl = (s_file*)malloc(sizeof(s_file));
	int  start = _mkdir("thebest");///main file
	_chdir("thebest");

	char rootaddress[_MAX_DIR];
	_getcwd(rootaddress, _MAX_DIR);


	if (start == 0) 
	{
		
		FILE* users_list;
		users_list = fopen("users_list.bin", "wb");

		///difult admin user
		strcpy(user[0].name, "nasiri");
		strcpy(user[0].username, "navid");
		strcpy(user[0].pass, "1190289822 navid nasiri");
		user[0].pass_str = percent_pass_str(user[0].pass);

		user[0].S_dastresi = 1;
		user[0].fail = 0;
		user[0].day_end = 20;
		user[0].mounth_end = 12;
		user[0].year_end = 2022;
		fwrite(user, sizeof(struct users), 1, users_list);

		fclose(users_list);

		FILE* files_list;
		files_list = fopen("files_list.bin" , "wb");
		strcpy(fl[0].file_creator, "navid");
		strcpy(fl[0].file_name, "users_list.bin");
		fwrite(fl, sizeof(s_file), number_of_files, files_list);
		fclose(files_list);


		_mkdir("navid");
		

	}
	else
	{
		///write structs from file to pointer
		FILE* users_list;
		users_list = fopen("users_list.bin", "rb");
		char str[30] = "users_list.bin";
		number_of_users = find_size_of_file(str) / sizeof(s_user);
		user = (s_user*)malloc(number_of_users * sizeof(s_user));
		fread(user, sizeof(struct users), number_of_users, users_list);
		fclose(users_list);
		///write struct of files from  file to poitnter
		FILE* files_list;
		files_list = fopen("files_list.bin", "rb");
		char str1[30] = "files_list.bin";
		number_of_files =find_size_of_file(str1) / sizeof(s_file);
		fl = (s_file*)malloc(sizeof(s_file) * number_of_files);
		fread(fl, sizeof(s_file), number_of_files, files_list);
		fclose(files_list);
		

	}
	///login for first
	
	s_user first;

	int andis = 0;///baraye jostojooye karbare moredenazar.

		///Enter username
	///enter password
	while (1)
	{
		int temp = 0;
		printf(ANSI_COLOR_CYAN "Enter username:" ANSI_COLOR_RESET);
		scanf("%s", first.username);
		for (andis = 0; andis < number_of_users; andis++)
		{
			if (strcmp(first.username, user[andis].username) == 0)
			{
				temp++;
				break;
			}
		}
		if (temp == 1)
		{

			printf(ANSI_COLOR_CYAN "Enter password:" ANSI_COLOR_RESET);
			pass_star(first.pass);

			if (strcmp(first.pass, user[andis].pass) == 0)
			{
				if (time_use(user[andis].day_end, user[andis].mounth_end, user[andis].year_end))
				{
					system("cls");
					char buffer[256];
					sprintf(buffer, "%s", user[andis].username);
					_chdir(buffer);
					break;
				}
				else if(user[andis].S_dastresi == 1)
				{
					system("cls");
					char buffer[256];
					sprintf(buffer, "%s", user[andis].username);
					_chdir(buffer);
					break;
				}
				else 
				{
					printf("\n\nThis user can't login.\n\nyour time finished.\n\n");
					continue;
				}
			}
			else
			{
				printf("\npassword not corect.\n\nplease try again.\n\n");
				continue;
			}

		}
		else
		{
			printf("username not found. please try again.\n");
			continue;
		}
	}

	///now time///
	int hours, minutes, seconds, day, month, year;
	time_t now;
	time(&now);
	struct tm* local = localtime(&now);
	hours = local->tm_hour;
	minutes = local->tm_min;
	seconds = local->tm_sec;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;

	//
	if (hours < 12)	// before midday
		printf(ANSI_COLOR_CYAN "Time is : %02d:%02d:%02d am" ANSI_COLOR_RESET, hours, minutes, seconds);

	else if(hours > 12 )	// after midday
		printf(ANSI_COLOR_CYAN "Time is : %02d:%02d:%02d pm" ANSI_COLOR_RESET, hours -12, minutes, seconds);

	else if(hours == 12)
		printf(ANSI_COLOR_CYAN "Time is : %02d:%02d:%02d pm" ANSI_COLOR_RESET, hours, minutes, seconds);

	// print current date
	printf(ANSI_COLOR_CYAN"\t\t\t\t\tDate is : %02d/%02d/%d\n\n" ANSI_COLOR_RESET, day, month, year);
	//




	printf(ANSI_COLOR_MAGENTA "\n------Wellcome %s-------\n" ANSI_COLOR_RESET, user[andis].name);
		


	char c;
	c = getchar();

	while (1)
	{


		char command[256] = { };
		//char S_dastresi[20] = { 0 };
		if (user[andis].S_dastresi == 1)
		{
			char path[_MAX_DIR];
			_getcwd(path, _MAX_DIR);
			shift_wo(path, strlen(rootaddress));
			//strcpy(S_dastresi, "admin");
			printf(ANSI_COLOR_GREEN "[%s@%s] admin:%s\\"  ANSI_COLOR_RESET, user[andis].username, user[andis].name, path);
		}
		else
		{

			char path[_MAX_DIR];
			_getcwd(path, _MAX_DIR);
			shift_wo(path, strlen(rootaddress));
			      
			//strcpy(S_dastresi, "user");
			printf(ANSI_COLOR_YELLOW "[%s@%s] user:%s\\"  ANSI_COLOR_RESET, user[andis].username, user[andis].name,path);
		}


		fgets(command, 256, stdin);
		// char c = getchar();
		///commands//////////
		if (strcmp(command, "\n") == 0)
			continue;

		if (strncmp(command, "su ", 3) == 0)
		{
			char u_name[256];
			//scanf("%s", u_name);
			int j = 0;
			for (int i = 3; command[i + 1] != '\0'; i++)
			{

				u_name[j] = command[i];
				j++;
			}
			u_name[j] = '\0';
			int temp = 0;
			int i = 0;
			for (i = 0; i < number_of_users; i++)
			{
				if (strcmp(u_name, user[i].username) == 0)
				{
					temp++;
					break;
				}
			}
			if (temp == 1)
			{
				if (user[andis].S_dastresi == 0)
				{
					printf("\nEnter password:");

					char u_pass[256] = { };
					pass_star(u_pass);
					if (strcmp(u_pass, user[i].pass) == 0)
					{
						if (!time_use(user[i].day_end, user[i].mounth_end, user[i].year_end) && (user[andis].S_dastresi == 0))
						{
							printf("\nThis user time finished.\n\nyoucan't enter.\n\n");
						}

						else
						{
							andis = i;

							_chdir(rootaddress);
							char buffer[256];
							sprintf(buffer, "%s", user[andis].username);
							
							_chdir(buffer);
							printf("\n");
							continue;
						}
					}
					else
					{
						printf("\npassword not corect.pleas try again.\n");
					}

				}

				else
				{

					andis = i;

					_chdir(rootaddress);
					char buffer[256];
					sprintf(buffer, "%s", user[andis].username);
					_chdir(buffer);
					printf("\n");
					continue;

				}

			}
			else
			{
				printf("user not found.\n");
			}




		}

		else if (strncmp(command, "clear", 5) == 0)
		{
			system("cls");
			///time now
			time(&now);
			struct tm* local = localtime(&now);
			hours = local->tm_hour;
			minutes = local->tm_min;
			seconds = local->tm_sec;
			day = local->tm_mday;
			month = local->tm_mon + 1;
			year = local->tm_year + 1900;


			if (hours < 12)	// before midday
				printf(ANSI_COLOR_CYAN "Time is : %02d:%02d:%02d am" ANSI_COLOR_RESET, hours, minutes, seconds);

			else if (hours > 12)	// after midday
				printf(ANSI_COLOR_CYAN "Time is : %02d:%02d:%02d pm" ANSI_COLOR_RESET, hours - 12, minutes, seconds);

			else if (hours == 12)
				printf(ANSI_COLOR_CYAN "Time is : %02d:%02d:%02d pm" ANSI_COLOR_RESET, hours, minutes, seconds);

			// print current date
			printf(ANSI_COLOR_CYAN"\t\t\t\t\tDate is : %02d/%02d/%d\n\n" ANSI_COLOR_RESET, day, month, year);


		}

		else if (strcmp(command, "whoami\n") == 0)
		{

			printf("name: %s\n\n", user[andis].name);
			printf("username: %s\n\n", user[andis].username);
			printf("You was entered %d incorect command.\n\n", user[andis].fail);
			printf("End time : %0.2d/%0.2d/%0.4d\n\n", user[andis].day_end, user[andis].mounth_end, user[andis].year_end);
			if (user[andis].S_dastresi == 1)printf("Admin\n\n");
			else printf("user\n\n");


		}

		else if (strcmp(command, "createuser\n") == 0)
		{
			if (user[andis].S_dastresi == 0)
				printf("you don't have permission to use this command.\n");
			else
			{

				char path[_MAX_DIR];
				_getcwd(path, _MAX_DIR);

				_chdir(rootaddress);
				FILE* users_list;
				users_list = fopen("users_list.bin", "ab");
				creat_user(users_list);
				fclose(users_list);


				users_list = fopen("users_list.bin", "rb");
				fread(user, sizeof(struct users), number_of_users, users_list);
				fclose(users_list);
				char buffer[30];
				sprintf(buffer, "%s", user[andis].username);
				_chdir(path);

				char c;
				c = getchar();

			}


		}

		else if (strncmp(command, "chgr ", 5) == 0)
		{
			char ch_name[256];
			//scanf("%s", u_name);
			int j = 0;
			for (int i = 5; command[i + 1] != '\0'; i++)
			{

				ch_name[j] = command[i];
				j++;
			}
			ch_name[j] = '\0';
			int temp = 0;
			int i = 0;
			if (user[andis].S_dastresi == 1)
			{
				for (i = 0; i < number_of_users; i++)
				{
					if (strcmp(user[i].username, ch_name) == 0)
					{
						temp++;
						break;
					}
				}

				if (temp)
				{
					if (user[i].S_dastresi == 0)
					{
						if (user[i].pass_str > 75)
						{
							if (user[i].fail <= 10)
							{
								user[i].S_dastresi = 1;
								char path[_MAX_DIR];
								_getcwd(path, _MAX_DIR);
								_chdir(rootaddress);
								///apdate file
								FILE* users_list;
								users_list = fopen("users_list.bin", "wb");
								fwrite(user, sizeof(struct users), number_of_users, users_list);
								fclose(users_list);
								///apdate *struct
								users_list = fopen("users_list.bin", "rb");
								fread(user, sizeof(struct users), number_of_users, users_list);
								fclose(users_list);
								
								_chdir(path);
								printf("changed group of this user.\n\n");
							}

							else
							{
								printf("This user has more than 10 incorrect command.\n\nincorect command of user most lower than 10\n\n");
							}
						}
						else
						{
							printf("\nThis user don't has a password that strog enogh.\n\nuser's password most >75 strong.\n\n");
						}
					}
					else
					{
						printf("\nThis user is admin .\n\nusername that you enter, must not admin.\n\n");
					}

				}
				else
				{
					printf("\n\nusername not found.\n\n");
				}

			}
			else
			{
				printf("\nyou are not admin.\nyou can't enter this command.\n\n");
			}
		}

		else if (strcmp(command, "passwd\n") == 0)
		{
			char N_pass[256];
			printf("\nEnter new password [max length 255] :");
			pass_star(N_pass);

			printf("\nconfirm password:");
			char N_pass_again[256];
			pass_star(N_pass_again);

			if (strcmp(N_pass, N_pass_again) == 0)
			{
				printf("\nYour password changed successfuly.\n");
				strcpy(user[andis].pass, N_pass);
				user[andis].pass_str = percent_pass_str(N_pass);
				///save in file...
				char path[_MAX_DIR];
				_getcwd(path, _MAX_DIR);
				_chdir(rootaddress);
				FILE* users_list;
				users_list = fopen("users_list.bin", "wb");
				fwrite(user, sizeof(struct users), number_of_users, users_list);
				fclose(users_list);

				///apdate *struct
				users_list = fopen("users_list.bin", "rb");
				fread(user, sizeof(struct users), number_of_users, users_list);
				fclose(users_list);
				
				_chdir(path);
			}
			else
			{
				printf("\npassword not match.\n");
			}


		}

		else if (strncmp(command, "passwd -l ", 10) == 0)
		{
			if (user[andis].S_dastresi == 1)
			{
				char day[2];
				char mounth[2];
				char year[4];
				int i = 10;
				int j = 0;

				for (i = 10; command[i] != '/'; i++)
				{
					day[j] = command[i];
					j++;
				}
				j = 0;

				for (i = i + 1; command[i] != '/'; i++)
				{
					mounth[j] = command[i];
					j++;

				}
				j = 0;

				for (i = i + 1; command[i] != ' '; i++)
				{
					year[j] = command[i];
					j++;

				}
				int d = atoi(day);
				int m = atoi(mounth);
				int y = atoi(year);

				char su_name[256];
				int x = 0;
				j = 0;

				for (i = i + 1; command[i] != '\n'; i++)
				{
					su_name[j] = command[i];
					x = j++;
				}
				su_name[x + 1] = '\0';

				int temp = 0;
				int z = 0;
				for (z = 0; z < number_of_users; z++)
				{
					if (strcmp(su_name, user[z].username) == 0)
					{
						temp++;
						break;
					}
				}
				if (temp == 1)
				{
					user[z].day_end = d;
					user[z].mounth_end = m;
					user[z].year_end = y;
					///save file

					char path[_MAX_DIR];
					_getcwd(path, _MAX_DIR);
					_chdir(rootaddress);
					FILE* users_list;
					users_list = fopen("users_list.bin", "wb");
					fwrite(user, sizeof(struct users), number_of_users, users_list);
					fclose(users_list);


					///apdate *struct
					users_list = fopen("users_list.bin", "rb");
					fread(user, sizeof(struct users), number_of_users, users_list);
					fclose(users_list);
					char buffer[30];
					sprintf(buffer, "%s", user[andis].username);
					_chdir(path);
				}
				else
				{
					printf("\nusername not found. please try again.\n");

				}

			}
			else
				printf("\nyou are user.\n\nyou can't enter this command.\n\n");

		}

		else if (strcmp(command, "cd ..\n") == 0 || strcmp(command, "cd..\n") == 0)
		{

		char path[_MAX_DIR];
		_getcwd(path, _MAX_DIR);

			if (user[andis].S_dastresi == 0)
				{
					char str[100];
					sprintf(str, "%s\\%s",rootaddress , user[andis].username);
					if(strcmp(path , str) != 0)
					_chdir("..");
					continue;
				}
			else if (user[andis].S_dastresi == 1)
			{

				//char str[100];
				//sprintf(str, "F:\\last project\\thebest\\thebest\\thebest", user[andis].username);
				if (strcmp(path, rootaddress) != 0)
					_chdir("..");
				continue;

			}
		
		}

		else if (strncmp(command, "cd ", 3) == 0)
		{
		    shift(command, 3);
			char buffer[256];
			sprintf(buffer, "%s", command);
			int a = _chdir(buffer);
			if (a != 0)
			{
				printf("\nThe system cannot find the path specified.\n\n");
			}


		}

		else if (strcmp(command, "pwd\n") == 0)
		{
		printf("your address in the computer:\n");
			char path[_MAX_DIR];
			_getcwd(path, _MAX_DIR);
			printf("\n%s\n\n", path);

			printf("your address in the this OS:");
			shift_wo(path, strlen(rootaddress));
			printf("\n\n\\thebest\%s\n\n", path);

		}
		else if (strncmp(command, "mkdir /h ", 9) == 0)
		 {
		 shift(command, 9);
		 char str1[40];
		 sprintf(str1, "mkdir %s", command);
		 system(str1);
		 char str2[40];
		 sprintf(str2, "attrib +h %s", command);
		 puts("");
		 system(str2);
		 puts("");


		}
		else if (strncmp(command, "mkfile /h ", 10) == 0)
		 {
		 shift(command, 10);
		 FILE* file1;
		 file1 = fopen(command, "w");
		 fclose(file1);
		 char str[40];
		 sprintf(str, "attrib +h %s", command);
		 system(str);

		 ////save file that created in the files_list and apdate pointer
		 char path[_MAX_DIR];
		 _getcwd(path, _MAX_DIR);
		 _chdir(rootaddress);
		 fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
		 strcpy(fl[number_of_files].file_creator, user[andis].username);
		 strcpy(fl[number_of_files].file_name, command);
		 number_of_files++;
		 FILE * files_list;
		 files_list = fopen("files_list.bin", "wb");
		 fwrite(fl, sizeof(s_file), number_of_files, files_list);
		 fclose(files_list);
		 _chdir(path);
		 
		 //////////
		 }
		else if (strncmp(command, "mkdir ", 6) == 0)
		{
			system(command);
			
		 }

		else if (strncmp(command, "rm -r ", 6) == 0)
		{
			shift(command, 6);
			char buffer[100];
			sprintf(buffer, "rmdir /S %s", command);
			system(buffer);
			
		}

		else if (strncmp(command, "rm ", 3) == 0)
		{
			
			char str[100];
			shift(command, 3);
			sprintf(str, "del %s",command);
			system(str);
			///rimove filename frome fileslist
			char path[_MAX_DIR];
				_getcwd(path, _MAX_DIR);
			_chdir(rootaddress);
			for (int i = 0; i < number_of_files; i++)
			{
				if (strcmp(fl[i].file_name, command) == 0)
				{
					for (int j = i; j < number_of_files-1; j++)
						fl[j] = fl[j + 1];
					number_of_files--;
				}
			}
			FILE* files_list;
			files_list = fopen("files_list.bin", "wb");
			fl = (s_file*)realloc(fl, number_of_files * sizeof(s_file));
			fwrite(fl, sizeof(s_file), number_of_files, files_list);
			fclose(files_list);
			_chdir(path);


		 }
		 
		else if (strcmp(command, "ls\n") == 0)
		{
			system("dir");

		 }

		
		else if (check1(command))
		{///>///
			command[strlen(command)] = '\0';
			char str[100];
			sprintf(str, "type %s", command);
			int a = system(str);
			if (a == 1)
			{
				puts("");
				printf("do you want to create file?(y:create file and write to destination file. n:joust write to file)");
				char c;
				scanf("%c", &c);

				if (c == 'y')
				{
					
					printf("\nEnter filename:(filename.format)");
					char str5[40];///esme fili ke mikhahim matn chap ra dar an berizim...
					scanf("%s", str5);
					///write to destination file;
					
					char str2[100];
					sprintf(str2, "echo %s", command);
					system(str2);
					//////////
					char namef[30];
					cut(namef, command);
					shift(command, strlen(namef) + 1);
					////save file that created
					char path[_MAX_DIR];
					_getcwd(path, _MAX_DIR);
					_chdir(rootaddress);
					fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
					strcpy(fl[number_of_files].file_creator, user[andis].username);
					strcpy(fl[number_of_files].file_name, command);
					number_of_files++;
					FILE * files_list1;
					files_list1 = fopen("files_list.bin", "wb");
					fwrite(fl, sizeof(s_file), number_of_files, files_list1);
					fclose(files_list1);
					_chdir(path);
					//////////
					///create file that name is str5;
					
					//char str4[30];
					//sprintf(str4, "%s.txt", namef);
					FILE* nfile;
					nfile = fopen(str5, "w");
					fprintf(nfile, "%s", namef);
					fclose(nfile);
					////save file that created
					
					_chdir(rootaddress);
					fl = (s_file*)realloc(fl,(number_of_files+1) * sizeof(s_file));
					strcpy(fl[number_of_files].file_creator, user[andis].username);
					strcpy(fl[number_of_files].file_name, str5);
					number_of_files++;
					FILE* files_list;
					files_list = fopen("files_list.bin", "wb");
					fwrite(fl, sizeof(s_file), number_of_files, files_list);
					fclose(files_list);
					_chdir(path);
					//////////

					char c = getchar();


					
				}
				else if (c == 'n')
				{
					char str2[100];
					sprintf(str2, "echo %s", command);
					system(str2);
					////////
					char namef[30];
					cut(namef, command);
					shift(command, strlen(namef) + 1);
					////save file that created
					char path[_MAX_DIR];
					_getcwd(path, _MAX_DIR);
					_chdir(rootaddress);
					fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
					strcpy(fl[number_of_files].file_creator, user[andis].username);
					strcpy(fl[number_of_files].file_name, command);
					number_of_files++;
					FILE * files_list;
					files_list = fopen("files_list.bin", "wb");
					fwrite(fl, sizeof(s_file), number_of_files, files_list);
					fclose(files_list);
					_chdir(path);
					//////////
					char c = getchar();
				}
				else
				{
					printf("\nEnter 'y' or 'n'.\n");
					continue;
				}

				

			}
			else if (a == 0)
			{
				continue;
			}
			

		}

		else if (check2(command))
		{
		///>>///
		command[strlen(command)] = '\0';
		char str[100];
		sprintf(str, "type %s", command);
		int a = system(str);
		if (a == 1)
		{
			puts("");
			printf("do you want to create file?(y:create file and write to destination file. n:joust write to file)");
			char c;
			scanf("%c", &c);
			if (c == 'y')
			{

				printf("\nEnter filename:(filename.format)");
				char str5[40];///esme fili ke mikhahim matn chap ra dar an berizim...
				scanf("%s", str5);
				///write to destination file;
				char str2[100];
				sprintf(str2, "echo %s", command);
				system(str2);
				//////////
				char namef[30];
				cut(namef, command);
				shift(command, strlen(namef) + 1);
				////save file that created
				char path[_MAX_DIR];
				_getcwd(path, _MAX_DIR);
				_chdir(rootaddress);
				fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
				strcpy(fl[number_of_files].file_creator, user[andis].username);
				strcpy(fl[number_of_files].file_name, command);
				number_of_files++;
				FILE * files_list1;
				files_list1 = fopen("files_list.bin", "wb");
				fwrite(fl, sizeof(s_file), number_of_files, files_list1);
				fclose(files_list1);
				_chdir(path);
				//////////
				///create file that name is scnaf.txt;
			
				//char str4[30];
				//sprintf(str4, "%s.txt", namef);
				FILE* nfile;
				nfile = fopen(str5, "w");
				fprintf(nfile, "%s", namef);
				fclose(nfile);
				////save file that created
		
				_chdir(rootaddress);
				fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
				strcpy(fl[number_of_files].file_creator, user[andis].username);
				strcpy(fl[number_of_files].file_name, str5);
				number_of_files++;
				FILE * files_list;
				files_list = fopen("files_list.bin", "wb");
				fwrite(fl, sizeof(s_file), number_of_files, files_list);
				fclose(files_list);
				_chdir(path);
				//////////
				char c = getchar();

			}
			else if (c == 'n')
			{
				char str2[100];
				sprintf(str2, "echo %s", command);
				system(str2);
				//////////
				char namef[30];
				cut(namef, command);
				shift(command, strlen(namef) + 1);
				////save file that created
				char path[_MAX_DIR];
				_getcwd(path, _MAX_DIR);
				_chdir(rootaddress);
				fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
				strcpy(fl[number_of_files].file_creator, user[andis].username);
				strcpy(fl[number_of_files].file_name, command);
				number_of_files++;
				FILE * files_list;
				files_list = fopen("files_list.bin", "wb");
				fwrite(fl, sizeof(s_file), number_of_files, files_list);
				fclose(files_list);
				_chdir(path);
				//////////
				char c = getchar();


			}
			else
			{
				printf("\nEnter 'y' or 'n'.\n");
				continue;
			}

		}
		else if (a == 0)
		{
			continue;
		}

		}

		else if (strncmp(command, "cp ", 3) == 0)
		{
			///if you want enter addres, start it whit F:\\last project\\thebest\\thebest\\thebest\\
			or
			///enter address whit '\\'
			shift(command , 3);
			char str[40];
			sprintf(str, "copy %s", command);
			system(str);
		}

		else if (strncmp(command, "mv ", 3) == 0)
		{
			///enter address whit '/'
			shift(command, 3);
			char str[40];
			sprintf(str, "move /y %s", command);
			system(str);
		}

		else if (strncmp(command, "exif ", 5) == 0)
		{ 
			shift(command, 5);
			

			/*and print creator of file*/

			struct stat file_stat;
			stat(command , &file_stat);

			//strcpy(file_stat.st_rdev, "user");

			if (stat(command , &file_stat) == 0)
			{

				char str[30];
				sprintf(str, "dir /A:-D /T:C /O:D %s", command);
				system(str);

				/*printf("\n\n----modified date and time:-----\n\n");
				char str2[30];
				sprintf(str2, "dir /T:W %s", command);
				system(str2);
*/
				for (int i = 0; i < number_of_files; i++)
				{
					if (strcmp(fl[i].file_name, command) == 0)
					{
						printf("\nThis file created by: %s", fl[i].file_creator);
						break;
					}
				}
				printFileProperties(file_stat);
			}
			else
			{
				printf("\nfile not found.\n");
				printf("\nUnable to get file properties.\n\n");

			}

		 }


		else if (strncmp(command, "myeditor ", 9) == 0)
		{
			system("cls");
			char input[25][80];
			fre(input);
			char n_file[40] = { '0' };
			shift(command, 9);
			strcpy(n_file, command);
			int edit = 0;

			
			int size = find_size_of_file(n_file);

			if (size == 0)
			{

			}
			else
			{
				FILE* file1;
				file1 = fopen(n_file, "r");
				
					gotoxy(0, 0);


					for (int i = 0; i < 25; i++)
					{
						for (int j = 0; j < 80; j++)
							input[i][j] = fgetc(file1);


					}
					fclose(file1);
					for (int i = 0; i <= 24; i++)
						for (int j = 0; j < 80; j++)
							printf("%c", input[i][j]);
					//printf("\n");
					edit = 1;
					gotoxy(0, 0);
					
				
			}
			int x = 0;
			int y = 0;
			int Z = 0;
			int X = 0;
			int S = 0;
			int R = 0;
			int F = 0;
			int contorol_x = 0;


			gotoxy(0, 25);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("^Z : exit"  ANSI_COLOR_RESET);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("\t^X : save & exit"  ANSI_COLOR_RESET);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("\t^R : open file"  ANSI_COLOR_RESET);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("\t ^S : save"  ANSI_COLOR_RESET);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("\t^F : search"  ANSI_COLOR_RESET);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("\n^C : copy"  ANSI_COLOR_RESET);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf("\tright cklick : paste"  ANSI_COLOR_RESET);

			gotoxy(0, 0);
			int list = 0;
			int save = 0;
			int filename = 0;
		

			while (1)
			{
				Z = 0;
				X = 0;
				S = 0;
				R = 0;
				F = 0;
				char v = getch();

				switch (v)
				{
				case -32:
					v = getch();

					//gotoxy(0, 25);
					if (v == 77) {
						//printf("Right Pressed\n");
						x++;
						if (x == 79)
						{
							x = 0;
							y++;
						}
						gotoxy(x, y);

					}
					if (v == 72) {
						//printf("Up Pressed\n");
						y--;
						gotoxy(x, y);

					}
					if (v == 80) {
						//printf("Down Pressed\n");
						y++;
						gotoxy(x, y);

					}
					if (v == 75) {
						//printf("Left Pressed\n");
						x--;
						gotoxy(x, y);

					}
					break;
					///enter enter
				case 13:
					y++;
					x = 0;
					gotoxy(x, y);
					break;

					///enter ^z
				case 26:
					Z++;

					break;
					///enter ^x
				case 24:
					X++;
					break;
					/// enter ^s
				case 19:
					S++;
					break;
					///enter ^R
				case 18:
					R++;
					break;
					///inter ^F
				case 6:
					F++;
					break;
					///enter backspace
				case 8:
					printf("%c", v);
					printf(" ");
					x--;
					input[y][x] = ' ';
					gotoxy(x, y);
					if (x == 0)
					{
						y--;
						x = 79;
						gotoxy(x, y);
					}

					break;
				default:

					printf("%c", v);
					input[y][x] = v;
					x++;
					if (x == 79)
					{
						printf("\n");
						input[y][x] = '\n';
						x = 0;
						y++;
						gotoxy(x, y);
					}

				}
				///////////////////end of swich
				if (F)
				{
					
					gotoxy(0, 27);
					for (int i = 0; i < 80; i++)
						printf(" ");
					gotoxy(0, 28);
					for (int i = 0; i < 80; i++)
						printf(" ");

					gotoxy(0, 26);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
					printf("\t\t\t\t\t^B : back" ANSI_COLOR_RESET);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
					printf("\t ^N : next find" ANSI_COLOR_RESET);
					gotoxy(0, 27);
					printf("Enter key word:");
					char search[30];
					int bre = 0;
					scanf("%s", search);
					gotoxy(0, 0);
					char* p = NULL;
					int n_fine = 0;
					int u = 1;
					while (u)
					{
						char b = 14;
						int i = 0;
						int k = 0;
						for (k = 0; k < 25; k++)
						{
							p = strstr(input[k], search);

							if (p)
							{

								//if (u == 1)
									//b = 14;
								//else
									// b = getch();
								///ctrl B
								if (b == 2)
								{

									gotoxy(0, 26);
									for (int i = 0; i < 80; i++)
										printf(" ");
									gotoxy(0, 26);
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
									printf("^C : copy"  ANSI_COLOR_RESET);
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
									printf("\t^P : past"  ANSI_COLOR_RESET);
									gotoxy(i, k);
									bre++;
									break;
								}
								///ctrl N
								if (b == 14)
								{
									for (i = 0; i < 80; i++)
									{
										int z = 0;
										if (p == &input[k][i])
										{
											z++;
											gotoxy(i, k);
											b = getch();
											break;
										}
										if (z)break;

									}


								}
								p = NULL;
								u++;
							}
							else
							{
								n_fine++;
								continue;
							}
						}
						if (n_fine == 25)
						{
							gotoxy(0, 28);
							printf("key word not founed.");
							gotoxy(0, 0);

							break;
						}
						else
						{
							gotoxy(0, 28);
							printf("key word founed.");
						}
						if (bre)
						{
							gotoxy(i, k);
							break;
						}
					}
				}
				if (Z)
				{

					gotoxy(0, 27);
					for (int i = 0; i < 80; i++)
						printf(" ");
					gotoxy(0, 28);
					for (int i = 0; i < 80; i++)
						printf(" ");

					if (save == 0)
					{

						gotoxy(0, 27);
						printf("Do you want to save?(y/n)");
						char q;
						scanf("%c", &q);


						if (q == 'n' || q == 'N')
						{
							system("cls");
							break;
						}
						else if (q == 'y' || q == 'Y')
						{

							if (n_file[0] == '0')
							{


								printf("Enter filename:(filename.format)");
								scanf("%s", n_file);
								if (list == 0)
								{
									////save file that created in the files_list and apdate pointer
									char path[_MAX_DIR];
									_getcwd(path, _MAX_DIR);
									_chdir(rootaddress);
									fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
									strcpy(fl[number_of_files].file_creator, user[andis].username);
									strcpy(fl[number_of_files].file_name, n_file);
									number_of_files++;
									FILE * files_list;
									files_list = fopen("files_list.bin", "wb");
									fwrite(fl, sizeof(s_file), number_of_files, files_list);
									fclose(files_list);
									_chdir(path);
									list = 1;
									//////////
								}



								FILE* file;

								file = fopen(n_file, "w");
								if (edit == 0)
								{
									for (int z = 0; z <= 24; z++)
									{
										for (int j = 0; j < 80; j++)
											fputc(input[z][j], file);///////////

										//fputc('\n', file);
									}
								}
								else if (edit)
								{

									for (int z = 0; z <= 24; z++)
									{
										for (int j = 0; j < 80; j++)
											fputc(input[z][j], file);///////////

										//fputc('\n', file);
									}
								}
								edit = 0;

								fclose(file);
								system("cls");


								break;
							}
							else
							{
								if (list == 0)
								{
									////save file that created in the files_list and apdate pointer
									char path[_MAX_DIR];
									_getcwd(path, _MAX_DIR);
									_chdir(rootaddress);
									fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
									strcpy(fl[number_of_files].file_creator, user[andis].username);
									strcpy(fl[number_of_files].file_name, n_file);
									number_of_files++;
									FILE * files_list;
									files_list = fopen("files_list.bin", "wb");
									fwrite(fl, sizeof(s_file), number_of_files, files_list);
									fclose(files_list);
									_chdir(path);
									list = 1;
									//////////
								}
								FILE* file;
								file = fopen(n_file, "w");
								if (edit == 0)
								{
									for (int z = 0; z <= 24; z++)
									{
										for (int j = 0; j < 80; j++)
											fputc(input[z][j], file);///////////

										//fputc('\n', file);
									}
								}
								else if (edit)
								{

									for (int z = 0; z <= 24; z++)
									{
										for (int j = 0; j < 80; j++)
											fputc(input[z][j], file);///////////

										//fputc('\n', file);
									}
								}
								edit = 0;
								fclose(file);
								system("cls");

								break;
							}
						}
						else
						{
							printf("please inter 'y' or 'n'.");
							gotoxy(x, y);
							continue;
						}
					}
					else if (save == 1);
					{
						system("cls");

						break;
					}
				}
				if (X)
				{

					gotoxy(0, 27);
					for (int i = 0; i < 80; i++)
						printf(" ");
					gotoxy(0, 28);
					for (int i = 0; i < 80; i++)
						printf(" ");


					if (n_file[0] == '0')
					{
						gotoxy(0, 27);

						printf("Enter filename:(filename.format)");
						scanf("%s", n_file);
						if (list == 0)
						{
							////save file that created in the files_list and apdate pointer
							char path[_MAX_DIR];
							_getcwd(path, _MAX_DIR);
							_chdir(rootaddress);
							fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
							strcpy(fl[number_of_files].file_creator, user[andis].username);
							strcpy(fl[number_of_files].file_name, n_file);
							number_of_files++;
							FILE * files_list;
							files_list = fopen("files_list.bin", "wb");
							fwrite(fl, sizeof(s_file), number_of_files, files_list);
							fclose(files_list);
							_chdir(path);
							list = 1;
							//////////
						}
						FILE* file3;
						file3 = fopen(n_file, "w");
						if (edit == 0)
						{
							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file3);///////////

								//fputc('\n', file3);
							}
						}
						else if (edit)
						{

							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file3);///////////

								//fputc('\n', file);
							}
						}
						edit = 0;
						fclose(file3);
						system("cls");
						

						break;
					}
					else
					{
						if (list == 0)
						{
							////save file that created in the files_list and apdate pointer
							char path[_MAX_DIR];
							_getcwd(path, _MAX_DIR);
							_chdir(rootaddress);
							fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
							strcpy(fl[number_of_files].file_creator, user[andis].username);
							strcpy(fl[number_of_files].file_name, n_file);
							number_of_files++;
							FILE * files_list;
							files_list = fopen("files_list.bin", "wb");
							fwrite(fl, sizeof(s_file), number_of_files, files_list);
							fclose(files_list);
							_chdir(path);
							list = 1;
							//////////
						}
						FILE* file;
						file = fopen(n_file, "w");
						if (edit == 0)
						{
							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file);///////////

								//fputc('\n', file);
							}
						}
						else if (edit)
						{

							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file);///////////

								//fputc('\n', file);
							}
						}
						edit = 0;
						fclose(file);
						contorol_x++;
						system("cls");


						break;
					}
				}

				if (S)
				{

					gotoxy(0, 27);
					for (int i = 0; i < 80; i++)
						printf(" ");
					gotoxy(0, 28);
					for (int i = 0; i < 80; i++)
						printf(" ");

					gotoxy(0, 27);
					if (n_file[0] == '0')
					{

						printf("Enter filename:(filename.format)");
						scanf("%s", n_file);

						if (list == 0)
						{
							////save file that created in the files_list and apdate pointer
							char path[_MAX_DIR];
							_getcwd(path, _MAX_DIR);
							_chdir(rootaddress);
							fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
							strcpy(fl[number_of_files].file_creator, user[andis].username);
							strcpy(fl[number_of_files].file_name, n_file);
							number_of_files++;
							FILE * files_list;
							files_list = fopen("files_list.bin", "wb");
							fwrite(fl, sizeof(s_file), number_of_files, files_list);
							fclose(files_list);
							_chdir(path);
							list = 1;
							//////////
						}
						FILE* file2;
						file2 = fopen(n_file, "w+");
						if (edit == 0)
						{
							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file2);///////////

								//fputc('\n', file2);
							}
						}
						else if (edit)
						{

							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file2);///////////

								//fputc('\n', file);
							}
						}
						edit = 0;
						printf("file saved.");

						fclose(file2);
						gotoxy(x, y);
						char c = getchar();
						continue;
					}

					else
					{

						if (list == 0)
						{
							////save file that created in the files_list and apdate pointer
							char path[_MAX_DIR];
							_getcwd(path, _MAX_DIR);
							_chdir(rootaddress);
							fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
							strcpy(fl[number_of_files].file_creator, user[andis].username);
							strcpy(fl[number_of_files].file_name, n_file);
							number_of_files++;
							FILE * files_list;
							files_list = fopen("files_list.bin", "wb");
							fwrite(fl, sizeof(s_file), number_of_files, files_list);
							fclose(files_list);
							_chdir(path);
							list = 1;
							//////////
						}
						FILE* file;
						file = fopen(n_file, "w");
						if (edit == 0)
						{
							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file);///////////

								//fputc('\n', file);
							}
						}
						else if (edit)
						{

							for (int z = 0; z <= 24; z++)
							{
								for (int j = 0; j < 80; j++)
									fputc(input[z][j], file);///////////

								//fputc('\n', file);
							}
						}
						edit = 0;

						fclose(file);
						printf("file saved.");
						gotoxy(x, y);
						continue;
					}
				}
				if (R)
				{
					///if you want edit file please don't enter, Enter key.......
					edit = 1;
					gotoxy(0, 27);
					for (int i = 0; i < 80; i++)
						printf(" ");
					gotoxy(0, 28);
					for (int i = 0; i < 80; i++)
						printf(" ");

					gotoxy(0, 27);
					printf("Enter filename:(filename.format)");
					scanf("%s", n_file);
					FILE * file1;
					file1 = fopen(n_file, "r");
					if (file1)
					{

						gotoxy(0, 0);

						for (int i = 0; i < 25; i++)
						{
							for (int j = 0; j < 80; j++)
								input[i][j] = fgetc(file1);


						}
						fclose(file1);
						for (int i = 0; i <= 24; i++)
							for (int j = 0; j < 80; j++)
								printf("%c", input[i][j]);
						//printf("\n");

						gotoxy(0, 0);
						continue;
					}
					else {


						printf("file not found.");
						gotoxy(0, 0);
						continue;
					}
				}
			}

			if(contorol_x == 0)
			char c = getchar();


		 }

		else if (strcmp(command, "myeditor\n") == 0)
		{
		system("cls");
		char input[25][80];
		fre(input);
		int x = 0;
		int y = 0;
		int Z = 0;
		int X = 0;
		int S = 0;
		int R = 0;
		int F = 0;
		int contorol_x = 0;
		int list = 0;

		gotoxy(0, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("^Z : exit"  ANSI_COLOR_RESET);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("\t^X : save & exit"  ANSI_COLOR_RESET);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("\t^R : open file"  ANSI_COLOR_RESET);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("\t ^S : save"  ANSI_COLOR_RESET);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("\t^F : search"  ANSI_COLOR_RESET);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("\n^C : copy"  ANSI_COLOR_RESET);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("\tright cklick : paste"  ANSI_COLOR_RESET);


		gotoxy(0, 0);
		int edit = 0;
		int save = 0;
		int filename = 0;
		char n_file[40] = { '0' };

		while (1)
		{
			Z = 0;
			X = 0;
			S = 0;
			R = 0;
			F = 0;
			char v = getch();

			switch (v)
			{
			case -32:
				v = getch();

				//gotoxy(0, 25);
				if (v == 77) {
					//printf("Right Pressed\n");
					x++;
					if (x == 79)
					{
						x = 0;
						y++;
					}
					gotoxy(x, y);

				}
				if (v == 72) {
					//printf("Up Pressed\n");
					y--;
					gotoxy(x, y);

				}
				if (v == 80) {
					//printf("Down Pressed\n");
					y++;
					gotoxy(x, y);

				}
				if (v == 75) {
					//printf("Left Pressed\n");
					x--;
					gotoxy(x, y);

				}
				break;
				///enter enter
			case 13:
				//printf("\n");
				//input[y][x] = v;
				y++;
				x = 0;
				gotoxy(x, y);
				break;

				///enter ^z
			case 26:
				Z++;

				break;
				///enter ^x
			case 24:
				X++;
				break;
				/// enter ^s
			case 19:
				S++;
				break;
				///enter ^R
			case 18:
				R++;
				break;
				///inter ^F
			case 6:
				F++;
				break;
				///enter backspace
			case 8:
				printf("%c", v);
				printf(" ");
				x--;
				input[y][x] = ' ';
				gotoxy(x, y);
				if (x == 0)
				{
					y--;
					x = 79;
					gotoxy(x, y);
				}

				break;
			default:

				printf("%c", v);
				input[y][x] = v;
				x++;
				if (x == 79)
				{
					printf("\n");
					input[y][x] = '\n';
					x = 0;
					y++;
					gotoxy(x, y);
				}

			}
			///////////////////end of swich
			int chom = 0;
			if (F)
			{
				chom++;
				gotoxy(0, 27);
				for (int i = 0; i < 80; i++)
					printf(" ");
				gotoxy(0, 28);
				for (int i = 0; i < 80; i++)
					printf(" ");

				gotoxy(0, 26);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
				printf("\t\t\t\t\t^B : back" ANSI_COLOR_RESET);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
				printf("\t ^N : next find" ANSI_COLOR_RESET);
				gotoxy(0, 27);
				printf("Enter key word:");
				char search[30];
				int bre = 0;
				scanf("%s", search);
				gotoxy(0, 0);
				char* p = NULL;
				int n_fine = 0;
				int u = 1;
				while (u)
				{
					char b = 14;
					int i = 0;
					int k = 0;
					for ( k = 0; k < 25; k++)
					{
						p = strstr(input[k], search);

						if (p)
						{
							
							//if (u == 1)
								//b = 14;
							//else
								// b = getch();
							///ctrl B
							if (b == 2)
							{

								gotoxy(0, 26);
								for (int i = 0; i < 80; i++)
									printf(" ");
								gotoxy(0, 26);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
								printf("^C : copy"  ANSI_COLOR_RESET);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
								printf("\t^P : past"  ANSI_COLOR_RESET);
								gotoxy(i, k);
								bre++;
								break;
							}
							///ctrl N
							if (b == 14)
							{
								for (i = 0; i < 80; i++)
								{
									int z = 0;
									if (p == &input[k][i])
									{
										z++;
										gotoxy(i, k);
										b = getch();
										break;
									}
									if (z)break;

								}


							}
							p = NULL;
							u++;
						}
						else
						{
							n_fine++;
							continue;
						}
					}
					if (n_fine == 25)
					{
						gotoxy(0, 28);
						printf("key word not founed.");
						gotoxy(0, 0);

						break;
					}
					else
					{
						gotoxy(0, 28);
						printf("key word founed.");
					}
					if (bre)
					{
						gotoxy(i, k);
						break;
					}
				}
			}
			if (Z)
			{
				

				gotoxy(0, 27);
				for (int i = 0; i < 80; i++)
					printf(" ");
				gotoxy(0, 28);
				for (int i = 0; i < 80; i++)
					printf(" ");

				if (save == 0)
				{

					gotoxy(0, 27);
					printf("Do you want to save?(y/n)");
					char q;
					
					scanf("%c", &q);
					

					if (q == 'n' || q == 'N')
					{
						system("cls");
						break;
					}
					else if (q == 'y' || q == 'Y')
					{
					
						if (n_file[0] == '0')
						{
							

							printf("Enter filename:(filename.format)");
							scanf("%s", n_file);
							if (list == 0)
							{
								////save file that created in the files_list and apdate pointer
								char path[_MAX_DIR];
								_getcwd(path, _MAX_DIR);
								_chdir(rootaddress);
								fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
								strcpy(fl[number_of_files].file_creator, user[andis].username);
								strcpy(fl[number_of_files].file_name, n_file);
								number_of_files++;
								FILE * files_list;
								files_list = fopen("files_list.bin", "wb");
								fwrite(fl, sizeof(s_file), number_of_files, files_list);
								fclose(files_list);
								_chdir(path);
								list = 1;
								//////////
							}
							FILE* file;
							
							file = fopen(n_file, "w");
							if (edit == 0)
							{
								for (int z = 0; z <= 24; z++)
								{
									for (int j = 0; j < 80; j++)
										fputc(input[z][j], file);///////////

									//fputc('\n', file);
								}
							}
							else if(edit)
							{

								for (int z = 0; z <= 24; z++)
								{
									for (int j = 0; j < 80; j++)
										fputc(input[z][j], file);///////////

									//fputc('\n', file);
								}
							}
							edit = 0;

							fclose(file);
							system("cls");
							

							break;
						}
						else 
						{
							if (list == 0)
							{
								////save file that created in the files_list and apdate pointer
								char path[_MAX_DIR];
								_getcwd(path, _MAX_DIR);
								_chdir(rootaddress);
								fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
								strcpy(fl[number_of_files].file_creator, user[andis].username);
								strcpy(fl[number_of_files].file_name, n_file);
								number_of_files++;
								FILE * files_list;
								files_list = fopen("files_list.bin", "wb");
								fwrite(fl, sizeof(s_file), number_of_files, files_list);
								fclose(files_list);
								_chdir(path);
								list = 1;
								//////////
							}
							FILE* file;
							file = fopen(n_file, "w");
							if (edit == 0)
							{
								for (int z = 0; z <= 24; z++)
								{
									for (int j = 0; j < 80; j++)
										fputc(input[z][j], file);///////////

								//	fputc('\n', file);
								}
							}
							else if (edit)
							{

								for (int z = 0; z <= 24; z++)
								{
									for (int j = 0; j < 80; j++)
										fputc(input[z][j], file);///////////

									//fputc('\n', file);
								}
							}
							edit = 0;
							fclose(file);
							system("cls");
							
							break;
						}
					}
					else
					{
						printf("please inter 'y' or 'n'.");
						gotoxy(x, y);
						continue;
					}
				}
				else if (save == 1);
				{
					system("cls");
				

					break;
				}
			}
			if (X)
			{

				gotoxy(0, 27);
				for (int i = 0; i < 80; i++)
					printf(" ");
				gotoxy(0, 28);
				for (int i = 0; i < 80; i++)
					printf(" ");

			
				if (n_file[0] == '0')
				{
					gotoxy(0, 27);

					printf("Enter filename:(filename.format)");
					scanf("%s", n_file);
					if (list == 0)
					{
						////save file that created in the files_list and apdate pointer
						char path[_MAX_DIR];
						_getcwd(path, _MAX_DIR);
						_chdir(rootaddress);
						fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
						strcpy(fl[number_of_files].file_creator, user[andis].username);
						strcpy(fl[number_of_files].file_name, n_file);
						number_of_files++;
						FILE * files_list;
						files_list = fopen("files_list.bin", "wb");
						fwrite(fl, sizeof(s_file), number_of_files, files_list);
						fclose(files_list);
						_chdir(path);
						list = 1;
						//////////
					}
					FILE* file3;
					file3 = fopen(n_file, "w");
					if (edit == 0)
					{
						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file3);///////////

							//fputc('\n', file3);
						}
					}
					else if (edit == 1)
					{

						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file3);///////////

							//fputc('\n', file);
						}
					}
					edit = 0;
					fclose(file3);
					system("cls");
					

					break;
				}
				else
				{
					if (list == 0)
					{
						////save file that created in the files_list and apdate pointer
						char path[_MAX_DIR];
						_getcwd(path, _MAX_DIR);
						_chdir(rootaddress);
						fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
						strcpy(fl[number_of_files].file_creator, user[andis].username);
						strcpy(fl[number_of_files].file_name, n_file);
						number_of_files++;
						FILE * files_list;
						files_list = fopen("files_list.bin", "wb");
						fwrite(fl, sizeof(s_file), number_of_files, files_list);
						fclose(files_list);
						_chdir(path);
						list = 1;
						//////////
					}
					FILE* file;
					file = fopen(n_file, "w");
					if (edit == 0)
					{
						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file);///////////

							//fputc('\n', file);
						}
					}
					else if (edit)
					{

						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file);///////////

							//fputc('\n', file);
						}
					}
					edit = 0;
					fclose(file);
					contorol_x++;
					system("cls");
					

					break;
				}
			}

			if (S)
			{

				gotoxy(0, 27);
				for (int i = 0; i < 80; i++)
					printf(" ");
				gotoxy(0, 28);
				for (int i = 0; i < 80; i++)
					printf(" ");

				gotoxy(0, 27);
				if (n_file[0] == '0')
				{
					
					printf("Enter filename:(filename.format)");
					scanf("%s", n_file);
					if (list == 0)
					{
						////save file that created in the files_list and apdate pointer
						char path[_MAX_DIR];
						_getcwd(path, _MAX_DIR);
						_chdir(rootaddress);
						fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
						strcpy(fl[number_of_files].file_creator, user[andis].username);
						strcpy(fl[number_of_files].file_name, n_file);
						number_of_files++;
						FILE * files_list;
						files_list = fopen("files_list.bin", "wb");
						fwrite(fl, sizeof(s_file), number_of_files, files_list);
						fclose(files_list);
						_chdir(path);
						list = 1;
						//////////
					}
					FILE* file2;
					file2 = fopen(n_file, "w+");
					if (edit == 0)
					{
						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file2);///////////

							//fputc('\n', file2);
						}
					}
					else if (edit)
					{

						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file2);///////////

							//fputc('\n', file);
						}
					}
					edit = 0;
					printf("file saved.");
					
					fclose(file2);
					gotoxy(x, y);
					char c = getchar();
					continue;
				}

				else
				{
					if (list == 0)
					{
						////save file that created in the files_list and apdate pointer
						char path[_MAX_DIR];
						_getcwd(path, _MAX_DIR);
						_chdir(rootaddress);
						fl = (s_file*)realloc(fl, (number_of_files + 1) * sizeof(s_file));
						strcpy(fl[number_of_files].file_creator, user[andis].username);
						strcpy(fl[number_of_files].file_name, n_file);
						number_of_files++;
						FILE * files_list;
						files_list = fopen("files_list.bin", "wb");
						fwrite(fl, sizeof(s_file), number_of_files, files_list);
						fclose(files_list);
						_chdir(path);
						list = 1;
						//////////
					}
					FILE* file;
					file = fopen(n_file, "w");
					if (edit == 0)
					{
						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file);///////////

							//fputc('\n', file);
						}
					}
					else if (edit == 1)
					{

						for (int z = 0; z <= 24; z++)
						{
							for (int j = 0; j < 80; j++)
								fputc(input[z][j], file);///////////

							//fputc('\n', file);
						}
					}
					edit = 0;
					contorol_x++;
					fclose(file);
					printf("file saved.");
					gotoxy(x, y);
					continue;
				}
			}
			if (R)
			{
				///if you want edit file please don't enter, Enter key.......
				edit = 1;
				gotoxy(0, 27);
				for (int i = 0; i < 80; i++)
					printf(" ");
				gotoxy(0, 28);
				for (int i = 0; i < 80; i++)
					printf(" ");

				gotoxy(0, 27);
				printf("Enter filename:(filename.format)");
				scanf("%s", n_file);
				FILE* file1;
				file1 = fopen(n_file, "r");
				if (file1)
				{
					
					gotoxy(0, 0);

					for (int i = 0; i < 25; i++)
					{
						for(int j=0 ; j < 80 ; j++)
						input[i][j] = fgetc(file1);


					}
					fclose(file1);
					for (int i = 0; i <= 24; i++)
						for(int j=0 ; j < 80 ; j++)
							printf("%c", input[i][j]);
					//printf("\n");

					gotoxy(0, 0);
					continue;
				}
				else {
					

					printf("file not found.");
					gotoxy(0, 0);
					continue;
				}
			}
		}
		//if(contorol_x == 0)
			char c = getchar();
			
		 }
		
		 else if (strncmp(command, "wc ", 3) == 0)
		 {
			 shift(command, 3);
			 char input[25][80];
			 fre(input);
			 FILE* file;
			 file = fopen(command, "r");

			 if (file)
			 {

				 for (int i = 0; i < 25; i++)
				 {
					 for (int j = 0; j < 80; j++)
						 input[i][j] = fgetc(file);
				 }
				 fclose(file);
				int line = number_of_line(input);
				int ch = number_of_char(input , line);
				int word = number_of_word(input, line);

				printf("\nnumber of line is: %d\n", line);
				printf("\nnumber of words: %d\n", word);
				printf("\nnumber of characters: %d\n\n", ch);

			 }
			 else
			 {
				 printf("\nfile not found.\n\n");
			 }
			
		}
		 else if (strcmp(command, "help\n") == 0)
		 {
			 puts("\nexit:\n\texit from OS.\n");
			 puts("clear:\n\trefresh consul and clear it.\n");
			 puts("su username:\n\tyou can enter username's account.\n");
			 puts("whoami:\n\tintroduce your account.\n");
			 puts("createuser:\n\tyou can create new user by this command.\n");
			 puts("chgr username:\n\tyou can convert simple user to admin.\n");
			 puts("passwd:\n\tyou can change your password.\n");
			 puts("passwd -l day/month/year username:\n\tjoust admin can use this command. you can ghange date of last access for username.\n");
			 puts("cd..:\n\tyou can back from this directory.\n");
			 puts("cd directoryname:\n\tyou can enter to the directory.\n");
			 puts("pwd:\n\twrite your location.\n");
			 puts("mkdir directoryname:\n\tmake a directory that name is directoryname.\n");
			puts("rm filename:\n\tyou can delete file that name is filename.\n");
			puts("rm -r directoryname:\n\tyou can delete directory that name is directoryname.\n");
			puts("ls:\n\tshow all document in this directory.\n");
			puts("cp file1 file2:\n\tthis command copy file1 to file2. and you can enter address of files whit '\\'.\n");
			puts("mv file1 file2:\n\tthes command move file1 to file2. and you cna enter address of files whit '\\'.\n");
			puts("exif filename:\n\tshow properties of file that name is filename.\n");
			puts("hidden+ filename:\n\thidden file but joust admin can enter this command.\n");
			puts("hidden- filename:\n\tvisible hidden file and joust admin can enter thes command.\n");
			puts("mkdir /h directoryname:\n\tcreate hidden directory.");
			puts("mkfile /h filename:\n\tcreate hidden file.");
			puts("wc:\n\tshow number of lines, words and character of file.\n");
			puts("myeditor:\n\topen editor whitout name.\n");
			puts("myeditor filename:\n\topen editor that name is filename.\n");
			puts("diff file1 file2:\n\tcompare file1 and file2.\n");
		}
		 else if (strncmp(command, "help ", 5) == 0)
		 {
		 shift(command, 5);

		 if (strcmp(command, "clear") == 0)
		 {
			 puts("\nclear:\n\trefresh consul and clear it.");

		 }
		 else if (strcmp(command, "diff") == 0)
		 {
			 puts("diff file1 file2:\n\tcompare file1 whit file2.\n");

		 }
		 else if (strcmp(command, "wc") == 0)
		 {
			 puts("wc:\n\tshow number of lines, words and character of file.");

		 }
		 else if (strcmp(command, "hidden") == 0)
		 {
			 puts("hidden+ filename:\n\thidden file but joust admin can enter this command.\n");
			 puts("hidden- filename:\n\tvisible hidden file and joust admin can enter thes command.\n");
			 puts("mkdir /h directoryname:\n\tcreate hidden directory.");
			 puts("mkfile /h filename:\n\tcreate hidden file.");
		 }
		 else if (strcmp(command, "exit") == 0)
			 puts("exit:\n\texit from OS.");
		 else if (strcmp(command, "su") == 0)
		 {
			 puts("su username:\n\tyou can enter username's account.");

		 }
		 else if (strcmp(command, "whoami") == 0)
		 {
			 puts("whoami:\n\tintroduce your account.");

		 }
		 else if (strcmp(command, "createuser") == 0)
		 {
			 puts("createuser:\n\tyou can create new user by this command.");

		 }
		 else if (strcmp(command, "chgr") == 0)
		 {
			 puts("chgr username:\n\tyou can convert simple user to admin.");

		 }
		 else if (strcmp(command, "passwd") == 0)
		 {
			 puts("passwd:\n\tyou can change your password.");
			 puts("passwd -l day/month/year username:\n\tjoust admin can use this command. you can ghange date of last access for username.");
		 }
		 else if (strcmp(command, "cp") == 0)
		 {
			 puts("cp file1 file2:\n\tthis command copy file1 to file2. and you can enter address of files whit '\\'.");

		 }
		 else if (strcmp(command, "mv") == 0)
		 {
			 puts("mv file1 file2:\n\tthes command move file1 to file2. and you cna enter address of files whit '\\'.");

		 }
		 else if (strcmp(command, "exif") == 0)
		 {
			 puts("exif filename:\n\tshow properties of file that name is filename.");
		 }
		 else if (strcmp(command, "myeditor") == 0)
		 {
			 puts("myeditor:\n\topen editor whitout name.");
			 puts("myeditor filename:\n\topen editor that name is filename.");
		 }
		 else if (strcmp(command, "cd") == 0)
		 {
			 puts("cd..:\n\tyou can back from this directory.");
			 puts("cd directoryname:\n\tyou can enter to the directory.");
		 }
		 else if (strcmp(command, "pwd") == 0)
		 {
			 puts("pwd:\n\tshow your location.");

		 }
		 else if (strcmp(command, "mkdir") == 0)
		 {
			 puts("mkdir directoryname:\n\tmake a directory that name is directoryname.");

		 }
		 else if (strcmp(command, "rm") == 0)
		 {
			 puts("rm filename:\n\tyou can delete file that name is filename.");
			 puts("rm -r directoryname:\n\tyou can delete directory that name is directoryname.");
		 }
		 else if (strcmp(command, "ls") == 0)
		 {
			 puts("ls:\n\tshow all document in this directory. ");

		 }





		}

		 else if (strncmp(command, "diff ", 5) == 0)
		 {
			 shift(command, 5);
			 char file1[30];
			 char file2[30];
			 for (int i = 0; ; i++)
			 {
				 file1[i] = command[i];
				 if (command[i] == ' ')
				 {
					 file1[i] = '\0';
					 shift_wo(command, i+1);
					 strcpy(file2, command);
					 break;
				 }
			 }
			 struct tm ti1;
			 struct tm ti2;
			 struct stat fil1;
			 struct stat fil2;
			 stat(file1, &fil1);
			 stat(file2, &fil2);
			 if(stat(file1, &fil1)==0  && stat(file2, &fil2)==0)
			 {
				 printf("\n\tsize of %s: %d\n",file1 ,  fil1.st_size);
				 printf("\tsize of %s: %d\n\n\n", file2, fil2.st_size);

				 ti1 = *(gmtime(&fil1.st_ctime));
				 ti2 = *(gmtime(&fil2.st_ctime));
				 printf("\t%s Created on: %d/%d/%d\t %d:%d:%d\n",file1 , ti1.tm_mday, ti1.tm_mon + 1, ti1.tm_year + 1900,
					 ti1.tm_hour, ti1.tm_min, ti1.tm_sec);
				 printf("\t%s Created on: %d/%d/%d\t %d:%d:%d\n\n\n",file2 , ti2.tm_mday, ti2.tm_mon + 1, ti2.tm_year + 1900,
					 ti2.tm_hour, ti2.tm_min, ti2.tm_sec);

				 ti1 = *(gmtime(&fil1.st_mtime));
				 ti2 = *(gmtime(&fil2.st_mtime));
				 printf("\t%s time of last Modified: %d/%d/%d\t %d:%d:%d\n", file1, ti1.tm_mday, ti1.tm_mon + 1, ti1.tm_year + 1900,
					 ti1.tm_hour, ti1.tm_min, ti1.tm_sec);
				 printf("\t%s time of last Modified: %d/%d/%d\t %d:%d:%d\n\n\n", file2, ti2.tm_mday, ti2.tm_mon + 1, ti2.tm_year + 1900,
					 ti2.tm_hour, ti2.tm_min, ti2.tm_sec);

				 ti1 = *(gmtime(&fil1.st_atime));
				 ti2 = *(gmtime(&fil2.st_atime));
				 printf("\t%s time of last access: %d/%d/%d\t %d:%d:%d\n", file1, ti1.tm_mday, ti1.tm_mon + 1, ti1.tm_year + 1900,
					 ti1.tm_hour, ti1.tm_min, ti1.tm_sec);
				 printf("\t%s time of last access: %d/%d/%d\t %d:%d:%d\n\n\n", file2, ti2.tm_mday, ti2.tm_mon + 1, ti2.tm_year + 1900,
					 ti2.tm_hour, ti2.tm_min, ti2.tm_sec);

			 }
			 else
			 {
				 printf("\nfiles not found.\n\n");
				// printf("%s\n", file1);
				 //printf("%s\n", file2);
			 }

		}

		 else if (strncmp(command, "hidden+ ", 8) == 0)
		 {
			 if (user[andis].S_dastresi == 1)
			 {
			 shift(command, 8);
			 char str[50];
			 sprintf(str, "attrib +h %s", command);
			 puts("");
			 system(str);
			 puts("");
			 }
			 else
				 {
					 printf("\nyou can't enter this command.\n\n");
				 }
		 }
		 else if (strncmp(command, "hidden- ", 8) == 0)
		 {
		 if (user[andis].S_dastresi == 1)
		 {
			 shift(command, 8);
			 char str[50];
			 sprintf(str, "attrib -h %s", command);
			 puts("");
			 system(str);
			 puts("");
		 }
		 else
		 {
			 printf("\nyou can't enter this command.\n\n");
		 }
		 }

		 else if (strncmp(command, "find ", 5) == 0)
		 {
			 shift(command, 5);
			 char str[50];
			 sprintf(str, "dir /s /b %s", command);
			 puts("");
			 system(str);
			 puts("");

		 }

		else if (strcmp(command, "exit\n") == 0)
		{
			free(user);
			break;

		}

		else
		{

			printf("\nyour command is incorect.\n\n");
			user[andis].fail++;

			char path[_MAX_DIR];
			_getcwd(path, _MAX_DIR);
			_chdir("F:\\last project\\thebest\\thebest\\thebest");
			FILE* users_list;
			users_list = fopen("users_list.bin", "wb");
			fwrite(user, sizeof(struct users), number_of_users, users_list);
			fclose(users_list);

			///apdate *struct
			users_list = fopen("users_list.bin", "rb");
			fread(user, sizeof(struct users), number_of_users, users_list);
			fclose(users_list);
			char buffer[30];
			sprintf(buffer, "%s", user[andis].username);
			_chdir(path);
			continue;
		}


	}



	return 0;
}



void pass_star(char pass[256])
{

	char c;
	int i = 0;
	while (i < 255)
	{
		c = getch();

		if (c == 13)
		{
			pass[i] = '\0';
			break;
		}
		else if (c == 8)
			i -= 2;

		pass[i] = c;

		i++;
	}



}


void creat_user(FILE * users_list)
{
	s_user newuser;
	
	printf("Is thes user admin?[y/n]");
	char q;
	scanf("%c", &q);
	if (q == 'y' || q=='Y')newuser.S_dastresi = 1;
	else if (q == 'n' || q == 'N')newuser.S_dastresi = 0;
	else
	{
		printf("\nplaese enter 'y' or 'n' .\n\n");
		return;
	}
	printf("Enter new name:");
	scanf("%s", newuser.name);
	printf("enter new username:");
	scanf("%s", newuser.username);
	printf("Enter max date of user :[day mounth year] ");
	scanf("%d", &newuser.day_end);
	scanf("%d", &newuser.mounth_end);
	scanf("%d", &newuser.year_end);

	char pass_again[256]={0};
	while (1)
	{
		printf("enter password [max length 255]:");
		pass_star(newuser.pass);


		
		printf("\nconfirm password:");

		pass_star(pass_again);



		if (strcmp(newuser.pass, pass_again) == 0)
		{
			if (percent_pass_str(newuser.pass) > 33 && newuser.S_dastresi == 0)
			{
				char buffer[256];
				printf("\nthe user creat successfuly.\n");
				number_of_users++;
				newuser.fail = 0;
				newuser.pass_str = percent_pass_str(newuser.pass);
				user = (s_user*)realloc(user, number_of_users * sizeof(s_user));

				///make a directory for user
				sprintf(buffer, "%s", newuser.username);
				_mkdir(buffer);

				///add user's characteristecs in users-list
				fwrite(&newuser, sizeof(s_user), 1, users_list);


				return;
			}
			else if (percent_pass_str(newuser.pass) > 75 && newuser.S_dastresi == 1)
			{

				char buffer[256];
				printf("\n\nthe user creat successfuly.\n");
				number_of_users++;
				newuser.fail = 0;
				newuser.pass_str = percent_pass_str(newuser.pass);
				user = (s_user*)realloc(user, number_of_users * sizeof(s_user));

				///make a directory for user
				sprintf(buffer, "%s", newuser.username);
				_mkdir(buffer);
				///add user's characteristecs in users-list
				fwrite(&newuser, sizeof(s_user), 1, users_list);

				return;
			}
			else

			{
			
				printf("\n\nyour password is not strong enough.\n\nplease enter password agian.\n\n");
				continue;
			}
		}
		else
		{
			printf("\n\npassword not match.please try agian.\n\n");
			continue;
		}
	}


}

int percent_pass_str(char pass[100])
{
	int darsad_amniyat = 0;
	for (int i = 0; pass[i] != '\0'; i++)
	{
		if (islower(pass[i]))darsad_amniyat += 2;
		else if (isupper(pass[i]))darsad_amniyat += 4;
		else if (isdigit(pass[i]))darsad_amniyat += 3;
		else if (pass[i] == ' ')darsad_amniyat += 1;
		else if (isprint(pass[i]))darsad_amniyat += 8;

	}
	if (darsad_amniyat >= 100)darsad_amniyat = 100;
	return darsad_amniyat;

}


int find_size_of_file(char filename[])
{
	FILE* pf;
	pf = fopen(filename, "a");

	fseek(pf, 0L, SEEK_END);

	int size = ftell(pf);
	fclose(pf);
	return size;

}
 
int time_use(int d, int m, int y)
{
	int n_d, n_m, n_y;

	time_t now;
	time(&now);
	struct tm* local = localtime(&now);

	n_d = local->tm_mday;
	n_m = local->tm_mon + 1;
	n_y = local->tm_year + 1900;

	if (y > n_y)
		return 1;
	else
	{
		if (y == n_y)
		{
			if (m > n_m)
			{
				return 1;
			}
			else
			{
				if (m == n_m)
				{
					if (d > n_d)
						return 1;
					else
					{
						if (d == n_d)
							return 1;
						else
							return 0;
					}

				}
				else
					return 0;
			}
		}
		else
			return 0;

	}
}

void shift(char str[], int T)
{
	int t = T;
	int i = 0;
	for (i = 0; str[i+t] != '\0'; i++)
	{
		str[i] = str[T];
		T++;
	}
	str[i-1] = '\0';

}

void shift_wo(char str[], int T)
{
	int t = T;
	int i = 0;
	for (i = 0; str[i + t] != '\0'; i++)
	{
		str[i] = str[T];
		T++;
	}
	str[i] = '\0';

}

int check1(char str[])
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '>' && str[i + 1] != '>')
			return 1;

	}
	return 0;
}

int check2(char str[])
{

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return 1;

	}
	return 0;
}
void cut(char str[], char command[])
{
	int i = 0;
	for (i = 0; command[i] != '>'; i++)
	{
		str[i] = command[i];
	}
	str[i] = '\0';

}

void printFileProperties(struct stat file_stat)
{

	struct tm dt;


	printf("\n\nFile size: %d", file_stat.st_size);

	// Get file creation time in seconds and 
   // convert seconds to date and time format
	dt = *(gmtime(&file_stat.st_ctime));
	printf("\n\nCreated on: %d/%d/%d\t %d:%d:%d", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
		dt.tm_hour, dt.tm_min, dt.tm_sec);


	// File modification time
	dt = *(gmtime(&file_stat.st_mtime));
	printf("\n\ntime of last Modified: %d/%d/%d\t %d:%d:%d", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
		dt.tm_hour, dt.tm_min, dt.tm_sec);
	// time of last access
	dt = *(gmtime(&file_stat.st_atime));
	printf("\n\ntime of last access: %d/%d/%d\t %d:%d:%d\n\n", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
		dt.tm_hour, dt.tm_min, dt.tm_sec);

	//printf("\n\nowner: %u \n\n", file_stat.st_uid);


}
void fre(char input[][80])
{
	for (int i = 0; i <= 24; i++)
		for (int j = 0; j < 80; j++)
		{
			input[i][j] = ' ';
			if (j == 79)input[i][j] = '\n';
		}
}

int number_of_line(char str[][80])
{
	int t = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < 25; i++)
	{
		t = 0;
		for (j = 0; j < 80; j++)
		{
			if (str[i][j] == ' ')
				t++;
			else break;

			//if (isalnum(str[i][j]))
			//	break;
			//else
			//{
			//	t++;
			//}
		}
		if (t == 79)break;

	}
	return i;
}
int number_of_char(char str[][80] , int line)
{
	int c = 0;
	for (int i = 0; i < line; i++)
		for (int j = 0; j < 80; j++)
			if ((isalnum(str[i][j]) && str[i][j] != ' ' ) || (ispunct(str[i][j]) && str[i][j] != ' '))
				c++;

	return c;

}
int number_of_word(char str[][80], int line)
{
	int w = 0;
	for (int i = 0; i < line; i++)
		for (int j = 1; j < 79; j++)
			if (str[i][j] == ' ' && isalnum(str[i][j - 1]) && isalnum(str[i][j + 1]))
				w++;
	return w + line;

}

