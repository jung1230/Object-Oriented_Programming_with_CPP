
#ifndef TEACHINGASSISTANT_H_
#define TEACHINGASSISTANT_H_

#include <string>
#include "Student.h"

class TeachingAssistant : public Student{
    private:
        std::string course;
    
    public:
        TeachingAssistant(std::string _course);
        virtual std::string getCourse();
};

#endif