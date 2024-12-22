#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
struct data
{
    char name[30];
    char mobile[11];
    char email[30];
    char address[50];
};
void add_contacts();
void print_contacts();
void search_contact();
void delete_contact();
void edit_contact();
int validate_mobile(char *,int);
int validate_email(char *);
int revalidate(char *);
void copy(FILE *,FILE *);
void sortcontacts(struct data *,int );
int main()
{
    char ch='y';
    char choice;
    while (ch=='y' || ch=='Y')
    { 
        system("clear");
       printf("==============================\n");
       printf("\033[1;32m");
       printf("FEATURES : \n");
       printf("1.ADD CONTACT \n2.PRINT CONTACTS\n3.SEARCH CONTACTS\n4.DELETE CONTACTS\n5.EDIT CONTACTS\nEnter your choice: \n");
       printf("\033[0m");
       printf("==============================\n");
       scanf(" %c",&choice);
       switch(choice)
       {
        case '1':
            add_contacts();
            break;
        case '2':
            print_contacts();
            break;
        case '3': search_contact();
                break;
        case '4' : delete_contact();
                break;
        case '5' : edit_contact();
                break;
        default: printf("\033[1;33m");
                 printf("Invalid Choice \n");
                 printf("\033[0m");
       }
       printf("\033[1;32m");
       printf("Do you want to continue?(y/n): ");
       printf("\033[0m");
       scanf(" %c",&ch);
    }
}
void add_contacts()
{
    system("clear");
    struct data d;
    int count=0;
    FILE *fdata = fopen("data.csv","r");
    if(fdata == NULL){
        printf("file not opened");
        return;
    }
    FILE *ftemp = fopen("temp.csv","w");
    fscanf(fdata,"%d\n",&count);
    fprintf(ftemp,"%d\n",count+1);
    for(int i=0;i<count;i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
        fprintf(ftemp,"%s,%s,%s,%s\n",d.name,d.mobile,d.email,d.address);
    }
    fclose(fdata);
    char buffer[50];
    label_1 : printf("Enter the name : ");
    scanf(" %[^\n]",buffer);

    //Checking is name is valid or not

    for(int i = 0; buffer[i] != '\0';i++)
    {
        if(buffer[i] == ' ')
        {
            continue;
        }
        if(isalpha(buffer[i]) == 0)
        {
            printf("\033[1;31m");
            printf("**ERROR ENTER A VALID NAME ****\n");
            printf("\033[0m");
            printf("\033[1;32m");
            printf("Do you want to enter the Name again ?(y/n)\n");
            printf("\033[0m");
            char ch;
            scanf(" %c",&ch);
            if(ch == 'y' || ch == 'Y')
                goto label_1;
            else
                return;
        }
    }
    strcpy(d.name,buffer);

    label_2 : printf("Enter the mobile number : ");
    scanf(" %[^\n]",buffer);
    
    //Validate Mobile number
    // 0 int the function call represents that the function validate_buffer is called from add_contact 
    //function where, i need to check whether the mobile number is repeated or not in the file
    if(validate_mobile(buffer,0))        
        strcpy(d.mobile,buffer);
    else
    {
        if(revalidate("mobile number"))
            goto label_2;
        else
            return;
    }
    
    label_3 : printf("Enter the email : ");
    scanf(" %[^\n]",buffer);

    // Validate Email

    if (validate_email(buffer))
        strcpy(d.email,buffer);
    else
    {
        if(revalidate("email"))
            goto label_3;
        else
            return;
    }
    printf("Enter the address : ");
    scanf(" %[^\n]",d.address);
    fprintf(ftemp,"%s,%s,%s,%s\n",d.name,d.mobile,d.email,d.address);
    fclose(ftemp);
    fdata=fopen("data.csv","w");
    ftemp=fopen("temp.csv","r");
    copy(fdata,ftemp);
    fclose(fdata);
    fclose(ftemp);
}
void print_contacts()
{
    system("clear");
    FILE *fdata = fopen("data.csv","r"); 
    int count = 0;
    fscanf(fdata,"%d\n",&count);
    printf("==============================\n");
    printf("\033[1;32m");
    printf("**** Printing Contacts ****\n");
    printf("\033[0m");
    printf("==============================\n");
    if(count == 0)
    {
        printf("\033[1;33m");
        printf("NO CONTACTS FOUND\n");
        printf("\033[0m");
        printf("==============================\n");
    }
    struct data d[200];
    for(int i = 0;i < count ; i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d[i].name,d[i].mobile,d[i].email,d[i].address);
    }
    fclose(fdata);
    sortcontacts(d,count);
    printf("==============================\n");
    printf("\033[1;32]");
    for(int i = 0;i < count ;i++)
    {
        printf("\033[1;32]");
        printf("Name: %s\nMob_No: %s\nEmail ID: %s\nAddress: %s\n", d[i].name, d[i].mobile, d[i].email, d[i].address);
        printf("\033[0m");
        printf("==============================\n");
    }
    // for(int i = 0; i < count ; i++)
    // {
    //     fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
    //     printf("Name: %s\nMob_No: %s\nEmail ID: %s\nAddress: %s\n", d.name, d.mobile, d.email, d.address);
    //     printf("==============================\n");
    // }
    // fclose(fdata);

}
void search_contact()
{
    system("clear");
    FILE *fdata = fopen("data.csv","r");
    int count = 0;
    struct data d;
    fscanf(fdata,"%d\n",&count);
    char find[20];
    printf("Enter the name to search : \n");
    label_s : scanf(" %[^\n]",find);
    for(int i = 0; find[i] != '\0';i++)
    {
        if(find[i] == ' ')
        {
            continue;
        }
        if(isalpha(find[i]) == 0)
        {
            printf("\033[1;31m");
            printf("**ERROR ENTER A VALID NAME ****\n");
            printf("\033[0m");
            if(revalidate("Name"))
            {
                printf("Enter the name : ");
                goto label_s;
            }
            else
                return;
        }
    }
    int name_count  = 0;
    for(int i = 0; i < count; i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
        if((strcmp(find,d.name)) == 0)
        {
            name_count++;
        }
    }
    printf("==============================\n");
    if(name_count == 0)
    {
        printf("\033[1;33m");
        printf("Contact Not found\n");
        printf("\033[0m");
        printf("==============================\n");
        return;
    }
    rewind(fdata);
    fscanf(fdata,"%d\n",&count);
    char find_mobile[11];
    char buffer[11];

    if(name_count > 1)
    {
        printf("\033[1;33m");
        printf("Multiple contacts found with the same name\n");
        printf("Enter the mobile number for confirmation: ");
        printf("\033[0m");
        label_4 : scanf(" %[^\n]",buffer);
        if(validate_mobile(buffer,1))
            strcpy(find_mobile,buffer);
        else
        {
            if(revalidate("mobile number"))
            {
                printf("Enter the Mobile Number : \n");
                goto label_4;
            }
            else
                return;
        }  
        printf("==============================\n");    
    }
    int flag = 0;
    for (int i = 0; i < count; i++) {
        fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", d.name, d.mobile, d.email, d.address);
        if (strcmp(find, d.name) == 0)
        {
            if (name_count == 1 || strcmp(d.mobile, find_mobile) == 0) 
            {
                flag = 1;
                break; 
            }
        }
    }

    if(flag == 0)
    {
        printf("\033[1;33m");
        printf("*CONTACT NOT FOUND*\n");
        printf("\033[0m");
        printf("==============================\n");
        return;
    }
    printf("\033[1;32m");
    printf("*Contact Found*\n");
    printf("\033[0m");
    printf("==============================\n");
    printf("Name: %s\nMob_No: %s\nEmail ID: %s\nAddress: %s\n", d.name, d.mobile, d.email, d.address);
    printf("==============================\n");
    fclose(fdata);
}
void delete_contact()
{
    system("clear");
    FILE *fdata = fopen("data.csv","r");
    FILE *ftemp = fopen("temp.csv","w");
    int count = 0;
    fscanf(fdata,"%d\n",&count);
    struct data d;
    char find[20];
    printf("Enter the name to delete : ");
    label_d : scanf(" %[^\n]",find);
    for(int i = 0; find[i] != '\0';i++)
    {
        if(find[i] == ' ')
        {
            continue;
        }
        if(isalpha(find[i]) == 0)
        {
            printf("\033[1;31m");
            printf("**ERROR ENTER A VALID NAME ****\n");
            printf("\033[0m");
            if(revalidate("Name"))
            {
                printf("Enter the name : ");
                goto label_d;
            }
            else
                return;
        }
    }
    int name_count  = 0;
    for(int i = 0; i < count; i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
        if((strcmp(find,d.name)) == 0)
        {
            name_count = name_count + 1;
        }
    }
    printf("==============================\n");
    if(name_count == 0)
    {
        printf("\033[1;33m");
        printf("ERROR : CONTACT NOT FOUND\n");
        printf("\033[0m");
        printf("==============================\n");
        return;
    }
    char find_mobile[11];
    char buffer[11];
    rewind(fdata);
    fscanf(fdata,"%d\n",&count);
    fprintf(ftemp,"%d\n",count - 1);
    if(name_count >= 2)
    {
        printf("\033[1;33m");
        printf("Multiple contacts found with the same name\n");
        printf("Enter the mobile number for confirmation: \n");
        printf("\033[0m");
        label_5 : scanf(" %[^\n]",buffer);
        if(validate_mobile(buffer,1))
            strcpy(find_mobile,buffer);
        else
        {
            if(revalidate("mobile number"))
            {
                printf("Enter the Mobile Number : ");
                goto label_5;
            }
            else
                return;
        }  
        printf("==============================\n");    
    }
    int flag = 0;
    for (int i = 0; i < count; i++) 
    {
        fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", d.name, d.mobile, d.email, d.address);
        if (strcmp(find, d.name) == 0) 
        {
            if (name_count == 1 || strcmp(d.mobile, find_mobile) == 0) 
            {
                flag = 1;
                continue; 
            }
        }
        fprintf(ftemp, "%s,%s,%s,%s\n", d.name, d.mobile, d.email, d.address);
    }

     if (flag == 0)
     {
        printf("\033[1;31m");
        printf("*ERROR: CONTACT NOT FOUND WITH THE GIVEN MOBILE NUMBER*\n");
        printf("\033[0m");
        printf("==============================\n");
     }
    else 
    {
        printf("\033[1;32m");
        printf("*Contact Deleted Successfully*\n");
        printf("\033[0m");
    }
    fclose(fdata);
    fclose(ftemp);
    fdata=fopen("data.csv","w");
    ftemp=fopen("temp.csv","r");
    copy(fdata,ftemp);
    fclose(fdata);
    fclose(ftemp);
}
void edit_contact()
{
    system("clear");
    FILE *fdata = fopen("data.csv","r");
    FILE *ftemp = fopen("temp.csv","w");
    int count  = 0;
    fscanf(fdata,"%d\n",&count);
    fprintf(ftemp,"%d\n",count);
    struct data d;
    char find[30];
    printf("Enter the contact name to edit : \n");
    label_n : scanf(" %[^\n]",find);
     for(int i = 0; find[i] != '\0';i++)
    {
        if(find[i] == ' ')
        {
            continue;
        }
        if(isalpha(find[i]) == 0)
        {
            printf("\033[1;31m");
            printf("**ERROR ENTER A VALID NAME ****\n");
            printf("\033[0m");
            if(revalidate("Name"))
            {
                printf("Enter the name : ");
                goto label_n;
            }
            else
                return;
        }
    }
    int name_count = 0;
    for(int  i =0 ; i < count ; i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
        if((strcmp(find,d.name)) == 0)
        {
            name_count++;
        }
    }
    printf("==============================\n");
    if(name_count == 0)
    {
        printf("\033[1;33m");
        printf("Contact Not Found\n");
        printf("\033[0m");
        printf("==============================\n");
        return;
    }
    char find_mobile[11];
    char buffer[50];
    rewind(fdata);
    fscanf(fdata,"%d\n",&count);
    if(name_count > 1)
    {
        printf("\033[1;33m");
        printf("Multiple contacts found with the same name\n");
        printf("Enter the mobile number for confirmation: ");
        printf("\033[0m");
        label_6 : scanf(" %[^\n]",buffer);
        if(validate_mobile(buffer,1))
            strcpy(find_mobile,buffer);
        else
        {
            if(revalidate("mobile number"))
            {
                printf("Enter the Mobile Number : \n");
                goto label_6;
            }
            else
                return;
        }  
        printf("==============================\n");    
    }
    int flag = 0;
    for(int i = 0; i < count; i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
        if((strcmp(find,d.name)) == 0)
        {
            if(name_count == 1 || (strcmp(d.mobile,find_mobile) == 0))
            {
                flag = 1;
                printf("\033[1;32m");
                printf("**Contact found, Enter the choice to edit : **\n");
                int choice;
                printf("1.Edit Name\n");
                printf("2.Mobile Number\n");
                printf("3.Email Id\n");
                printf("4.Address\n");
                printf("\033[0m");
                scanf("%d",&choice);
                printf("==============================\n");
                switch(choice)
                {
                    case 1 : printf("Enter the name : ");
                             label_7 : scanf(" %[^\n]",buffer);
                             for(int i = 0; buffer[i] != '\0';i++)
                            {
                                if(buffer[i] == ' ')
                                {
                                    continue;
                                }
                                if(isalpha(buffer[i]) == 0)
                                {
                                    printf("\033[1;31m");
                                    printf("**ERROR ENTER A VALID NAME ****\n");
                                    printf("\033[0m");
                                    if(revalidate("Name"))
                                    {
                                        printf("Enter the name : ");
                                        goto label_7;
                                    }
                                    else
                                        return;
                                }
                            }
                            strcpy(d.name,buffer);
                            break;
                    case 2 : printf("Enter the mobile number : ");
                            label_8 : scanf(" %[^\n]",buffer);
                             if(validate_mobile(buffer,0))
                                strcpy(d.mobile,buffer);
                             else
                             {
                                if(revalidate("mobile number"))
                                {
                                    printf("Enter the mobile Number : \n");
                                    goto label_8;
                                }
                                else
                                    return;
                             } 
                            break;
                    case 3 : printf("Enter the email : ");
                            label_9 : scanf(" %[^\n]",buffer);
                             if (validate_email(buffer))
                                strcpy(d.email,buffer);
                             else
                            {
                                if(revalidate("email"))
                                    goto label_9;
                                else
                                    return;
                            }
                            break;
                    case 4 : printf("Enter the address : ");
                             scanf(" %[^\n]",d.address);
                             break;
                             default : printf("Invalid choice\n");
                }

            }
        }
        fprintf(ftemp,"%s,%s,%s,%s\n",d.name,d.mobile,d.email,d.address);
    }
    if (flag == 0)
    {
        printf("\033[1;31m");
        printf("*ERROR: CONTACT NOT FOUND*\n");
        printf("\033[0m");
    }
    else
    {
        printf("\033[1;32m");
        printf("*Contact Updated Successfully*\n");
        printf("\033[0m");
    }

    fclose(fdata);
    fclose(ftemp);
    fdata = fopen("data.csv", "w");
    ftemp = fopen("temp.csv", "r");
    copy(fdata, ftemp);
    fclose(fdata);
    fclose(ftemp);
}
void copy(FILE *fptr1,FILE *fptr2)
{
    char ch;
    while((ch = fgetc(fptr2)) != EOF)
    {
        fputc(ch,fptr1);
    }
}
int validate_mobile(char buffer[],int val)
{
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if(isdigit(buffer[i]) == 0)
        {
            printf("\033[1;31m");
            printf("*ERROR : ENTER A VALID NUMBER*\n");
            printf("\033[0m");
            return 0;
        }
    }
    if(strlen(buffer) != 10)
    {
        printf("\033[1;31m");
        printf("*ERROR : MOBILE NUMBER SHOULD CONTAIN 10 DIGITS ONLY\n");
        printf("\033[0m");
        return 0;
    }
    if(val == 0)
    {
        FILE *fdata = fopen("data.csv","r");
        int count  = 0;
        struct data d;
        fscanf(fdata,"%d\n",&count);
        for(int i = 0; i < count ; i++)
        {
            fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
            if(strcmp(buffer,d.mobile) == 0)
            {
                printf("\033[1;33m");
                printf("*** SAME MOBILE NUMBER DETECTED ***\n");
                printf("\033[0m");
                printf("==============================\n");
                printf("CONTACT DETAILS : \n");
                printf("Name : %s\nMob_No : %s\nEmail_ID : %s\nAddress : %s\n",d.name,d.mobile,d.email,d.address);
                printf("==============================\n");
                fclose(fdata);
                return 0;
            }
        }
        fclose(fdata);
    }
        return 1;
}
int validate_email(char buffer[])
{
    int i = 0;
    int at_pos = -1;
    int dot_pos = -1;
    int flag = 0;   
    int count = 0;  
    int unique = 0;
    for(i = 0; buffer[i] != '\0'; i++)
    {
        if(buffer[i] == '@')
        {
            if(at_pos == -1) 
            {
                at_pos = i;
                flag++; 
                if(isalpha(buffer[i + 1])) 
                    count++;
            }
            else 
            {
                printf("\033[1;31m");
                printf("**** ERROR: MORE THAN ONE '@' FOUND ****\n");
                printf("\033[0m");
                return 0;
            }
        }
        else if(buffer[i] == '.' && at_pos != -1)
        {
            if(dot_pos == -1)
            {
                dot_pos = i;
                flag++;
                if(isalpha(buffer[i + 1])) 
                    count++;
            }
        }
        else if(strcmp(buffer+(dot_pos+1),"com") == 0)
            unique = 1;
    }
    int data_count = 0;
    FILE *fdata = fopen("data.csv","r");
    struct data d;
    fscanf(fdata,"%d\n",&data_count);
    for(int i = 0; i < data_count ; i++)
    {
        fscanf(fdata,"%[^,],%[^,],%[^,],%[^\n]\n",d.name,d.mobile,d.email,d.address);
        if(strcmp(buffer,d.email) == 0)
        {
            printf("==============================\n");
            printf("\033[1;33m");
            printf("*** SAME EMAIL DETECTED ***\n");        //if an existing mobile number is entered the details of that number is printed
            printf("\033[0m");
            printf("==============================\n");
            printf("CONTACT DETAILS : \n");
            printf("Name : %s\nMob_No : %s\nEmail_ID : %s\nAddress : %s\n",d.name,d.mobile,d.email,d.address);
            printf("==============================\n");
            fclose(fdata);
            return 0;
        }
    }
    fclose(fdata);
    if(flag >= 2 && count >= 2 && at_pos != -1 && ((dot_pos - at_pos) > 1) && at_pos != 0 && unique)
        return 1;
    else
    {
        printf("\033[1;31m");
        printf("**** ERROR: INVALID EMAIL STRUCTURE ****\n");
        printf("\033[0m");
        return 0;
    }
}
// Giving an option to the user that if he enters name, email, mob_no ,in wrong format he can enter the details once again or he can exit from there 
int revalidate(char str[]) 
{
    printf("\033[1;32m");
    printf("Do you want to enter the %s again (y/n) ?\n",str);
    printf("\033[0m");
    char ch;
    scanf(" %c",&ch);
    if(ch == 'y' || ch == 'Y')
        return 1;
    else
        return 0;
}
// function to print all the contacts in a sorted order in terms of names 
void sortcontacts(struct data d[], int count)
{
    for(int i = 0; i < count - 1 ; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(strcmp(d[j].name,d[j+1].name) > 0)
            {
                struct data temp = d[j];
                d[j] = d[j+1];
                d[j+1] = temp;
            }
        }
    }
}