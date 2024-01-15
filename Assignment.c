#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

void menu();
void login();
void Admin();
void Add_Staff();
void Update_Balance();
void Search_Staff_Info();
void Search_Staff_Leave();
void Report();
void Staff();
void Apply_Leave();
int Check_Current_Time(char *leave_date);
void Cancel_Leave();
void Leave_Status();
void Summary();
void Superior();
void Approve_Leave();
void Check_Date();
char id[100],name[100],department[100];

int main()
{
    menu();
    return 0;
}
void menu()
{   //Declare
    int choice;
    //Display
    system("cls");
    printf("\nWelcome to APU Leave Application and Management System\n\n"
            "1.School of Computing, Technology and Games Development\n"
            "2.School of Engineering\n"
            "3.School of Business, Management, Marketing and Tourism\n"
            "4.School of Accounting, Banking, Finance and Actuarial\n"
            "5.School of Media, International Relations and Psychology\n"
            "6.School of Design, Advertising and Animation\n"
            "7.Exit\n");
    //Do while loop for validation 
    do
    {   //Declare
        int i;
        printf("\nPlease select which school you from: ");
        //Get input
        i = scanf("%d",&choice);
        //Reloop if not integer
        if (i!=1)
        {
            printf("\nInsert a valid number\n");
            scanf("%*s");
            continue;
        }
        if (choice==1)
        {
            printf("\nWelcome to APU School of Computing, Technology and Games Development\n");
            //call out login function
            login();
            break;
        } 
        //if input between 2 to 7
        else if (choice>=2&&choice<7)
        {
            printf("\nThis option is not available right now, Please choose another option\n(Press any key to try again)");
            scanf("%*s");
            //call out menu function to let them see the display again
            menu();
        }
        else if (choice==7)
        {
            printf("\nThanks for visiting\n");
            //stop the program
            exit(1);
        }
        //if input not between 1 to 7
        else
        {
            printf("\nInsert a valid number\n");
        }
    }
    while(!(choice>0&&choice<=7));
}
void login()
{   //call out structure Staff and named as File
    struct Staff File;
    //Declare
    char input[50],input2[50];
    //Display
    system("cls");
    printf("LOGIN\n");
    printf("___________________________________________________________________\n");
    //Get input
    printf("\nPlease enter username:");
    scanf("%s", input);
    printf("Please enter password:");
    scanf("%s", input2);
    //Open File
    FILE *fptr;
    fptr = fopen("Username.txt", "r");
    if(fptr == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    else
    {   //Read from file
        while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",id,name,department,File.role,File.username,File.pwd) == 6)
        {   //Compare username and password in file with input
            if (strcmp(input, File.username) == 0 && strcmp(input2, File.pwd) == 0)
            {   //Compare role
                if(strcmp(File.role,"Staff") == 0)
                {   //call out staff function if role is Staff
                    Staff();
                    break;
                }
                //Compare role
                else if(strcmp(File.role,"Superior") == 0)
                {   //call out staff function if role is Superior
                    Superior();
                    break;
                }
            }
            //Compare username and password with input
            else if(strcmp(input,"apuadmin")==0 && strcmp(input2, "admin0") == 0)
            {   //call out Admin function if correct
                Admin();
                break;
            }
        }
        //if input username and password is not found in the file
        if (feof(fptr))
        {   
            printf("\nWrong username or password.\n\n(Press any key to try again) ");
            scanf("%*s");
            //call out login function to run this function again
            login();
        }
    }//Close File
    fclose(fptr);
}
void Admin()
{   //Declare
    int adminchoice;
    //Display
    system("cls");
    printf("ADMIN PAGE\n");
    printf("___________________________________________________________________\n");
    printf("\nWelcome Admin\n\n");
    printf( "1.Add New Staff\n"
            "2.Update Leave Balance\n"
            "3.Search Staff Information\n"
            "4.Search Staff Leave Information\n"
            "5.Generate Monthly Report\n"
            "6.Exit\n");
    //Do while loop for validation 
    do
    {   //Declare
        int i;
        printf("Please select activity: ");
        //Get input
        i = scanf("%d",&adminchoice);
        //Reloop if not integer
        if(i!=1)
        {
            printf("\nInsert a valid number\n");
            scanf("%*s");
            continue;
        }
        else
        {
            switch(adminchoice)
            {
            case 1://call out Add_staff function
                Add_Staff();
                break;
            case 2://call out Update_balance function
                Update_Balance();
                break;
            case 3://call out Search_Staff_Info function
                Search_Staff_Info();
                break;
            case 4://call out Search_Staff_Leave function
                Search_Staff_Leave();
                break;
            case 5://call out Report function
                Report();
                break;
            case 6://call out menu function back to menu
                printf("\nThank You, Have A Nice Day");
                menu();
                break;
            default://if input not between 1 to 6 reloop
                printf("\nInsert a valid number\n");
                continue;
            }
        }
    }
    while (!(adminchoice>0&&adminchoice<6));
}
void Add_Staff()
{
    system("cls");
    //call out struct Staff and Leave
    struct Staff add;
    struct Staff Check;
    struct Leave ad;
    //Declare
    char line[500],last_pk[10],new_pk[10];
    int sure,count;
    //Open files "Username.txt" and "Leave.txt" as append
    FILE *fptr;
    FILE *fptr2;
    fptr = fopen("Username.txt", "a");
    fptr2 = fopen("Leave.txt", "a");
    if((fptr == NULL ||fptr2 == NULL))
    {
        printf("File cannot be found");
        exit;
    }
    //Open files "Username.txt" as read
    FILE *fp;
    fp = fopen("Username.txt", "r");
    if(fp == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    else
    {   //read "Username.txt"
        while (fgets(line, sizeof(line), fp)) 
        { //read the first 3 character (StaffID)
            sscanf(line, "%3s", last_pk);
        }//Close "Username.txt" read file
        fclose(fp);
        //convert the part of StaffID(string) that contains number to integer
        int last_pk_num = atoi(last_pk + 1);
        //integer +1 as the new StaffID and convert to string
        sprintf(new_pk, "S%02d", last_pk_num + 1);
        //Display
        fflush(stdin);
        printf("ADD STAFF\n");
        printf("___________________________________________________________________\n");
        printf("\nPlease enter new staff name      : ");
        //Get input that contains spaces
        scanf("%[^\n]", add.name);
        while (1)
        {   //Declare
            int i,input;
            //Display
            printf("\n1.Academic\n"
                   "2.Technical\n"
                   "3.Management\n"
                   "4.Adminstration\n"
                   "Please enter new staff department: ");
            //get input
            i=scanf("%d",&input);
            //validation
            if (i!=1)
            {
                printf("\nInsert a valid number\n");
                scanf("%*s");
                continue;
            }
            else
            {
                if(input == 1)
                {   //copy string into variable
                    strcpy(add.department,"Academic");
                    break;
                }
                else if(input == 2)
                {   //copy string into variable
                    strcpy(add.department,"Technical");
                    break;
                }
                else if(input == 3)
                {   //copy string into variable
                    strcpy(add.department,"Management");
                    break;
                }
                else if(input == 4)
                {   //copy string into variable
                    strcpy(add.department,"Adminstration");
                    break;
                }
                else
                {
                    printf("\nInsert a valid number\n");
                    continue;
                }
            }
        }
        while (1)
        {   //declare
            int i,input;
            //display
            printf("\n1.Staff\n"
                   "2.Superior\n"
                   "Please enter new staff role      : ");
            //get input
            i=scanf("%d",&input);
            //validation
            if (i!=1)
            {
                printf("\nInsert a valid number\n");
                scanf("%*s");
                continue;
            }
            else
            {   
                if(input == 1)
                {   //copy string into variable
                    strcpy(add.role,"Staff");
                    break;
                }
                else if(input == 2)
                {   //copy string into variable
                    strcpy(add.role,"Superior");
                    break;
                }
                else
                {
                    printf("\nInsert a valid number\n");
                    continue;
                }
            }
        }
        //open file
        fp = fopen("Username.txt", "r");
        do
        {   //counter
            count = 0;
            printf("Please enter new staff username  : ");
            scanf("%s", add.username); //get input
            //read from file
            while(fscanf(fp,"%*[^|]|%*[^|]|%*[^|]|%*[^|]|%[^|]|%*[^\n]\n",Check.username)==1)
            {   //compare username with input
                if(strcmp(add.username,Check.username)==0)
                {
                    printf("Username has been used\nPlease try again\n\n");
                    count =1;
                    break;
                }
            }
        }
        while(count); //while counter has value reloop
        fclose(fp); //close file

        printf("Please enter new staff password  : ");
        scanf("%s", add.pwd); //get input
        while (1)
        {
            int i; //declare
            printf("Annual Leave: ");
            i=scanf("%d",&ad.Annual); //get input
            //validation
            if (i!=1)
            {
                printf("Invalid Input\n");
                scanf("%*s");
                continue;
            }
            else
            {
                break;
            }
        }
        while (1)
        {
            int i; //declare
            printf("Medical Leave: ");
            i=scanf("%d",&ad.Medical); //get input
            //validation
            if (i!=1)
            {
                printf("Invalid Input\n");
                scanf("%*s");
                continue;
            }
            else
            {
                break;
            }
        }
        while(1)
        {
            int i; //declare
            printf("Emergency Leave: ");
            i=scanf("%d",&ad.Emergency); //get input
            //validation
            if (i!=1)
            {
                printf("Invalid Input\n");
                scanf("%*s");
                continue;
            }
            else
            {
                break;
            }
        }
        while(1)
        {
            int i; //declare
            printf("Compassionate Leave: ");
            i=scanf("%d",&ad.Compassionate); //get input
            //validation
            if (i!=1)
            {
                printf("Invalid Input\n");
                scanf("%*s");
                continue;
            }
            else
            {
                break;
            }
        }
        while (1)
        {
            int i; //declare
            printf("Personal Leave: ");
            i=scanf("%d",&ad.Personal); //get input
            //validation
            if (i!=1)
            {
                printf("Invalid Input\n");
                scanf("%*s");
                continue;
            }
            else
            {
                break;
            }
        }

        while(1)
        {
            int i; //declare
            printf("\nAre you sure to add this staff information?\n"
            "1. Yes\n"
            "2. No\n"
            "Please Select: ");
            i = scanf("%d",&sure); //get input
            //validation
            if (i != 1)
            {
                printf("\nInvalid input\n");
                scanf("%*s");
                continue;
            }
            else
            {
                if(sure == 1)
                {   //write in files
                    fprintf(fptr,"%s|%s|%s|%s|%s|%s\n"
                    ,new_pk,add.name,add.department,add.role,add.username,add.pwd);
                    fprintf(fptr2,"%s|%02d|%02d|%02d|%02d|%02d\n"
                    ,new_pk,ad.Annual,ad.Medical,ad.Emergency,ad.Compassionate,ad.Personal);
                    //close files
                    fclose(fptr);
                    fclose(fptr2);
                    //display
                    printf("\nAll information have been written into file\n");   
                    printf("\n(Press any key to exit) ");
                    scanf("%*s");
                    Admin(); //call out Admin function
                    break;
                }
                else if(sure == 2)
                {
                    Admin();//call out Admin function
                    break;
                }
                else
                {
                    printf("\nInsert a valid number\n");
                    continue;
                }
            }
        }
    }
}
void Update_Balance()
{
    system("cls");
    fflush(stdin);
    //call out structure
    struct Leave update;
    struct Staff File;
    //declare
    int sure;
    char input[100],replace[100],line[500];
    //display
    printf("UPDATE LEAVE BALANCE\n");
    printf("___________________________________________________________________\n");
    printf("\nWhich staff's leave balance you want to update (Please insert staff's ID): ");
    scanf("%s",input); //get input
    //open file
    FILE *fptr;
    fptr = fopen("Leave.txt", "r");
    if(fptr == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    //read from file
    while(fscanf(fptr,"%[^|]|%d|%d|%d|%d|%d\n"
    ,File.id,&File.staff_leave.apply_leave.Annual,&File.staff_leave.apply_leave.Medical,
    &File.staff_leave.apply_leave.Emergency,&File.staff_leave.apply_leave.Compassionate,
    &File.staff_leave.apply_leave.Personal)==6)
    {   //compare id
        if(strcmp(input,File.id)==0)
        {   //display
            printf("ID            : %s\n"
                   "Annual        : %d\n"
                   "Medical       : %d\n"
                   "Emergency     : %d\n"
                   "Compassionate : %d\n"
                   "Personal      : %d\n"
                   ,File.id,File.staff_leave.apply_leave.Annual,File.staff_leave.apply_leave.Medical,
                    File.staff_leave.apply_leave.Emergency,File.staff_leave.apply_leave.Compassionate,
                    File.staff_leave.apply_leave.Personal);
            while (1){
                int i; //declare
                printf("\nAnnual Leave        : ");
                i=scanf("%d",&update.Annual);//get input
                if (i!=1) { //validaion
                    printf("Invalid Input");
                    scanf("%*s");
                    continue;
                }
                else{
                    break;
                }
            }
            while (1){
                int i;//declare
                printf("Medical Leave       : ");
                i=scanf("%d",&update.Medical);//get input
                if (i!=1){ //validaion
                    printf("Invalid Input\n");
                    scanf("%*s");
                    continue;
                }
                else{
                    break;
                }
            }
            while(1){
                int i; //declare
                printf("Emergency Leave     : ");
                i=scanf("%d",&update.Emergency); //get input
                if (i!=1){ //validaion
                    printf("Invalid Input\n");
                    scanf("%*s");
                    continue;
                }
                else
                {
                    break;
                }
            }
            while(1){
                int i; //declare
                printf("Compassionate Leave : ");
                i=scanf("%d",&update.Compassionate); //get input
                if (i!=1){ //validation
                    printf("Invalid Input\n");
                    scanf("%*s");
                    continue;
                }
                else{
                    break;
                }
            }
            while (1){
                int i; //declare
                printf("Personal Leave      : ");
                i=scanf("%d",&update.Personal); //get input
                if (i!=1){//validation
                    printf("Invalid Input\n");
                    scanf("%*s");
                    continue;
                }
                else{
                    break;
                }
            }
            while(1){
                int i; //declare
                printf("\nAre you sure to add this staff information?\n"
                "1. Yes\n"
                "2. No\n"
                "Please Select: ");
                i = scanf("%d",&sure); //get input
                if (i != 1){//validation
                    printf("\nInvalid input\n");
                    scanf("%*s");
                    continue;
                }
                else
                {   //open file
                    FILE *fpt;
                    fpt = fopen("temp.txt", "w");
                    if(fpt == NULL)
                    {
                        printf("File cannot be found");
                        exit;
                    }
                    if(sure == 1)
                    {   //store input in replace
                        sprintf(replace,"%s|%02d|%02d|%02d|%02d|%02d\n"
                        ,File.id,update.Annual,update.Medical,update.Emergency,update.Compassionate,update.Personal);
                        rewind(fptr); //rewind pointer in file
                        while (fgets(line, sizeof(line), fptr) != NULL) //read file
                        {
                            if (strstr(line,input) != NULL) //if input StaffID is readed 
                            {
                                fputs(replace, fpt); //write replace to replace the line instead in file
                            } 
                            else 
                            {
                                fputs(line, fpt); //write other line in file
                            }
                        }
                        fclose(fpt);
                        fclose(fptr); //close files
                        remove("Leave.txt"); //remove "leave.txt"
                        rename("temp.txt", "Leave.txt"); //rename "temp.txt" as "leave.txt"

                        printf("\nLeave balance has been updated.\n(Press any key to exit)");
                        scanf("%*s");
                        fclose(fptr);
                        Admin(); //call out Admin function
                        break;
                    }
                    else if(sure == 2){
                        Admin();//call out Admin function
                        break;
                    }
                    else{//validation
                        printf("\nInsert a valid number\n");
                        continue;//reloop
                    }
                }
            }
        }
    }
    if (feof(fptr))//if reach the end of file(didnt read the input in file)
    {
        printf("\nStaff ID cannot be found.\n\n(Press any key to try again) ");
        scanf("%*s");
        Update_Balance();//call out Update_Balance to try again
    }
}
void Search_Staff_Info()
{
    system("cls");
    fflush(stdin);
    //declare
    char input[100], line[500];
    struct Staff File;
    //display
    printf("SEARCH STAFF INFORMATION\n");
    printf("___________________________________________________________________\n");
    printf("\nPlease enter the Name or the ID that you want to search: ");
    scanf("%[^\n]", input); //get input with spaces
    //open file
    FILE *fptr;
    fptr = fopen("Username.txt", "r");
    if (fptr == NULL)
    {
        printf("File does not exist");
        exit;
    }
    while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
    ,File.id,File.name,File.department,File.role,File.username,File.pwd) == 6)//read from file
    {   //compare id or name
        if (strcmp(File.id, input) == 0 || strcmp(File.name, input) == 0)
        {   //display
            printf("\n");
            printf("ID         : %s\n", File.id);
            printf("Name       : %s\n", File.name);
            printf("Department : %s\n", File.department);
            printf("Role       : %s\n", File.role);
            printf("Username   : %s\n", File.username);
            printf("Password   : %s\n", File.pwd);
            printf("\n(Press any key to exit) ");
            scanf("%*s");
            Admin();//call out Admin function
            break;
        }
    }
    if (feof(fptr)) //if reach the end of file(didnt read the input in file)
    {
        printf("\nStaff ID or NAME cannot be found.\n\n(Press any key to try again) ");
        scanf("%*s");
        Search_Staff_Info(); //call out Search_Staff_Info to try again
    }
    fclose(fptr); //close file
}
void Search_Staff_Leave()
{
    system("cls");
    fflush(stdin);
    //declare
    char input[100],line[500];
    int count = 0;
    struct Staff File;
    //display
    printf("SEARCH STAFF LEAVE INFORMATION\n");
    printf("___________________________________________________________________\n");
    printf("\nPlease enter the Name or the ID that you want to search: ");
    scanf("%[^\n]", input);//get input with spaces
    //open file
    FILE *fptr;
    fptr=fopen("Apply.txt","r");
    if (fptr==NULL)
    {
        printf("File does not exists");
        exit;
    }
    else
    {
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                        |Status\n");
        while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
        File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
        ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare id or name
            if (strcmp(File.id, input) == 0 || strcmp(File.name, input) == 0)
            {
                printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-30s|%s\n"
                ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                ,File.staff_leave.reason,File.staff_leave.status);//write into file
                count++; //counter
            }
        }
        if (count == 0) //validation (id or name didnt read in file)
        {
            printf("\n____________________________________________________________________________________________________________________________________\n");
            printf("\nThis staff has not apply any leave.\n\n(Press any key to exit) ");
            scanf("%*s");
            Admin();//call out Admin function
        }
        else
        {
            printf("\n(Press any key to exit) ");
            scanf("%*s");
            Admin();//call out Admin function
        }
    }
    fclose(fptr);//close file
}
void Report()
{
    system("cls");
    //declare
    struct Staff File;
    struct Apply select;
    char dept[100];
    int a=0,b=0,c=0,month;
    //display
    printf("GENERATE MONTHLY REPORT\n");
    printf("___________________________________________________________________\n");
    while (1)
    {   //declare
        int i,input;
        printf("\n1.Academic\n"
                "2.Technical\n"
                "3.Management\n"
                "4.Adminstration\n"
                "Please enter the department you want to generate report: ");
        i=scanf("%d",&input);//get input
        if (i!=1)//validation
        {
            printf("Invalid Input\n");
            scanf("%*s");
            continue;
        }
        else
        {
            if(input == 1)
            {   //copy string in variable
                strcpy(dept,"Academic");
                break;
            }
            else if(input == 2)
            {   //copy string in variable
                strcpy(dept,"Technical");
                break;
            }
            else if(input == 3)
            {   //copy string in variable
                strcpy(dept,"Management");
                break;
            }   //copy string in variable
            else if(input == 4)
            {   //copy string in variable
                strcpy(dept,"Adminstration");
                break;
            }
            else//validation
            {
                printf("\nInsert a valid number\n");
                continue;
            }
        }
    }
    while (1)
    {   //declare
        int i;
        printf("\nSelect Month: ");
        i=scanf("%02d",&select.month);//get input
        if (i!=1)//validation
        {
            printf("Invalid Input\n");
            while (getchar() != '\n');
            continue;
        }
        else
        {
            if(select.month < 0 || select.month > 12)//validation
            {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
            }
            else
            {
                break;
            }
        }
    }
    //open files
    FILE *fptr1;
    FILE *fptr2;
    fptr1 = fopen("Apply.txt", "r");
    fptr2 = fopen("Report.txt", "w");
    if(fptr1 == NULL||fptr2 == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    //write in files
    fprintf(fptr2,"MONTHLY REPORT\n");
    fprintf(fptr2,"___________________________________________________________________\n");
    fprintf(fptr2,"\nDepartment     : %s\n",dept);
    fprintf(fptr2,"\nSelected Month : %d\n",select.month);
    fprintf(fptr2,"\n======== Pending List ========\n");
    fprintf(fptr2,"\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");  

    while(fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
    ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
    ,File.staff_leave.reason,File.staff_leave.status)==8) //read from file
    {
        sscanf(File.staff_leave.leave_date,"%*d-%d",&month);//convert string to integer
        //compare department, month and Pending status
        if(strcmp(dept,File.department)==0 && month == select.month && strcmp(File.staff_leave.status,"Pending")==0)
        {   //write in file
            fprintf(fptr2,"%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n",File.staff_leave.PK,File.id,File.name
            ,File.staff_leave.type,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status);
            a++; //counter
        }
    }  
    if(!a)//validation
    {   //write in file
        fprintf(fptr2,"____________________________________________________________________________\n");
        fprintf(fptr2,"There is not any Pending leave application in this department for this month\n");
    }

    fclose(fptr1);  //close file
    fptr1 = fopen("Apply.txt", "r"); //open file
    fprintf(fptr2,"\n======== Approved List ========\n"); //write in file
    fprintf(fptr2,"\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");
    while(fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
    ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
    ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
    {
        sscanf(File.staff_leave.leave_date,"%*d-%d",&month);//convert string to integer
        //compare department, month and Approved status
        if(strcmp(dept,File.department)==0 && month == select.month && strcmp(File.staff_leave.status,"Approved")==0)
        {   //write in file
            fprintf(fptr2,"%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n",File.staff_leave.PK,File.id,File.name
            ,File.staff_leave.type,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status);
            b++; //counter
        }
    }
    if(!b)//validation
    {   //write in file
        fprintf(fptr2,"____________________________________________________________________________\n");
        fprintf(fptr2,"There is not any Approved leave application in this department for this month\n");
    }
    fclose(fptr1);   //close file
    fptr1 = fopen("Apply.txt", "r");//open file
    fprintf(fptr2,"\n======== Rejected List ========\n");//write in file
    fprintf(fptr2,"\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");
    while(fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
    ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
    ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
    {
        sscanf(File.staff_leave.leave_date,"%*d-%d",&month);//convert string to integer
        //compare department, month and Rejected status
        if(strcmp(dept,File.department)==0 && month == select.month && strcmp(File.staff_leave.status,"Rejected")==0)
        {   //write in file
            fprintf(fptr2,"%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n",File.staff_leave.PK,File.id,File.name
            ,File.staff_leave.type,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status);
            c++; //counter
        }   
    }
    if(!c) //validation
    {   //write in file
        fprintf(fptr2,"____________________________________________________________________________\n");
        fprintf(fptr2,"There is not any Rejected leave application in this department for this month\n");
    }
    //write in file
    fprintf(fptr2,"\n____________________________________________________________________________\n");
    fprintf(fptr2,"There is %d pending leave application in this month by %s department\n",a,dept);
    fprintf(fptr2,"There is %d approved leave application in this month by %s department\n",b,dept);
    fprintf(fptr2,"There is %d rejected leave application in this month by %s department\n",c,dept);
    //close files
    fclose(fptr1);   
    fclose(fptr2);
    printf("\n\nMonthly report has been generated\n(Press any key to exit)");
    scanf("%*s");
    Admin(); //call out Admin function
}
void Staff()
{   //declare
    int staffchoice;
    //display
    system("cls");
    printf("STAFF PAGE\n");
    printf("___________________________________________________________________\n");
    printf("\nHi %s, Welcome to APU Leave Application and Management System\n\n",name);
    printf( "1.Apply Leave\n"
            "2.Cancel Leave\n"
            "3.Check Leave Status\n"
            "4.Check Summary of Leave Information\n"
            "5.Exit\n");
    do
    {
        int i;//declare
        printf("Please select activity: ");
        i = scanf("%d",&staffchoice);//get input
        if(i!=1)//validation
        {
            printf("\nInsert a valid number\n");
            scanf("%*s");
            continue;
        }
        else
        {
            switch(staffchoice)
            {
            case 1:
                Apply_Leave();//call out Apply_Leave function
                break;
            case 2:
                Cancel_Leave();//call out Cancel_Leave function
                break;
            case 3:
                Leave_Status();//call out Leave_Status function
                break;
            case 4:
                Summary();//call out Summary function
                break;
            case 5:
                printf("\nThank You, Have A Nice Day\n");
                menu();//call out menu function
                break;
            default://validation
                printf("\nInsert a valid number\n");
                continue;
            }
        }
    }
    while (!(staffchoice>0&&staffchoice<6));
}
void Apply_Leave()
{
    system("cls");
    printf("APPLY LEAVE\n");
    printf("___________________________________________________________________\n");
    //declare
    struct Staff File;
    struct Apply apply;
    char line[500],count = 0,last_pk[10],new_pk[10];
    int sure, leavetype;
    //open files
    FILE *fp;
    FILE *fpt;
    FILE *fptr;
    fptr = fopen("Apply.txt", "a");
    fp = fopen("Apply.txt", "r");
    fpt = fopen("Leave.txt", "r");
    if(fpt == NULL||fp == NULL||fptr == NULL){
        printf("File cannot be found");
        exit;
    }
    while (fgets(line, sizeof(line), fp)) //read "Apply.txt" file
    {   //read the first 3 character (StaffID)
        sscanf(line, "%3s", last_pk);
    }
    fclose(fp);//close file
    int last_pk_num = atoi(last_pk + 1);//convert the part of LeaveID(string) that contains number to integer
    sprintf(new_pk, "L%02d", last_pk_num + 1);//integer +1 as the new LeaveID and convert to string
    while(1)
    {
        int i;//declare
        printf("1.Annual\n"
               "2.Medical\n"
               "3.Emergency\n"
               "4.Compassionate\n"
               "5.Personal\n"
               "Please select leave type: ");//display
        i = scanf("%d",&leavetype);//get input
        if(i!=1)//validation
        {
            printf("\nInsert a valid number\n");
            scanf("%*s");
            continue;
        }
        else
        {
            if(leavetype == 1){   //copy string to variable
                strcpy(apply.type,"Annual");
                break;
            }
            else if(leavetype == 2){   //copy string to variable
                strcpy(apply.type,"Medical");
                break;
            }
            else if(leavetype == 3){   //copy string to variable
                strcpy(apply.type,"Emergency");
                break;
            }
            else if(leavetype == 4){   //copy string to variable
                strcpy(apply.type,"Compassionate");
                break;
            }
            else if(leavetype == 5){   //copy string to variable
                strcpy(apply.type,"Personal");
                break;
            }
            else{   //validation
                printf("\nInsert a valid number\n");
                continue;
            }
        }
    }
    while (1)
    {
        int i;//declare
        printf("\nMonth: ");
        i=scanf("%d",&apply.month);//get input
        if (i!=1)
        {//validation
            printf("Invalid Input\n");
            while (getchar() != '\n');
            continue;
        }
        else
        {
            if(apply.month < 0 || apply.month > 12)
            {//validation
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
            }
            else
            {
                break;
            }
        }
    }
    while (1)
    {
        int i;//declare
        printf("\nDate: ");
        i=scanf("%d",&apply.date);//get input
        if (i!=1){//validation
            printf("Invalid Input\n");
            scanf("%*s");
            continue;
        }
        else{//validation
            if(apply.month==1||apply.month==3||apply.month==5||apply.month==7||apply.month==8
            ||apply.month==10||apply.month==12)
            {
                if(apply.date < 1 ||apply.date > 31 )
                {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
                }
                else
                {
                    break;
                }
            }
            else if(apply.month==4 ||apply.month==6 ||apply.month==9 ||apply.month==11){//validation
                if(apply.date < 1 ||apply.date > 30 )
                {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
                }
                else
                {
                    break;
                }
            }
            else if(apply.month==2){//validation
                if(apply.date < 1 ||apply.date > 28 )
                {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
                }
                else
                {
                    break;
                }
            }
        }
    }
    sprintf(apply.leave_date, "%02d-%02d", apply.date, apply.month);//convert the date and month input to string
    fflush(stdin);
    printf("\nPlease state reason: ");
    scanf("%[^\n]",apply.reason);//get input with spaces
    strcpy(apply.status, "Pending");//copy string to variable
    while(fscanf(fpt,"%[^|]|%d|%d|%d|%d|%d\n",File.id,&apply.apply_leave.Annual,&apply.apply_leave.Medical
    ,&apply.apply_leave.Emergency,&apply.apply_leave.Compassionate,&apply.apply_leave.Personal)==6)//read from file
    {   //compare id
        if(strcmp(id, File.id)==0)
        {   //validation if no annual leave balance
            if(apply.apply_leave.Annual == 0 && leavetype == 1){
                printf("\nYou have already use all your annual leave\n(Press any key to exit)");
                scanf("%*s");
                Staff();//call out Staff function
                break;
            }
            if(apply.apply_leave.Medical == 0 && leavetype == 2){ //validation if no medical leave balance
                printf("\nYou have already use all your medical leave\n(Press any key to exit)");
                scanf("%*s");
                Staff();//call out Staff function
                break;
            }
            if(apply.apply_leave.Emergency == 0 && leavetype == 3){//validation if no emergency leave balance
                printf("\nYou have already use all your emergency leave\n(Press any key to exit)");
                scanf("%*s");
                Staff();//call out Staff function
                break;
            }
            if(apply.apply_leave.Compassionate == 0 && leavetype == 4){//validation if no comp leave balance
                printf("\nYou have already use all your compassionate leave\n(Press any key to exit)");
                scanf("%*s");
                Staff();//call out Staff function
                break;
            }
            if(apply.apply_leave.Personal == 0 && leavetype == 5){//validation if no personal leave balance
                printf("\nYou have already use all your personal leave\n(Press any key to exit)");
                scanf("%*s");
                Staff();//call out Staff function
                break;
            }
        }
    }
    while(1)
    {
        int i;//declare
        printf("\nAre you sure to add this leave?\n"
               "1. Yes\n"
               "2. No\n"
               "Please Select: ");
        i = scanf("%d",&sure);//get input
        if (i != 1){//validation
            printf("\nInvalid input\n");
            scanf("%*s");
            continue;
        }
        else{
            if(sure == 1){   //write in file
                fprintf(fptr,"%s|%s|%s|%s|%s|%s|%s|%s\n",new_pk,id,name,department,apply.type
                ,apply.leave_date,apply.reason,apply.status);
                fclose(fptr); //close file
                printf("\nAll information have been written into file");   
                printf("\n(Press any key to exit) ");
                scanf("%*s");
                Staff();//call out Staff function
                break;
            }
            else if(sure == 2){
                Staff();//call out Staff function
                break;
            }
            else{//validation
                printf("\nInsert a valid number\n");
                continue;
            }
        }
    }
    fclose(fpt);
}
int Check_Current_Time(char *leave_date)
{   //declare
    char current_date[100];
    time_t current = time(0); // get current time
    struct tm *t = localtime(&current); // convert to local time
    int current_year=t->tm_year+1900;// get current year
    int current_month=t->tm_mon+1;// get current monthh
    int current_day=t->tm_mday;// get current day
    //declare
    int month,day;
    sscanf(leave_date,"%d-%d",&day,&month);//convert integer to string
    if ((month < current_month) || (month == current_month && day < current_day))
    {   //denying date that smaller than current date
        return 1;
    }
    return 0;
}
void Cancel_Leave(){
    system("cls");
    fflush(stdin);
    printf("CANCEL LEAVE\n");
    printf("___________________________________________________________________\n");
    //declare
    char line[500],input[100];
    int count = 0,sure;
    struct Staff File;
    //open file
    FILE *fptr;
    fptr=fopen("Apply.txt","r");
    if (fptr==NULL)
    {
        printf("File does not exists");
        exit;
    }
    else
    {
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");
        while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type
        ,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare id and date
            if(strcmp(id, File.id)==0 && !(Check_Current_Time(File.staff_leave.leave_date)))
            {
                printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
                ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type
                ,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status);//display
                count++;
            }
        }
        if (count == 0){//validation
            printf("\nYou have not applied any leave.\n\n(Press any key to exit) ");
            scanf("%*s");
            Staff();
        }
        else
        {
            fclose(fptr);//close file
            fptr = fopen("Apply.txt", "r");//open file
            printf("\nPlease enter the ID of the leave you wanted to cancel: ");
            scanf("%s",input);//get input

            rewind(fptr);//rewind pointer in file
            int count = 0;//declare
            while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
            ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type
            ,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
            {   //compare LeaveID, StaffId and date
                if(strcmp(input,File.staff_leave.PK)==0 && strcmp(id, File.id)==0 
                && !(Check_Current_Time(File.staff_leave.leave_date)))
                {
                    count = 1;
                    if(strcmp(File.staff_leave.status,"Pending")==0)//compare pending status
                    {
                        while(1)
                        {
                            int i;//declare
                            printf("\nAre you sure to cancel this leave?\n"
                            "1. Yes\n"
                            "2. No\n"
                            "Please Select: ");
                            i = scanf("%d",&sure);//get input
                            if (i != 1)//validation
                            {
                                printf("\nInvalid input\n");
                                scanf("%*s");
                                continue;
                            }
                            else
                            {   //open file
                                FILE *fpt;
                                fpt = fopen("temp.txt", "w");
                                if(fpt == NULL)
                                {
                                    printf("File cannot be found");
                                    exit;
                                }
                                if (sure == 1)
                                {
                                    rewind(fptr);//rewind file pointer
                                    while (fgets(line,sizeof(line), fptr) != NULL) //read file
                                    {   // Check if the line contains the data to be deleted
                                        if (strstr(line, input) == NULL) 
                                        {   // Write the line to file if it does not contain the data to be deleted
                                            fputs(line, fpt);
                                        }
                                    }
                                    fclose(fpt);
                                    fclose(fptr);//close file
                                    remove("Apply.txt");//remove
                                    rename("temp.txt", "Apply.txt");//rename

                                    printf("\nLeave has been cancelled.\n(Press any key to exit)");
                                    scanf("%*s");
                                    Staff();//call out Staff function
                                    break;
                                }
                                if (sure == 2)
                                {
                                    Staff();//call out Staff function
                                    break;
                                }
                                else
                                {   //validation
                                    printf("\nInsert a valid number\n");
                                    continue;
                                }
                            }
                        }
                    }//validation for not cancelling leave that have been review
                    else if(strcmp(File.staff_leave.status,"Approved")==0||strcmp(File.staff_leave.status,"Rejected")==0)
                    {
                        printf("\nThis leave have been review by your superior, you cannot cancel it\n(Press any key to exit)");
                        scanf("%*s");
                        Staff();//call out Staff function
                        break;
                    }
                }
            }
            if(!count)//validation
            {
                printf("Leave ID cannot be found\n(Press any key to try again)");
                scanf("%*s");
                Cancel_Leave();//call out Cancel_Leave function to try again
            }
        }      
    }
}
void Leave_Status()
{
    system("cls");
    fflush(stdin);
    printf("LEAVE STATUS\n");
    printf("___________________________________________________________________\n");
    //declare
    char line[500];
    struct Staff File;
    //open file
    FILE *fptr;
    fptr=fopen("Apply.txt","r");
    if (fptr==NULL)
    {
        printf("File does not exists");
        exit;
    }
    else
    {
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");
        while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type
        ,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare id
            if(strcmp(id, File.id)==0)
                {
                    printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
                    ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                    ,File.staff_leave.reason,File.staff_leave.status);//display
                }
        }
        printf("\n(Press any key to exit) ");
        scanf("%*s");
        Staff();//call out Staff function
    }
    fclose(fptr);//close file
}
void Summary()
{
    system("cls");
    printf("SUMMARY OF LEAVE INFORMATION\n");
    printf("___________________________________________________________________\n");
    //declare
    struct Staff File;
    struct Leave view;
    char line[500];
    int a=0,b=0,c=0;
    //open file
    FILE *fptr;
    FILE *fptr1;
    fptr = fopen("Leave.txt", "r");
    fptr1 = fopen("Apply.txt", "r");
    if(fptr == NULL||fptr1 == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    else
    {
        while(fscanf(fptr,"%[^|]|%d|%d|%d|%d|%d\n"
        ,File.id,&view.Annual,&view.Medical,&view.Emergency,&view.Compassionate,&view.Personal)==6)//read from file
        {   //compare id
            if(strcmp(id, File.id)==0)
            {
                printf("Hi %s, You still have\n"
                       "%d days of Annual Leave\n"
                       "%d days of Medical Leave\n"
                       "%d days of Emergency Leave\n"
                       "%d days of Compassionate Leave\n"
                       "%d days of Personal Leave\n\n"
                       ,name,view.Annual,view.Medical,view.Emergency,view.Compassionate,view.Personal);//display
            }
        }
        printf("\n======== Pending List ========\n");
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");  
        while(fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type
        ,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare id and pending status
            if(strcmp(id,File.id)==0 && strcmp(File.staff_leave.status,"Pending")==0)
            {
                printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
                ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                ,File.staff_leave.reason,File.staff_leave.status);//display
                a++;
            }
        }  
        if(!a)//validation
        {
            printf("____________________________________________________________________________\n");
            printf("You dont have a leave application that is pending\n");
        }
        fclose(fptr1); //close file
        fptr1 = fopen("Apply.txt", "r"); //open file
        printf("\n======== Approve List ========\n");
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");  
        while(fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type
        ,File.staff_leave.leave_date,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare id and approved status
            if(strcmp(id,File.id)==0 && strcmp(File.staff_leave.status,"Approved")==0)
            {
                printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
                ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                ,File.staff_leave.reason,File.staff_leave.status);//display
                b++;
            }
        }  
        if(!b)//validation
        {
            printf("____________________________________________________________________________\n");
            printf("You dont have a leave application that is approved\n");
        }
        fclose(fptr1);   //close file
        fptr1 = fopen("Apply.txt", "r");
        printf("\n======== Rejected List ========\n");
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");  
        while(fscanf(fptr1, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
        ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare id and rejected status
            if(strcmp(id,File.id)==0 && strcmp(File.staff_leave.status,"Rejected")==0)
            {
                printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
                ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                ,File.staff_leave.reason,File.staff_leave.status);//display
                c++;
            }
        }  
        if(!c)//validation
        {
            printf("____________________________________________________________________________\n");
            printf("You dont have a leave application that is rejected\n");
        }
        printf("\n(Press any key to exit) ");
        scanf("%*s");
        Staff();//call out Staff function

        fclose(fptr1);  //close file
    }
    fclose(fptr); //close file
}
void Superior()
{   //declare
    int superiorchoice;
    //display
    system("cls");
    printf("SUPERIOR PAGE\n");
    printf("___________________________________________________________________\n");
    printf("\nHi %s, Welcome to APU Leave Application and Management System\n\n",name);
    printf( "1.Approve Leave\n"
            "2.Check Date\n"
            "3.Exit\n");
    do{
        int i;//declare
        printf("Please select activity: ");
        i = scanf("%d",&superiorchoice);//get input
        if(i!=1){//validation
            printf("\nInsert a valid number\n");
            scanf("%*s");
            continue;
        }
        else{
            switch(superiorchoice)
            {
            case 1:
                Approve_Leave();//call out Approve_Leave function
                break;
            case 2:
                Check_Date();//call out Check_Date function
                break;
            case 3:
                printf("\nThank You, Have A Nice Day\n");
                menu();//call out menu function
                break;
            default: //validation
                printf("\nInsert a valid number\n");
                continue;
            }
        }
    }
    while (!(superiorchoice>0&&superiorchoice<4));
}
void Approve_Leave()
{
    system("cls");
    fflush(stdin);
    printf("APPROVE LEAVE\n");
    printf("___________________________________________________________________\n");
    //declare
    struct Staff File;
    struct Staff Check;
    struct Leave view;
    char line[500],ID[100],TYPE[100];
    int status,sure,found = 0;
    char input[100],replace[500];
    //open file
    FILE *fptr;
    fptr = fopen("Apply.txt", "r");
    if(fptr == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");
    while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
    ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
    ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
    {   //compare pending status, department and date
        if(strcmp(File.staff_leave.status, "Pending")==0 && strcmp(department,File.department)==0 
        && !(Check_Current_Time(File.staff_leave.leave_date)))
        {
            printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
            ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
            ,File.staff_leave.reason,File.staff_leave.status);//display
            found++;
        }
    }
    if (!found)//validation
    {
        printf("\nThere is no leave application in your department.\n\n(Press any key to exit) ");
        scanf("%*s");
        Superior();//call out Superior function
    }
    else
    {
        fclose(fptr);//close file
        fptr = fopen("Apply.txt", "r");//open file
        
        printf("\nPlease enter the ID of the leave you wanted to make change: ");
        scanf("%s",input);//get input
        rewind(fptr);//rewind  pointer in file
        int count = 0;//declare
        while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
        ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare LeaveID, pending status and date
            if(strcmp(input,File.staff_leave.PK)==0 && strcmp(File.staff_leave.status,"Pending")==0 
            && !(Check_Current_Time(File.staff_leave.leave_date)))
            {   
                strcpy(ID,File.id);//copy variable
                strcpy(TYPE,File.staff_leave.type);//copy variable
                count = 1;
                while(1)
                {
                    int i;//declare
                    printf("\n1.Approved\n"
                        "2.Rejected\n"
                        "Please select leave type: ");
                    i = scanf("%d",&status);//get input
                    if(i!=1)//validation
                    {
                        printf("\nInsert a valid number\n");
                        scanf("%*s");
                        continue;
                    }
                    else{
                        if(status == 1){
                            strcpy(File.staff_leave.status,"Approved");//copy string to variable
                            break;
                        }
                        else if(status == 2){
                            strcpy(File.staff_leave.status,"Rejected");//copy string to variable
                            break;
                        }
                        else{//validation
                            printf("\nInsert a valid number\n");
                            continue;
                        }
                    }
                }
                while(1)
                {
                    int i;//declare
                    printf("\nAre you sure to edit this leave?\n"
                        "1. Yes\n"
                        "2. No\n"
                        "Please Select: ");
                    i = scanf("%d",&sure);//get input
                    if (i != 1)//validation
                    {
                        printf("\nInvalid input\n");
                        scanf("%*s");
                        continue;
                    }
                    else
                    {   //open file
                        FILE *fpt;
                        fpt = fopen("temp.txt", "w");
                        if(fpt == NULL)
                        {
                            printf("File cannot be found");
                            exit;
                        }
                        if(sure == 1)
                        {
                            sprintf(replace,"%s|%s|%s|%s|%s|%s|%s\n"
                            ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                            ,File.staff_leave.reason,File.staff_leave.status);//store the new data
                            rewind(fptr);//rewind the pointer in file
                            while (fgets(line, sizeof(line), fptr) != NULL) //read from file
                            {
                                if (strstr(line,input) != NULL) // Check if the line contains input to be deleted
                                {
                                    fputs(replace, fpt); //relace the line contains input with new data
                                } 
                                else 
                                {
                                    fputs(line, fpt);// Write the line to file if it does not contain the input
                                }
                            }
                            fclose(fpt);
                            fclose(fptr);//close files
                            remove("Apply.txt");//remove file
                            rename("temp.txt", "Apply.txt");//rename file
                            if(status == 1)
                            {   //open files
                                FILE *fpt;
                                FILE *fptr1;
                                fpt = fopen("temp.txt", "w");
                                fptr1 = fopen("Leave.txt", "r");
                                if(fpt == NULL||fptr1 == NULL)
                                {
                                    printf("File cannot be found");
                                    exit;
                                }
                                while (fgets(line,sizeof(line), fptr1) != NULL) //read from file
                                {
                                    sscanf(line,"%[^|]|%d|%d|%d|%d|%d\n",File.id,&view.Annual,&view.Medical
                                    ,&view.Emergency,&view.Compassionate,&view.Personal);//read from file
                                    //compare id
                                    if (strcmp(ID,File.id)==0)
                                    {
                                        if(strcmp(TYPE,"Annual")==0){//compare leave type and -1
                                            view.Annual -= 1;
                                        }
                                        else if(strcmp(TYPE,"Medical")==0){//compare leave type and -1
                                            view.Medical -= 1;
                                        }
                                        else if(strcmp(TYPE,"Emergency")==0){//compare leave type and -1
                                            view.Emergency -= 1;
                                        }
                                        else if(strcmp(TYPE,"Compassionate")==0){//compare leave type and -1
                                            view.Compassionate -= 1;
                                        }
                                        else if(strcmp(TYPE,"Personal")==0){//compare leave type and -1
                                            view.Personal -= 1;
                                        }
                                        sprintf(replace,"%s|%d|%d|%d|%d|%d\n",File.id,view.Annual,view.Medical
                                        ,view.Emergency,view.Compassionate,view.Personal);//store new data
                                        fputs(replace, fpt);//relace the line contains input with new data
                                    } 
                                    else 
                                    {
                                        fputs(line, fpt);// Write the line to file if it does not contain the input
                                    }
                                }
                                fclose(fpt);
                                fclose(fptr1);//close files
                                remove("Leave.txt");//remove
                                rename("temp.txt", "Leave.txt");//rename
                                printf("\nLeave has been updated.\n(Press any key to exit)");
                                scanf("%*s");
                                Superior();//call out Superior function
                                break;
                            }
                            else if(status == 2)
                            {   //open files
                                FILE *fpt;
                                FILE *fptr1;
                                fpt = fopen("temp.txt", "w");
                                fptr1 = fopen("Leave.txt", "r");
                                if(fpt == NULL||fptr1 == NULL)
                                {
                                    printf("File cannot be found");
                                    exit;
                                }
                                while (fgets(line,sizeof(line), fptr1) != NULL) //read from files
                                {
                                    sscanf(line,"%[^|]|%d|%d|%d|%d|%d\n",File.id,&view.Annual,&view.Medical
                                    ,&view.Emergency,&view.Compassionate,&view.Personal);//read from files
                                    sprintf(replace,"%s|%d|%d|%d|%d|%d\n",File.id,view.Annual,view.Medical
                                    ,view.Emergency,view.Compassionate,view.Personal);//store new data(its the same data)
                                    if (strcmp(ID,File.id)==0)//compare id
                                    {
                                        fputs(replace, fpt);//relace the line contains input with new data
                                    }
                                    else 
                                    {
                                        fputs(line, fpt);// Write the line to file if it does not contain the input
                                    }
                                } 
                                fclose(fpt);
                                fclose(fptr1);//close files
                                remove("Leave.txt");//remove
                                rename("temp.txt", "Leave.txt");//rename
                                printf("\nLeave has been updated.\n(Press any key to exit)");
                                scanf("%*s");
                                Superior();//call out Superior function
                                break;
                            }
                        }
                        else if(sure == 2)
                        {
                            Superior();//call out Superior function
                            break;
                        }
                        else//validation
                        {
                            printf("\nInsert a valid number\n");
                            continue;
                        }
                    }
                }
            }
        }
        if (!count)
        {
            printf("\nLeave ID cannot be found.\n\n(Press any key to try again) ");
            scanf("%*s");
            Approve_Leave();
        }
    }
}
void Check_Date()
{
    fflush(stdin);
    system("cls");
    printf("CHECK DATE\n");
    printf("___________________________________________________________________\n");
    //declare
    char line[500],string[50];
    int input,input2,found = 0;
    struct Staff File;
    while (1)
    {
        int i;//declare
        printf("\nPlease enter the month you want to search: ");
        i=scanf("%02d",&input);//get input
        if (i!=1)//validation
        {
            printf("Invalid Input\n");
            while (getchar() != '\n');
            continue;
        }
        else
        {
            if(input < 0 || input > 12)//validation for month
            {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
            }
            else
            {
                break;
            }
        }
    }
    while (1)
    {
        int i;//declare
        printf("\nPlease enter the date you want to search: ");
        i=scanf("%02d",&input2);//get input
        if (i!=1)//validation
        {
            printf("Invalid Input\n");
            scanf("%*s");
            continue;
        }
        else
        {
            if(input==1 ||input==3 ||input==5 ||input==7 ||input==8 ||input==10 ||input==12)
            {
                if(input2 < 1 ||input2> 31 )//validation for date
                {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
                }
                else
                {
                    break;
                }
            }
            else if(input==4 ||input==6 ||input==9 ||input==11)
            {
                if(input2 < 1 ||input2 > 30 )//validation for date
                {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
                }
                else
                {
                    break;
                }
            }
            else if(input==2)
            {
                if(input2 < 1 ||input2 > 28 )//validation for date
                {
                printf("Invalid Input\n");
                while (getchar() != '\n');
                continue;
                }
                else
                {
                    break;
                }
            }
        }
    }
    sprintf(string, "%02d-%02d", input2, input);//convert input month and date to string
    FILE *fptr;//open file
    fptr = fopen("Apply.txt", "r");
    if(fptr == NULL)
    {
        printf("File cannot be found");
        exit;
    }
    else
    {
        printf("\nLeave ID  |Staff ID  |Name                          |Leave Type     |Date      |Reason                                  |Status\n");
        while(fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n"
        ,File.staff_leave.PK,File.id,File.name,File.department,File.staff_leave.type,File.staff_leave.leave_date
        ,File.staff_leave.reason,File.staff_leave.status)==8)//read from file
        {   //compare date and department
            if (strcmp(string,File.staff_leave.leave_date)==0 && strcmp(department,File.department)==0)
            {
                printf("%-10s|%-10s|%-30s|%-15s|%-10s|%-40s|%s\n"
                ,File.staff_leave.PK,File.id,File.name,File.staff_leave.type,File.staff_leave.leave_date
                ,File.staff_leave.reason,File.staff_leave.status);//display
                found++;
            }  
        }
        if (found == 0)//validation
        {   //display
            printf("\n____________________________________________________________________________________________________________________________________\n");
            printf("\nNo staff under your department have leave applications found for the given date and month.\n\n(Press any key to exit) ");
            scanf("%*s");
            Superior();//call out Superior function
        }
        else//validation
        {
            printf("\n(Press any key to exit) ");
            scanf("%*s");
            Superior();//call out Superior function
        }
    }
    fclose(fptr);//close file
}
