#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//#include"cheking.h"
typedef enum{}Area;
/*
Employee Sign in and Sing up
}*/
//mail,password,first name,last name,ID,Age,gender,phone,Address,cv file,personal user detail file
typedef struct {
	char mail[50], password[13], first_name[20], last_name[20], ID[10], gender[7], phone[10], location[10], cv_file_name[30], pud_file_name[30];
	int age;
	

}Employee;

//write the Employee's datat to files.
void add_employee_to_files(Employee* emp) {
	if (emp) {
		char line[255];
		FILE* ud = fopen("Book1.csv", "a+");
		if (ud) {
			///
			/// /*mail,password,first name,last name,ID,Age,gender,phone,Address,cv file,personal user detail file*/
			///
			while(fgets(line, 255, ud)){}
			fprintf(ud, "%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n", emp->mail, emp->password, emp->first_name, emp->last_name, emp->ID, emp->age, emp->gender, emp->phone, emp->location, emp->cv_file_name, emp->pud_file_name);
			return;
		}
		fclose(ud);
	}
}


//Sign Up:
/*
  creating user, return true if succees.
*/
Employee* employee_sign_up() {
	Employee* new_user = malloc(sizeof(Employee));
	char input[100];
	printf("SIGN UP:\n");
	
	printf("Enter your first name:");
	scanf("%s", new_user->first_name);
	printf("Enter your last name:");
	scanf("%s", new_user->last_name);
	printf("Enter your email:");
	scanf("%s", new_user->mail);
	do {
		printf("Enter your password:");
		scanf("%s", new_user->password);
	} while (/*!check_password(new_user->password)*/ false);
	do {
		printf("Reenter your password:");
		scanf("%s", input);
	} while (strcmp(new_user->password, input));

	printf("Enter your Age: ");
	scanf("%d", &new_user->age);
	printf("Enter your  phone:");
	scanf("%s", new_user->phone);
	printf("Enter your  ID:");
	scanf("%s", new_user->ID);
	printf("Enter your  gender:");
	scanf("%s", new_user->gender);
	printf("Enter your  location:");
	scanf("%s", new_user->location);
	strcpy(new_user->cv_file_name, "None");
	strcpy(new_user->pud_file_name, "None");
	add_employee_to_files(new_user);
	return new_user;
}



//this function to return the password for the specific email.
// if the email doesn't exist, so the function will return 'not found'
char* get_pass_by_mail(const char* mail) {
	FILE* tmp = fopen("C://Users//moyal//OneDrive//Desktop//Book1.csv", "r");
	char line[255], c, *token;
	//while the file not in the end of file (eof).
	while (!feof(tmp)){
		fgets(line, 255, tmp);
		token = strtok(line, ", ");//'strtok' function split a line(string) to some tokens by the sign we choose.
		
		while (token != NULL)
		{
			// if the token is the same mail(that's mean the same user) so return the password of this account.
			if (strcmp(token, mail) == 0) { return strtok(NULL, ", "); }
			token = strtok(NULL, ", ");// promote token to the next token.
		}
	}
	
	fclose(tmp);// close and save the file.
	return "not found";
}


Employee* get_user_by_mail(const char* mail) {
	Employee* res = NULL;
	char buffer[1024], *token = NULL;
	FILE* tmp = fopen("Book1.csv", "r");
	if (tmp) {
		fgets(buffer, 1024, tmp);
		while (!feof(tmp)) {
			fgets(buffer, 1024, tmp);
			token = strtok(buffer, ",");
			if (!strcmp(token, mail)) {
				res = (Employee*)malloc(sizeof(Employee));
				strcpy(res->mail, token);
				token = strtok(NULL, ",");
				strcpy(res->password, token);
				token = strtok(NULL, ",");
				strcpy(res->first_name, token);
				token = strtok(NULL, ",");
				strcpy(res->last_name, token);
				token = strtok(NULL, ",");
				strcpy(res->ID, token);
				token = strtok(NULL, ",");
				res->age = atoi(token);
				token = strtok(NULL, ",");
				strcpy(res->gender, token);
				token = strtok(NULL, ",");
				strcpy(res->phone, token);
				token = strtok(NULL, ",");
				strcpy(res->location, token);
				token = strtok(NULL, ",");
				strcpy(res->cv_file_name, token);
				token = strtok(NULL, ",");
				strcpy(res->pud_file_name, token);
				token = strtok(NULL, ",");
				break;
			}

		}
		
	}
	return res;
	
}


//Sign In:
/*
  checking user details, return true if the details are correct.

*/
bool sign_in() {
	Employee* user = NULL;
	bool signIn = false;
	char mail[50] = "";// to store the user inputs.
	char password[12] = "", userPassword[12] = "";// to store the password.
	printf("Mail: ");//ask user for mail.
	scanf("%s", mail);
	strcpy(userPassword, get_pass_by_mail(mail));// 'get_pass_by_mail()' return the password of the account if exist in the system.
	printf("Password: ");//ask user for password.
	scanf("%s", password);
	if (strcmp(userPassword, password) == 0) {
		signIn = true;// check the password.
		user = get_user_by_mail(mail);
	}
	return signIn;

}
void printEmployee(Employee* emp) {
	char buffer[256];
	printf("Full Name: %s %s.\n", emp->first_name, emp->last_name);
	printf("Mail: %s.\n", emp->mail);
	printf("ID: %s.\nPhone Number: %s.\nGender: %s.\nAddress: %s.\nAge: %d.\n", emp->ID, emp->phone, emp->gender, emp->location, emp->age);
	if (strcmp(emp->cv_file_name, "None")) {
		FILE* tmp = fopen(emp->cv_file_name, "r");
		if (tmp) {
			printf("CV: \n");
			while (fgets(buffer, 256, tmp)) {
				puts(buffer);
			}
			fclose(tmp);
		}
	}
	if (strcmp(emp->pud_file_name, "None")) {

		FILE* tmp = fopen(emp->pud_file_name, "r");
		if (tmp) {
			printf("personal user details: \n");
			while (fgets(buffer, 256, tmp)) {
				puts(buffer);
			}
			fclose(tmp);
		}
	}
}

bool upload_cv(Employee* emp) {
	char cvFileName[50];
	printf("Enter your cv file name: ");
	scanf("%s", cvFileName);
	FILE* tmp = fopen(cvFileName, "r");
	if (tmp) { strcpy(emp->cv_file_name, cvFileName); fclose(tmp); return true; }
	else { puts("can't open your file, make sure you've wrote the rigth path to file."); return false; }
}


int main() {
	//SIGN UP:
	/*Employee* emp = get_user_by_mail("moyal.shoham@gmail.com");
	printEmployee(emp);
	printf(upload_cv(emp) ? "yeyy\n" : "failed\n");
	printEmployee(emp);*/
	Employee* emp = employee_sign_up();
	//printf(add_to_file ? "%s %s added to the files succeessfully\n" : "%s %s arn't added to the files\n", emp->first_name, emp->last_name);

	/*SIGN IN:
	Employee* user = NULL;
	bool log_in = sign_in(user);
	printf(log_in ? "succeess\n" : "failed\n");
	if (log_in) {
		puts("Do you ");
	}*/
}