#include<iostream>
using namespace std;

class User{
protected:
 int id;
 string name;

public:
User(int i,string n){
    id = i;
    name = n;
}

virtual void display()=0; 

};

class Student:public User{
public:
Student(int i,string n):User(i,n){}

void display(){
    cout<<"Student ID: "<<id<<endl;
    cout<<"Student Name: "<<name<<endl;
}


    void enroll(string course) {
        FILE *fp = fopen("enroll.txt", "a");

        if (fp == NULL) {
            cout << "File Error!\n";
            return;
        }

        fprintf(fp, "%d %s %s\n", id, name.c_str(), course.c_str());
        fclose(fp);

        cout << "Enrolled successfully!\n";
    }

};

class Teacher:public User{
    public:
    Teacher(int i,string n):User(i,n){}

    void display(){
        cout<<"Teacher ID: "<<id<<endl;
        cout<<"Teacher Name: "<<name<<endl;
    }

    void assignCourse(string course){
        cout<<name<<" has been assigned to teach "<<course<<endl;
    }   
};


class Course {
private:
    string courseName;

public:
    // Constructor
    Course(string name) {
        courseName = name;
    }

    // Add Course
    void addCourse() {
        FILE *fp = fopen("course.txt", "a");

        if (fp == NULL) {
            cout << "File Error!\n";
            return;
        }

        fprintf(fp, "%s\n", courseName.c_str());
        fclose(fp);

        cout << "Course Added: " << courseName << endl;
    }

    // View Courses
    static void viewCourses() {
        FILE *fp = fopen("course.txt", "r");
        char course[100];

        if (fp == NULL) {
            cout << "No courses found\n";
            return;
        }

        cout << "\nCourses:\n";
        while (fgets(course, sizeof(course), fp)) {
            cout << course;
        }

        fclose(fp);
    }
};

class Enrollment {
public:
    static void viewEnrollments() {
        FILE *fp = fopen("enroll.txt", "r");
        char data[100];

        if (fp == NULL) {
            cout << "No enrollments found\n";
            return;
        }

        cout << "\nEnrollments:\n";
        while (fgets(data, sizeof(data), fp)) {
            cout << data;
        }

        fclose(fp);
    }
};

class Assignment {
public:

    // Student submits assignment
    static void submitAssignment(int id, string name, string course, string content) {
        FILE *fp = fopen("assign.txt", "a");

        if (fp == NULL) {
            cout << "File Error!\n";
            return;
        }

        // Marks initially 0
        fprintf(fp, "%d %s %s %s %d\n", id, name.c_str(), course.c_str(), content.c_str(), 0);
        fclose(fp);

        cout << "Assignment submitted!\n";
    }

    // Teacher gives marks
    static void evaluateAssignment(int sid, int marks) {
        FILE *fp = fopen("assign.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (fp == NULL || temp == NULL) {
            cout << "File Error!\n";
            return;
        }

        int id, m;
        char name[50], course[50], content[50];

        while (fscanf(fp, "%d %s %s %s %d", &id, name, course, content, &m) != EOF) {
            if (id == sid) {
                m = marks; // update marks
            }
            fprintf(temp, "%d %s %s %s %d\n", id, name, course, content, m);
        }

        fclose(fp);
        fclose(temp);

        remove("assign.txt");
        rename("temp.txt", "assign.txt");

        cout << "Marks updated!\n";
    }

    // View assignments
    static void viewAssignments() {
        FILE *fp = fopen("assign.txt", "r");

        if (fp == NULL) {
            cout << "No assignments found\n";
            return;
        }

        int id, marks;
        char name[50], course[50], content[50];

        cout << "\nAssignments:\n";
        while (fscanf(fp, "%d %s %s %s %d", &id, name, course, content, &marks) != EOF) {
            cout << "ID: " << id 
                 << " Name: " << name 
                 << " Course: " << course 
                 << " Work: " << content 
                 << " Marks: " << marks << endl;
        }

        fclose(fp);
    }
};


int main() {
    int choice;

    do {
        cout << "\n===== LMS MENU =====\n";
        cout << "1. Student\n";
        cout << "2. Instructor\n";
        cout << "3. View Courses\n";
        cout << "4. View Enrollments\n";
        cout << "5. View Assignments\n";
        cout << "6. Exit\n";  
        cout << "Enter choice: ";
        cin >> choice;

        try {
            // ----- STUDENT -----
            if (choice == 1) {
                int id;
                string name, course;

                cout << "Enter ID: ";
                cin >> id;
                if (id <= 0) throw "Invalid ID";

                cout << "Enter Name: ";
                cin >> name;

                Student s(id, name); // Object
                s.display();

               

                int opt;
cout << "\n1. Enroll Course\n2. Submit Assignment\nChoice: ";
cin >> opt;

if (opt == 1) {
    cout << "Enter Course: ";
    cin.ignore();
    getline(cin, course);
    s.enroll(course);
}
else if (opt == 2) {
    string content;
    cout << "Enter Course: ";
    cin >> course;

    cout << "Enter Assignment Content: ";
    cin >> content;

    Assignment::submitAssignment(id, name, course, content);
}
            }

            // ----- TEACHER -----
            else if (choice == 2) {
                int id;
                string name, course;

                cout << "Enter ID: ";
                cin >> id;
                if (id <= 0) throw "Invalid ID";

                cout << "Enter Name: ";
                cin >> name;

                Teacher i(id, name); // Object
                i.display();

                cout << "Enter Course to Add: ";
                cin >> course;

                Course c(course); // Object (Course Module)
                c.addCourse();

                int opt;
cout << "\n1. Add Course\n2. Evaluate Assignment\nChoice: ";
cin >> opt;

if (opt == 1) {
    cout << "Enter Course to Add: ";
    cin >> course;

    Course c(course);
    c.addCourse();
}
else if (opt == 2) {
    int sid, marks;
    cout << "Enter Student ID: ";
    cin >> sid;

    cout << "Enter Marks: ";
    cin >> marks;

    Assignment::evaluateAssignment(sid, marks);
}
            }

            // ----- VIEW COURSES -----
            else if (choice == 3) {
                Course::viewCourses();
            }

            // ----- VIEW ENROLLMENTS -----
            else if (choice == 4) {
                Enrollment::viewEnrollments();
            }

            else if (choice == 5) {
    Assignment::viewAssignments();
}

else if (choice == 6) {
     cout << "Exiting...\n"; }

            else {
                throw "Invalid Choice";
            }
        }

        catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }

    } while (choice != 6);

    return 0;
}