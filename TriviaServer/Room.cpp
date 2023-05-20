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
	_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
	_users.erase(std::find(_users.begin(), _users.end(), user));
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
		str += data.name + '\n';
	}

	str.erase(str.end() - 1);
	return str;
}
