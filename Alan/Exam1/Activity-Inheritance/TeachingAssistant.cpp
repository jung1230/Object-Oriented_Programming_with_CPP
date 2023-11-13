#include <string>
#include <iostream>

#include "TeachingAssistant.h"

TeachingAssistant::TeachingAssistant(float _gpa, std::string name, std::string _course):Student(_gpa, name){
    course = _course;
}
std::string TeachingAssistant::getCourse(){
    return course;
}
void TeachingAssistant::Print(){

   std::cout << this -> getName() << " "  << getGPA() << " "  <<course << std::endl;

}