#include "imports.h"
#include "Auth//Auth.h"
#include "User//User.h"



int main(int argc, char* argv[]) {
    
    setlocale(LC_ALL, "ru");
    
    User Person;
    Auth auth;

    //auth.Register(Person);
    auth.Аuth(Person);

}