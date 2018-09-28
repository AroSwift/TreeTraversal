//
// Name: Aaron Barlow
// Date: 3/29/2016
// Description: Header file that encapsulates the person class
// as well as the traversal and person prototypes.
//

#pragma once
#include <string>
#include "tree.h"
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255

class Person {
public:
   Person() {}; // Constructor
   Person(string first_name, string last_name); // Constructor
   Person( string first_name, string last_name, string street_address, string city, string state, string zip );
   void print_person_data();
   void search_for_person();
   friend bool compare_people(Person p1, Person p2);
   friend bool compare_equality(Person p1, Person p2);
   friend void print_data(Person p, string settings);
private:
   string first_name;
   string last_name;
   string street_address;
   string city;
   string state;
   string zip;
};


//
// Person constructor
// Constructor for first_name, last name, street address, city, state, and zip.
//
Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {
   this->first_name = first_name;
   this->last_name = last_name;
   this->street_address = street_address;
   this->city = city;
   this->state = state;
   this->zip = zip;
}

//
// Person constructor
// Constructor for only first name and last name.
//
Person::Person(string first_name, string last_name) {
   this->first_name = first_name;
   this->last_name = last_name;
}


/* Prototypes */


void load_people(Tree<Person>* tree);
string lower_case( string value );

// Search functions
void search_for_person(Tree<Person>* tree, string settings);
void search(Tree<Person>* tree, Person p, string settings);

// Menu functions
void main_menu(Tree<Person>* tree, string settings);
void options_menu(string &settings);
void change_settings_menu(string &settings);

// Traversal functions
void pre_order_traversal( Tree<Person>* node, string settings );
void in_order_traversal( Tree<Person>* tree, string settings );
void post_order_traversal( Tree<Person>* tree, string settings );
void breadth_first_traversal( Tree<Person>* node, string settings );


/* Class friends for comparising people */

//
// compare_people
// Given two person objects, see which person's
// last name then first name is larger.
// Return true if the person p1 is higher alphebetically
// by last name and first name and false if otherwise.
//
bool compare_people(Person p1, Person p2) {
   return( (p2.last_name < p1.last_name) || ((p2.last_name == p1.last_name) && (p2.first_name < p1.first_name)) );
}

//
// compare_people
// Given two person objects, compare person's
// Lowercased version of first name and last name.
//
bool compare_equality(Person p1, Person p2) {
   string p1_first_name = lower_case(p1.first_name), p2_first_name = lower_case(p2.first_name);
   string p1_last_name = lower_case(p1.last_name), p2_last_name = lower_case(p2.last_name);
   return p1_first_name == p2_first_name && p1_last_name == p2_last_name;
}

