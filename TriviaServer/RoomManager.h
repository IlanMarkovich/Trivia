#pragma once

#include "Room.h"

#include <map>

using std::map;

class RoomManager
{
private:
	map<unsigned int, Room> _rooms;

public:
	void createRoom(const LoggedUser& user, const RoomData metadata);
	void deleteRoom(int roomId);

	unsigned int getRoomState(int roomId) const;
	vector<RoomData> getRooms() const;
	Room& getRoom(int roomId);
};
