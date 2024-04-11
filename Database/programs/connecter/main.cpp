#include <iostream>
#include <stdlib.h>

#include <mysql/jdbc.h>

using namespace std;


class Database {
public:
// Initilaizer...
    Database(const string& host, const string& username, const string& password, const string& schema);
//    To get rid of Strucrture..
    ~Database(); 

    // methods to retrieve the values of member variables
    string getHost() const { return host_; }
    string getUsername() const { return username_; }
    string getPassword() const { return password_; }
    string getSchema() const { return schema_; }

    void connect();
    void disconnect();
    void executeQuery(const std::string& query);
    virtual void updateQuery(const std::string& query);

private:
    string host_;
    string username_;
    string password_;
    string schema_; //database name
    sql::Driver* driver_;
protected:
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

void Database:: executeQuery(const string& query) {
    if (!connection_) {
        cout << "Connecting inside executeQuery " << endl;
        return;
    }
    try {
        sql::Statement* stmt = connection_->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        // First need to the number of columns in the result set
        int numColumns = res->getMetaData()->getColumnCount();

        // Iterate over the result set and print each row's data
        while (res->next()) {
            for (int i = 1; i <= numColumns; ++i) {
                // Print the value of each column in the current row
                cout << res->getString(i) << "\t";
            }
            cout << endl; // Move to the next line for the next row
        }

        delete res;
        delete stmt;
    }
    catch (const sql::SQLException& e) {
        cout << "Handling Query ERR: " << e.what() << endl;
    }
}


void Database::updateQuery(const string& query) {
    
        
        if (!connection_) {
        cout << "Failure Connecting inside UpdateQuery " << endl;
            return;
        }
        try {
            sql::Statement* stmt = connection_->createStatement();
            int affectedRows = stmt->executeUpdate(query);
            cout << "Number of rows affected: " << affectedRows << endl;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            cout << "Handling Update Query ERR: " << e.what() << endl;
        }
    
}

// Derived Class!
class ViewQuery: public Database{
public:
    ViewQuery(const string& host, const string& username, const string& password, const string& schema, const string& createViewQuery, const string& viewName)
        : Database(host, username, password, schema), viewCreated_(false), viewName_(viewName){
             // Connect to the database
        connect();

        try{
            sql::Statement* stmt = connection_->createStatement();
            // need to use execute update for VIEW
            bool success = stmt->execute(createViewQuery);
            if (success) {
                cout << "View created successfully!!!!" << endl;
                viewCreated_ = true;
            } else {
                cout << "View creation failed" << endl;
            }
            delete stmt;

        }

        catch(const sql::SQLException& e) {
            cout << "Error creating view: " << e.what() << endl;
            if (string(e.what()).find("already exists") != string::npos) {
                viewCreated_ = true;
    }
        }

        disconnect();

        }

        void printView();
        void updateQuery(const std::string& query) override;


        private:
            bool viewCreated_;
            string viewName_;
};



void ViewQuery:: printView(){
            connect();
            if (!viewCreated_) {
                cout << "Unknown view, it hasn,t been created." << endl;
                return;
        }
            executeQuery("SELECT * FROM " + viewName_);
            disconnect();

};

void ViewQuery::updateQuery(const string& query) {
    connect();
    if (!connection_) {
        cout << "Connecting inside UpdateQuery " << endl;
        return;
    }
    try {
        sql::Statement* stmt = connection_->createStatement();
        int affectedRows = stmt->executeUpdate(query);
        cout << "Number of rows affected in view: " << affectedRows << endl;
        delete stmt;
    } catch (const sql::SQLException& e) {
        cout << "Handling Update Query ERR in view: " << e.what() << endl;
    }
    disconnect();
}




int main() {
    Database Huda("127.0.0.1", "root", "password", "studentmarket");
    Huda.connect();
    Huda.executeQuery("SELECT * FROM campuses");
    string viewName= "my_view6";
    string createViewQuery = "CREATE VIEW " + viewName + " AS SELECT * FROM campuses WHERE id = 1";

    
    ViewQuery Huda_view(Huda.getHost(),Huda.getUsername(),Huda.getPassword(),Huda.getSchema(),createViewQuery,viewName );
    Huda_view.printView();
    Huda_view.updateQuery("UPDATE " + viewName + " SET campus_name = 'Huda\\'s University' WHERE id = 1");
    Huda_view.printView();
    Huda.disconnect();

    // delete Huda;
    // delete Huda_view;
    return 0;
}