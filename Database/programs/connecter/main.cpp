#include <iostream>
#include <stdlib.h>

#include <mysql/jdbc.h>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <nlohmann/json.hpp>

using namespace std;

using json = nlohmann::json;

// Defining a WebSocket client type
typedef websocketpp::client<websocketpp::config::asio_client> client;
client ws_client;

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
    string executeQuery(const std::string& query);
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

string Database::executeQuery(const string& query) {
    cout << "Executing query: " << query << endl;

    if (!connection_) {
        cout << "No database connection." << endl;
        return ""; // Return an empty string if there's no connection
    }

    try {
        // Create a statement object
        sql::Statement* stmt = connection_->createStatement();

        // Determine if the query is a SELECT statement or another type
        if (query.find("SELECT") == 0 || query.find("select") == 0) {
            // Execute the query and obtain a result set
            sql::ResultSet* res = stmt->executeQuery(query);

            // Create a JSON array to store the results
            json resultArray = json::array();

            // Iterate over the result set and build JSON array
            while (res->next()) {
                json row;

                // Add each column's value to the JSON object
                sql::ResultSetMetaData* meta = res->getMetaData();
                int columnCount = meta->getColumnCount();

                for (int i = 1; i <= columnCount; i++) {
                    string columnName = meta->getColumnName(i);
                    int columnType = meta->getColumnType(i);

                    switch (columnType) {
                        case sql::DataType::INTEGER: // INT
                            row[columnName] = res->getInt(i);
                            break;
                        case sql::DataType::DOUBLE: // FLOAT or DOUBLE
                            row[columnName] = res->getDouble(i);
                            break;
                        case sql::DataType::DECIMAL: // DECIMAL
                            row[columnName] = res->getDouble(i); // Use getDouble for DECIMAL as well
                            break;
                        case sql::DataType::VARCHAR: // STRING
                            row[columnName] = res->getString(i);
                            break;
                        // case sql::DataType::TEXT: // TEXT
                        //     row[columnName] = res->getString(i);
                        //     break;
                        // case sql::DataType::BOOLEAN: // BOOLEAN
                        //     row[columnName] = res->getBoolean(i);
                        //     break;
                        case sql::DataType::BIGINT: // BIGINT
                            row[columnName] = res->getInt64(i);
                            break;
                        case sql::DataType::SMALLINT: // SMALLINT
                            row[columnName] = res->getInt(i);
                            break;
                        case sql::DataType::TINYINT: // TINYINT
                            row[columnName] = res->getInt(i);
                            break;
                        // case sql::DataType::BINARY: // BINARY
                        default:
                            cout << "Unhandled data type: " << columnType << endl;
                            break;
                    }
                }

                // Add the row to the JSON array
                resultArray.push_back(row);
            }

            // Clean up resources
            delete res;
            delete stmt;

            // Return the JSON string representation of the results
            return resultArray.dump();
        } else {
            // Execute the query as an update, insert, or delete operation
            int rowsAffected = stmt->executeUpdate(query);

            // Clean up resources
            delete stmt;

            // Return the number of rows affected as a string
            return "Rows affected: " + to_string(rowsAffected);
        }
    } catch (const sql::SQLException& e) {
        cout << "Error during query execution: " << e.what() << endl;
        return ""; // Return an empty string on error
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
    // Create a Database object and establish a database connection
    Database Huda("127.0.0.1", "root", "password", "studentmarket");
    Huda.connect();
    

    // Initialize the WebSocket client
    ws_client.init_asio();
    
    // // Define event handlers for the WebSocket client
    ws_client.set_open_handler([&](websocketpp::connection_hdl hdl) {
        cout << "Connected to the WebSocket server." << endl;
    });


    // // Define the WebSocket message handler
    ws_client.set_message_handler([&](websocketpp::connection_hdl hdl, client::message_ptr msg){
        // Parse the received message
        string message_payload = msg->get_payload();
        cout << "Received message: " << message_payload << endl;
        try {
            // Parse the message as JSON
            nlohmann::json message_json = nlohmann::json::parse(message_payload);

            // Check the action and parameters in the received message
            string action = message_json["action"];
            string query_key = message_json["params"]["key"];

            if (action == "retrieve_data") {
                // Handle the 'retrieve_data' action by executing the SQL query
                string query = query_key;
                cout << "Executing query: " << query << endl;

                // Execute the query and capture results
                string query_results = Huda.executeQuery(query);

                // Create a JSON object for the response
                json response_json;
                response_json["status"] = "success";
                response_json["data"] = query_results;

                // Convert JSON object to string
                string response_payload = response_json.dump();
                cout << response_payload <<endl;

                // Send the response back to the WebSocket server
                ws_client.send(hdl, response_payload, websocketpp::frame::opcode::text);
            } else {
                cout << "Unknown action received: " << action << endl;
            }
        } catch (const std::exception &e) {
            cout << "Error handling message: " << e.what() << endl;
        }
    });
  


    ws_client.set_close_handler([&](websocketpp::connection_hdl hdl) {
        cout << "Disconnected from the WebSocket server." << endl;
    });

    // Establish the WebSocket connection
    // Establish the WebSocket connection
    std::string uri = "ws://localhost:3000";
    websocketpp::lib::error_code ec;
    client::connection_ptr conn = ws_client.get_connection(uri, ec);
    if (ec) {
        std::cout << "Connection failed: " << ec.message() << std::endl;
        return 1; // Return with a failure code
    }

    // Connect the WebSocket client
    ws_client.connect(conn);

    // Run the WebSocket client event loop in a separate thread
    std::thread ws_thread([&]() {
        ws_client.run();
    });


    // Huda.executeQuery("SELECT * FROM campuses;");

    // Perform other database operations if needed

    // Gracefully shut down the WebSocket client
    // ws_client.stop();
    ws_thread.join();

    // Disconnect the database connection
    Huda.disconnect();

    return 0;
}
