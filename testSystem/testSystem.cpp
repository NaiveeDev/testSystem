#include "imports.h"
#include "Auth.h"
#include "User.h"



int main(int argc, char* argv[]) {
    
    
    setlocale(LC_ALL, "ru");
    
    User Person;
    Auth auth;

    //auth.Register(Person);
    auth.Login(Person);

}