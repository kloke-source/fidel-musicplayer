#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  string command;
  if (argc <= 2){
    command = argv[1];
  }

  if (command == "about-creator"){
    cout << "\n -------------------------------------- \n" << endl;
    cout << "Fidel was created by: Tashrif Sanil" << endl;
    cout << "\n -------------------------------------- \n" << endl;
  }

  if (command == "font-cache-update"){
    cout << "\n -------------------------------------- \n" << endl;
    cout << "Fidel will now update your font cache" << endl;
    cout << "\n -------------------------------------- \n" << endl;
  }

  if (command == "font-install-notify"){
    cout << "\n -------------------------------------- \n" << endl;
    cout << "Fidel fonts will now be installed" << endl;
    cout << "Note: This is optional but it is recommended" << endl;
    cout << "\n -------------------------------------- \n" << endl;
  }
  return 0;
}
