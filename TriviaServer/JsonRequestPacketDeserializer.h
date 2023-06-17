#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct LoginRequest
{
	string username;
	string password;
};

struct SignupRequest
{
	string username;
	string password;
	string email;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequset
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionsCount;
	unsigned int answerTimeout;
};

struct SubmitAnswerRequest
{
	unsigned int answerId;
};

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(vector<unsigned char> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(vector<unsigned char> buffer);
	static JoinRoomRequset deserializeJoinRoomRequest(vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(vector<unsigned char> buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(vector<unsigned char> buffer);
};
