#include <iostream>
#include <stdlib.h>

#include <mysql/jdbc.h>

using namespace std;

class Database {
public:
    Database(const string& host, const string& username, const string& password, const string& schema);
    ~Database();
    void connect();
    void disconnect();
    void executeQuery(const std::string& query);

private:
    string host_;
    string username_;
    string password_;
    string schema_;
    sql::Driver* driver_;
    sql::Connection* connection_;
};

Database::Database(const string& host, const string& username, const string& password, const string& schema)
    : host_(host), username_(username), password_(password), schema_(schema), driver_(nullptr), connection_(nullptr) {}

Database::~Database() {
    disconnect();
}

void Database::connect() {
    try {
        driver_ = get_driver_instance();
        connection_ = driver_->connect("tcp://" + host_ + ":3306", username_, password_);
        connection_->setSchema(schema_);
    }
    catch (const sql::SQLException& e) {
        cout << "Connecting ERR: " << e.what() << endl;
    }
}

void Database::disconnect() {
    if (connection_) {
        delete connection_;
        connection_ = nullptr;
    }
    driver_ = nullptr;
}

void Database::executeQuery(const std::string& query) {
    if (!connection_) {
        cout << "Connecting inside executeQuery " << endl;
        return;
    }
    try {
        sql::Statement* stmt = connection_->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            cout << "ID: " << res->getInt("id") << endl;
            cout << "Campus Name: " << res->getString("campus_name") << endl;
            cout << "Address: " << res->getString("address") << endl;
            cout << "City: " << res->getString("city") << endl;
            cout << "State: " << res->getString("state") << endl;
            cout << "Country: " << res->getString("country") << endl;
            cout << "Postal Code: " << res->getString("postal_code") << endl;
            cout << "Latitude: " << res->getDouble("latitude") << endl;
            cout << "Longitude: " << res->getDouble("longitude") << endl;
            cout << "Description: " << res->getString("description") << endl;
            cout << "Established Date: " << res->getString("established_date") << endl;
            cout << endl;
        }
        delete res;
        delete stmt;
    }
    catch (const sql::SQLException& e) {
        cout << "Handling Query ERR: " << e.what() << endl;
    }
}

int main() {
    Database Huda("127.0.0.1", "root", "huda", "studentmarket");
    Huda.connect();
    Huda.executeQuery("SELECT * FROM campuses");
    Huda.disconnect();
    return 0;
}



