#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<iomanip.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
class user
{char username[30];
char password[10];
public:
void get_username()
{cout<<"\nEnter username: ";
gets(username);
cout<<"\nEnter password: ";
gets(password);
}
char* returnpass()
{return password;}
char*returnname()
{return username;}
};

class book
{char book_number[30];
char book_name[50];
char author_name[20];
int num_copies;
public:
void get_book_details()
{cout<<"\nENTER DETAILS ABOUT BOOK \n";
cout<<"\nEnter The Book Number: ";
gets(book_number);
cout<<"\nEnter The Name of The Book: ";
gets(book_name);
cout<<"\nEnter The Author's Name: ";
gets(author_name);
cout<<"\nEnter No. Of Copies : ";
cin>>num_copies;
}
void show_book()
{cout<<"\nBook Number: ";
puts(book_number);
cout<<"\nBook Name: ";
puts(book_name);
cout<<"\nAuthor's Name: ";
puts(author_name);
cout<<"\nCOPIES : "<<num_copies;
}
void modify_book()
{cout<<"\nBOOK NUMBER OF THE BOOK TO BE MODIFIED ";
cin>>book_number;
 cout<<"\nModify Book Name : ";
 gets(book_name);
 cout<<"\nModify Author's Name: ";
 gets(author_name);
 cout<<"\nEnter No. Of Copies : ";
 cin>>num_copies;

}
char* getbooknumber()
{
return book_number;
}
void report()
{
cout<<book_number<<setw(25)<<book_name<<setw(15)<<author_name<<setw(25)<<num_copies<<endl;
}

}; //end of the class

fstream fp; //global declaration of file fp
fstream users;
book bk;  //object which along to class book
user u;
void write_book()
{ cout<<"\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
 cout<<"\nFUNCTION TO ADD BOOKS";
 cout<<"\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";

          int more_or_mainmenu;
          fp.open("book.dat",ios::out|ios::app|ios::binary);
          do
          {
                    bk.get_book_details();
                    fp.write((char*)&bk,sizeof(book));
                    cout<<"\nPress 1 to add more books.";
                    cout<<"\nPress 2 to return to main menu.\n";
                    cout<<"Enter: ";
                    cin>>more_or_mainmenu;
          }while(more_or_mainmenu == 1);
          fp.close();
}

void display_a_book(char n[])
{

          cout<<"\nBOOK DETAILS\n";
          int check=0;
          fp.open("book.dat",ios::in);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                              check=1;
                    }
          }
          fp.close();
          if(check==0)
         cout<<"\n\nBook does not exist";
        getch();
}

void modify_book()
{

          char n[20];
          int found=0;
          cout<<"\n\n\tMODIFY BOOK";
          cout<<"\n\n\tEnter The book number: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out|ios::binary);
          while(fp.read((char*)&bk,sizeof(book)) && found==0)
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                               cout<<"\nEnter The New Details of book"<<endl;
                               bk.modify_book();
                               int pos=-1*sizeof(bk);
                              fp.seekp(pos,ios::cur);
                              fp.write((char*)&bk,sizeof(book));
                              cout<<"\n\n\t Record Updated Successfully...";
                              found=1;
                    }
          }
          fp.close();
          if(found==0)
                    cout<<"\n\n Record Not Found ";
          getch();
}

void delete_book()
{

          char n[20];
          int flag=0;
          cout<<"\n\n\n\tDELETE BOOK";
          cout<<"\n\nEnter The Book's number You Want To Delete: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out|ios::binary);
          fstream fp2;
          fp2.open("Temp.dat",ios::out);
          fp.seekg(0,ios::beg);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)!=0)
                    {
                               fp2.write((char*)&bk,sizeof(book));
                    }
                    else
                              flag=1;
          }
          fp2.close();
          fp.close();
          remove("book.dat");
          rename("Temp.dat","book.dat");
          if(flag==1)
                    cout<<"\n\n\tRecord Deleted ..";
          else
                    cout<<"\n\nRecord not found";
          getch();
}

void display_allbook()
{

          fp.open("book.dat",ios::in|ios::binary);
          if(!fp)
          {
                    cout<<"ERROR!!! FILE  NOT FOUND ";
                    getch();
                    return;
          }
          cout<<"\n\n\t\tBook LIST\n\n";
         cout<<"===============================================================================\n";
          cout<<"| Book Number |"<<setw(10)<<"| Book Name |"<<setw(15)<<"| Author |"<<setw(30)<<"| Copies |"<<endl;
          cout<<"==============================================================================\n";
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    bk.report();
          }
          fp.close();
          getch();
}
void admin()
{
           system("color E9");
          int option = 0;
            cout<<"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
            cout<<"\n\t\t WELCOME BOOKSHOP STAFF";
             cout<<"\n\t\tPress 1 to TO ADD BOOK";
                cout<<"\n\t\tPress 2 to SHOW ALL BOOKS";
                cout<<"\n\t\tPress 3 to CHECK AVAILABILITY";
                cout<<"\n\t\tPress 4 to MODIFY BOOKS";
                cout<<"\n\t\tPress 5 to DELETE BOOKS";
                cout<<"\n\t\tPress 6 to Exit";
            cout<<"\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
  cout<<"\n\t\tEnter your Option: ";

  cin>>option;
  switch(option)
          {
                    case 1:system("color B2");
                           write_book();
                          system("cls");
                           break;
                    case 2: system("color D0");
                            display_allbook();
                            system("cls");
                            break;
                    case 3:   system("color A3");
                              char num[20];
                              system("cls");
                              cout<<"\n\n\tPlease Enter The book No. ";
                              cin>>num;
                              display_a_book(num);
                              break;
                    case 4:  system("color F0");
                             modify_book();
                             system("cls");
                             break;
                    case 5:  system("color E5");
                             delete_book();
                             system("cls");
                             break;
                    case 6: exit(0);
                            break;
                    default:cout<<"INVALID OPTION";
          }



}


void passage()
{int d=0;
cout<<"\nNEW USER? ENTER 0";
cout<<"\nOLD USER? ENTER 1";
int opp;
cout<<"\nENTER YOUR OPTION: ";
cin>>opp;
if(opp==0)
{users.open("u.dat",ios::out|ios::in|ios::binary);
 u.get_username();
 users.write((char*)&u,sizeof(u));
 cout<<"\n****MESSAGE: WELCOME NEW USER****";
 cout<<"\nENTER 2 TO CONTINUE: ";
 cin>>d;
if(d==2)
admin();
else
cout<<"****WARNING: ERROR";
}
if(opp==1)
{users.open("u.dat",ios::in|ios::out|ios::binary);
char us[30];
char ps[10];
cout<<"\nENTER USERNAME: ";
gets(us);
cout<<"\nENTER PASSWORD: ";
gets(ps);
while(users.read((char*)&u,sizeof(u)))
 {
                    if(strcmp(u.returnname(),us)==0)
                    {if(strcmp(u.returnpass(),ps)==0)
                      admin();
                    }


}
if(d!=2)
{cout<<"***ERROR: INCORRECT USERNAME***";}
}
users.close();

}

 void main()
{for(;;)
 {int op;
   op=0;
cout<<"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
                cout<<"\t\tWELCOME TO THE WINNER'S BOOKSHOP";
                cout<<"\n\t\tPress 1 to CONTINUE AS BOOKSHOP STAFF";
                cout<<"\n\t\tPress 2 to  CONTINUE AS CUSTOMER";
                cout<<"\n\t\tPress 3 to Exit";
 cout<<"\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
 cout<<"\n\t\tEnter your Option: ";
 cin>>op;
 if(op==1)
 passage();
 if(op==2)
 {system("color E9");
  cout<<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
  cout<<"\n\t\tWELCOME CUSTOMER TO WINNER'S BOOKSHOP";
  cout<<"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
  cout<<"\nTHE BOOKS AVAILABLE IN OUR SHOP : ";
  display_allbook();
  system("cls");
 }
 if(op==3)
 exit(0);
 if(op!=1&&op!=2&&op!=3)
 cout<<"\n***ERROR:enter valid input***";
 }


getch();
}

