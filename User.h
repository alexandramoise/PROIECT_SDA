#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

class User {
private:
    int id;
    string role, name, password;

public:
    User() {}
    User(int i, string r, string n, string p) : id(i),role(r),name(n),password(p) { }
    User(string r, string n, string p) : role(r),name(n),password(p) { }
    User(string r, string n) : role(r), name(n) { }
    ~User() { }
    int getId() { return this->id;}
    string getRole() { return this->role; }
    string getName() { return this->name; }
    string getPassword() { return this->password; }
    void setId(int x) { this->id = x; }
    User& operator= (const User& u) {
        id = u.id; role = u.role; name = u.name; password = u.password;
        return *this;
    }

    void printUser() { cout<<this->getRole()<<": "<<this->getName()<<" + "<<this->getPassword()<<endl; }

    bool loginUser(string r, User &u) {
        string nume = u.getName();
        transform(nume.begin(), nume.end(), nume.begin(), ::tolower);
        nume.erase(std::remove(nume.begin(), nume.end(), ' '),nume.end());

        if(r == "profesor") {
            std::ifstream fisier_profesori;
            fisier_profesori.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/profesori.txt");
            string line;
            string user = nume+" "+u.getPassword();

            if(fisier_profesori.is_open()) {
                while( fisier_profesori) {
                        std::getline(fisier_profesori,line);
                        int space{ line.find_first_of(' ')};
                        string text{line.substr(0, space)};
                        line.erase(0,space+1);
                        if(line == user) {
                            int idi = stoi(text);
                            u.setId(idi);
                            return true;
                        }

                }
            }
            return false;
        }
        else {
            std::ifstream fisier_studenti;
            fisier_studenti.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/studenti.txt");
            string line;
            string user = nume+" "+u.getPassword();
            if(fisier_studenti.is_open()) {
                while( fisier_studenti ) {
                    std::getline(fisier_studenti,line);
                        int space{ line.find_first_of(' ')};
                        string text{line.substr(0, space)};
                        line.erase(0,space+1);
                        if(line == user) {
                            int idi = stoi(text);
                            u.setId(idi);
                            return true;
                        }
                }
            }
            return false;
        }
    }

    string get_student(int nr) {
        std::ifstream fisier_studenti;
            fisier_studenti.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/studenti.txt");
            string line;
            if(fisier_studenti.is_open()) {
                while( fisier_studenti ) {
                    std::getline(fisier_studenti,line);
                        int space{ line.find_first_of(' ')};
                        int last { line.find_last_of(' ')};
                        string text{line.substr(0, space)};
                        if(stoi(text) == nr) {
                            string name{ line.substr(space+1,last-2)};
                            return name;
                        }
                }
            }
    }

    string student_grade(string nume,string subject) {
    transform(nume.begin(), nume.end(), nume.begin(), ::tolower);
        nume.erase(std::remove(nume.begin(), nume.end(), ' '),nume.end());

    int ok = 0;
    std::ifstream fisier_note;
    if(subject == "romana")
        fisier_note.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/note_romana.txt");
    else if(subject == "matematica")
        fisier_note.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/note_mate.txt");
    else if(subject == "fizica")
        fisier_note.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/note_fizica.txt");
    string line;

    if(fisier_note.is_open()) {
        while(fisier_note) {
            std::getline(fisier_note,line);
            auto space1{ line.find_first_of(' ')};
            auto space2{ line.find_last_of(' ')};
            if(space1 < 4) {
                string student{line.substr(space1+1,space2-2)};
                //cout<<student<<";";
                if(student == nume)
                    { string grade{ line.substr(space2+1,line.size())};
                      return grade; }
           }
        }
    }
    fisier_note.close();
    return "";
}

};

#endif // USER_H_INCLUDED
