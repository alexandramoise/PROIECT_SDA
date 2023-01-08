#include <iostream>
#include <string>
#include <algorithm>
#include<bits/stdc++.h>
#include "User.h"
#include "RB.h"

using namespace std;

// creare arbore red black cu id-urile studentilor
RBTree* tree_with_students_ids() {
    RBTree *r = new RBTree();
        std::ifstream fisier_studenti;
            fisier_studenti.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/studenti.txt");
            string line;
            if(fisier_studenti.is_open()) {
                while( fisier_studenti ) {
                        std::getline(fisier_studenti,line);
                        int space{ line.find_first_of(' ')};
                        string text{line.substr(0, space)};
                        if(text.size() > 0)
                            r->RBInsert(r->createNode(stoi(text)));
                        }
            }
    return r;
    fisier_studenti.close();
}

// creare arbore red black cu notele studentilor la fiecare materie - se vor folosi pt Statistici
RBTree* tree_with_student_grades(string subject) {
    RBTree *gr = new RBTree();

    /*string nume = s.getName();
    transform(nume.begin(), nume.end(), nume.begin(), ::tolower);
        nume.erase(std::remove(nume.begin(), nume.end(), ' '),nume.end());*/

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
                //if(student == nume) {
                    string grade{ line.substr(space2+1,line.size())};
                    gr->RBInsert(gr->createNode(stoi(grade)));
                //}
            }
        }
    }
    return gr;
    fisier_note.close();
}

void student_got_grades(User u,string str) {
    string s = str;
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    cout<<str<<": ";
        if(u.student_grade(u.getName(),s).size()>=1)
            cout<<u.student_grade(u.getName(),s)<<endl;
        else
            cout<<"Inca nu ai primit nota!"<<endl;
}

bool no_grade(int k,string s) {
    User aux = User();
    if(aux.student_grade(aux.get_student(k),s).size()<1)
        return true;
    return false;
}

bool subject_password(string s1,string s2) {
    std::ifstream fisier_parole;
    fisier_parole.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/parole_discipline.txt");
    string linie;
    if(fisier_parole.is_open()) {
        while(fisier_parole) {
            std::getline(fisier_parole,linie);
            auto sp{ linie.find_last_of(' ')};
            string subj{ linie.substr(0,sp)};
            string pass { linie.substr(sp+1,linie.size())};
            if(subj == s1 && pass == s2)
                return true;
        }
    }
    return false;
    fisier_parole.close();
}

// verificare daca studentul a primit deja nota la o materie cu ajutorul arborelui cu id-uri
void give_grade(string subj,RBTree *stt) {
    stt->inorder(stt->root,subj);

    cout<<"Maxim: "<<stt->maximum(stt->root)->key<<endl;
    int k;
    cout<<"Alegeti unul din studenti introducand codul acestuia: "; cin>>k;
    while(k > stt->maximum(stt->root)->key ) {
            cout<<"Introduceti o valoare mai mica decat "<<stt->maximum(stt->root)->key<<": ";
            cin>>k;
    }

    while(!no_grade(k,subj)) {
            cout<<"Are deja nota! Introduceti din nou: "; cin>>k;
     }

    int nota;
    cout<<endl<<"Acordati nota studentului: "<<User().get_student(k)<<" ";
    cin>>nota;
    cout<<"Ati acordat nota: "<<nota;

    std::ofstream outfile;
    if(subj == "romana")
        outfile.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/note_romana.txt", std::ios_base::app); // append instead of overwrite
    else if(subj == "matematica")
        outfile.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/note_mate.txt", std::ios_base::app);
    else if(subj == "fizica")
        outfile.open("C:/Users/WINDOWS 10/Desktop/Structuri date avansate/PROIECT/note_fizica.txt", std::ios_base::app);
    outfile << k << " " << User().get_student(k)<<" "<< nota<<endl;
}


int main()
{

    cout<<"             Bine ai venit pe catalogul virtual!             "<<endl<<endl;
    cout<<"Selecteaza rolul tau: "<<endl<<"1 - Profesor "<<endl<<"2 - Student"<<endl<<"3 - Iesire din aplicatie"<<endl<<endl;
    string entry; cout<<"Introduceti optiunea: "; cin>>entry;
    while(entry < "1" || entry > "3" || entry.size()> 1) {
        cout<<"Optiune invalida! \nSelecteaza din nou rolul: "; cin>>entry;
    }

    if(entry == "1") {
        system("cls");
        cout<<"== PROFESOR =="<<endl<<"Conecteaza-te la contul de Profesor: "<<endl;
        string nume, parola;
        cout<<"Introduceti numele dvs: "; cin.ignore(); getline(cin,nume);
        cout<<"Introduceti parola: "; getline(cin,parola);
        User u = User("profesor", nume, parola);
        while(u.loginUser("profesor",u) == false) {
            cout<<endl<<"INCORECT! "<<endl; system("pause"); system("cls");
            cout<<"== PROFESOR =="<<endl<<"Conecteaza-te la contul de Profesor: "<<endl;
            cout<<"Introduceti numele dvs: "; cin.ignore(); getline(cin,nume);
            cout<<"Introduceti parola: "; getline(cin,parola);
            User aux = User("profesor", nume, parola);
            u = aux;
        }
        system("cls");
        cout<<"==PROFESOR=="<<endl<<"Bine ai venit! "<<u.getId()<<" "<<u.getName()<<endl;
        string sub = "0";
        cout<<"Alegeti o materie : \n1 - Romana \n2 - Matematica \n3 - Fizica"<<endl;
        cout<<"Introduceti optiunea: "; cin>>sub;
        while (sub < "1" || sub > "3" || sub.size() > 1) {
            cout<<"Invalid! Introduceti din nou: "; cin>>sub;
        }
        if(sub == "1") {
            system("cls");
            cout<<"~Romana~"<<endl; string p;
            cout<<"Introduceti parola pt disciplina LIMBA ROMANA: "; cin.ignore(); getline(cin,p);
            while(subject_password("romana",p) == false) {
                cout<<"Incorect! Introduceti din nou: ";
                getline(cin,p);
            }
            system("cls");
            string prof = "0";
            cout<<u.getName()<<", bine ati venit la Catalog - LIMBA ROMANA"<<endl;
            cout<<"Alegeti: \n1 - Acorda note \n2 - Vezi statistici despre note \n3 - Iesire"<<endl;
            cout<<"Introduceti optiunea: "; cin>>prof;
            while (prof < "1" || prof > "3" || prof.size() > 1) {
                cout<<"Invalid! Introduceti din nou: "; cin>>prof;
            }
            if(prof == "1") {
                system("cls");
                cout<<"~~ Acordare note ~~\n Iata lista cu studentii care nu au primit nota: "<<endl<<endl;
                RBTree *sts = tree_with_students_ids();
                give_grade("romana",sts);
            }
            else if(prof == "2") {
                RBTree *grades = tree_with_student_grades("romana");
                cout<<endl<<"Notele obtinute de studenti sunt: ";
                grades->display(grades->root,0);
                cout<<endl<<"Nota maxima: "<<grades->maximum(grades->root)->key<<endl;
                cout<<"Cea mai mica nota: "<<grades->minimum(grades->root)->key<<endl;
                cout<<"Nu au trecut: "<<grades->countPassed(grades->root)<<" studenti"<<endl;
            }
            else if(prof == "3") {
                sub = "0";
            }
        }
        else if(sub == "2") {
            system("cls");
            cout<<"~Matematica~"<<endl; string p;
            cout<<"Introduceti parola pt disciplina MATEMATICA: "; cin.ignore(); getline(cin,p);
            while(subject_password("matematica",p) == false) {
                cout<<"Incorect! Introduceti din nou: ";
                getline(cin,p);
            }
            system("cls");
            string prof = "0";
            cout<<u.getName()<<", bine ati venit la Catalog - MATEMATICA"<<endl;
            cout<<"Alegeti: \n1 - Acorda note \n2 - Vezi statistici despre note \n3 - Iesire"<<endl;
            cout<<"Introduceti optiunea: "; cin>>prof;
            while (prof < "1" || prof > "3" || prof.size() > 1) {
                cout<<"Invalid! Introduceti din nou: "; cin>>prof;
            }
            if(prof == "1") {
                system("cls");
                cout<<"~~ Acordare note ~~\n Iata lista cu studentii care nu au primit nota: "<<endl<<endl;
                RBTree *sts = tree_with_students_ids();
                give_grade("matematica",sts);
            }
            else if(prof == "2") {
                RBTree *grades = tree_with_student_grades("matematica");
                cout<<endl<<"Notele obtinute de studenti sunt: ";
                grades->display(grades->root,0);
                cout<<endl<<"Nota maxima: "<<grades->maximum(grades->root)->key<<endl;
                cout<<"Cea mai mica nota: "<<grades->minimum(grades->root)->key<<endl;
                cout<<"Nu au trecut: "<<grades->countPassed(grades->root)<<" studenti"<<endl;
            }
            else if(prof == "3") {
                sub = "0";
            }
        }
        else if(sub == "3") {
            system("cls");
            cout<<"~Fizica~"<<endl; string p;
            cout<<"Introduceti parola pt disciplina FIZICA: "; cin.ignore(); getline(cin,p);
            while(subject_password("fizica",p) == false) {
                cout<<"Incorect! Introduceti din nou: ";
                getline(cin,p);
            }
            system("cls");
            string prof = "0";
            cout<<u.getName()<<", bine ati venit la Catalog - FIZICA"<<endl;
            cout<<"Alegeti: \n1 - Acorda note \n2 - Vezi statistici despre note \n3 - Iesire"<<endl;
            cout<<"Introduceti optiunea: "; cin>>prof;
            while (prof < "1" || prof > "3" || prof.size() > 1) {
                cout<<"Invalid! Introduceti din nou: "; cin>>prof;
            }
            if(prof == "1") {
                system("cls");
                cout<<"~~ Acordare note ~~\n Iata lista cu studentii care nu au primit nota: "<<endl<<endl;
                RBTree *sts = tree_with_students_ids();
                give_grade("fizica",sts);
            }
            else if(prof == "2") {
                RBTree *grades = tree_with_student_grades("fizica");
                cout<<endl<<"Notele obtinute de studenti sunt: ";
                grades->display(grades->root,0);
                cout<<endl<<"Nota maxima: "<<grades->maximum(grades->root)->key<<endl;
                cout<<"Cea mai mica nota: "<<grades->minimum(grades->root)->key<<endl;
                cout<<"Nu au trecut: "<<grades->countPassed(grades->root)<<" studenti"<<endl;
            }
            else if(prof == "3") {
                sub = "0";
            }
        }
    }

    else if(entry == "2") {
        system("cls");
        cout<<"== STUDENT =="<<endl<<"Conecteaza-te la contul de Student: "<<endl;
        string nume, parola;
        cout<<"Introduceti numele dvs - nume si prenume: "; cin.ignore(); getline(cin,nume);
        cout<<"Introduceti parola: "; getline(cin,parola);
        User u = User("student", nume, parola);
        while(u.loginUser("student",u) == false) {
            cout<<endl<<"INCORECT! "<<endl; system("pause"); system("cls");
            cout<<"== STUDENT =="<<endl<<"Conecteaza-te la contul de Student: "<<endl;
            cout<<"Introduceti numele dvs - nume si prenume: "; cin.ignore(); getline(cin,nume);
            cout<<"Introduceti parola: "; getline(cin,parola);
            User aux = User("student", nume, parola);
            u = aux;
        }
        system("cls");
        cout<<"==STUDENT=="<<endl<<"Bine ai venit STUDENT! "<<u.getId()<<" "<<u.getName()<<endl;
        cout<<"Alege una dintre optiunile: "<<endl<<" 1 - Vezi note "<<endl<<"2 - Iesire"<<endl;
        string opstud = "0"; cout<<"Introdu optiunea: "; cin>>opstud;
        while(opstud < "1" || opstud > "2" || opstud.size() > 1) {
            cout<<"Invalid! Introdu din nou: "; cin>>opstud;
        }
        if(opstud == "1") {
            system("cls");
            cout<<"Notele studentului: "<<u.getName()<<endl;
            student_got_grades(u,"romana");
            student_got_grades(u,"matematica");
            student_got_grades(u,"fizica");
        }
        else {
            cout<<"Bye student!"; system("pause"); system("cls");
        }

    }
    else {
        system("cls"); cout<<"La revedere!"; system("pause"); system("cls");
    }
    return 0;
}
