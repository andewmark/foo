#include <stdlib.h>
#include <iostream>


#include <mysql/jdbc.h>


// using namespace sql;
using namespace std;



// Parent Class
class Database {
public:

// Initialize Database
    Database(const string& host, const string& username, const string& password, const string& schema);
    ~Database(); //Deconstructor

    void connect(); // child class to connect
    void disconnect();// child class to disconnect
    void executeQuery(const std::string& query); //like SELECT/INSERT/Mesages
    // Other methods for database interactions

private: //using Encapsulation
    string host_;
    string username_;
    string password_;
    string schema_;
    sql::Driver* driver_;
    sql::Connection* connection_;
    // Other private members and methods as needed
};

// Initializer
Database::Database(const string& host, const string& username, const string& password, const string& schema)
    : host_(host), username_(username), password_(password), schema_(schema), driver_(nullptr), connection_(nullptr) {}


// Destructor
Database::~Database() {
    disconnect(); 
}

// Child class derived from main class., Inherites private varibales
void Database::connect() {   
    try {
        driver_ = get_driver_instance();
        connection_ = driver_->connect("tcp://" + host_ + ":3306", username_, password_);
        connection_->setSchema(schema_);
    } catch (const sql::SQLException& e) {
        cout << "Connecting ERR: " << e.what()<<endl;
    }
}


// IDEAS
// inherited class with establish tables
// Update polymorphism

// Deleting Connection!!!!
void Database::disconnect() {
    if (connection_) {
        delete connection_; // delete the connection driver ptr
        connection_ = nullptr;
    }
    driver_ = nullptr;
}

// To excute Queries
void Database::executeQuery(const std::string& query) {
    if (!connection_) {
        // Handle connection error
        cout << "Connecting inside executeQuery " << endl;
        return;
    }
    try {
        sql::Statement* stmt = connection_->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        // Process the result set
        delete res;
        delete stmt;
    } catch (const sql::SQLException& e) {
        cout << "Handling Query ERR: " << e.what()<<endl;
    }
}

int main() {

  // Creating my first object 
    Database Huda("127.0.0.1", "root", "password", "studentmarket");
    Huda.connect();
    Huda.executeQuery("SELECT 'Hello World!' AS _message");
    Huda.disconnect();
    return 0;
}


