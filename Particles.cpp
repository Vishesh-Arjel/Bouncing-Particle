#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct loc {
	int x, y;
	string dir;
};

class bounce {
private:
	const int width = 30;
	const int height = 10;
	vector <loc> object;
	bool run = true;
	HANDLE s = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ci;

public:

	void spawn() {
		loc obj;
		obj.x = rand() % width;
		obj.y = rand() % height;
		obj.dir = "downright";
		object.push_back(obj);
	}
	
	void draw() {
		cout << "\033[H";
		GetConsoleCursorInfo(s, &ci);
		ci.bVisible = 0;
		SetConsoleCursorInfo(s, &ci);
		
		/* top wall */

		for (int i = 0; i < width + 2; ++i) {
			cout << '#';
		}
		cout << endl;
		
		/* printing middle body */

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width + 2; ++j) {
				
				bool printed = false;
				
				for (int k = 0; k < object.size(); ++k) {
					if (object[k].x == j && object[k].y == i) {
						cout << 'o';
						printed = true;
						break;
					} 
				}
				if (!printed) {
					if (j == 0) {
						cout << '#';
					}
					else if (j == width + 1) {
						cout << '#';
					}
					else {
						cout << ' ';
					}
				}
			}
			cout << endl;
		}

		/* bottom wall */

		for (int i = 0; i < width + 2; ++i) {
			cout << '#';
		}
		cout << endl << "Press 'x' to quit \nPress 's' to spawn new particles \n\nNumber of particles: " << object.size();
	}

	void input() {
		if (_kbhit()) {
				switch(_getch()) {
				case 'x':
					run = false;
				case 's':
					spawn();
			}
		}
	}

	void logic() {
		
		for (int k = 0; k < object.size(); ++k) {
			
			/* for moving the object */
			
			if (object[k].dir == "upleft") {
				object[k].x -= 1;
				object[k].y -= 1;
			}
			if (object[k].dir == "upright") {
				object[k].x += 1;
				object[k].y -= 1;
			}
			if (object[k].dir == "downleft") {
				object[k].x -= 1;
				object[k].y += 1;
			}
			if (object[k].dir == "downright") {
				object[k].x += 1;
				object[k].y += 1;
			}
	
			/* for detecting collisions */
	
			if (object[k].x == width) {
				if (object[k].dir == "upright") object[k].dir = "upleft";
	
				if (object[k].dir == "downright") object[k].dir = "downleft";
			}
			if (object[k].x == 1) {
				if (object[k].dir == "upleft") object[k].dir = "upright";
	
				if (object[k].dir == "downleft") object[k].dir = "downright";
			}
			if (object[k].y == height - 1) {
				if (object[k].dir == "downleft") object[k].dir = "upleft";
	
				if (object[k].dir == "downright") object[k].dir = "upright";
			}
			if (object[k].y == 0) {
				if (object[k].dir == "upleft") object[k].dir = "downleft";
	
				if (object[k].dir == "upright") object[k].dir = "downright";
			}	
			
			for (int m = 0; m < object.size(); ++m) {
				if (object[k].x == object[m].x && object[k].y == object[m].y && m != k) {
					if (object[k].dir == "upright") object[k].dir = "upleft";
					
					if (object[k].dir == "downright") object[k].dir = "downleft";
					
					if (object[k].dir == "upleft") object[k].dir = "upright";
					
					if (object[k].dir == "downleft") object[k].dir = "downright";
					
					if (object[k].dir == "downleft") object[k].dir = "upleft";
					
					if (object[k].dir == "downright") object[k].dir = "upright";
					
					if (object[k].dir == "upleft") object[k].dir = "downleft";
					
					if (object[k].dir == "upright") object[k].dir = "downright";
				}
			}
		}
	}

	void Run() {
		while (run) {
			draw();
			input();
			logic();
			Sleep(10);
		}
		system("pause");
	}
};

int main() {
	srand(static_cast<unsigned>(time(0)));
	bounce b;
	b.Run();
}

