#include "DatabaseFunc.h"

template<typename Out>

void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

static int callback(void *pString, int argc, char **argv, char **azColName) {
    if (argc > 0) {
        std::string *str = static_cast<std::string *>(pString);
        str->assign(argv[0]);
    }
    return 0;
}

void insertUser(Textbox textbox) {
    std::string enteringText = textbox.getString();
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = nullptr;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("C:/Users/mikhail/CLionProjects/Dinosaur/DB/dbUser.db", &db);

    if (rc) {
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return;
    }
    sql = "INSERT INTO User( id, namespace, balance, inventory) VALUES ('1', '" + enteringText +
          "', '300', '') ON CONFLICT (id) DO UPDATE SET namespace = '" + enteringText +
          "', balance = '300', inventory = '' WHERE id ='1';";

    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);
    sqlite3_close(db);
}

void selectInventory(std::string &outInventory) {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = nullptr;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("C:/Users/mikhail/CLionProjects/Dinosaur/DB/dbUser.db", &db);

    if (rc) {
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return;
    }
    sql = "Select inventory FROM User WHERE id ='1';";

    // Run the SQL (convert the string to a C-String with c_str() )

    rc = sqlite3_exec(db, sql.c_str(), callback, &outInventory, &zErrMsg);

    std::vector<std::string> splittedInventory = split(outInventory, ' ');
    sqlite3_close(db);

}

void selectBalance(sf::Font font, std::string &outStr) {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = nullptr;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("C:/Users/mikhail/CLionProjects/Dinosaur/DB/dbUser.db", &db);

    if (rc) {
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return;
    }

    sql = "Select balance FROM User WHERE id ='1';";

    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, &outStr, &zErrMsg);
    sqlite3_close(db);
}

void selectNamespace(std::string &outStrNamespace) {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = nullptr;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("C:/Users/mikhail/CLionProjects/Dinosaur/DB/dbUser.db", &db);

    if (rc) {
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return;
    }
    sql = "Select namespace FROM User WHERE id ='1';";

    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, &outStrNamespace, &zErrMsg);
    sqlite3_close(db);

}

void updateBalance(std::string outStr, std::string name) {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = nullptr;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("C:/Users/mikhail/CLionProjects/Dinosaur/DB/dbUser.db", &db);

    if (rc) {
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return;
    }

    sql = "UPDATE User SET balance = (balance - 100) WHERE id = '1';";
    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);
    sql = "Select inventory from User";
    rc = sqlite3_exec(db, sql.c_str(), callback, &outStr, &zErrMsg);

    sql = "Update User SET inventory = '" + outStr + name + " ' WHERE id='1';";
    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);
    sqlite3_close(db);
}

void updateBalanceAfterWin() {
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = nullptr;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    std::string sql;

    // Save the result of opening the file
    rc = sqlite3_open("C:/Users/mikhail/CLionProjects/Dinosaur/DB/dbUser.db", &db);

    if (rc) {
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return;
    }

    sql = "UPDATE User SET balance = (balance + 25) WHERE id = '1';";
    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);

    sqlite3_close(db);
}
