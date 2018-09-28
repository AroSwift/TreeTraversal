//
// Name: Aaron Barlow
// Date: 3/29/2016
// Description: Traversal program allows user to traverse a tree in various ways.
// When given a file, the following data is read into a tree:
// first_name, last_name, street_address, city, state, zip
// The user is then given a menu that provides pre order traversal,
// In order traversal, post order traversal, breadth first traversal,
// A search for a person, and an exit option. The traversals and
// search for person utlize the tree that was built with the data.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include "traversal.h"
using namespace std;

int main() {
   // Instantiate a new instance of tree with person as the template data
   Tree<Person>* tree = new Tree<Person>;
   string settings;

   // Load the people from file and put it in the tree
   load_people(tree);

   // Show the main menu
   main_menu(tree, settings);

   // Dellocate tree with the tree destructor
   delete tree;

}

//
// load_people
// Get a valid file from the user and then
// Read in the people into the tree.
//
void load_people(Tree<Person>* tree) {
   ifstream input;
   char filename[MAX_FILE_LENGTH];
   bool file_errors;

   do { // Find a file that exists
      file_errors = false;

      // Prompt for file and read it in
      cout << "Enter file name: ";
      cin.getline( filename, MAX_FILE_LENGTH );

      // Attempt to open the given filename
      input.open( filename );

      // When file could not be found
      if( input.fail() ) {
         cout << "Input file " << filename << " does not exist. \n";
         file_errors = true;

         // When file is empty
      } else if( input.peek() == EOF ) {
         cout << "Input file " << filename << " is empty. \n";
         file_errors = true;
      }

   // Continue until we get a valid file
   } while( file_errors );


   // Read in file row by row while there is data to read in
   while( !input.eof() ) {
      string first_name, last_name, street_address, city, state, zip;

      // Remove preceding whitespace with 'ws' if it is present,
      // But do not assume it will be by using getline delimiters
      input >> ws;
      getline( input, first_name, ',' );
      input >> ws;
      getline( input, last_name, ',' );
      input >> ws;
      getline( input, street_address, ',' );
      input >> ws;
      getline( input, city, ',' );
      input >> ws;
      getline( input, state, ',' );
      input >> ws;
      getline( input, zip, '\n' );

      // Instantiate a new person with the data that was read in
      Person *p = new Person(first_name, last_name, street_address, city, state, zip);

      // Then put this data in the tree
      tree->insert(*p, &compare_people);
      
   }

}



//
// main_menu
// Display a menu to the user with the following options:
// pre order traversal, in order traversal, post order traversal,
// breadth first traversal, search for a name, and exit the program.
// Read in the user's choice and then do the appropriate action.
//
void main_menu(Tree<Person>* tree, string settings) {
   bool exit = false;
   char choice;

   // Display a menu
   do {

      // Give user choices
      cout << "Main Menu" << endl
      << "------------------" << endl
      << "1.) Pre-order traversal" << endl
      << "2.) In-order traversal" << endl
      << "3.) Post-order traversal" << endl
      << "4.) Breadth-first traversal" << endl
      << "5.) Search for a name" << endl
      << "6.) Exit" << endl
      << "Choice: ";
      cin >> choice;

      // Associate choice with an action
      switch(choice) {
         case '1': // Pre-order traversal
            cout << endl;
            options_menu(settings); // Determine fields that can be displayed
            pre_order_traversal(tree->get_root(), settings);
            break;

         case '2': // In-order traversal
            cout << endl;
            options_menu(settings); // Determine fields that can be displayed
            in_order_traversal(tree->get_root(), settings);
            break;

         case '3': // Post-order traversal
            cout << endl;
            options_menu(settings); // Determine fields that can be displayed
            post_order_traversal(tree->get_root(), settings);
            break;

         case '4': // Breadth-order traversal
            cout << endl;
            options_menu(settings); // Determine fields that can be displayed
            breadth_first_traversal(tree->get_root(), settings);
            break;

         case '5': // Search for Name
            cout << endl;
            options_menu(settings); // Determine fields that can be displayed
            search_for_person(tree, settings);
            break;

         case '6': // Exit the menu
            exit = true;
            break;

         default: // An error occured
            cout << "Please enter a valid option." << endl;
            cout << endl;
            break;
      }

   // Continue to give the menu until user is done with program
   } while(!exit);
}

//
// options_menu
// When there are no settings, give user the change settings menu.
// When there are settings, ask the user if they would like to utilize
// The previous settings. If they would, give the user the change settings menu,
// Otherwise, allow the user to utilize the previous settings. Continue to ask
// Until a yes or no is provided.
//
void options_menu(string &settings) {
   // When the settings are not set
   if( settings != "" ) {
      bool acceptable_input;
      do { // Continue to ask the user for a response until valid input is given
         char user_choice;
         cout << "Would you like to use your previous settings? (Y, N): ";
         cin >> user_choice;

         // The user wants to use the current settings
         if( user_choice == 'Y' || user_choice == 'y' ) {
            acceptable_input = true;
         // The user wants to change the settings
         } else if( user_choice == 'N' || user_choice == 'n' ) {
            acceptable_input = true;
            change_settings_menu(settings);
         } else { // No appropriate input was given
            cout << "Please enter 'Y' or 'N' to indicate whether you would like to use the prior settings." << endl;
            acceptable_input = false;
         }
      } while( !acceptable_input );
   } else { // There are no previous settings
      // Give user the change settings menu
      change_settings_menu(settings);
   }
}

//
// change_settings_menu
// Display settings menu and allow the user to select
// Which fields they want to be displayed. Allows user to input
// Multiple fields and then sets the settings string to that input.
//
void change_settings_menu(string &settings) {
   string choice;

   // Display the options of fields that the user can select to be displayed
   cout << "Field Selection Menu" << endl
   << "-------------------------" << endl
   << "Please select which fields you would like to be displayed:" << endl
   << "1.) Show first name" << endl
   << "2.) Show last name" << endl
   << "3.) Show street address" << endl
   << "4.) Show city" << endl
   << "5.) Show state" << endl
   << "6.) Show zip" << endl
   << "Choice: ";
   cin >> choice;

   // Set the settings to what the user wants to use
   settings = choice;
   
   cout << endl;

}

//
// search
// Call the private method search
// and set the base case to root
// and pass the passed paramaters.
//
void search(Tree<Person>* tree, Person p, string settings) {
   // Search for the person and set the search_person to what is returned
   Person *person_searched = tree->search( tree->get_root(), p, &compare_equality, 1 );
   
   // User was not found
   if(person_searched == NULL) {
      // Inform user no person was found
      cout << "The person could not be found." << endl << endl;
   } else { // User was found
      // Print the user that was found with the fields the user wants
      print_data(*person_searched, settings);
   }
}

//
// search_for_person
// Prompt the user to enter the first name
// And last name of ther person they are searching for.
// After getting input, searching for the person.
//
void search_for_person(Tree<Person>* tree, string settings) {
   string first_name, last_name;

   cout << "Find a Person:" << endl
   << "-------------------" << endl;

   // Prompt user for first name
   cout << "Enter the first name: ";
   cin >> first_name;

   // Prompt user for last name
   cout << "Enter the last name: ";
   cin >> last_name;

   // Instantiate a new instance of person
   Person *search_person = new Person( first_name, last_name );
   
   // Then search for the person and show the fields that the user wants to see
   search(tree, *search_person, settings);
   
}

//
// lower_case
// Lowercases all characters in a given string.
// Returns the lowercased string.
//
string lower_case( string value ) {
   // Lowercase each character in a given string
   for( int i = 0; i < strlen( value.c_str() ); i++ ) {
      value[i] = tolower( value[i] );
   }

   return value; // As a lowercased string
}

//
// print_data
// Print out the fields that the user has
// Indicated that they want to view.
//
void print_data(Person p, string settings) {
   // For each setting determine if field should be displayed
   if( settings.find('1') != string::npos) cout << "First Name: " << p.first_name << endl;
   if( settings.find('2') != string::npos) cout << "Last Name: " << p.last_name << endl;
   if( settings.find('3') != string::npos) cout << "Street Address: " << p.street_address << endl;
   if( settings.find('4') != string::npos) cout << "City: " << p.city << endl;
   if( settings.find('5') != string::npos) cout << "State: " << p.state << endl;
   if( settings.find('6') != string::npos) cout << "Zip: " << p.zip << endl;

   // Add sufficent spacing between records
   if(settings != "") cout << endl;
}


//
// pre_order_traversal
// Traverse the tree starting at root and
// Then go to the left side and then right
// The result is the data is printed in order.
//
void pre_order_traversal( Tree<Person>* node, string settings ) {
   // Ensure node exists
   if( node == NULL ) return;

   // Print the node's data with the fields that the user wants to view
   print_data(node->get_data(), settings);

   // Recursively go to left side of tree
   if( node->get_left() != NULL ) pre_order_traversal(node->get_left(), settings);

   // Recursively go to right side of tree
   if( node->get_right() != NULL ) pre_order_traversal(node->get_right(), settings);
}

//
// in_order_traversal
// Traverse the tree on the left side
// Then go to the root then the right side.
// The result is the data is printed in order.
//
void in_order_traversal( Tree<Person>* node, string settings ) {
   // Ensure that node exists
   if( node == NULL ) return;

   // Recursively go to left side of tree
   if( node->get_left() != NULL ) in_order_traversal(node->get_left(), settings);

   // Print the node's data with the fields that the user wants to view
   print_data(node->get_data(), settings);

   // Recursively go to right side of tree
   if( node->get_right() != NULL ) in_order_traversal(node->get_right(), settings);
}

//
// post_order_traversal
// Traverse the tree starting at root
// Then go to the left side then the right side.
//
void post_order_traversal( Tree<Person>* node, string settings ) {
   // Ensure that node exists
   if( node == NULL ) return;

   // Recursively go to left side of tree
   if( node->get_left() != NULL ) post_order_traversal(node->get_left(), settings);

   // Recursively go to right side of tree
   if( node->get_right() != NULL ) post_order_traversal(node->get_right(), settings);

   // Print the node's data with the fields that the user wants to view
   print_data(node->get_data(), settings);
}

//
// breadth_first_traversal
// Traverse the tree starting at root
// Then go to the left side then the right side.
//
void breadth_first_traversal( Tree<Person>* node, string settings ) {
//    Ensure root node exists
   if (node->get_root() == NULL)  return;

   // Create an empty queue
   queue<Tree <Person> > q;

   // Enqueue root
   q.push(*node->get_root());

   // Continue to go through each node while queue is not empty
   while ( !q.empty() ) {
      // Get and print front of queue
      Tree<Person> node = q.front();
      print_data(node.get_data(), settings);

      q.pop(); // Remove the node from the queue

      // Enqueue left node
      if (node.get_left() != NULL) q.push(*node.get_left());

      // Enqueue right node
      if (node.get_right() != NULL) q.push(*node.get_right());
   }
}

