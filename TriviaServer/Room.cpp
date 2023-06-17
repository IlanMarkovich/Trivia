#include "Room.h"

#include <algorithm>
#include <sstream>

// C'tor

Room::Room()
{
	_metadata = {0, "", 0, 0, 0, false};
}

Room::Room(RoomData metadata) : _metadata(metadata)
{
}

// METHODS

void Room::addUser(const LoggedUser& user)
{
	if (hasUser(user) || _users.size() == _metadata.maxPlayers)
	{
		throw std::exception("User already in room or the room is full");
	}

	_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
	_users.erase(std::find(_users.begin(), _users.end(), user));
}

bool Room::hasUser(const LoggedUser& user) const
{
	for (LoggedUser iter : _users)
	{
		if (iter.getUsername() == user.getUsername())
		{
			return true;
		}
	}

	return false;
}

vector<string> Room::getAllUsers() const
{
	vector<string> allUsers;
	
	for (const LoggedUser& user : _users)
	{
		allUsers.push_back(user.getUsername());
	}

	return allUsers;
}

RoomData Room::getData() const
{
	return _metadata;
}

string Room::roomDataVecToString(const vector<RoomData>& vec)
{
	string str;

	for (const RoomData& data : vec)
	{
		str += std::to_string(data.id) + "," + data.name + "," + std::to_string(data.maxPlayers) + ",";
		str += std::to_string(data.numOfQuestionsInGame) + "," + std::to_string(data.timePerQuestion) + "|";
	}

	// If the string isn't empty, delete the last seperator
	if (!str.empty())
	{
		str.erase(str.end() - 1);
	}

	return str;
}
