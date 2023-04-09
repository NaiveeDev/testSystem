#include "imports.h"
#include "Auth.h"
#include "User.h"
#include "Application.h"
#include "md5.h"




int main(int argc, char* argv[]) {
   
    setlocale(LC_ALL, "ru");

      
    Application app;
    User Person;
    //app.run();
    
    Test Test;
    Test.TestMenu(Person);

}

