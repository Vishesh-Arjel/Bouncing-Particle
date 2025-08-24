#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
using namespace std;

struct loc {
	unsigned int x, y;
};

class bounce {
private:
	string word = "hello";
	const int width = 40;
	const int height = 10;
	loc object[5];
	string direction = "upleft";
	bool run = true;
	HANDLE s = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ci;

public:
	
	bounce(){
		for(int i = 0; i < 5; ++i){
			object[i].x = width/2 + i - 2;
			object[i].y = height/2;
		}
	}
	
	void draw() {
		cout << "\x1b[H";
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
            if (j == 0 || j == width + 1) {
                cout << '#';  // Print side walls
            } 
            else {
                bool printed = false;
                for (int k = 0; k < 5; ++k) {  // Check if current position matches any character
                    if (object[k].x == j && object[k].y == i) {
                        cout << word[k];
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << ' '; // Print empty space
            }
        }
        cout << endl;
    }
		
		/* bottom wall */

		for (int i = 0; i < width + 2; ++i) {
			cout << '#';
		}
		cout << endl;
	}

	void input() {
		if (_kbhit() && _getch() == 'x') {
			run = false;
		}
	}

	void logic() {
		
		/* for moving the object */
		
		if (direction == "upleft") {
			for(int k = 0; k < 5; ++k){
				object[k].x -= 1;
				object[k].y -= 1;	
			}
		}
		
		if (direction == "upright") {
			for(int k = 0; k < 5; ++k){
				object[k].x += 1;
				object[k].y -= 1;	
			}
		}
		
		if (direction == "downleft") {
			for(int k = 0; k < 5; ++k){
				object[k].x -= 1;
				object[k].y += 1;	
			}
		}
		if (direction == "downright") {
			for(int k = 0; k < 5; ++k){
				object[k].x += 1;
				object[k].y += 1;	
			}
		}

		/* for detecting collisions */

		if (object[4].x == width) {
			if (direction == "upright") direction = "upleft";

			if (direction == "downright") direction = "downleft";
		} 
		if(object[0].x == 1) {
			if (direction == "upleft") direction ="upright";

			if (direction == "downleft") direction = "downright";
		}
		if(object[0].y == height - 1) {
			if (direction == "downleft") direction = "upleft";

			if (direction == "downright") direction = "upright";
		}
		if(object[0].y == 0) {
			
			if (direction == "upleft") direction ="downleft";

			if (direction == "upright") direction = "downright";
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
	bounce b;
	b.Run();
}
