						/***************************/
						/*                         */
						/*      Osman Çetin        */
						/*       161044069         */
						/*         HW-07           */
						/*	  Part 2           */
						/*                         */
						/***************************/

#include <stdio.h>
#include <string.h>

int zellers_rule(int day,int month,int year);
/*this program prints given all dates between start and end date to input file. after these processes, program reads dates from input file. after reading program converts date format (dd/MM/yyyy) to (dddd, MMMM dd, yyyy) */
int main(){
	char day_name[10],month_name[10],begin_date[10], end_date[10],a;
	int day,month,year,end_day,end_month,end_year,k=0,read_day,read_month,read_year,day_code;
	FILE *fl1,*fl2;
	printf("Enter begin date:");
	scanf("%s",begin_date);
	printf("Enter end date:");
	scanf("%s",end_date);
	
	day= (begin_date[0]-'0')*10 + (begin_date[1]-'0');/*this gets start day from user*/
	month= (begin_date[3]-'0')*10 + (begin_date[4]-'0');/*this gets start month from user*/
	year= (begin_date[6]-'0')*1000 + (begin_date[7]-'0')*100 + (begin_date[8]-'0')*10 + (begin_date[9]-'0');/*this gets start year from user*/
	
	end_day= (end_date[0]-'0')*10 + (end_date[1]-'0');/*this gets day from user*/
	end_month= (end_date[3]-'0')*10 + (end_date[4]-'0');/*this gets end month from user*/
	end_year= (end_date[6]-'0')*1000 + (end_date[7]-'0')*100 + (end_date[8]-'0')*10 + (end_date[9]-'0');/*this gets end year from user*/
	
	fl1=fopen("input_date.txt","a");/*this opens input file*/
	
	while(day!=end_day+1 || month!=end_month || year!=end_year){/*this loop works until start and end date equals between*/
		if(day<10 && month<10) fprintf(fl1,"0%d/0%d/%d\n",day,month,year);
		else if(day<10) fprintf(fl1,"0%d/%d/%d\n",day,month,year);/*this writes date to file*/
		else if(month<10) fprintf(fl1,"%d/0%d/%d\n",day,month,year);
		else fprintf(fl1,"%d/%d/%d\n",day,month,year);
		
		day++;
		
		
		if(year%4==0 && month==2 && day==30){/*this condition calculates leap year*/
			day=1;
			month++;
		}
		
		if(year%4!=0 && month==2 && day==29){
			day=1;
			month++;
		}
		
		if(month<8){
			if(month%2==0 && day==31 && month!=2){
				day=1;
				month++;
			}
	
			if(month%2==1 && day==32){
				day=1;
				month++;
			}			
		}
		else{
			if(month%2==1 && day==31){
				day=1;
				month++;
			}
	
			if(month%2==0 && day==32 && month!=2){
				day=1;
				month++;
			}
			
		}	
		
		if(month==13){
			month=1;
			year++;
		}
		
	}
	fclose(fl1);/*this closes file*/
	
	fl2=fopen("input_date.txt","r");
	fl1=fopen("new_date.txt","a");
	do{/*this loop writes converted date to new file until end of file */
		
		a=fscanf(fl2,"%d/%d/%d",&read_day,&read_month,&read_year);	
		day_code=zellers_rule(read_day,read_month,read_year);
		
		
		if(a!=EOF){
		
			while(day_code<0){
				day_code+=7;
			}
		
			if(day_code>7) day_code=day_code%7;
				
			switch(day_code){/*this finds day's name*/
				case 0: strcpy(day_name , "Sunday"); break;
				case 1: strcpy(day_name , "Monday"); break;
				case 2: strcpy(day_name , "Tuesday"); break;
				case 3: strcpy(day_name , "Wednesday"); break;
				case 4: strcpy(day_name , "Thursday"); break;
				case 5: strcpy(day_name , "Friday"); break;
				case 6:	strcpy(day_name , "Saturday"); break;		
			}
		
			switch(read_month){/*this finds month name*/
				case 1: strcpy(month_name , "January"); break;
				case 2: strcpy(month_name , "February"); break;
				case 3: strcpy(month_name , "March"); break;
				case 4: strcpy(month_name , "April"); break;
				case 5: strcpy(month_name , "May"); break;
				case 6: strcpy(month_name , "June"); break;
				case 7: strcpy(month_name , "July"); break;
				case 8: strcpy(month_name , "August"); break;
				case 9: strcpy(month_name , "September");; break;
				case 10: strcpy(month_name , "October"); break;
				case 11: strcpy(month_name , "November"); break;
				case 12: strcpy(month_name , "December"); break;
			}	
		
			if(read_day<10) fprintf(fl1,"%s, %s 0%d, %d\n",day_name,month_name,read_day,read_year);/*this function writes*/
			else fprintf(fl1,"%s, %s %d, %d\n",day_name,month_name,read_day,read_year);/*this function writes*/
		}
		
		
	}while(a!=EOF);	
		
	fclose(fl2);
	fclose(fl1);

	return 0;
}

int zellers_rule(int day,int month,int year){/*this function calculates date's day with using zeller's rule*/
	
	int month_code,result;
	
	switch(month){
		case 1: month_code=11; break;
		case 2: month_code=12; break;
		case 3: month_code=1; break;
		case 4: month_code=2; break;
		case 5: month_code=3; break;
		case 6: month_code=4; break;
		case 7: month_code=5; break;		
		case 8: month_code=6; break;
		case 9: month_code=7; break;
		case 10: month_code=8; break;
		case 11: month_code=9; break;
		case 12: month_code=10; break;
 	}	
	
	if(month==1 || month==2) year--;	
	
	result=(day + (13*month_code-1)/5 + year%100 + (year%100)/4 + (year/100)/4 - 2*(year/100));
		
	return result;
}


	
