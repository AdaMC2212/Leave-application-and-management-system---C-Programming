#ifndef STRUCT_H
#define STRUCT_H

struct Leave
{
    int Annual;
    int Medical;
    int Emergency;
    int Compassionate;
    int Personal;
};

struct Apply
{
    char PK[10];
    char type[100];
    int date;
    int month;
    char leave_date[100];
    char reason[100];
    char status[100];
    struct Leave apply_leave; 
};

struct Staff
{
    char username[100];
    char pwd[100];
    char department[100];
    char id[100];
    char role[100];
    char name[100];
    struct Apply staff_leave;
};

#endif