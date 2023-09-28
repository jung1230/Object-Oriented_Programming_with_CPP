#include <string>
#include "TeachingAssistant.h"

TeachingAssistant::TeachingAssistant(std::string _course):Student(){
    course = _course;
}
std::string TeachingAssistant::getCourse(){
    return course;
}