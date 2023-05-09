#pragma once

#include <string>
#include <vector>
#include <functional>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using std::string;
using std::vector;

struct ErrorResponse
{
	string message;
};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

class JsonResponsePacketSerializer
{
private:
	static vector<unsigned char> createBuffer(std::function<json()> serRes, unsigned char code);

public:
	static vector<unsigned char> serializeResponse(ErrorResponse response);
	static vector<unsigned char> serializeResponse(LoginResponse response);
	static vector<unsigned char> serializeResponse(SignupResponse response);
};
