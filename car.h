#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include<time.h>

struct user
{
    char userid[20];
    char name[20];
    char pwd[20];


};
struct car
{
    char car_id[20];
    char car_name[30];
    int capacity;
    int car_count;
    int price;

};
struct customer_car_details
{
    char car_id[20];
    char cust_name[30];
    char pick[30];
    char drop[30];
    struct tm sd;
    struct tm ed;

};
typedef struct user user;
typedef struct car car;
typedef struct customer_car_details customer_car_details;
void addAdmin();
user* getInput();
int checkUserExist(user,char*);
int addEmployee();
int adminMenu();
void viewEmployee();
void addCarDetails();
void showCarDetails();
void allcardetails();
int deleteEmp();
int deleteCarModel();
void updateCars();
void sub_str(char*,char*,char);
int empMenu();
int rentCar();
void selectCarModel(char*);
void updateCarCount(char *);
void bookedCarDetails();
void returnCar();
char * getCarName(char *);
int isValidDate(struct tm);
int getcarid();
void fsort();
void empsort();
int getempid();
int cal_rdays(struct tm,struct tm);
void deletebooking(char *,char *);


#endif // CAR_H_INCLUDED
