// #include <crow.h>
// #include <crow/websocket.h>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <thread>

// std::vector<corw::websocket::connection*> connections;

// class WebSocketHandler : public crow:websock::handler{
    
// }

#include "database.h"
#include "WebSocketManager.h"


app.port(8080).multithreaded().run();
return 0;

int main(){
    std::string db_conn="postgresql://username:password@localhost/messaging_db"
    Database db(db_conn);
    WebSocketManager ws_manager;
    
    crow::App<crow:CORSHANDLER> app;
    auto &cors=app.get_middleware<crow::CORSHandler>();
    cors.global()
    .header("*")
    .methods("GET"_method, "POST"_method, "OPTIONS"_method)
    .origin("https://localhost:3000")
    CROW_ROUTE(app, "/api/register").methods("POST"_method)
    ([&db](const crow::request& req) {
        Json::Value root;
        Json::Reader reader;
        
        if (!reader.parse(req.body, root)) {
            return crow::response(400, "Invalid JSON");
        }
        
        std::string username = root["username"].asString();
        std::string email = root["email"].asString();
        std::string password = root["password"].asString();
        
        if (username.empty() || email.empty() || password.empty()) {
            return crow::response(400, "Missing required fields");
        }
        
        std::string password_hash = hashPassword(password);
        
        if (db.createUser(username, email, password_hash)) {
            Json::Value response;
            response["success"] = true;
            response["message"] = "User created successfully";
            
            Json::StreamWriterBuilder builder;
            return crow::response(201, Json::writeString(builder, response));
        } else {
            return crow::response(409, "User already exists");
        }
    });

    //login route
    CROW_ROUTE(app, "/api/login").methods("POST"_method)
    ([&db](const crow::request& req) {
        Json::Value root;
        Json::Reader reader;
        
        if (!reader.parse(req.body, root)) {
            return crow::response(400, "Invalid JSON");
        }
        
        std::string username = root["username"].asString();
        std::string password = root["password"].asString();
        
        Json::Value user = db.getUser(username);
        if (user.empty()) {
            return crow::response(401, "Invalid credentials");
        }
        
        std::string provided_hash = hashPassword(password);
        if (provided_hash != user["password_hash"].asString()) {
            return crow::response(401, "Invalid credentials");
        }
        
        Json::Value response;
        response["success"] = true;
        response["user"]["id"] = user["id"];
        response["user"]["username"] = user["username"];
        response["user"]["email"] = user["email"];
        
        Json::StreamWriterBuilder builder;
        return crow::response(200, Json::writeString(builder, response));
    });
    //get all users route
    CROW_ROUTE(app, "/api/users").methods("GET"_method)
    ([&db](const crow::request& req)){
        std::vector<Json::Value> users=db.getAllUsers();
        Json::Value response;
        response["users"]=Json::Value(Json::arrayValue);
        for (const auto&user: users){
            response["users"].append(user);
        }
        
        }
}