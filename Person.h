#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

class Person {
public:
    string name;
    int age;
    int height;
    string NIC;
    char gender;
    bool was_married;
    bool is_graduated;
    string race;
    int score;

    Person(){

    }

    Person(const string &name, int age, int height, const string &nic, char gender, bool wasMarried, bool isGraduated,
           const string &race) : name(name), age(age), height(height), NIC(nic), gender(gender),
                                 was_married(wasMarried), is_graduated(isGraduated), race(race) {}

};
