#pragma once

struct DirectionMag
{
	float x;
	float y;
	float mag;
};

class InputController {
public:
	InputController();
	~InputController();

	void setPickupPlace(bool pp) { pickupPlace = pp; }
	bool getPickupPlace() { return pickupPlace; }

	void setUseItem() { }
	bool getUseItem() { return useItem;  }

	DirectionMag getDirectionMag() { return dirMag;  }

protected:
	bool pickupPlace;

	bool useItem;

	DirectionMag dirMag;

};