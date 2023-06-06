// 12S22012 - Reinhard Batubara
// 12S22001 - Winfrey Nainggolan

#include "academic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *grade_to_text(enum grade_t _grade) 
{ 
    if( _grade == 0) return "None" ;
    else if(_grade == 1) return "T" ;
    else if(_grade == 2) return "E";
    else if(_grade == 3) return "D" ;
    else if(_grade == 4) return "C";
    else if(_grade == 5) return "BC";
    else if(_grade == 6) return "B" ;
    else if(_grade == 7) return "AB" ;
    else if(_grade == 8) return "A" ;
    else return "None";
    
    return NULL; 
}

float calculate_performance(enum grade_t _grade, unsigned short _credit)
{
    if(_grade == 1) return 0.0;
    else if(_grade == 2) return _credit * 0.0;
    else if(_grade == 3) return _credit * 1.0;
    else if(_grade == 4) return _credit * 2.0;
    else if(_grade == 5) return _credit * 2.5;
    else if(_grade == 6) return _credit * 3.0;
    else if(_grade == 7) return _credit * 3.5;
    else if(_grade == 8) return _credit * 4.0;

    return 0.0;
}

void print_course(struct course_t _course) 
{   
    printf("%s|%s|%d|%s\n", _course.code, _course.name, _course.credit, grade_to_text(_course.passing_grade));
}

void print_student(struct student_t _student) 
{
    printf("%s|%s|%s|%s|%.2f\n", _student.id, _student.name, _student.year, _student.study_program, _student.gpa);
}

void print_enrollment(struct enrollment_t _enrollment) 
{
    printf("%s|%s|%s|%.2f\n", _enrollment.course.code, _enrollment.student.id,grade_to_text(_enrollment.grade), calculate_performance(_enrollment.grade,_enrollment.course.credit));
}

void print_enrollments(struct enrollment_t *_enrollments,unsigned short int _enrollment_size) 
{
    for (int i = 0; i < _enrollment_size; i++)
    {
    print_enrollment(_enrollments[i]);
    }
}

struct course_t create_course(char *_code, char *_name, unsigned short _credit,enum grade_t _passing_grade)
{
    struct course_t crs;
    strcpy(crs.code, _code);
    strcpy (crs.name, _name);
    crs.credit = _credit;
    crs.passing_grade = _passing_grade;
    return crs;
}

struct student_t create_student(char *_id, char *_name, char *_year,char *_study_program)
{
    struct student_t std;
    strcpy(std.id, _id);
    strcpy(std.name,_name);
    strcpy(std.year, _year);
    strcpy(std.study_program, _study_program);
    std.gpa = 0.00;
    return std;
}

struct enrollment_t create_enrollment(struct course_t _course,struct student_t _student, char *_year,enum semester_t _semester)
{
    struct enrollment_t emt;
    emt.course = _course;
    emt.student = _student;
    strcpy(emt.year,_year);
    emt.semester = _semester;
    return emt;
}

void calculate_gpa(struct student_t *_student, struct enrollment_t *_enrollments,unsigned short int _enrollment_size)
{
    unsigned int sum, sks;
    float hasil;
    sum = sks = 0;
    for ( int i = 0 ; i< _enrollment_size;i++){
    hasil = hasil + calculate_performance(_enrollments[i].grade, _enrollments[i].course.credit);
    sks = sks + _enrollments[i].course.credit;
    }
    hasil = hasil / sks;
    for(int i = 0; i<_enrollment_size;i++){
        if(strcmp(_enrollments[i].student.id, _student->id) == 0 )
        _student->gpa = hasil;
    }  
}

void set_enrollment_grade(struct course_t _course, struct student_t _student, struct enrollment_t *_enrollments, unsigned short int _enrollment_size, enum grade_t _grade)
{
    for(int i = 0; i < _enrollment_size;i++){
        if (strcmp( _enrollments[i].course.code, _course.code) == 0 && strcmp( _enrollments[i].student.name, _student.name) == 0 )
        {
        _enrollments[i].grade = _grade;
        }
    }
}