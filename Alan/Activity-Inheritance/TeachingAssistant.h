
#ifndef TEACHINGASSISTANT_H_
#define TEACHINGASSISTANT_H_

#include <string>
#include "Student.h"

class TeachingAssistant : public Student{
    private:
        std::string course;
    
    public:
        TeachingAssistant(float _gpa, std::string name, std::string _course);
        virtual std::string getCourse();
        void Print();
};

#endif