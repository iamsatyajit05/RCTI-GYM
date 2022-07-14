#include <fstream>
#include <cstring>
#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>

#define ENTER 13
#define TAB 9
#define BCKSPC 8

using namespace std;

int getadpassword();

class alogin {
    string username, actualUsername = "admin";

public:
    int adlogin() {
    	for (int cnt = 0; cnt < 3; cnt++) {
        	cout << "\tEnter the username: ";
        	cin >> username;
        	if (username == actualUsername) {
	            int p = getadpassword();
            	if (p == 1) {
//        	        cout << endl << "\tLogin succesful" << endl;
    	            return 1;
	            }
            	else {
        	    	return 0;
				}
	        }
        	else {
	            cout << "\tUser name not found" << endl<< endl;
        	}
        	
        	if(cnt == 3) {
				cout << "\tLogin Failed" << endl;
            	return 0;
			}
    	}
//        return 0;
    }
    friend int getadpassword();
};

int getadpassword() {
    char password[50];
	  string actualPassword = "admin";
    
    for (int cnt = 0; cnt < 3; cnt++) {
        cout << "\tEnter the password: ";
    	  int i = 0;
		    char ch;
		    while(1){
			      ch = getch();
			  
            if(ch == ENTER || ch == TAB){
			          password[i] = '\0';
				        break;
			      }
			      else if(ch == BCKSPC && i>0){
				        i--;
				        printf("\b \b");
			      }
			      else{
				      password[i++] = ch;
				      printf("* \b");
			      }
		    }
    	
    	  if (password == actualPassword) {
//      	    cout << "\tWELCOME!!" << endl;
    	      return 1;
    	  }
    	  else {
    	      cout << "\tEntered password is incorrect!" << endl;
    	      
   	      	if(cnt == 3) {
   		  	      return 0;
			      }
    	  }
    }
	  return 0;
}

int traianer = 10;

int trainee_allotment(char *c) {
    char class_type[10];
    
    strcpy(class_type, c);
    
    if (traianer > 0) {
        if (strcmp(class_type, "gold") == 0) {
            cout << endl << "\tGold Plan - Trainer alloted" << endl;
        }
        else if (strcmp(class_type, "silver") == 0) {
            cout << endl << "\tSilver Plan - Trainer alloted" << endl;
        }
        traianer--;
        return 1;
    }
    else {
        cout << endl << "\tNo traianer availbale" << endl;
        return 0;
    }
}

class member {
    int member_number, j;
    char mem_name[50], classs[50], timings[50];
    float fee;

    long int contact;

public:
    void time_slots() {
        int opt;
        cout << "\n\n\tPlease select your preferred timing\n";
		    cout << "\t1 for - MORNING 6-7\n";
		    cout << "\t2 for - MORNING 7-8\n";
		    cout << "\t3 for - MORNING 8-9\n\n";
		    cout << "\t4 for - EVENING 6-7\n";
		    cout << "\t5 for - EVENING 7-8\n";
		    cout << "\t6 for - EVENING 8-9\n";
		    cout << "\tWhich slot? ";
        cin >> opt;
        
        switch (opt) {
        	case 1:
        	    strcpy(timings, "6AM-7AM");
        	    break;
        	case 2:
        	    strcpy(timings, "7AM-8AM");
        	    break;
        	case 3:
        	    strcpy(timings, "8AM-9AM");
        	    break;
        	case 4:
        	    strcpy(timings, "4PM-5PM");
        	    break;
        	case 5:
        	    strcpy(timings, "5PM-6PM");
        	    break;
        	case 6:
        	    strcpy(timings, "6PM-7PM");
        	    break;
        }
    }
    
    void create_mem() {
        int opt;
        
        cout << endl << "\tPlease Enter The ID: ";
        cin >> member_number;
        
        cout << endl << "\tPlease Enter The Name: ";
        getchar();
        cin.getline(mem_name, 50);
        
        cout << endl << "\tPlease Enter The Contact Number: ";
        cin >> contact;
        
        cout << endl << "\tSelect The Plan" << endl;
		    cout << "\t\t1 for GOLD" << endl;
		    cout << "\t\t2 for SILVER" << endl << endl;
        cout << "\tWhich Plan? ";
        cin >> opt;
        
        switch (opt) {
        	case 1:
        		strcpy(classs, "gold");
        	    if(trainee_allotment(classs)) {	
        	    	fee = 2500;
        	    	cout << "\tYour monthly fee would be: " << fee << endl;
       		     	time_slots();
				}
        		break;
        	case 2:
        		strcpy(classs, "silver");
        		if(trainee_allotment(classs)) {	
        	    	fee = 2000;
        	    	cout << "\tYour monthly fee would be: " << fee << endl;
       	     		time_slots();
				}
        		break;
        }
    }
    
    void show_mem() {
        cout << endl;
		cout << "\tID: " << member_number << endl;
        cout << "\tName: " << mem_name << endl;
        cout << "\tCategory: " << classs << endl;
        cout << "\tFee: " << fee << endl;
        cout << "\tContact: " << contact << endl;
        cout << "\tTimings: " << timings << endl;
    }
    
    int getmem() {
        return member_number;
    }
};

fstream fp;
member m1;

void save_member() {
	
	system("cls");
    cout << endl << "\tNEW USER" << endl;
	
    fp.open("newdata2.dat", ios::out | ios::app);
    
    m1.create_mem();
    fp.write((char *)&m1, sizeof(m1));
    
    fp.close();
    cout << endl << endl << "\tThe member has been succesfully added...";
    
	  getchar();
}

void show_all() {
	system("cls");
    cout << endl << "\tRECORDS..." << endl;
        			
    fp.open("newdata2.dat", ios::in);
    
    while (fp.read((char *)&m1, sizeof(m1))) {
        m1.show_mem();
        getchar();
    }
    
    fp.close();
    getchar();
}

void display_record() {
	int num;
	
	system("cls");
    cout << endl << "\tSEARCH USER" << endl;
	
	cout << "\n\n\tPlease Enter The ID: ";
    cin >> num;
    
    bool found = false;
    fp.open("newdata2.dat", ios::in);
    
    while (fp.read((char *)&m1, sizeof(m1))) {
        if (m1.getmem() == num) {
            cout<<endl;
            m1.show_mem();
            getchar();
            found = true;
        }
    }
    
    fp.close();
    
    if (found == false) {
        cout << "\n\n\tNo record found!";
	  }
    
    getchar();
}

void edit_member() {
    int num;
    bool found = false;
    
    system("cls");
    cout << endl << "\tEDIT USER" << endl;
    
    cout << endl << endl << "\tPlease Enter The ID: ";
    cin >> num;
    
    fp.open("newdata2.dat", ios::in | ios::out);
    
    while (fp.read((char *)&m1, sizeof(m1)) && found == false) {
        if (m1.getmem() == num) {
            m1.show_mem();
            cout << "\nPlease Enter The New details of the member: " << endl;
            m1.create_mem();
            int pos = 1 * sizeof(m1);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&m1, sizeof(m1));
            cout << endl << endl << "\t Record Successfully Updated...";
            found = true;
        }
    }
    
    fp.close();
    
    if (found == false)
        cout << endl << endl << "\tRecord Not Found...";
             
}

void delete_member() {
    int num;
    
    system("cls");
    cout << endl << "\tDELETE USER" << endl;
    
    cout << endl << endl << "\tPlease Enter The ID: ";
    cin >> num;
    
    fp.open("newdata2.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp2.dat", ios::out);
    fp.seekg(0, ios::beg);
    
    while (fp.read((char *)&m1, sizeof(m1))) {
        if (m1.getmem() != num) {
            fp2.write((char *)&m1, sizeof(m1));
        }
    }
    
    fp2.close();
    fp.close();
    
    remove("newdata2.dat");
    rename("Temp2.dat", "newdata2.dat");
    
    cout << endl << endl << "\tRecord Deleted...";
    getchar();  
}

void fnmanage() {
        int opt;
        bool isStart = true;
        while(isStart) { 	
        	system("cls");
        	cout << "\n\n\t---------------------------------------------";
        	cout << "\n\tPress 1 to CREATE MEMBER";
        	cout << "\n\tPress 2 to DISPLAY ALL RECORDS";
        	cout << "\n\tPress 3 to SEARCH FOR A PARTICULAR RECORD ";
        	cout << "\n\tPress 4 to EDIT MEMBER DETAILS";
        	cout << "\n\tPress 5 to DELETE MEMBER";
        	cout << "\n\tPress 6 to EXIT";
        	cout << "\n\t-----------------------------------------------";
        	cout << "\n\n\tOption: ";
        	cin >> opt;
        
        	switch (opt) {
        		case 1:
        		    save_member();
        		    getchar();
        		    break;

        		case 2:
        		    show_all();
        		    getchar();
        		    break;

        		case 3:
        	    	display_record();
        	    	getchar();
        	    break;

        		case 4:
        		    edit_member();
        		    getchar();
        	    break;
	
        		case 5:
        		    delete_member();
        		    getchar();
        		    break;

        		case 6:
        		    system("cls");
        		    isStart = false;
        		    break;

        		default:
        		    fnmanage();
        }
	  }
}

int main() {
    string name, code;
    system("color E0");
    cout << endl <<"\tRCTI GYM" << endl <<endl;
    alogin ad;
    
    if (ad.adlogin()) {
       	fnmanage();
    }
    
    else {
       	cout << endl << endl << "\tYou cannot access manageral details!" << endl << endl;
    }
    
    return 0;
}
