#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>
#include <filesystem>
#include <unordered_map>
#include "WebServer.h"

// Function to set the current working directory to the folder containing the executable
void setWorkingDirectoryToExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::filesystem::path exePath(buffer);
    std::filesystem::current_path(exePath.parent_path());
    std::cout << "Changed working directory to: " << std::filesystem::current_path() << std::endl;
}

// Function to get the content type based on the file extension
std::string getContentType(const std::string& filePath) {
    std::unordered_map<std::string, std::string> contentTypes = {
        {".html", "text/html"},
        {".css", "text/css"},
        {".js", "application/javascript"},
        {".png", "image/png"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".gif", "image/gif"},
        {".ico", "image/x-icon"}
    };

    std::string extension = std::filesystem::path(filePath).extension().string();
    if (contentTypes.find(extension) != contentTypes.end()) {
        return contentTypes[extension];
    }
    return "application/octet-stream";
}

// Handler for when a message is received from the client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	// Set the current working directory to the folder containing the executable
	setWorkingDirectoryToExecutablePath();
	// Parse out the client's request string e.g. GET /index.html HTTP/1.1
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	// Some defaults for output to the client (404 file not found 'page')
	std::string content = "<h1>404 Not Found</h1>";
	std::string htmlFile = "/index.html";
	int code = 404;


	// If the GET request is valid, try and get the name
	if (parsed.size() >= 3 && parsed[0] == "GET")
	{
		htmlFile = parsed[1];

		// If the file is just a slash, use index.html. This should really
		// be if it _ends_ in a slash. I'll leave that for you :)
		if (htmlFile == "/")
		{
			htmlFile = "/index.html";
		}
	}

	// Open the document in the local file system
	std::string filePath = "./wwwroot" + htmlFile;
	std::cout << "Attempting to open file: " << filePath << std::endl;
	std::ifstream f(filePath, std::ios::binary);

	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
	
	// Check if the file exists
    // std::string filePath = "./wwwroot/index.html";
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "File does not exist: " << filePath << std::endl;
    }

	// // Check if it opened and if it did, grab the entire contents
	if (f.good()) {
		std::cout << "File opened successfully: " << filePath << std::endl;

		// iter string buffer in the file and read the content in that
		std::ostringstream oss;
        oss << f.rdbuf();
        content = oss.str();
        code = 200;
	} else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }

	f.close();

	// Write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << code << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: " << getContentType(filePath) << "\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), size);
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{
	
}