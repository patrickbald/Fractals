// Patrick Bald
// fund comp lab 12

#include <iostream>
#include <cmath>
#include <unistd.h>
#include "gfx.h"

using namespace std;

void sierpinski(int, int, int, int, int, int);
void drawTriangle(int, int, int, int, int, int);
void shrinkingSquares(int, int, int);
void drawSquare(int, int, int);
void spiralSquares(float, float, float, float, float, float, float);
void circularLace(float, float, float, float, float);
void snowflake(float, float, float, float, float);
void tree(float, float, float, float, float);
void fern(float, float, float, float, float);
void spiralOfSpirals(float, float, float, float);

const float PI = 3.14159265359;

int main() {
	
	int width = 800, height = 800, mrgn = 20;
	char c;
  
  	bool loop = true;

   gfx_open(width, height, "Fractals");

   while (loop) {
     c = gfx_wait();
     gfx_clear();
     switch (c) {
       case '1': // Sierpinski Triangle
			sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
         break;
       case '2': {// Shrinking Squares
         int x_center = (width)/2, y_center = (height)/2;
			int length = width/2;
         shrinkingSquares(x_center, y_center, length);
			}
         break;
		case '3': { // spriral squares 
			float x_center = width/2, y_center = height/2;
			float x, y;
			float angle = PI/2;
			float radius = 400;
			float side = 160;
			spiralSquares(x_center, y_center, x, y, radius, side, angle);
			}
			break;
		case '4': { // circular lace
			float radius = 200;
			float x_center = width/2, y_center = height/2;
			float angle = (3*PI/2)-(PI/6);
			float inc_angle = 2*PI/6;
			circularLace(x_center, y_center, radius, angle, inc_angle);
			}
			break;
		case '5': { // snowflake
			float x_center = width/2, y_center = height/2;
			float angle = 0;
			float inc_angle = 2*PI/5;
			float length = 200;
			snowflake(x_center, y_center, length, angle, inc_angle);
			}
			break;
		case '6': { // tree
			float startX = width/2, startY = height;
			float angle = PI/2;
			float ia = PI/6;
			float length = 150;
			gfx_line(startX, startY, startX, startY - 300);
			tree(startX, startY-300, angle, length, ia);
			}
			break;
		case '7': { // fern
			float length = 500;
			float angle = PI/2;
			float ia = PI/6;
			float startX = width/2, startY = height - mrgn;
			fern(startX, startY, length, angle, ia);
			}
			break;
     	case '8': {// Spiral of Spirals
        	float angle = PI/2;
			float radius = 600;
			float x_center = width/2, y_center = height/2;
        	spiralOfSpirals(x_center, y_center, angle, radius);
			}
        	break;
      case 'q':
        	loop = false;
      default:
        	break;
    }

  }

	return 0;
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case.
  if( abs(x2-x1) < 5 ) return;

  // Draw the triangle
  drawTriangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

void shrinkingSquares(int x_center, int y_center, int length){
	// base case
	if (length < 5) return;

	// draw shape
	drawSquare(x_center, y_center, length);
	length = length / 2;

	// recursive
	shrinkingSquares(x_center - length, y_center - length, length);
	shrinkingSquares(x_center + length, y_center - length, length);
	shrinkingSquares(x_center - length, y_center + length, length);
	shrinkingSquares(x_center + length, y_center + length, length);

}

void drawSquare(int x_center, int y_center, int length){

	int startx = x_center - length/2;
	int starty = y_center - length/2;

	gfx_line(startx, starty, startx + length, starty);
	gfx_line(startx + length, starty, startx + length, starty + length);
	gfx_line(startx + length, starty + length, startx, starty + length);
	gfx_line(startx, starty + length, startx, starty);	

}

void spiralSquares(float x_center, float y_center, float x, float y, float radius, float side, float angle){
 
	if(radius < 2) return;

	side *= .85;
	radius *= .85;

	angle = angle - (40 *(PI/180));
	x = x_center + (radius*cos(angle));
	y = y_center + (radius*sin(angle));
	drawSquare(x, y, side);
	
	spiralSquares(x_center, y_center, x, y, radius, side, angle);
	

}

void circularLace(float x_center, float y_center, float radius, float angle, float inc_angle) {

	if(radius < 1) return;

	gfx_circle(x_center, y_center, radius);
	
	for(int i = 1; i <= 6; i++){
		angle = angle + inc_angle;
		circularLace(x_center + radius*cos(angle), y_center + radius*sin(angle), radius*.3, angle, inc_angle);
	}
	

}

void snowflake(float x_center, float y_center, float length, float angle, float inc_angle){

	if(length < 1) return;

	for(int i = 1; i <= 5; i++){
		angle = angle + inc_angle;
		gfx_line(x_center, y_center, x_center + length*cos(angle), y_center + length*sin(angle));
		snowflake(x_center + length*cos(angle), y_center + length*sin(angle), length*.35, angle+inc_angle, inc_angle);
	}

}

void tree(float startX, float startY, float angle, float length, float ia){

	if(length < 2) return;

	gfx_line(startX, startY, startX + length*cos(angle+ia), startY - length*sin(angle+ia)); // draws left line
	gfx_line(startX, startY, startX + length*cos(angle-ia), startY - length*sin(angle-ia)); // draws right line
	
	tree(startX + length*cos(angle+ia), startY - length*sin(angle+ia), angle + ia, length*.7, ia); // goes left
	tree(startX + length*cos(angle-ia), startY - length*sin(angle-ia), angle - ia, length*.7, ia); // goes right

}

void fern(float startX, float startY, float length, float angle, float ia){

	if(length < 4) return;
	
	gfx_line(startX, startY, startX + length*cos(angle), startY - length*sin(angle)); 
	
	// one for each "leaf" of the large fern 
	fern(startX + (length/4) *cos(angle), startY - (length/4)*sin(angle), length/3, angle - ia, ia);
	fern(startX + (length/4) *cos(angle), startY - (length/4)*sin(angle), length/3, angle + ia, ia);
	fern(startX + (length/2) *cos(angle), startY - (length/2)*sin(angle), length/3, angle - ia, ia);
	fern(startX + (length/2) *cos(angle), startY - (length/2)*sin(angle), length/3, angle + ia, ia);
	fern(startX + (3*length/4) *cos(angle), startY - (3*length/4)*sin(angle), length/3, angle - ia, ia);
	fern(startX + (3*length/4) *cos(angle), startY - (3*length/4)*sin(angle), length/3, angle + ia, ia);
	fern(startX + (length) *cos(angle), startY - (length)*sin(angle), length/3, angle - ia, ia);
	fern(startX + (length) *cos(angle), startY - (length)*sin(angle), length/3, angle + ia, ia);
	
}

void spiralOfSpirals(float x_center, float y_center, float angle, float radius){

		if(radius < 1) return;

		radius = radius * .875;
		angle = angle + (40*(PI/180));
		gfx_point(x_center + radius*cos(angle), y_center + radius*sin(angle));
		
		spiralOfSpirals(x_center, y_center, angle, radius);
		spiralOfSpirals(x_center + radius*cos(angle), y_center + radius*sin(angle), angle, radius/2.4);

}




