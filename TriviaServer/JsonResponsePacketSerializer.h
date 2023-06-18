#pragma once

#include "Room.h"

#include <string>
#include <vector>
#include <functional>
#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define LEN_SIZE 4

using std::string;
using std::vector;
using std::map;

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

struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	vector<string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	unsigned int averageAnswerTime;
};

struct GetGameResultsResponse
{
	unsigned int status;
	vector<PlayerResults> results;
};

// Response Type for the client to know if the request is for the request he automatically sent (for ex. GetRoomState)
// or the response is to a request one of the users sent (for ex. CloseRoom)
enum ResponseType
{
	REGULAR, START_GAME_RESPONSE, LEAVE_ROOM_RESPONSE, CLOSE_ROOM_RESPONSE
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
	static vector<unsigned char> serializeResponse(GetGameResultsResponse response);
	static vector<unsigned char> serializeResponse(SubmitAnswerResponse response);
	static vector<unsigned char> serializeResponse(GetQuestionResponse response);
	static vector<unsigned char> serializeResponse(LeaveGameResponse response);
};
