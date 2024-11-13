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
	Route* currentRoute = routeHead;
	while (currentRoute) {
		TourPoint* temp = currentRoute->pointHead;
		if (temp && temp->next) {
			const int segments = 40;
			const float thickness = 50.0f;

			while (temp->next) {
				TourPoint* next = temp->next;
				for (float offset = -thickness / 2; offset <= thickness / 2; offset += 1.0f) {
					VertexArray neat(LinesStrip, segments + 1);

					for (int i = 0; i < segments; i++) {
						float t = i / static_cast<float>(segments);
						float t1 = t * t;
						float t2 = t1 * t;
						Vector2f interpolationPos((2 * t2 - 3 * t1 + 1) * temp->x + (t2 - 2 * t1 + t) * (temp->x + 60 + offset) +
							(-2 * t2 + 3 * t1) * next->x + (t2 - t1) * ( next->x - 60 + offset),

							(2 * t2 - 3 * t1 + 1) * temp->y + (t2 - 2 * t1 + t) * (temp->y + 60 + offset) +
							(-2 * t2 + 3 * t1) * next->y + (t2 - t1) * (next->y - 60 + offset)
						);

						neat[i].position = interpolationPos;
						neat[i].color = Color::Blue;
					}
					window.draw(neat);
				}
				temp = temp->next;
			}
		}

		temp = currentRoute->pointHead;
		while (temp) {
			CircleShape circle(5);
			circle.setOrigin(2, 2);
			circle.setPosition(Vector2f(temp->x,temp->y));
			circle.setFillColor(Color::Red);
			window.draw(circle);

			Font font;
			if (!font.loadFromFile("MONSTER OF FANTASY.otf")) {
				cerr << "No se pudo cargar la fuente" << endl;
			}

			Text Label(temp->name, font, 10);
			Label.setPosition(temp->x + 7, temp->y);
			Label.setFillColor(Color::White);

			RectangleShape LabelBox(Vector2f(30, 15));
			LabelBox.setFillColor(Color(0, 0, 0, 150));
			LabelBox.setPosition(temp->x + 10, temp->y);
			window.draw(LabelBox);
			window.draw(Label);

			temp = temp->next;
		}
		currentRoute = currentRoute->next;
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
			cerr << "Ha ocurrido un error\n";
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
		displayRoutes();
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


