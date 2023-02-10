#include <iostream>
#include <vector>
#include <unordered_map>
#include "LikedList.h"
#include "Person.h"

using namespace std;

bool compareScores(const Person& a, const Person& b) {
    return a.score > b.score;
}

LinkedList<Person> getRecommendations(unordered_map<string,Person>& people, Person targetPerson) {
    LinkedList<Person> result;
    for (auto personPair : people) {
        Person person = personPair.second;
        if (person.gender == targetPerson.gender) {
            continue;
        }
        // For sorting purpose we use scoring system
        int score = 0;
        if (targetPerson.gender == 'M') {
            // consider height for male-user ( prefer female_height <= male_height  )
            if (person.height <= targetPerson.height) {
                score += 5;
            }
            // consider age for male-user ( prefer female_age <= male_height )
            if (person.age <= targetPerson.age) {
                score += 5;
            }
        } else {
            // consider height for female-user ( prefer male_height > female_height )
            if (person.height > targetPerson.height) {
                score += 5;
            }
            // consider age for female-user ( prefer male_age > female_age )
            if (person.age > targetPerson.age) {
                score += 5;
            }
        }

        // consider race (prefer same race)
        // only check for first letter b'cuz avoiding user's typo errors
        if (person.race[0] == targetPerson.race[0]) {
            score += 5;
        }
        // consider marital status (prefer same status)
        if (person.was_married == targetPerson.was_married) {
            score += 5;
        }
        // consider educational status (prefer same status)
        if (person.is_graduated == targetPerson.is_graduated) {
            score += 5;
        }

        person.score = score;
        result.push_back(person);
    }

    result.sort(compareScores);

    return result;
}

int main() {

    unordered_map<string, Person> people;

    vector<Person> peeps = {
            {"Nayumi", 28, 170, "NIC1", 'F', false,true, "sinhalese"},
            {"Kamal ", 32, 180, "NIC2", 'M', true,false, "sinhalese"},
            {"Saduni", 35, 185, "NIC3", 'F', false,true, "sinhalese"},
            {"Sunil ", 25, 165,  "NI44", 'M', false,true, "tamil"},
            {"Amali ", 30, 160,"NIC5", 'F', true,false, "sinhalese"},
            {"Saman ", 40, 190, "NIC6", 'M', false,true, "muslim"},
            {"Naduni", 26, 175, "NIC7", 'F', false,true, "tamil"},
            {"Kanil ", 36, 182, "NIC8", 'M', false,false, "sinhalese"},
            {"Amadi ", 27, 168,  "NIC9", 'F', true,true, "muslim"},
            {"Pasan ", 33, 186,"NIC11", 'M', false,true, "sinhalese"},
            {"Samadi", 30, 175,"NIC12", 'F', false,true, "sinhalese"},
            {"Sahan ", 25, 165, "NIC13", 'M', true,true, "muslim"},
            {"Manari", 35, 185, "NIC14", 'F', false,false, "sinhalese"},
            {"Nimal ", 20, 155, "NIC15", 'M', false,true, "tamil"},
            {"Nuravi", 40, 190, "NIC16", 'F', true,true, "sinhalese"},
    };
    for(auto e:peeps) people[e.NIC]=e;

    while(1){
        cout<<"---------MATRIMONY MATCH MAKING APP-----------\n";

        Person targetPerson;
        cout<<"-> Enter Your Name:\n";cin>>targetPerson.name;

        cout<<"-> Enter Your Age:\n";cin>>targetPerson.age;
        targetPerson.age = 25;

        cout<<"-> Enter Your Height in cm (eg:180):\n";cin>>targetPerson.height;

        cout<<"-> Enter Your NIC (eg:NIC_XX):\n";cin>>targetPerson.NIC;

        cout<<"-> Enter Your Gender(Male/Female):\n";string gen;cin>>gen;
        targetPerson.gender = (toupper(gen[0])=='M') ? 'M':'F';

        cout<<"-> Were you married(Yes/No):\n";string married;cin>>married;
        targetPerson.was_married = toupper(married[0]) == 'Y';

        cout<<"-> Are you graduated(Yes/No):\n";string graduated;cin>>graduated;
        targetPerson.is_graduated = toupper(graduated[0]) == 'Y';

        cout<<"-> Enter Your Race(sinhalese/tamil/muslim):\n";cin>>targetPerson.race;


        // Get best 3 matching for targetPerson
        LinkedList<Person> result = getRecommendations(people, targetPerson);

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ You ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "-> "<<targetPerson.name;
        cout<<"\tAge:"<<targetPerson.age;
        cout<<"\tHeight:"<<targetPerson.height;
        cout<<"\tWas married:"<<targetPerson.was_married;
        cout<<"\tIs graduated:"<<targetPerson.is_graduated;
        cout<<"\tRace:"<<targetPerson.race;
        cout<<"\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Best matches for " << targetPerson.name << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        for(auto personNode=result.head;personNode!= nullptr;personNode=personNode->next){
            cout << "-> "<<personNode->data.name;
            cout<<"\tAge:"<<personNode->data.age;
            cout<<"\tHeight:"<<personNode->data.height;
            cout<<"\tWas married:"<<personNode->data.was_married;
            cout<<"\tIs graduated:"<<personNode->data.is_graduated;
            cout<<"\tRace:"<<personNode->data.race;
            cout<<"\n";
        }

        // inserting target person to hashtable for use of making matches for future users
        people[targetPerson.NIC] = targetPerson;

        cout<<"Press 'Q' to exit, press any other key to continue :-)\n";
        string c;cin>>c;
        if(toupper(c[0])=='Q') break;
    }

    cout<<"Thanks for using our Matrimony match making app!. Hope you found your life partner ;-)\n";


    return 0;
}


