#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "car.h"
int main()
{
    int i;
    gotoxy(41,5);
    textcolor(CYAN);
    printf("PROJECT WITH C PROGRAMMING LANGUAGE");
    gotoxy(41,6);
    textcolor(LIGHTCYAN);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    gotoxy(1,8);
    textcolor(RED);
    for(i=0;i<120;i++)
        printf("*");
    gotoxy(44,11);
    textcolor(YELLOW);
    printf("WELCOME TO CAR RENTAL SYSTEM");
    gotoxy(44,12);
    textcolor(LIGHTGREEN);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    gotoxy(40,15);
    textcolor(YELLOW);
    printf("*RENT A CAR AND GO WHENEVER YOU NEED*");
    gotoxy(40,16);
    textcolor(LIGHTGREEN);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    gotoxy(1,19);
    textcolor(RED);
    for(i=0;i<120;i++)
        printf("*");
    gotoxy(5,23);
    textcolor(LIGHTRED);
    printf("Press any key to continue...");
    _getch();
    textcolor(YELLOW);
    addAdmin();
    user *usr;
    int result;
    int choice,type;
    while(1)//because when we given 1 in the input and the next screen is again opened//
    {
        clrscr();
        textcolor(CYAN);
        gotoxy(44,4);
        printf("CAR RENTAL SYSTEM");
        //uperline//
        gotoxy(44,5);
        textcolor(LIGHTCYAN);
        printf("~~~~~~~~~~~~~~~~~");
        gotoxy(1,8);
        textcolor(LIGHTRED);
        for(i=0;i<120;i++)
            printf("*");//the *line is using horizontally//
        //lowerline//
        gotoxy(1,17);
        for(i=0;i<120;i++)
            printf("*");
        gotoxy(80,9);
        textcolor(WHITE);
        printf("Press 0 to exit the Program.");
        gotoxy(42,10);
        textcolor(YELLOW);
        printf("1. ADMIN");
        gotoxy(42,12);
        printf("2. EMPLOYEE");
        gotoxy(42,14);
        textcolor(WHITE);
        int k;
        printf("Select your role : ");
        do
        {
            scanf("%d",&type);
            k=0;
            if(type==1)
               {
                    do
                    {
                       usr=getInput();
                       if(usr!=NULL)
                       {
                           k=checkUserExist(*usr,"admin");
                       }
                       else
                       {
                           break;
                       }
                   }while(k==0);
                   if(k==1)
                   {
                       gotoxy(20,21);
                       textcolor(GREEN);
                       printf("Login Accepted");
                       gotoxy(20,23);
                       textcolor(WHITE);
                       printf("Press any key to continue...");
                       _getch();
                       while(1)
                       {
                           clrscr();
                           choice=adminMenu();
                           if(choice==8)
                           {
                               clrscr();
                               break;
                           }
                           switch(choice)
                           {
                           case 1:
                               clrscr();
                               addEmployee();
                               break;
                           case 2:
                               clrscr();
                               addCarDetails();
                               break;
                           case 3:
                              clrscr();
                              viewEmployee();
                              break;
                           case 4:
                              clrscr();
                              allcardetails();
                              break;
                           case 5:
                               clrscr();
                               result=deleteEmp();
                               if (result==0)
                               {
                                   gotoxy(20,18);
                                   textcolor(LIGHTRED);
                                   printf("Sorry! no employee found with the given employee id");
                                   textcolor(WHITE);
                                   printf("\n\n\t\tPress any key to go back to the main menu...");
                                   _getch();
                               }
                               else if(result==1)
                               {

                                   gotoxy(20,18);
                                   textcolor(GREEN);
                                   printf("Record deleted successfully");
                                   textcolor(WHITE);
                                   printf("\n\n\t\t Press any key to go back to the main menu...");
                                   _getch();
                               }
                               break;
                           case 6:
                               clrscr();
                               result=deleteCarModel();
                               if (result==0)
                               {
                                   gotoxy(20,18);
                                   textcolor(LIGHTRED);
                                   printf("Sorry! no car found with the given car id.");
                                   textcolor(WHITE);
                                   printf("\n\n\t\tPress any key to go back to the main menu...");
                                   _getch();
                               }
                               else if(result==1)
                               {

                                   gotoxy(20,18);
                                   textcolor(LIGHTRED);
                                   printf("Record deleted successfully");
                                   textcolor(WHITE);
                                   printf("\n\n\t\tPress any key to go back to the main menu...");
                                   _getch();
                               }
                               break;
                           case 7:
                                clrscr();
                                updateCars();
                                break;
                           default:
                               {
                                   gotoxy(20,26);
                                   textcolor(RED);
                                   printf("Incorrect choice...");
                               }
                            _getch();

                           }


                       }
                   }
               }
              else if(type==2)
               {
                   //code for handelling employee login
                   do
                   {
                       usr=getInput();
                       if(usr!=NULL)
                       {
                           k=checkUserExist(*usr,"emp");
                       }
                       else
                       {
                           break;
                       }
                   }while(k==0);
                   if(k==1)
                   {
                       gotoxy(20,21);
                       textcolor(LIGHTGREEN);
                       printf("Login Accepted");
                       gotoxy(20,23);
                       textcolor(WHITE);
                       printf("press any key to continue");
                       _getch();
                       while(1)
                       {
                           clrscr();
                           choice=empMenu();
                           if(choice==6)
                           {
                               clrscr();
                               break;
                           }
                           switch(choice)
                           {
                           case 1:
                               clrscr();
                               result = rentCar();
                               if(result==0)
                                    printf("Booking Cancelled\nNo Car Available for this model");
                               _getch();
                               break;
                           case 2:
                               clrscr();
                               bookedCarDetails();
                               _getch();
                               break;
                           case 3:
                              clrscr();
                              showCarDetails();
                              break;
                           case 4:
                              clrscr();
                              allcardetails();
                              break;
                           case 5:
                              clrscr();
                              returnCar();
                              break;
                           default:
                            {
                                gotoxy(20,24);
                                textcolor(RED);
                                printf("Incorrect choice...");
                            }
                            _getch();

                           }


                       }
                   }
               }
               else if(type==0)
               {
                   char ch_exit;
                   gotoxy(20,20);
                   textcolor(RED);
                   printf("Are you sure ?..(Y/N)  ");
                   scanf(" %c",&ch_exit);
                   if(ch_exit=='y'||ch_exit=='Y')
                   {
                        textcolor(WHITE);
                        return 0;
                   }
                   else
                        break;
                }
               else
               {
                   textcolor(LIGHTRED);
                   gotoxy(30,20);
                   printf("Invalid user type");
                   _getch();//pause the screen//
                   gotoxy(30,20);
                   printf("\t\t\t");//remove the msg invalid user type//
                   gotoxy(61,14);
                   printf("\t");
                   gotoxy(61,14);
                   textcolor(WHITE);


            }

    }
    while (type!=1&&type!=2);//when this condition is false then the loop is run again//
}
   return 0;
}


