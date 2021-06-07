#include<stdio.h>
#include<string.h>
#include "car.h"
#include "conio2.h"
#include <time.h>
#include<stdlib.h>

int isVaildDate(struct tm dt)
{
    if(dt.tm_year>=2020 && dt.tm_year<=2022)
    {
        if(dt.tm_mon>=1 && dt.tm_mon<=12)
        {
            if((dt.tm_mday>=1 && dt.tm_mday<=31)&& (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 || dt.tm_mon==7 || dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
                return 1;
            else if((dt.tm_mday>=1 && dt.tm_mday<=30) && (dt.tm_mon==4 || dt.tm_mon==6 || dt.tm_mon==9 || dt.tm_mon==11))
                return 1;
            else if((dt.tm_mday>=1 && dt.tm_mday<28) && (dt.tm_mon==2))
                return 1;
            else if(dt.tm_mday==29 && dt.tm_mon==2 && (dt.tm_year%400==0||(dt.tm_year%4==0 && dt.tm_year%100!=0)))
                return 1;
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


void selectCarModel(char *c)
{
    FILE *fp=fopen("car.bin","rb");
    car C;
    int i;
    char sub[3];
    int id;
    int choice,x=11;
    gotoxy(40,x);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            sub_str(C.car_id,sub,'-');
            id=atoi(sub);
            printf("%d . %s",id,C.car_name);
            gotoxy(40,++x);
        }
    }
    gotoxy(1,x+4);
    textcolor(LIGHTCYAN);
    for(i=0;i<120;i++)
        printf("%c",247);
    gotoxy(38,x+2);
    printf("Enter your choice : ");
    while(1)
    {
        scanf("%d",&choice);
        fflush(stdin);
        if(choice=='\n')
        {
            gotoxy(30,x+6);
            textcolor(RED);
            printf("Wrong Input. Press any key to continue...");
            _getch();
            gotoxy(38,x+6);
            printf("\t\t");
            gotoxy(58,x+2);
            printf("\t");
            gotoxy(58,x+2);
            textcolor(WHITE);
            continue;
        }
        rewind(fp);
        while(fread(&C,sizeof(C),1,fp)==1)
        {
            sub_str(C.car_id,sub,'-');
            id=atoi(sub);
            if(id==choice && C.car_count>0)
            {
                textcolor(LIGHTCYAN);
                gotoxy(1,x+4);
                for(i=0;i<120;i++)
                    printf("%c",247);
                strcpy(c,C.car_id);
                gotoxy(40,x+6);
                textcolor(LIGHTGREEN);
                printf("Car Selected. Enter Details...");
                _getch();
                return;
            }
        }
        gotoxy(40,x+6);
        textcolor(RED);
        printf("Wrong Input.Press any to continue..");
        _getch();
        gotoxy(38,x+6);
        printf("\t\t\t\t\t\t");
        gotoxy(58,x+2);
        printf("\t");
        gotoxy(58,x+2);
        textcolor(WHITE);
    }
}



void addAdmin()
{
    FILE *fp;
    fp=fopen("admin.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("admin.bin","wb");
        user u[4]={{"ad-1","ameen","ameen123"},{"ad-2","aftab","abc"},{"ad-3","Md Aftab Ahmed","xyz"}};
        fwrite(u,sizeof(u),1,fp);
        fclose(fp);
        gotoxy(5,21);
        textcolor(LIGHTRED);
        printf("File Saved!");
        _getch();
    }
    else
    {
        fclose(fp);
    }

}
user *getInput()
{
    int i;
    clrscr();
    textcolor(YELLOW);
    gotoxy(50,4);
    printf("CAR RENTAL SYSTEM\n");
    gotoxy(50,5);
    textcolor(LIGHTGREEN);
    printf("~~~~~~~~~~~~~~~~~");
    gotoxy(53,7);
    textcolor(YELLOW);
    printf("LOGIN PANEL");
    gotoxy(53,8);
    textcolor(LIGHTGREEN);
    printf("~~~~~~~~~~~");
    gotoxy(1,10);
    textcolor(RED);
    for(i=0;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,18);
    for(i=0;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(80,11);
    textcolor(WHITE);
    printf("Press 0 to exit");
    gotoxy(35,13);
    textcolor(LIGHTCYAN);
    printf("Enter User Id : ");
    fflush(stdin);
    textcolor(WHITE);
    static user usr;
    fgets(usr.userid,20,stdin);
    char *pos;
    pos=strchr(usr.userid,'\n');
    *pos='\0';
    if(strcmp(usr.userid,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(20,21);
        printf("Login Cancelled..Press any key to continue...");
        _getch();
        return NULL;
    }
    gotoxy(35,15);
    textcolor(LIGHTCYAN);
    printf("Enter Password : ");
    fflush(stdin);
    textcolor(WHITE);
    i=0;
    for(;;)
    {
        usr.pwd[i]=getch();
        if(usr.pwd[i]==13)
        {
            break;
        }
        if(usr.pwd[i]==8)
        {
            i--;
            gotoxy(52+i,15);
            printf("  ");
            gotoxy(52+i,15);
            continue;
        }
        printf("*");
        i++;
    }
    usr.pwd[i]='\0';
    if(strcmp(usr.pwd,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(20,21);
        printf("Login Cancelled..Press any key to continue...");
        _getch();
        return NULL;
    }
    return &usr;
}


int  checkUserExist(user u, char *usertype)
{
    if(strcmp(u.userid,"")==0||strcmp(u.pwd,"")==0)
    {
        gotoxy(20,21);
        textcolor(LIGHTRED);
        printf("BOTH THE FIELDS ARE MANDATORY. Retry...");
        _getch();
        gotoxy(20,21);
        printf("\t\t\t\t\t\t\t\t");
        return 0;
    }
    int found=0;
    if(!(strcmp(usertype,"admin")))
    {
        FILE *fp=fopen("admin.bin","rb");
        user user;
        while((fread(&user,sizeof(user),1,fp))==1)
        {
            if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            gotoxy(20,21);
            textcolor(LIGHTRED);
            printf("INVALID USERNAME OR PASSWORD. Re-Enter Details...");
            _getch();
            fclose(fp);
            return 0;
        }
        fclose(fp);
        return 1;
    }
    else if(!(strcmp(usertype,"emp")))
    {
        FILE *fp=fopen("emp.bin","rb");
        user user;
        while((fread(&user,sizeof(user),1,fp))==1)
        {
            if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            gotoxy(20,21);
            textcolor(LIGHTRED);
            printf("INVALID USERNAME OR PASSWORD. Re-Enter Details...");
            _getch();
            fclose(fp);
            return 0;
        }
        fclose(fp);
        return 1;
    }
    return 0;
}


int adminMenu()
{
    int choice,i;
    textcolor(RED);
    gotoxy(48,4);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(48,5);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTGREEN);
    gotoxy(51,6);
    printf("ADMIN MENU ");
    textcolor(YELLOW);
    gotoxy(51,7);
    printf("~~~~~~~~~~ \n\n");
    textcolor(LIGHTRED);
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    gotoxy(1,23);
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(42,11);
    printf("1. Add Employee");
    gotoxy(42,12);
    printf("2. Add Car Details");
    gotoxy(42,13);
    printf("3. Show Employee");
    gotoxy(42,14);
    printf("4. Show Car Details");
    gotoxy(42,15);
    printf("5. Delete Employee");
    gotoxy(42,16);
    printf("6. Delete Car Details");
    gotoxy(42,17);
    printf("7. Update a Car");
    gotoxy(42,18);
    printf("8. Exit");
    gotoxy(42,21);
    printf("Enter Your Choice : ");
    textcolor(WHITE);
    scanf("%d",&choice);

    return choice;
}



int addEmployee()
{
    FILE *fp = fopen("emp.bin","rb");
    int id,k;
    char uchoice;
    char emp[10] = "EMP-";
    char empid[10];
    user u,ur;
    if(fp == NULL)
    {
        fp = fopen("emp.bin","ab");
        id = 1;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");
        k=1;
    }
    else
    {
        fp = fopen("emp.bin","ab+");
        fseek(fp,-60,SEEK_END);
        fread(&ur,sizeof(ur),1,fp);
        id = getempid();
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");
        k=0;
    }
    do
    {
        clrscr();
        gotoxy(48,2);
        textcolor(RED);
        printf("CAR RENTAL APP");
        textcolor(YELLOW);
        gotoxy(48,3);
        printf("~~~~~~~~~~~~~~");
        textcolor(LIGHTGREEN);
        int i;
        gotoxy(1,5);
        for(i=0;i<120;i++)
        {
            printf("*");
        }
        gotoxy(1,16);
        for(i=0;i<120;i++)
        {
            printf("*");
        }
        gotoxy(80,17);
        textcolor(WHITE);
        printf("Press 0 to exit.");
        textcolor(WHITE);
        gotoxy(38,7);
        printf("*****  ADD EMPLOYEE DETAILS *****");
        gotoxy(25,10);
        textcolor(YELLOW);
        printf("Enter Employee Name : ");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.name,20,stdin);
        char *pos;
        pos = strchr(u.name,'\n');
        *pos = '\0';
        if(u.name[0]=='0'||u.name[0]=='\0')
        {
            gotoxy(30,19);
            textcolor(RED);
            printf("Process Canceled...");
            if(k==1)
                remove("emp.bin");
            _getch();
            fclose(fp);
            return 1;
        }
        textcolor(YELLOW);
        gotoxy(25,12);
        printf("Enter Employee Pwd : ");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.pwd,20,stdin);
        pos = strchr(u.pwd,'\n');
        *pos = '\0';
        if(u.pwd[0]=='0'||u.pwd[0]=='\0')
        {
            gotoxy(30,19);
            textcolor(RED);
            printf("Process Canceled...");
            if(k==1)
                remove("emp.bin");
            _getch();
            fclose(fp);
            return 1;
        }
        textcolor(YELLOW);
        fseek(fp,0,SEEK_END);
        fwrite(&u,sizeof(user),1,fp);
        gotoxy(30,19);
        textcolor(LIGHTGREEN);
        printf("EMPLOYEE ADDED SUCCESFULLY");
        textcolor(LIGHTRED);
        gotoxy(30,21);
        printf("EMPLOYEE ID IS: %s",u.userid);
        _getch();
        gotoxy(30,23);
        textcolor(LIGHTGREEN);
        printf("DO YOU WANT TO ADD MORE EMPLOYEE (Y/N): ");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&uchoice);
        fclose(fp);
        id=getempid();
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"EMP-");
        fp=fopen("emp.bin","ab+");
    }
    while(uchoice=='Y'||uchoice=='y');
    fclose(fp);
    empsort();
    return 1;
}


void empsort()
{
    FILE *fp=fopen("emp.bin","rb+");
    int i=0,j,k;
    struct user e[20],e1;
    while(fread(&e1,sizeof(e1),1,fp)==1)
    {
        e[i]=e1;
        i++;
    }
    for(j=0;j<i;j++)
    {
        for(k=j+1;k<i;k++)
        {
            if(strcmp(e[j].userid,e[k].userid)>0)
            {
                e1=e[j];
                e[j]=e[k];
                e[k]=e1;
            }
        }
    }
    fclose(fp);
    fp = fopen("emp.bin","wb");
    for(j=0;j<i;j++)
    {
        fwrite(&e[j],sizeof(user),1,fp);
    }
    fclose(fp);

}

int getempid()
{
    empsort();
    FILE *fp = fopen("emp.bin","ab+");
    struct user emp;
    int id,i=1,eid=-1,maxid=0;
    char sub[3];
    char str[20];
    while(fread(&emp,sizeof(emp),1,fp)==1)
    {
        strcpy(str,emp.userid);
        sub_str(str,sub,'-');
        id = atoi(sub);
        if(id>maxid)
            maxid=id;
        if(id==i)
        {
            i++;
            continue;
        }
        if(eid==-1)
        {
            eid=i;
            return eid;
        }
        i++;
    }
    if(eid==-1)
    {
        eid=maxid+1;
    }
    return eid;
}

void sub_str(char *str,char *sub,char c)
{
    int i, j=0;
    for(i=0;str[i]!='\0';i++)
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            sub[j]=str[i];
            j++;
        }

    }

}

void viewEmployee()
{
    empsort();
    FILE *fp = fopen("emp.bin","rb");
    user ur;
    int i;
    textcolor(LIGHTRED);
    gotoxy(49,4);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,5);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,7);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(46,9);
    textcolor(YELLOW);
    printf("** EMPLOYEE DETAILS **");
    gotoxy(1,11);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,12);
    printf(" Employee ID\t\t\t\t Name\t\t\t\tPassword");
    gotoxy(1,13);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
        printf("%c",247);
    int x = 14;
    textcolor(YELLOW);

    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(5,x);
        printf("%s",ur.userid);
        gotoxy(41,x);
        printf("%s",ur.name);
        gotoxy(75,x);
        printf("%s",ur.pwd);
        x++;
    }
    printf("\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    textcolor(LIGHTCYAN);
    printf("\n\n\t\tPress Any Key to Return...");
    fclose(fp);
    _getch();
}


int deleteEmp()
{
    FILE *fp1 = fopen("emp.bin","rb");
    char empid[10];
    int i;
    textcolor(LIGHTRED);
    gotoxy(49,3);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,6);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(44,8);
    textcolor(YELLOW);
    printf("** DELETE EMPLOYEE DETAILS **");
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,15);
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(80,16);
    textcolor(WHITE);
    printf("Press 0 to exit...");
    if(fp1==NULL)
    {
        gotoxy(20,19);
        textcolor(RED);
        printf("\nNo Employee Added Yet");
        return -1;
    }
    FILE *fp2 = fopen("temp.bin","wb+");
    gotoxy(10,12);
    textcolor(YELLOW);
    printf("Enter Employee ID to DELETE the Record : ");
    fflush(stdin);
    textcolor(WHITE);
    fgets(empid,20,stdin);
    char *pos;
    pos = strchr(empid,'\n');
    *pos = '\0';
    if(strcmp(empid,"0")==0||strcmp(empid,"\0")==0)
    {
        gotoxy(20,18);
        textcolor(RED);
        printf("Process Canceled! Press any key to return....");
        _getch();
        fclose(fp2);
        remove("temp.bin");
        fclose(fp1);
        return -1;
    }
    user U;
    int found = 0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.userid,empid)!=0)
            fwrite(&U,sizeof(U),1,fp2);
        else
            found = 1;
    }
    fclose(fp1);
    if(found == 1)
    {
        rewind(fp2);
        fp1 = fopen("emp.bin","wb");
        while(fread(&U,sizeof(U),1,fp2)==1)
        {
            fwrite(&U,sizeof(U),1,fp1);
        }
        fclose(fp1);

    }
    fclose(fp2);
    remove("temp.bin");
    return found;
}



void addCarDetails()
{
    FILE *fp = fopen("car.bin","rb");
    FILE *fpa = fopen("admincar.bin","rb");
    int id;
    short k;
    char uchoice;
    char car[10] = "CAR-";
    char carid[10];
    struct car u;
    if(fp == NULL)
    {
        fp = fopen("car.bin","ab+");
        fpa = fopen("admincar.bin","ab+");
        id = 1;
        sprintf(carid,"%d",id);
        strcat(car,carid);
        strcpy(u.car_id,car);
        strcpy(car,"CAR-");
        k=1;
    }
    else
    {
        fp = fopen("car.bin","ab+");
        fpa = fopen("admincar.bin","ab+");
        id=getcarid();
        sprintf(carid,"%d",id);
        strcat(car,carid);
        strcpy(u.car_id,car);
        strcpy(car,"CAR-");
        k=0;
    }
    do
    {
        clrscr();
        gotoxy(48,2);
        textcolor(RED);
        printf("CAR RENTAL APP");
        textcolor(YELLOW);
        gotoxy(48,3);
        printf("~~~~~~~~~~~~~~");
        textcolor(LIGHTGREEN);
        int i;
        gotoxy(1,5);
        for(i=0;i<120;i++)
        {
            printf("*");
        }
        gotoxy(1,18);
        for(i=0;i<120;i++)
        {
            printf("*");
        }
        gotoxy(80,19);
        textcolor(WHITE);
        printf("Press 0 to exit.");
        textcolor(WHITE);
        gotoxy(41,7);
        printf("*****  ADD CAR DETAILS *****");
        gotoxy(10,9);
        textcolor(YELLOW);
        printf("Enter Car Name : ");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.car_name,20,stdin);
        char *pos;
        pos = strchr(u.car_name,'\n');
        *pos = '\0';
        if(u.car_name[0]=='0'||u.car_name[0]=='\0')
        {
            gotoxy(30,20);
            textcolor(RED);
            printf("Process Canceled...");
            if(k==1)
            {
                remove("car.bin");
                remove("admincar.bin");
            }
            _getch();
            fclose(fp);
            fclose(fpa);
            return;
        }
        gotoxy(10,11);
        textcolor(YELLOW);
        printf("Enter Car Capacity : ");
        textcolor(WHITE);
        scanf("%d",&u.capacity);
        textcolor(YELLOW);
        gotoxy(10,13);
        printf("Enter Car Count : ");
        textcolor(WHITE);
        scanf("%d",&u.car_count);
        textcolor(YELLOW);
        gotoxy(10,15);
        printf("Enter Car Price :");
        textcolor(WHITE);
        scanf("%d",&u.price);
        fseek(fp,0,SEEK_END);
        fwrite(&u,sizeof(u),1,fp);
        fwrite(&u,sizeof(u),1,fpa);
        gotoxy(30,20);
        textcolor(LIGHTGREEN);
        printf("CAR ADDED SUCCESFULLY");
        printf("\n CAR ID IS: %s",u.car_id);
        _getch();
        gotoxy(1,22);
        textcolor(LIGHTRED);
        printf("DO YOU WANT TO ADD MORE CAR (Y/N):");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&uchoice);
        fclose(fpa);
        id=getcarid();
        sprintf(carid,"%d",id);
        strcat(car,carid);
        strcpy(u.car_id,car);
        strcpy(car,"CAR-");
        fpa=fopen("admincar.bin","ab+");
    }while(uchoice=='Y'||uchoice=='y');
    fclose(fp);
    fclose(fpa);
    fsort();
}

void fsort()
{
    FILE *fp=fopen("car.bin","rb+");
    int i=0,j,k;
    struct car c[20],c1;
    while(fread(&c1,sizeof(c1),1,fp)==1)
    {
        c[i]=c1;
        i++;
    }
    for(j=0;j<i;j++)
    {
        for(k=j+1;k<i;k++)
        {
            if(strcmp(c[j].car_id,c[k].car_id)>0)
            {
                c1=c[j];
                c[j]=c[k];
                c[k]=c1;
            }
        }
    }
    fclose(fp);
    fp = fopen("car.bin","wb");
    for(j=0;j<i;j++)
    {
        fwrite(&c[j],sizeof(car),1,fp);
    }
    fclose(fp);

    //Sorting admin car

    fp=fopen("admincar.bin","rb+");
    i=0;
    while(fread(&c1,sizeof(c1),1,fp)==1)
    {
        c[i]=c1;
        i++;
    }
    for(j=0;j<i;j++)
    {
        for(k=j+1;k<i;k++)
        {
            if(strcmp(c[j].car_id,c[k].car_id)>0)
            {
                c1=c[j];
                c[j]=c[k];
                c[k]=c1;
            }
        }
    }
    fclose(fp);
    fp = fopen("admincar.bin","wb");
    for(j=0;j<i;j++)
    {
        fwrite(&c[j],sizeof(car),1,fp);
    }
    fclose(fp);
}

int getcarid()
{
    fsort();
    FILE *fp = fopen("admincar.bin","ab+");
    struct car car;
    int id,i=1,cid=-1,maxid=0;
    char sub[3];
    char str[20];
    while(fread(&car,sizeof(car),1,fp)==1)
    {
        strcpy(str,car.car_id);
        sub_str(str,sub,'-');
        id = atoi(sub);
        if(id>maxid)
            maxid=id;
        if(id==i)
        {
            i++;
            continue;
        }
        if(cid==-1)
        {
            cid=i;
            return cid;
        }
        i++;
    }
    if(cid==-1)
    {
        cid=maxid+1;
    }
    return cid;
}

void showCarDetails()
{
    fsort();
    FILE *fp = fopen("car.bin","rb");
    struct car ur;
    int i;
    textcolor(LIGHTRED);
    gotoxy(49,3);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,6);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(45,8);
    textcolor(YELLOW);
    printf("** AVAILABLE CAR DETAILS **");
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,11);
    printf(" Car ID\t\t\t\tName\t\t\t     Capacity\t\t   Count\t      Prices");
    gotoxy(1,12);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
        printf("%c",247);
    int x = 13;
    textcolor(YELLOW);

    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%s",ur.car_id);
        gotoxy(33,x);
        printf("%s",ur.car_name);
        gotoxy(66,x);
        printf("%d",ur.capacity);
        gotoxy(86,x);
        printf("%d",ur.car_count);
        gotoxy(104,x);
        printf("%d",ur.price);
        x++;
    }
    printf("\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
        printf("%c",247);
    textcolor(LIGHTCYAN);
    printf("\n\n\t\tPress Any Key to Continue...");
    _getch();
    fclose(fp);
}


int deleteCarModel()
{
    FILE *fp1 = fopen("car.bin","rb");
    char carid[10];
    int i;
    textcolor(LIGHTRED);
    gotoxy(49,3);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,6);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(46,8);
    textcolor(YELLOW);
    printf("** DELETE CAR DETAILS **");
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,15);
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(80,16);
    textcolor(WHITE);
    printf("Press 0 to exit...");
    if(fp1==NULL)
    {
        gotoxy(20,18);
        textcolor(RED);
        textcolor(LIGHTRED);
        printf("\nNo CAR Added Yet");
        return -1;
    }
    FILE *fp2 = fopen("temp.bin","wb+");
    gotoxy(10,12);
    textcolor(YELLOW);
    printf("Enter CAR ID to DELETE the Record : ");
    fflush(stdin);
    textcolor(WHITE);
    fgets(carid,20,stdin);
    char *pos;
    pos = strchr(carid,'\n');
    *pos = '\0';
    if(strcmp(carid,"0")==0||strcmp(carid,"\0")==0)
    {
        gotoxy(20,18);
        textcolor(RED);
        printf("Process Canceled! Press any key to return....");
        _getch();
        fclose(fp2);
        remove("temp.bin");
        fclose(fp1);
        return -1;
    }
    struct car U;
    int found = 0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.car_id,carid)!=0)
            fwrite(&U,sizeof(U),1,fp2);
        else
            found = 1;
    }
    fclose(fp1);
    if(found == 1)
    {
        rewind(fp2);
        fp1 = fopen("car.bin","wb");
        while(fread(&U,sizeof(U),1,fp2)==1)
        {
            fwrite(&U,sizeof(U),1,fp1);
        }
        fclose(fp1);
        fclose(fp2);
        fp2 = fopen("temp.bin","wb");
        FILE *fpa = fopen("admincar.bin","rb");
        while(fread(&U,sizeof(U),1,fpa)==1)
        {
            if(strcmp(U.car_id,carid)!=0)
                fwrite(&U,sizeof(U),1,fp2);
        }
        fclose(fpa);
        fclose(fp2);
        fp2=fopen("temp.bin","rb");
        fpa = fopen("admincar.bin","wb");
        rewind(fp2);
        while(fread(&U,sizeof(U),1,fp2)==1)
        {
            fwrite(&U,sizeof(U),1,fpa);
        }
        fclose(fpa);
    }
    fclose(fp2);
    remove("temp.bin");
    return found;
}

void updateCars()
{
    FILE *fp=fopen("car.bin","rb+");
    FILE *fpa=fopen("admincar.bin","rb+");
    char carid[10];
    int i;
    textcolor(LIGHTRED);
    gotoxy(49,3);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,6);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(46,8);
    textcolor(YELLOW);
    printf("** UPDATE CAR DETAILS **");
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,20);
    for(i=1;i<=120;i++)
        printf("%c",247);
    gotoxy(80,21);
    textcolor(WHITE);
    printf("Press 0 to exit...");
    if(fp==NULL)
    {
        gotoxy(20,23);
        textcolor(RED);
        printf("No Cars Added! Press any key to return...");
        _getch();
        return;
    }
    textcolor(YELLOW);
    gotoxy(25,13);
    printf("Enter CAR-Id of the Car : ");
    fflush(stdin);
    textcolor(WHITE);
    fgets(carid,20,stdin);
    char *pos;
    pos = strchr(carid,'\n');
    *pos = '\0';
    if(strcmp(carid,"0")==0||strcmp(carid,"\0")==0)
    {
        gotoxy(20,23);
        textcolor(RED);
        printf("Process Canceled! Press any key to return....");
        _getch();
        fclose(fp);
        fclose(fpa);
        return;
    }
    struct car U;
    int found = 0;
    while(fread(&U,sizeof(U),1,fp)==1)
    {
        if(strcmp(carid,U.car_id)==0)
        {
            found=1;
            break;
        }
    }
    if(found==0)
    {
        gotoxy(20,23);
        textcolor(RED);
        printf("No Cars found! Press any key to return....");
        _getch();
        fclose(fp);
        fclose(fpa);
        return;
    }
    int cars,choice;
    gotoxy(25,15);
    textcolor(YELLOW);
    printf("No.of Cars to be added/removed : ");
    textcolor(WHITE);
    scanf("%d",&cars);
    if(cars==0)
    {
        gotoxy(20,23);
        textcolor(RED);
        printf("No Updates Required! Press any key to return....");
        fclose(fp);
        fclose(fpa);
        return;
    }
    gotoxy(25,17);
    printf("Press 1 for adding or 2 for removing : ");
    textcolor(WHITE);
    do
    {
        scanf("%d",&choice);
        if(choice==0)
        {
            gotoxy(20,23);
            textcolor(RED);
            printf("Process Canceled! Press any key to return....");
            _getch();
            fclose(fp);
            fclose(fpa);
            return;
        }
        if(choice!=1&&choice!=2)
        {
            gotoxy(20,23);
            textcolor(RED);
            printf("Incorrect choice...");
            _getch();
            gotoxy(64,17);
            printf("\t");
            gotoxy(20,23);
            printf("\t\t\t");
            gotoxy(64,17);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    int newCount;
    if(choice==1)
    {
        rewind(fp);
        while(fread(&U,sizeof(U),1,fp)==1)
        {
            if(strcmp(U.car_id,carid)==0)
            {
                newCount=U.car_count+cars;
                fseek(fp,(-2)*sizeof(int),SEEK_CUR);
                fwrite(&newCount,sizeof(int),1,fp);
                break;
            }
        }
        fclose(fp);
        while(fread(&U,sizeof(U),1,fpa)==1)  //&&(U.car_count-cars>=0)
        {
            if(strcmp(U.car_id,carid)==0)
            {
                newCount=U.car_count+cars;
                fseek(fpa,(-2)*sizeof(int),SEEK_CUR);
                fwrite(&newCount,sizeof(int),1,fpa);
                break;
            }
        }
        fclose(fpa);
    }
    else
    {
        rewind(fp);
        while(fread(&U,sizeof(U),1,fp)==1)
        {
            if(strcmp(U.car_id,carid)==0&&(U.car_count-cars>=0))
            {
                newCount=U.car_count-cars;
                fseek(fp,(-2)*sizeof(int),SEEK_CUR);
                fwrite(&newCount,sizeof(int),1,fp);
                break;
            }
            else if(strcmp(U.car_id,carid)==0&&(U.car_count-cars<0))
            {
                gotoxy(20,23);
                textcolor(RED);
                printf("Cars are less! Press any key to continue...");
                _getch();
                fclose(fp);
                fclose(fpa);
                return;
            }
        }
        fclose(fp);
        while(fread(&U,sizeof(U),1,fpa)==1)
        {
            if(strcmp(U.car_id,carid)==0)
            {
                newCount=U.car_count-cars;
                fseek(fpa,(-2)*sizeof(int),SEEK_CUR);
                fwrite(&newCount,sizeof(int),1,fpa);
                break;
            }
        }
        fclose(fpa);
    }
    gotoxy(20,23);
    textcolor(LIGHTGREEN);
    printf("Cars Updated Successfully. Press any key to continue...");
    _getch();
    clrscr();
    allcardetails();
    return;
}

int empMenu()
{
    int choice,i;
    textcolor(RED);
    gotoxy(48,4);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(48,5);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTGREEN);
    gotoxy(50,6);
    printf("EMPLOYEE MENU ");
    textcolor(YELLOW);
    gotoxy(50,7);
    printf("~~~~~~~~~~~~~ \n\n");
    textcolor(LIGHTRED);
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    gotoxy(1,21);
    for(i=0;i<120;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(42,11);
    printf("1. Rent A Car");
    gotoxy(42,12);
    printf("2. Booking Details");
    gotoxy(42,13);
    printf("3. Available Car Details");
    gotoxy(42,14);
    printf("4. Show All Car Details");
    gotoxy(42,15);
    printf("5. Return Car");
    gotoxy(42,16);
    printf("6. Exit");
    gotoxy(42,18);
    printf("Enter Choice : ");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}

void bookedCarDetails()
{
    clrscr();
    int i;
    FILE *fp=fopen("customer.bin","rb");
    struct customer_car_details CC;
    textcolor(LIGHTRED);
    gotoxy(49,3);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,6);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(46,8);
    textcolor(YELLOW);
    printf("** BOOKED CAR DETAILS **");
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,11);
    textcolor(LIGHTRED);
    printf("Model\t\tCust Name\t Pick Up\t     Drop\t\t s_Date\t\t\tE_Date");
    gotoxy(1,12);
    textcolor(LIGHTGREEN);
    for(i=1; i<120; i++)
        printf("%c",247);
    int x=13;
    textcolor(YELLOW);
    while(fread(&CC,sizeof(customer_car_details),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%s",getCarName(CC.car_id));
        gotoxy(20,x);
        printf("%s",CC.cust_name);
        gotoxy(34,x);
        printf("%s",CC.pick);
        gotoxy(55,x);
        printf("%s",CC.drop);
        gotoxy(73,x);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);
        gotoxy(96,x);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);
        x++;
    }
    printf("\n");
    textcolor(LIGHTGREEN);
    for(i=1; i<120; i++)
        printf("%c",247);
    fclose(fp);
    textcolor(RED);
    printf("\n\n\n          Press any to exit...");
    _getch();
}


void updateCarCount(char *c)
{
    FILE *fp=fopen("car.bin","rb+");
    car C;
    while(fread(&C,sizeof(car),1,fp)==1)
    {
        if(strcmp(C.car_id,c)==0)
        {
            fseek(fp,(-2)*sizeof(int),SEEK_CUR);
            int cc_new=C.car_count-1;
            fwrite(&cc_new,sizeof(cc_new),1,fp);
            break;
        }
    }
    fclose(fp);
}



char *getCarName(char *carid)
    {
        FILE *fp=fopen("car.bin","rb");
        static car C;
        while(fread(&C,sizeof(C),1,fp)==1)
            {
            if(strcmp(C.car_id,carid)==0)
            break;
            }

            fclose(fp);
            return C.car_name;
    }

int rentCar()
{
    customer_car_details CC;
    char c[8];
    int i;
    textcolor(LIGHTRED);
    gotoxy(45,3);
    printf("CAR RENTEL SYSTEM");
    textcolor(YELLOW);
    gotoxy(45,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTGREEN);
    gotoxy(47,6);
    printf("EMPLOYEE MENU");
    textcolor(YELLOW);
    gotoxy(47,7);
    printf("~~~~~~~~~~~~~");
    gotoxy(1,9);
    textcolor(LIGHTCYAN);
    for(i=0; i<120; i++)
    {
        printf("%c",247);
    }
    textcolor(YELLOW);
    gotoxy(40,12);
    selectCarModel(c);
    strcpy(CC.car_id,c);
    clrscr();
    textcolor(LIGHTRED);
    gotoxy(45,3);
    printf("CAR RENTEL SYSTEM");
    textcolor(YELLOW);
    gotoxy(45,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTGREEN);
    gotoxy(47,6);
    printf("EMPLOYEE MENU");
    textcolor(YELLOW);
    gotoxy(47,7);
    printf("~~~~~~~~~~~~~");
    gotoxy(1,9);
    textcolor(LIGHTCYAN);
    for(i=0; i<120; i++)
    {
        printf("%c",247);
    }
    gotoxy(1,18);
    for(i=0; i<120; i++)
    {
        printf("%c",247);
    }
    gotoxy(35,12);
    printf("ENTER customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos=strchr(CC.cust_name,'\n');
    *pos='\0';
    if(CC.cust_name[0]==0||CC.cust_name[0]=='\0')
    {
        gotoxy(35,21);
        textcolor(RED);
        printf("Process Canceled...");
        _getch();
        return -1;
    }
    gotoxy(35,13);
    textcolor(YELLOW);
    printf("Enter Pick Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.pick,30,stdin);
    pos=strchr(CC.pick,'\n');
    *pos='\0';
    if(CC.pick[0]==0||CC.pick[0]=='\0')
    {
        gotoxy(35,21);
        textcolor(RED);
        printf("Process Canceled...");
        _getch();
        return -1;
    }
    gotoxy(35,14);
    textcolor(YELLOW);
    printf("Enter Drop Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.drop,30,stdin);
    pos=strchr(CC.drop,'\n');
    *pos='\0';
    if(CC.drop[0]==0||CC.drop[0]=='\0')
    {
        gotoxy(35,21);
        textcolor(RED);
        printf("Process Canceled...");
        _getch();
        return -1;
    }
    gotoxy(35,15);
    textcolor( YELLOW);
    printf("Enter start date (dd/m/yyyy):");
    textcolor(WHITE);
    int datevaild;
    do
    {
        scanf("%d/%d/%d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        datevaild=isVaildDate(CC.sd);
        if(datevaild==0)
        {
            gotoxy(35,21);
            textcolor(LIGHTRED);
            printf("Wrong Date ");
            _getch();
            gotoxy(35,21);
            printf("\t\t");
            gotoxy(64,15);
            printf("\t\t\t");
            gotoxy(64,15);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    gotoxy(35,16);
    textcolor(YELLOW);
    printf("Enter end date(dd/m/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        datevaild=isVaildDate(CC.ed);
        if(datevaild==0)
        {
            gotoxy(35,21);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            _getch();
            gotoxy(35,21);
            printf("\t\t");
            gotoxy(61,16);
            printf("\t\t\t");
            gotoxy(61,16);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    FILE *fp;
    fp=fopen("Customer.bin","ab");
    fwrite(&CC,sizeof(customer_car_details),1,fp);
    gotoxy(25,22);
    textcolor(LIGHTGREEN);
    printf("Details Saved. Press any key to continue...");
    _getch();
    fclose(fp);
    updateCarCount(c);
    bookedCarDetails();
    return 1;

}

void returnCar()
{
    FILE *fp=fopen("car.bin","rb+");
    FILE *fpc=fopen("Customer.bin","rb");
    struct customer_car_details CC;
    struct car car;
    char carid[10], name[20];
    int rdays;
    long rent;
    int i;
    textcolor(LIGHTRED);
    gotoxy(45,3);
    printf("CAR RENTEL SYSTEM");
    textcolor(YELLOW);
    gotoxy(45,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTGREEN);
    gotoxy(47,6);
    printf("EMPLOYEE MENU");
    textcolor(YELLOW);
    gotoxy(47,7);
    printf("~~~~~~~~~~~~~");
    gotoxy(1,9);
    textcolor(LIGHTCYAN);
    for(i=0; i<120; i++)
    {
        printf("%c",247);
    }
    gotoxy(1,20);
    for(i=0; i<120; i++)
    {
        printf("%c",247);
    }
    gotoxy(80,21);
    textcolor(WHITE);
    printf("Press 0 to Cancel process..");
    gotoxy(46,11);
    textcolor(LIGHTGREEN);
    printf("RETURNING A CAR");
    gotoxy(20,13);
    textcolor(YELLOW);
    printf("Enter CAR-ID of the Car : ");
    fflush(stdin);
    textcolor(WHITE);
    fgets(carid,10,stdin);
    char *pos;
    pos = strchr(carid,'\n');
    *pos = '\0';
    if(carid[0]=='\0'||carid[0]=='0')
    {
        gotoxy(20,23);
        textcolor(RED);
        printf("Process Canceled. Press any key to continue...");
        _getch();
        return;
    }
    while(fread(&CC,sizeof(CC),1,fpc)==1)
    {
        if(strcmp(carid,CC.car_id)==0)
        {
            gotoxy(20,14);
            textcolor(YELLOW);
            printf("Enter Name of the Customer : ");
            fflush(stdin);
            textcolor(WHITE);
            fgets(name,20,stdin);
            pos = strchr(name,'\n');
            *pos = '\0';
            if(name[0]=='\0'||name[0]=='0')
            {
                gotoxy(20,23);
                textcolor(RED);
                printf("Process Canceled. Press any key to continue...");
                _getch();
                return;
            }
            if(strcmp(CC.cust_name,name)==0)
            {
                struct tm r_date;
                gotoxy(20,15);
                printf("Enter return date (dd/mm/yyyy): ");
                textcolor(WHITE);
                int datevaild;
                do
                {
                    scanf("%d/%d/%d",&r_date.tm_mday,&r_date.tm_mon,&r_date.tm_year);
                    datevaild=isVaildDate(r_date);
                    if(datevaild==0)
                    {
                        gotoxy(35,23);
                        textcolor(LIGHTRED);
                        printf("Wrong Date!");
                        _getch();
                        gotoxy(35,23);
                        printf("\t\t");
                        gotoxy(52,12);
                        printf("\t\t\t");
                        gotoxy(52,15);
                        textcolor(WHITE);
                    }
                    else
                        break;
                }while(1);
                rdays=cal_rdays(CC.sd,r_date);
                if(rdays==-1)
                {
                    gotoxy(20,23);
                    textcolor(RED);
                    printf("Incorrect Date! Process Canceled. Press any key to continue...");
                    _getch();
                    fclose(fp);
                    fclose(fpc);
                    return;
                }
                while(fread(&car,sizeof(car),1,fp)==1)
                {
                    if(strcmp(car.car_id,CC.car_id)==0)
                    {
                        rent = rdays*car.price;
                        car.car_count++;
                        fseek(fp,-1*sizeof(car),SEEK_CUR);
                        fwrite(&car,sizeof(car),1,fp);
                        gotoxy(20,17);
                        textcolor(LIGHTBLUE);
                        printf("RENT is : %ld",rent);
                        gotoxy(20,23);
                        textcolor(LIGHTGREEN);
                        printf("Press any key to return...");
                        _getch();
                        fclose(fp);
                        fclose(fpc);
                        deletebooking(carid,name);
                        return;
                    }
                }
            }
        }
    }
    gotoxy(20,23);
    textcolor(RED);
    printf("CAR NOT FOUND! Press any key to return...");
    _getch();
    fclose(fp);
    fclose(fpc);
    return;
}

int cal_rdays(struct tm sd,struct tm rd)
{
    int rdays,y,m,d;
    if(rd.tm_year<sd.tm_year||(rd.tm_year==sd.tm_year&&rd.tm_mon<sd.tm_mon)||(rd.tm_year==sd.tm_year&&rd.tm_mon==sd.tm_mon&&rd.tm_mday<sd.tm_mday))
        return -1;
    y=rd.tm_year-sd.tm_year;
    if(y>=1&&(rd.tm_mon<sd.tm_mon||(rd.tm_mon==sd.tm_mon&&rd.tm_mday<sd.tm_mday)))
    {
        y--;
    }
    m=rd.tm_mon-sd.tm_mon;
    if(rd.tm_mon<sd.tm_mon)
        m=12+m;
    d=rd.tm_mday-sd.tm_mday;
    if(d<0)
        d=30+d;
    rdays=y*365+d+m*30+((int)(rd.tm_year/4)-(int)(sd.tm_year/4))-((int)(rd.tm_year/100)-(int)(sd.tm_year/100))+((int)(rd.tm_year/400)-(int)(sd.tm_year/400));
    return rdays;
}

void deletebooking(char *carid,char *name)
{
    FILE *fp1 = fopen("Customer.bin","rb");
    FILE *fp2 = fopen("temp.bin","wb+");
    struct customer_car_details U;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.car_id,carid)!=0&&strcmp(U.cust_name,name)!=0)
            fwrite(&U,sizeof(U),1,fp2);
    }
    fclose(fp1);
    rewind(fp2);
    fp1 = fopen("Customer.bin","wb");
    while(fread(&U,sizeof(U),1,fp2)==1)
    {
        fwrite(&U,sizeof(U),1,fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

void allcardetails()
{
    fsort();
    FILE *fp=fopen("admincar.bin","rb");
    int i;
    struct car ur;
    textcolor(LIGHTRED);
    gotoxy(49,3);
    printf("CAR RENTAL SYSTEM");
    textcolor(YELLOW);
    gotoxy(49,4);
    printf("~~~~~~~~~~~~~~~~~");
    textcolor(LIGHTCYAN);
    gotoxy(1,6);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(48,8);
    textcolor(YELLOW);
    printf("** ALL CAR DETAILS **");
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,11);
    printf(" Car ID\t\t\t\tName\t\t\t     Capacity\t\t   Count\t      Prices");
    gotoxy(1,12);
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
        printf("%c",247);
    int x = 13;
    textcolor(YELLOW);

    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%s",ur.car_id);
        gotoxy(33,x);
        printf("%s",ur.car_name);
        gotoxy(66,x);
        printf("%d",ur.capacity);
        gotoxy(86,x);
        printf("%d",ur.car_count);
        gotoxy(104,x);
        printf("%d",ur.price);
        x++;
    }
    printf("\n");
    textcolor(LIGHTGREEN);
    for(i=1;i<120;i++)
        printf("%c",247);
    textcolor(LIGHTCYAN);
    printf("\n\n\t\tPress Any Key to Continue...");
    fclose(fp);
    _getch();

}
