// Shapes.h
#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include "color.h"

#include <SDL.h>
#include <vector>

// Problem: SDL only offers Points and Rectangles, I'd like to extend that for more shapes
// NOT TRUE: There are other geometry rendering functions, need to investigate those


namespace Shapes {

	struct Point {

		int x;
		int y;

	};


	class Renderable {}; // Interface to pass shapes to a separate SDL renderer or rendering class --> This shouldn't worry about the details of the rendering, just how to do it based on the info provided --> abstract class?

	class Shape : Renderable {
	public:

		Shape() : color(Color::getSDLColor(Color::WHITE)), pnt({ 0,0 }) {} // Default white


		// Virtual deconstructor?


		void moveTo(Point point) {
			pnt = point;
		} // A shape can be moved to a new location on the screen --> Different shapes are represented by different things, how to address that? --> Maybe each shape has a Point to reference?

		Point getPos() {
			return pnt;
		}

		void setColor(SDL_Color nColor) {
			color = nColor;
		}

		SDL_Color getColor() {
			return color;
		}



	protected:
		Point pnt; // Point where shape will be rendered
		SDL_Color color; // All shapes have a color


	}; // Base class for shapes

	class PointShape : public Shape {
	public:
		PointShape(Point point) : position(point) {}




	private:
		Point position;


	};


	class Text : Renderable {}; // Simple text


	class Rectangle : public Shape {
	public:

		Rectangle(Point point, int size) : topLeft(point), width(size), height(size), filled(false) {}

		Rectangle(Point point, int size, bool fld) : topLeft(point), width(size), height(size), filled(fld) {}

		Rectangle(Point point, int wid, int hei) : topLeft(point), width(wid), height(hei), filled(false) {}

		Rectangle(Point point, int wid, int hei, bool fld) : topLeft(point), width(wid), height(hei), filled(fld) {}

		void render(SDL_Renderer* renderer) const {
			if (!filled) {
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // Set the color of the rectangle
				SDL_Rect rect = { topLeft.x, topLeft.y, width, height };
				SDL_RenderDrawRect(renderer, &rect); // Draw the rectangle 
			}
			else {
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // Set the color of the rectangle
				SDL_Rect rect = { topLeft.x, topLeft.y, width, height };
				SDL_RenderFillRect(renderer, &rect); // Draw the rectangle 
			}
		}

		Point getTopLeft() {
			return topLeft;
		}

		Point getTopRight() {
			return { topLeft.x + width, topLeft.y };
		}

		Point getBottomLeft() {
			return { topLeft.x, topLeft.y + height };
		}

		Point getBottomRight() {
			return { topLeft.x + width, topLeft.y + height };
		}

		Point getCenter() {
			return { topLeft.x + (width / 2), topLeft.y + (height / 2) };
		}

		int getWidth() {
			return width;
		}

		int getHeight() {
			return height;
		}

		bool isFilled() {
			return filled;
		}

		bool isPointInside(Point point) {
			// Check if a given point is inside the rectangle
			int& x = point.x;
			int& y = point.y;

			if ((x > topLeft.x) && (x < topLeft.x + width) && (y > topLeft.y) && (y < topLeft.y + height)) {
				return true;
			}
			else {
				return false;
			}
		}



	private:
		// A rectangle is stored as the top left point and the width and height. We can use simple functions to get other desired points, such as the other corners
		Point topLeft;

		int width;
		int height;
		bool filled;


	}; // Wrapper for SDL Rectangle class(es?)

	class Square : public Rectangle {

		Square(Point topLeft, int size) : Rectangle(topLeft, size, size) {}

		Square(Point topLeft, int size, bool fld) : Rectangle(topLeft, size, size, fld) {}

	};

	class Line : public Shape { // Generate a filled rectangle of a given thickness (default 1 px)
	public:

		Line(Point pt1, Point pt2) : p1(pt1), p2(pt2) {
			if (p1.x == p2.x && p1.y == p2.y) { // If p1 = p2, the line is a point
				p2.x++; // Can't have a zero size point, enforce 1 px points
			}
		}

		double getLength() {} // Will generally not be a whole number off axis

		double getAngle() {} // Also generally not a whole number




	private:
		Point p1; // Beginning
		Point p2; // End


	}; // Special case of Rectangle

	class Lines : Shape { // Collection of lines
	public:

		Lines() {}

	private:


	}; // Special case of Line

	class Curve : Shape {}; // For drawing unique function curves --> Later

	class Arrow : Shape {}; // Arrow shape

	class Triangle : Shape {};

	class Polygon : Shape {};

	class Circle : Shape {};

	class CompositeShape : Shape {};
}

#endif // SHAPES_H