#include "imports.h"
#include "Auth.h"
#include "User.h"
#include "md5.h"




int main(int argc, char* argv[]) {
    
    //Task
    //1. Проверка на пустое поле при регистрации
    //2. Application Run
    //3. Администратора
   

    User Person;
    Auth auth;

    auth.AuthMenu(Person);

    //auth.Register(Person);
    //auth.Login(Person);

}

