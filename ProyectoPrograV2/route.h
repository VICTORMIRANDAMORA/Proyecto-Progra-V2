#pragma once
#include<string>
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

struct TourPoint {
	string name;
	int x, y;
	string color;
	TourPoint* next;
	TourPoint* prev;

	TourPoint(const string& _name, int _x, int _y, const string& _color) : name(_name), x(_x), y(_y), color(_color), next(nullptr), prev(nullptr) {}


};

struct Route {
	string routeName;
	TourPoint* pointHead;
	Route* next;
	Route* prev;


	Route(string& _name) : routeName(_name), pointHead(nullptr), next(nullptr),prev(nullptr){}
};

class List {
private:
	Route* routeHead;
public:
	List() : routeHead(nullptr){}
	void addRoute(string& _name);
	void deleteRoute(string& _name);
	void addPoint(string& _name, string& _point, int x, int y, const string& _color);
	void deletePoint(string& _name, string& _point);
	void displayRoutes() const;
	void drawRoutes(sf::RenderWindow& window)const;
	void deleteNearPoint(int x, int y);
	void saveRoutesToFiles(string name) const;
	void loadRouteFromFiles(string name);
	bool isEmpty() const { return routeHead == nullptr; }

	~List();
};

