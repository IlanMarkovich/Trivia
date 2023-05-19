#include "RoomManager.h"

#include <algorithm>

void RoomManager::createRoom(const LoggedUser& user, const RoomData metadata)
{
	Room room(metadata);
	room.addUser(user);

	_rooms[room.getData().id] = room;
}

void RoomManager::deleteRoom(int roomId)
{
	_rooms.erase(_rooms.find(roomId));
}

unsigned int RoomManager::getRoomState(int roomId) const
{
	return _rooms.at(roomId).getData().isActive;
}

vector<RoomData> RoomManager::getRooms() const
{
	vector<RoomData> roomsDataVec;

	for (auto i = _rooms.begin(); i != _rooms.end(); ++i)
	{
		roomsDataVec.push_back(i->second.getData());
	}

	return roomsDataVec;
}

Room& RoomManager::getRoom(int roomId)
{
	return _rooms[roomId];
}
