#include<iostream>
#include<vector>

#define MAX_ROW 20

struct RowSeat {
	std::vector<bool> Seat;
	int emptySeat = 5;

	RowSeat() {
		Seat.assign(6, false);
	}
};

std::vector<RowSeat> SeatList(25);

void ChooseSeat(int ticketNum) {
	//找到连坐位置
	for (int i = 1; i <= MAX_ROW; ++i) {
		//当前空座位不够
		if (SeatList[i].emptySeat < ticketNum) {
			continue;
		}
		//当前空座位够
		else {
			int j = 1 ;
			while (j <= 5) {
				int k = j;

				while (k<=5 && SeatList[i].Seat[k] == false) {
					if (k - j + 1 == ticketNum) {
						for (int t = j; t <= k; ++t) {
							std::cout << 5 * (i - 1) + t << " ";
							SeatList[i].Seat[t] = true;
							SeatList[i].emptySeat--;
						}
						std::cout << "\n";
						return;
					}
					++k;
				}

				++j;
			}
		}
	}

	//找不到连坐位置
	int seatNum = 0;
	for (int i = 1; i <= MAX_ROW; ++i) {
		for (int j = 1; j <= 5; ++j) {
			if (SeatList[i].Seat[j] == false) {
				std::cout << 5 * (i - 1) + j << " ";
				SeatList[i].emptySeat--;
				seatNum++;
				if (seatNum == ticketNum) {
					std::cout << "\n";
					return; 
				}
			}
		}
	}

	return;
}


int main(int argc, char* argv[]) {

	int n;
	std::cin >> n;

	for (int i = 1; i <= n; ++i) {
		int ticketNum;
		std::cin >> ticketNum;
		ChooseSeat(ticketNum);

	}
	
	return EXIT_SUCCESS;
}