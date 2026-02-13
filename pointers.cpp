// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    //the user can have up to 9 digits so we want to make sure that we can hold the max amount here
    student.id = promptInt("Please enter the student's id number: ", 1, 1000000000);
    //we need something to have the pointer, point to in memory.
    student.f_name = new char[128];
    student.l_name = new char[128];


    std::cout<<"Please enter the student's first name: ";
    std::cin>>student.f_name;

    std::cout<<"Please enter the student's last name: ";
    std::cin>>student.l_name;

    std::cin.ignore(1000,'\n');


    //Prompt them for an int for the number of assignments
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);
    std::cout << std::endl;
    //reference class example, create an array with the input of the number assignments and then for each
    student.grades = new double[student.n_assignments];
    for (int i = 0; i < student.n_assignments; i++) {
        student.grades[i] = promptDouble("Please enter grade for assignment "+std::to_string(i)+": ",0,1000.0);
    }
    std::cout << std::endl;
    // Call `CalculateStudentAverage(???, ???)`
    calculateStudentAverage(&student,&average);
    // Output `average`
    std::cout<<"Student: " << student.f_name << " "<<student.l_name << " ["<<student.id<<"]"<< std::endl ;
    //using fixed and set precision we only allow for one decimal place
    std::cout<<"  " <<"Average grade: "<<std::fixed<<std::setprecision(1)<<average<<std::endl;

    delete [] student.grades;
    delete [] student.f_name;
    delete [] student.l_name;
    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    std::string errorMessage = "Sorry, I cannot understand your answer\n";

    while(true) {
        char userInput[128];
        std::cout << message;

        std::cin.getline(userInput, 128);
        int length = std::strlen(userInput);

        if (length == 0) {
            std::cout << errorMessage;
            continue;
        }

        bool validInt = true;
        for(int i = 0; i < length; i++) {
            if (!isdigit(userInput[i])) {
                validInt = false;
                break;
            }
        }

        if (!validInt) {
            std::cout << errorMessage;
            continue;
        }

        int integerInput = std::atoi(userInput);

        if (integerInput < min || integerInput > max) {
            std::cout << errorMessage;
            continue;
        }

        return integerInput;
    }
}


/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    std::string errorMessage = "Sorry, I cannot understand your answer\n";

        while(true) {
            char userInput[128];
            std::cout << message;
            std::cin.getline(userInput, 128);

            int length = std::strlen(userInput);

            if (length == 0) {
                std::cout << errorMessage;
                continue;
            }

            bool validDouble = true;
            int decimals = 0;

            for (int i = 0; i < length; i++) {
                if (isdigit(userInput[i])) {
                    continue;
                } else if (userInput[i] == '.') {
                    decimals++;
                    if (decimals > 1) {
                        validDouble = false;
                        break;
                    }
                } else {
                    validDouble = false;
                    break;
                }
            }
            //cant put a . in the first index, not valid
            if (length == 1 && userInput[0] == '.') {
                validDouble = false;
            }
            if (!validDouble) {
                std::cout << errorMessage;
                continue;
            }

            double doubleInput = std::atof(userInput);

            if (doubleInput < min || doubleInput > max) {
                std::cout << errorMessage;
                continue;
            }

            return doubleInput;
        }
    }

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    Student *student = (Student *)object;
    double sum = 0.0;
    for (int i = 0; i < student->n_assignments; i++) {
        sum = sum + student->grades[i];
    }
    *avg = sum / student->n_assignments;
}