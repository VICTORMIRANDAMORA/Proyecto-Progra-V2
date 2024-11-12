#include "route.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<fstream>

using namespace std;
using namespace sf;

void List::addRoute(string& _name) {
	Route* newRoute = new Route(_name);
	if (!routeHead) {
		routeHead = newRoute;
	}
	else {
		Route* temp = routeHead;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newRoute;
		newRoute->prev = temp;
	}
}

void List::deleteRoute(string& _name) {
	Route* temp = routeHead;
	while (temp && temp->routeName != _name) {
		temp = temp->next;
	}
	if (!temp) return;
	if (temp->prev)temp->prev->next = temp->next;
	if (temp->next)temp->next->prev = temp->prev;
	if (temp == routeHead)routeHead = temp->next;
	delete temp;
}

void List::addPoint(string& _name, string& _point, int x, int y, const string& _color){
	Route* route = routeHead;
	while (route && route->routeName != _name) {
		route = route->next;
	}
	if (!route) return;
	TourPoint* newPoint = new TourPoint(_point, x, y, _color);
	if (!route->pointHead) {
		route->pointHead = newPoint;
	}
	else {
		TourPoint* temp = route->pointHead;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newPoint;
		newPoint->prev = temp;
	}
}

void List::deletePoint(string& _name, string& _point) {
	Route* route = routeHead;
	while (route && route->routeName != _name) {
		route = route->next;
	}
	if (!route) return;
	TourPoint* temp = route->pointHead;
	while (temp && temp->name != _point) {
		temp = temp->next;
	}
	if (!temp) return;
	if (temp->prev)temp->prev->next = temp->next;
	if (temp->next)temp->next->prev = temp->prev;
	if (temp == route->pointHead)route->pointHead = temp->next;
	delete temp;
}

void List::displayRoutes() const {
	Route* route = routeHead;
	while (route) {
		cout << "Ruta " << route->routeName << endl;
		TourPoint* point = route->pointHead;
		while (point) {
			cout << "Punto: " << point->name << " (" << point->x << ", " << point->y << ") Color: " << point->color << endl;
			point = point->next;
		}
		route = route->next;
	}
}


void List::drawRoutes(sf::RenderWindow& window) const {
	Route* route = routeHead;
	while (route) {
		TourPoint* point = route->pointHead;
		TourPoint* prevPoint = nullptr;
		while (point) {
			CircleShape circle(5);
			circle.setPosition(point->x - 5, point->y - 5);
			circle.setFillColor(Color::Red);
			window.draw(circle);
			if (prevPoint) {
				Vertex line[] = {
					Vertex(Vector2f(prevPoint->x, prevPoint->y), Color::Blue),Vertex(Vector2f(point->x,point->y),Color::Blue)
				};
				window.draw(line, 2, Lines);
			}
			prevPoint = point;
			point = point->next;
		}
		route = route->next;
	}
}

void List::deleteNearPoint(int x, int y) {

	if (!routeHead)return;

	float minDistanceSquared = numeric_limits<float>::max();
	TourPoint* closestPoint = nullptr;
	Route* closestRoute = nullptr;

	Route* route = routeHead;
	while (route) {
		TourPoint* point = route->pointHead;
		while (point) {
			int dx = point->x - x;
			int dy = point->y - y;
			float distanceSquared = dx * dx + dy * dy;
			if (distanceSquared < minDistanceSquared) {
				minDistanceSquared = distanceSquared;
				closestPoint = point;
				closestRoute = route;
			}
			point = point->next;
		}
		route = route->next;
	}
	if (closestPoint && closestRoute) {
		deletePoint(closestRoute->routeName, closestPoint->name);
	}
	else {
		cout << "No se encontro ningun punto a eliminar\n";
	}
}

void List::saveRoutesToFiles(string name) const {
	Route* currentRoute = routeHead;
	while (currentRoute) {
		string filename = "ruta_" + name + ".txt";
		ofstream outFile(filename);
		if (outFile.is_open()) {
			outFile << currentRoute->routeName << "\n";
			TourPoint* currentPoint = currentRoute->pointHead;
			while (currentPoint) {
				outFile << currentPoint->name << " " << currentPoint->x << " " << currentPoint->y << " " << currentPoint->color << "\n";
				currentPoint = currentPoint->next;
			}
			outFile.close();
		}
		else {
			cerr << "Error al abrir el archivo " << filename << " para escritura.\n";
		}
		currentRoute = currentRoute->next;
	}
}

void List::loadRouteFromFiles(string name) {
	for (int i = 1; ; i++) {
		string filename = "ruta_" + name + ".txt";
		ifstream inFile(filename);
		if (!inFile.is_open()) {
			break;
		}
		string routeName;
		getline(inFile, routeName);
		addRoute(routeName);

		string pointName;
		int x, y;
		string color;
		while (inFile >> pointName >> x >> y >> color) {
			addPoint(routeName, pointName, x, y, color);
		}
		inFile.close();
	}
}

List::~List() {
	Route* currentRoute = routeHead;
	while (currentRoute) {
		TourPoint* currentPoint = currentRoute->pointHead;
		while (currentPoint) {
			TourPoint* nextPoint = currentPoint->next;
			delete currentPoint;
			currentPoint = nextPoint;
		}
		Route* nextRoute = currentRoute->next;
		delete currentRoute;
		currentRoute = nextRoute;
	}
}