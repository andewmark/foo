#include <stdlib.h>
#include <iostream>


#include <mysql/jdbc.h>


using namespace sql;
int main(void){
  sql::Driver *driver;
  sql::Connection *con;

  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306","root","password");
  
  return 0;
}