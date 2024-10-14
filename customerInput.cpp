#include <iostream>
#include <string>

//path to sqlite3.h
//#include "genLibs/sqlite3.h"

bool checkStreamErrors(const std::ostream& out, const std::istream& in);
bool nameCheck(std::string n);
bool unitNumCheck(std::string n);
bool numberCheck(std::string n);
bool checkBlock(std::string n, std::string blocks[]);
std::string getNext(std::ifstream read, int ctr, int max);

int main(){
    
    //constant variable declarations
    const std::string INPUTFILE, DATABASE;
    const int PARAMETERCOUNT = 4; 
    const int BLOCKCOUNT = 2;

    //create database instance
    sqlite3* db;

    //create datafield char arrays
    char name[25];
    char number[13];
    char unitNum[8];
    char block[20];

    //Const variable definition//
    INPUTFILE = "";
    DATABASE = "postgame.db";


    std::string blocks[BLOCKCOUNT] = {"vox", "uclub"};

    //opens stream to file
    std::ifstream read;
    read.open(INPUTFILE);


    //opens database and checks to see if it works
    int rc;
    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    //heart of program, runs line by line to send individual sqlite statements adding a new entry to a table every time
    while(!read.eof()){
        int rc;
        for(int i = 0 ; i< PARAMETERCOUNT; i++){
            std::string str;
            str = getNext(std::cin, i%PARAMETERCOUNT, PARAMETERCOUNT); 

            switch(i){
                case 0:
                    strcpy(name, str.cstr()); 
                    break;
                case 1:
                    strcpy(number, str.c_str());
                    break;
                case 2:
                    strcpy(unitNum, str.c_str());
                    break;
                case 3:
                    strcpy(block, str.c_str());
                    break;
                default:
                    return 1;
                    break;
                
            }
        }
        
        //prepares statement for security
        std::string insertSQL = "INSERT into " + &block + " (name, number, unit, block) values (?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
        
        //error checks
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return 1;
        }

        //binds each value to the right field
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, number, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, unitNum, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, block, -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        
        //checks execution success
        if (rc != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Entry added successfully!" << std::endl;
        }

        //finalizes statement
        sqlite3_finalize(stmt);
    }

    //closes database
    sqlite3_close(db);

return 0;
}

bool checkStreamErrors(const std::ostream& out, const std::istream& in) {
    if (out.fail()) {
        std::cerr << "Error: Output stream failure.\n";
    }
    
    if (in.fail()) {
        std::cerr << "Error: Input stream failure.\n";
    }
    
    if (in.eof()) {
        std::cerr << "Error: End of file reached on input stream.\n";
    }
    
    if (in.bad()) {
        std::cerr << "Error: Unrecoverable stream error on input.\n";
    }
    else 
        return true;

    return false;
}

bool nameCheck(std::string n){
    bool valid = true;
    for(int i = 0; i < n.size(); i++){
        if(isdigit(n[i])){
            std::cout << "There can not be numbers in the name\n";
            valid = false;
        }
    }
        if(!isupper(n[0])){
            std::cout << "First letter must be capitalized\n";
            valid = false;
        }

        if(n.size() > 25){
            std::cout << "The name must be less than 25 characters\n";
            valid = false;
        }


    return valid;
}

bool unitNumCheck(std::string n){
    bool valid = true;

    for(int i = 0; i<n.size(); i++){
        if(!isdigit(n[i])){
            std::cout << "Unit Num must be all digits\n";
            valid = false;
        }
        if(n.size() > 8)
            valid = false;
    }

    return valid;
}

bool numberCheck(std::string n){
    bool valid = true;
    //checks length of phone number
    if(n.size() != 10){
        std::cout << "Number input must be 10 chracters\n";
        valid = false;
    }

    for(int i = 0; i < n.size(); i++){
        if(!isdigit(n[i])){ 
            std::cout << "Phone number is in digits only\n";
            valid = true;
        }
    }
    
    return valid;
}

bool checkBlock(std::string n, std::string blocks[]){
    bool valid = false;

    for(int i = 0; i < blocks.size(); i++){
        if(n == blocks[i])
            valid = true;
    }

    if(!valid)
        "Block is invalid: Doesn't match the list\n";
    
    return valid;

}

std::string getNext(std::ifstream read, int ctr, int max){
    std::string str;
    bool valid;

    read >> str;

    switch(ctr){
        case 0:
            valid = (nameCheck(str) && checkStreamErrors(read, std::out)); 
            break;
        case 1:
            valid = (numberCheck(str) && checkStreamErrors(read, std::out)); 
            break;
        case 2:
            valid = (unitNumCheck(str) && checkStreamErrors(read, std::out));
            break;
        case 3:
            valid = (checkBlock(str) && checkStreamErrors(read, std::out)); 
            break;
        default:
            str = "ERROR";
    }
    if(!valid)
        str = "ERROR";

    return str;
}

