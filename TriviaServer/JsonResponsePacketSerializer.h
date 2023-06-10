#pragma once

#include "Room.h"

#include <string>
#include <vector>
#include <functional>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define LEN_SIZE 4

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

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomResponse
{
	unsigned int status;
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	unsigned int status;
	vector<string> players;
};

struct GetHighScoresResponse
{
	unsigned int status;
	vector<string> players;
};

struct GetPersonalStatResponse
{
	unsigned int status;
	vector<string> statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionsCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

enum ResponseType
{
	REGULAR, START_GAME_RESPONSE, LEAVE_ROOM_RESPONSE
};

class JsonResponsePacketSerializer
{
private:
	static vector<unsigned char> createBuffer(std::function<json()> serRes);
	static vector<unsigned char> createBuffer(std::function<json()> serRes, ResponseType type);
	static vector<unsigned char> serializeOnlyStatusResponse(unsigned int status);
	static vector<unsigned char> serializeOnlyStatusResponse(unsigned int status, ResponseType type);
	static vector<unsigned char> serializeStatusAndStrVecResponse(unsigned int status, const vector<string>& vec, string fieldName);

public:
	static vector<unsigned char> serializeResponse(ErrorResponse response);
	static vector<unsigned char> serializeResponse(LoginResponse response);
	static vector<unsigned char> serializeResponse(SignupResponse response);
	static vector<unsigned char> serializeResponse(LogoutResponse response);
	static vector<unsigned char> serializeResponse(GetRoomResponse response);
	static vector<unsigned char> serializeResponse(GetPlayersInRoomResponse response);
	static vector<unsigned char> serializeResponse(GetHighScoresResponse response);
	static vector<unsigned char> serializeResponse(GetPersonalStatResponse response);
	static vector<unsigned char> serializeResponse(JoinRoomResponse response);
	static vector<unsigned char> serializeResponse(CreateRoomResponse response);
	static vector<unsigned char> serializeResponse(CloseRoomResponse response);
	static vector<unsigned char> serializeResponse(StartGameResponse response);
	static vector<unsigned char> serializeResponse(GetRoomStateResponse response);
	static vector<unsigned char> serializeResponse(LeaveRoomResponse response);
};
