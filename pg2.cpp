#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <string.h>
#include <process.h>

fstream fp;
int n = 0;
char fname[10];
class student
{
private:
    char usn[10], name[10], branch[5];

public:
    void pack();
    void unpack(char[]);
    void display();
    void search();
};
void student ::pack()
{
    char buffer[28];
    cout << "enter the USN,Name and Branch: ";
    cin >> usn >> name >> branch;
    strcpy(buffer, usn);
    strcat(buffer, "|");
    strcat(buffer, name);
    strcat(buffer, "|");
    strcat(buffer, branch);
    strcat(buffer, "|");
    int len = strlen(buffer);
    while (len < 27)
    {
        strcat(buffer, "#");
        len++;
    }
    buffer[27] = '\0';
    fp << buffer << '\n';
}
void student::unpack(char buffer[])
{
    char *t;
    t = strtok(buffer, "|");
    cout << "USN:" << t << endl;
    t = strtok(NULL, "|");
    cout << "Name:" << t << endl;
    t = strtok(NULL, "|");
    cout << "Branch:" << t << endl;
}
void student::display()
{
    char buffer[28];
    int i, j;
    if (n == 0)
    {
        cout << "No records to display";
        return;
    }
    cout << "\nFile Contents are \n";
    fp.open(fname, ios::in);
    for (i = 1; i <= n; i++)
    {
        fp >> buffer;
        unpack(buffer);
        cout << endl;
    }
    fp.close();
}
void student::search()
{
    char buffer[28], temp[28];
    char key[15];
    char *usn;
    int i, j, k, choice;
    cout << "Enter the USN to search: ";
    cin >> key;
    fp.open(fname, ios::in | ios::out);
    for (i = 1; i <= n; i++)
    {
        fp >> buffer;
        strcpy(temp, buffer);
        usn = strtok(temp, "|");
        if (strcmp(key, usn) == 0)
        {
            cout << "\nRecord Found..\n";
            unpack(buffer);
            cout << endl;
            cout << "\nDo you wish to modify?\n";
            cout << "\nEnter your choice \n 1.Yes \n 2.No\n";
            cin >> choice;
            if (choice == 1)
            {
                fp.seekp(-27, ios::cur);
                pack();
            }
            fp.close();
            return;
        }
    }
    cout << "Record not found..!\n";
    fp.close();
    getch();
}
void main()
{
    int i, ch;
    student s1;
    clrscr();
    cout << "Enter the File Name : ";
    cin >> fname;
    fp.open(fname, ios::out | ios::trunc);
    fp.close();
    for (;;)
    {
        cout << "\n 1.Insert\n 2.Display\n 3.Search and Modify\n 4.Exit \n";
        cout << "Enter Your Choice\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            n++;
            fp.open(fname, ios::app);
            s1.pack();
            fp.close();
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
            cout << "Invalid Choice..!\n";
        }
    }
}