

//constructor
Boat::Boat(int size, int player, Player* PlayerPointer) :
size(size), player(player), pointsNum(1), horizontal(0), hit(0), PlayerPointer(PlayerPointer){}

//getters
int Boat::getHorizontal(){
	return this.horizontal;
}

int Boat::getPlayer(){
	return this.player;
}
int Boat::getPointNum(){
	return this.pointsNum;
}
int Boat::getSize(){
	return this.size;
}
int Boat::isSunk(){
	if (hit == size){
		return true;
	}
	else{
		return false;
	}
}
//setters
void Boat::setHit(int hitPoints){
	this.hit = hitPoints;
}
void Boat::addPoint(){
	this.pointsNum = pointsNum + 1;
}
void Boat::setHorizontal(int horizontal){
	this.horizontal = horizontal;
}


//private
void Boat::notifyPlayerSunk(){
	PlayerPointer->removeBoat();
}
void Boat::notifyPlayerCreated(){
	PlayerPointer->addBoat();
}