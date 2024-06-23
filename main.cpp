#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class User {
    std::string _name;    
    std::string _login;   
    std::string _pass;    

public:
    User() = default;  
    User(const std::string& name, const std::string& login, const std::string& pass)
        : _name(name), _login(login), _pass(pass) {} 

   
    void serialize(std::ofstream& ofs) const {
        ofs << _name << '\n' << _login << '\n' << _pass << '\n';
    }

  
    void deserialize(std::ifstream& ifs) {
        std::getline(ifs, _name);
        std::getline(ifs, _login);
        std::getline(ifs, _pass);
    }

   
    void print() const {
        std::cout << "Name: " << _name << ", Login: " << _login << ", Password: " << _pass << '\n';
    }
};


class Message {
    std::string _text;     
    std::string _sender;   
    std::string _receiver; 

public:
    Message() = default;  
    Message(const std::string& text, const std::string& sender, const std::string& receiver)
        : _text(text), _sender(sender), _receiver(receiver) {}  

  
    void serialize(std::ofstream& ofs) const {
        ofs << _text << '\n' << _sender << '\n' << _receiver << '\n';
    }

   
    void deserialize(std::ifstream& ifs) {
        std::getline(ifs, _text);
        std::getline(ifs, _sender);
        std::getline(ifs, _receiver);
    }

   
    void print() const {
        std::cout << "Text: " << _text << ", Sender: " << _sender << ", Receiver: " << _receiver << '\n';
    }
};


void writeUsersToFile(const std::vector<User>& users, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::out | std::ios::trunc);  
    for (const auto& user : users) {
        user.serialize(ofs);  
    }
    ofs.close();  
}


std::vector<User> readUsersFromFile(const std::string& filename) {
    std::ifstream ifs(filename);  
    std::vector<User> users;  
    User user;  
    while (ifs.peek() != EOF) {  
        user.deserialize(ifs);  
        users.push_back(user); 
    }
    ifs.close(); 
    return users; 
}


void writeMessagesToFile(const std::vector<Message>& messages, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::out | std::ios::trunc);  
    for (const auto& message : messages) {
        message.serialize(ofs);  
    }
    ofs.close();  
}


std::vector<Message> readMessagesFromFile(const std::string& filename) {
    std::ifstream ifs(filename); 
    std::vector<Message> messages; 
    Message message;  
    while (ifs.peek() != EOF) {  
        message.deserialize(ifs);  
        messages.push_back(message);  
    }
    ifs.close(); 
    return messages; 
}

int main() {
    std::string userFile = "users.txt";  
    std::string messageFile = "messages.txt";  


    std::vector<User> users = readUsersFromFile(userFile); 
    std::vector<Message> messages = readMessagesFromFile(messageFile); 


    std::cout << "Users:\n";
    for (const auto& user : users) {
        user.print();  
    }

    std::cout << "\nMessages:\n";
    for (const auto& message : messages) {
        message.print();  
    }

   
    users.push_back(User("Alice", "alice123", "password")); 
    messages.push_back(Message("Hello!", "alice123", "bob456"));  

    writeUsersToFile(users, userFile);  
    writeMessagesToFile(messages, messageFile);  

    return 0;  
}
