#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
float finalAmount;

struct customer
 {
   char c_name[20],c_phno[10],c_address[30];
   int c_id;
   float price;
 };
 
struct bill
 { 
   int b_id;
   int cid;
   char name[20],phno[10],address[30];
   float price;	
   int unit;
 };
 float totalAmount=0,temptotal=0;
 int units;
 
int customer_id() {
    int a;
    FILE *fp;
    fp = fopen("ci.txt", "r");
    if (fp == NULL) {
        a = 1;
    } else {
        fscanf(fp, "%d", &a);
        fclose(fp);
        a++;
    }

    fp = fopen("ci.txt", "w");
    fprintf(fp, "%d", a);
    fclose(fp);

    return a;
}

 
  
  int bill_id()
  {
   int y;
   FILE *fp;
   fp=fopen("bi.txt","r");
    if(fp==NULL) 
      y=1;
    else
      {
       fscanf(fp,"%d",&y);
       y++;
      }
   fclose(fp);
   
   fp=fopen("bi.txt","w");
   fprintf(fp,"%d",y);
   fclose(fp);
   return y;
  } 
   
 void add_customer()
  {
   FILE *ptr;
   int i;
   struct customer c;
   ptr=fopen("cust.txt","a");
     fflush(stdin);
   printf("\n Enter customer details :- \n Name  -  ");
   gets(c.c_name);
    printf(" phno:-");
    gets(c.c_phno);
    printf("Address:-");
    gets(c.c_address);
   
     fflush(stdin);
   c.c_id=customer_id();
    
       printf("\n Record added successfully.  ");
       printf("\n Your customer id is   %d",c.c_id); 	
    
   fwrite(&c,sizeof(c),1,ptr);
   fclose(ptr);   
 } 
  
   void generate_bill()
  {
   int find,flag=0,chargesPerUnit,units,minamount;
   ;
   FILE *ptr,*ptr1;
   struct customer c;
   struct bill b;
   printf("\n Enter your customer id.  ");
   scanf("%d",&find);
    
   ptr=fopen("cust.txt","r");
    while(!feof(ptr))
     {
       fread(&c,sizeof(c),1,ptr);
       if(c.c_id==find)
        { flag=1;
          ptr1=fopen("bill.txt","a");
          b.b_id=bill_id();
          strcpy(b.name,c.c_name);
          strcpy(b.phno,c.c_phno);
          strcpy(b.address,c.c_address);
          b.price=c.price;
          b.cid=c.c_id;
          printf("\n Enter number of unit consumed in this month.  ");
          scanf("%d",&units);
           if (units < 50) {
           	minamount=100;
        chargesPerUnit = 4;
        totalAmount = (units * chargesPerUnit)+minamount;
    } else if (units >= 50 && units < 100) {
    	minamount=110;
        chargesPerUnit = 5;
        totalAmount = ((units-50) * chargesPerUnit)+200+minamount;
    } else if (units >= 100 && units < 200) {
    	minamount=175;
        chargesPerUnit = 7;
        totalAmount = ((units-100) * chargesPerUnit)+450+minamount;
        
    } else { 
        minamount=200;
        chargesPerUnit = 8;
        totalAmount = ((units-200) * chargesPerUnit)+1150+minamount;
    }    printf("\n   Electricity Bill");
           printf("\n   Bill id        :- %d",b.b_id);
           printf("\n   Name           :- %s",b.name);
           printf("\n   Customer id    :-  %d",b.cid);
           printf("\n****Total Amount (in Rupees)*****: Rs %f\n", totalAmount);
           finalAmount=totalAmount;
		   printf("Breakdown:\n");
           
    if (units < 50) {
        printf(" MinimumCharge %d\n Units < 50: %d units x Rs. %.2f = Rs. %.2f\n",minamount, units, 4.0, units * 4.0);
    } else if (units >= 50 && units < 100) {
        printf(" MinimumCharge %d\n Units < 50: 50 units x Rs. %.2f = Rs. %.2f\n",minamount, 4.0, 50 * 4.0);
        printf("  Units >= 50 and < 100: %d units x Rs. %.2f = Rs. %.2f\n", units - 50, 5.0, (units - 50) * 5.0);
    } else if (units >= 100 && units < 200) {
        printf(" MinimumCharge %d\n Units < 50: 50 units x Rs. %.2f = Rs. %.2f\n",minamount, 4.0, 50 * 4.0);
        printf("  Units >= 50 and < 100: 50 units x Rs. %.2f = Rs. %.2f\n", 5.0, 50 * 5.0);
        printf("  Units >= 100 and < 200: %d units x Rs. %.2f = Rs. %.2f\n", units - 100, 7.0, (units - 100) * 7.0);
    } else {
        printf(" MinimumCharge %d\n Units < 50: 50 units x Rs. %.2f = Rs. %.2f\n",minamount,4.0, 50 * 4.0);
        printf("  Units >= 50 and < 100: 50 units x Rs. %.2f = Rs. %.2f\n", 5.0, 50 * 5.0);
        printf("  Units >= 100 and < 200: 100 units x Rs. %.2f = Rs. %.2f\n",7.0,100 * 7.0);
        printf(" Units >= 200: %d units x Rs. %.2f = Rs. %.2f\n", units - 200, 8.0, (units - 200) * 8.0);

         
}

          fflush(stdin);
          printf("\n Bill has been generated successfully.   ");
          printf("\n Your bill id is   %d",b.b_id);
          fwrite(&b,sizeof(b),1,ptr1);
          fclose(ptr1);
          break;
        }
	    		
     }
   if(flag==0)
      printf("\n Error! No such customer with id no.  %d exist.",find);
   fclose(ptr);
    	
  }
  
 void display_bill()
{
    int flag = 0, billid, custid;
    float totalAmount=temptotal;
    FILE* ptr1;
    time_t currentTime = time(NULL);;
    char* dateString = ctime(&currentTime);
    struct tm* currentDate = localtime(&currentTime);

    // Add 15 days to the current date
    currentDate->tm_mday += 15;

    // Convert the updated date back to time_t
    time_t dueTime = mktime(currentDate);

    // Convert the due time to a string representation
    char dueDate[20];
    strftime(dueDate, sizeof(dueDate), "%Y-%m-%d", localtime(&dueTime));

    struct bill b;
    ptr1 = fopen("bill.txt", "r");
    if (!ptr1)
    {
        printf("NO RECORDS FOUND\n");
        exit(0);
    }
    printf("\n Enter your customer id: ");
    scanf("%d", &custid);
    fflush(stdin);
    printf("\n Enter the bill id whose bill you want to display: ");
    scanf("%d", &billid);
    while (!feof(ptr1))
    {
        fflush(stdin);

        fread(&b, sizeof(b), 1, ptr1);
        if ((b.b_id == billid) && (b.cid == custid))
        {
            flag++;

            printf("\n   Electricity Bill");
            printf("\n Date of Bill Generation: %s", dateString);
            printf("\n   Bill id: %d", b.b_id);
            printf("\n   Name: %s", b.name);
            printf("\n   Customer id: %d", b.cid);
            //printf("\n   Phone number: %s", b.phno);
            printf("\n   Address: %s", b.address);
            printf("\n*********Total Amount (in Rupees)************: Rs %f\n", finalAmount);
            printf("\n   DueDate: %s", dueDate);
            break;
        }
    }
    if (flag == 0)
        printf("\n Error! No customer id %d or bill id %d exists.", custid, billid);
    fclose(ptr1);
}

  
  void payment()
  {
     int flag=0,billid,custid,totalAmount,custamt;
   totalAmount=temptotal;
   FILE *ptr1;
   struct bill b;
   ptr1=fopen("bill.txt","r");
   if(!ptr1)
   {
   	printf("NO RECORDS FOUND\n");
   	//exit(0);
   }
   printf("\n Enter your customer id.  ");
   scanf("%d",&custid);
   fflush(stdin);
   printf("\n Enter bill id. whose bill you want to Pay.  ");
   scanf("%d",&billid);
    while(!feof(ptr1))
     {  fflush(stdin);
     
       fread(&b,sizeof(b),1,ptr1);
        if((b.b_id==billid)&&(b.cid==custid))
         {
           flag++;
           
           printf("\n   Electricity Bill");
           printf("\n   Bill id        :- %d",b.b_id);
           printf("\n   Name           :- %s",b.name);
           printf("\n   Customer id    :-  %d",b.cid);
            printf("\n************Total Amount (in Rupees)************: Rs %f\n", finalAmount);
           printf ("\n ENTER THE AMOUNT FOR PAYMENT");
           scanf("%d",&custamt);
          
  
           while (custamt != finalAmount) 
		   {
              printf("\nPlease enter a valid amount: ");
              scanf("%d", &custamt);
            }

            printf("Payment Will Be Processed");
 
		
           
           break;
         }
     } 
  if(flag==0)
  {
      printf("\n Error! No such customer id no.  %d  OR bill no. %d  exist.",custid,billid);
  fclose(ptr1);    
  }
		     	
}
  void delete_bill()
   {
    int flag=0,billid,custid;
    FILE *ptr,*ptr1;
    struct bill b;
    ptr=fopen("bill.txt","r");
    ptr1=fopen("temp.txt","w");
	if(!ptr||!ptr1)
    {
        printf("no record found\n");
        exit(0);
}

    printf("\n Enter bill id. whose bill you want to delete.  ");
    scanf("%d",&billid);
     while(!feof(ptr))
      {
       fread(&b,sizeof(b),1,ptr);
        if(b.b_id==billid)
         {
           printf("\n Bill with id no.  %d DELETED successfully.",b.b_id);
           flag=1;
           break;
         }
        else
         fwrite(&b,sizeof(b),1,ptr1);
      }
   
    fclose(ptr);  
    fclose(ptr1);
     if(flag==0)
      printf("\n Error! No such bill with id no.  %d  exist.",billid);
    remove("bill.txt");
    rename("temp.txt","bill.txt");
   }
  
 main()
  { 
  
char username[20];
	char password[20];
	printf("*********************************************************\n");
	printf("WELCOME TO ELECTRICITY BILL MANAGEMENT SYSTEM\n");
	printf("*********************************************************\n");
	printf("please enter the username:");
	scanf("%s",username);
	printf("please enter the password: ");
	int i=0;
	for(i=0;i<5;i++)
	{
		password[i]=getch();
		printf("%c",'*');
	}
	password[i]='\0';
	if(strcmp(username,"admin1")==0)
	{
		if(strcmp(password,"12345")==0)
		{
			printf("\nwelcome _____login successfull");
		}
		else
		{
			printf("\n invalid password");
			exit(0);
		}
	}
	else
	{
		printf("\n username is invalid");
		exit(0);
	}
   int choice=1;
    while(choice!=5)
     {
      
      printf("\n **************************************  ");
     printf("\n  Electricity Bill Management System");
      printf("\n **************************************  ");
     
      
      printf("\n  MAIN MENU  ");
      printf("\n  1. Add new customer  "); 	
      printf("\n  2. Bill Generation  ");
      printf("\n  3. Display bill  ");
      printf("\n  4. Bill Payment ");
      printf("\n  5. Delete Bill by Id");
      printf("\n  6. EXIT ");
      printf("\n Enter your choice    ");
      scanf("%d",&choice);
       switch(choice)
        {
          case 1: add_customer();
                  break;
          case 2: generate_bill();
                  break;        
          case 3: display_bill();
                  break;
          case 4: payment();                          
                  break;
          case 5: delete_bill();
		          break;     
          case 6: 
		            printf("THANK YOU FOR USING");
					exit(0);
		         break;	  	  
          default:{
          	   printf("\n\n  Invalid Choice...!");
          	   printf("\n\n Press any key to continue..");
          	   getch();
	  } 	          	  	
        }
     } 	
 }
  

