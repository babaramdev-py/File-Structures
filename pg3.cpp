#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
fstream fp1, fp2;
int n = 0;
char fname[10];
class student
{
private:
    char usn[15], name[15], branch[5];

public:
    void pack(int);
    void unpack(char[]);
    void display();
    void search();
};
void student ::pack(int a)
{
    char buffer[100];
    cout << "Enter the student USN, Name and Branch:";
    cin >> usn >> name >> branch;
    strcpy(buffer, usn);
    strcat(buffer, "|");
    strcat(buffer, name);
    strcat(buffer, "|");
    strcat(buffer, branch);
    if (a == 1)
    {
        fp1 << buffer;
        fp1 << "\n";
    }
    else
    {
        fp2 << buffer;
        fp2 << "\n";
    }
}
void student::display()
{
    char buffer[100];
    int i, j;
    cout << "\nFile Contents are \n";
    fp1.open(fname, ios::in);
    for (i = 1; i <= n; i++)
    {
        fp1 >> buffer;
        unpack(buffer);
    }
    fp1.close();
}
void student::unpack(char buffer[])
{
    char *t;
    t = strtok(buffer, "|");
    cout << "\nUSN : " << t << endl;
    t = strtok(NULL, "|");
    cout << "Name : " << t << endl;
    t = strtok(NULL, '\0');
    cout << "Branch :" << t << endl;
}
void student::search()
{
    char buffer[100], temp[100];
    char *usn;
    char key[15];
    int i, choice;
    cout << "\nEnter the USN to search : ";
    cin >> key;
    fp1.open(fname, ios::in);
    fp2.open("out.txt", ios::out);
    for (i = 1; i <= n; i++)
    {
        fp1 >> buffer;
        strcpy(temp, buffer);
        usn = strtok(buffer, "|");
        if (strcmp(usn, key) == 0)
        {
            cout << "Record Found\n";
            unpack(buffer);
            cout << "\n Do you wish to modify?" << endl;
            cout << "\n1.Yes \n2.No : ";
            cin >> choice;
            if (choice == 1)
            {
                pack(2);
                while (!fp1.fail())
                {
                    fp1 >> buffer;
                    fp2 << buffer << "\n";
                }
                fp1.close();
                fp2.close();
                remove(fname);
                rename("out.txt", fname);
                return;
            }
            else
            {
                fp1.close();
                fp2.close();
                remove("out.txt");
            }
        }
        else
        {
            fp2 << buffer;
            fp2 << "\n";
        }
    }
    cout << "Record not found";
    fp1.close();
    fp2.close();
    remove("out.txt");
}
void main()
{
    int i, ch;
    student s1;
    clrscr();
    cout << "Enter the file name : ";
    cin >> fname;
    fp1.open(fname, ios::out | ios::trunc);
    fp1.close();
    for (;;)
    {
        cout << "\n 1.Insert\n 2.Display\n 3.Search and Modify\n 4.Exit \n";
        cout << "Enter Your Choice\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            n++;
            fp1.open(fname, ios::app);
            s1.pack(1);
            fp1.close();
            break;
        case 2:
            s1.display();
            break;
        case 3:
            s1.search();
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid Choice\n";
        }
    }
}