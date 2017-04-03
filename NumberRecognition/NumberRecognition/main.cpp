#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<stdio.h>

#define MIN(a, b) (a<b)? a:b
#define MAX(a, b) (a>b)? a:b

IplImage * src;
CvSize size;
int **arr;

int realSize_x1 = 0;
int realSize_x2 = 0;
int realSize_y1 = 0;
int realSize_y2 = 0;

bool isHorizontalSym;
bool isVerticalSym;
bool isHaveHorizontalLine;
int horizontalLocation;
bool isHaveBlockField;
int blockLocation;
int centerLineNumber;

bool isHorizontalSymmetry() {

	int total = 0;
	int sum = 0;
	for (int y = realSize_y1; y <= realSize_y2; y++) {
		for (int x = realSize_x1; x <= (realSize_x1 + realSize_x2) / 2; x++) {

			int _x = realSize_x2 - (x - realSize_x1);

			//printf("x : %d, _x : %d\n", x, _x);

			if (arr[y][x] == arr[y][_x]) {
				sum += 1;
			}

			total += 1;

		}
	}

	float percentage = ((float)sum / total);

	return percentage >= 0.90;

}

bool isVerticalSymmetry() {

	int total = 0;
	int sum = 0;

	for (int x = realSize_x1; x <= realSize_x2; x++) {
		for (int y = realSize_y1; y <= (realSize_y1 + realSize_y2) / 2; y++) {

			int _y = realSize_y2 - (y - realSize_y1);

			if (arr[y][x] == arr[_y][x]) {
				sum += 1;
			}

			total += 1;

		}
	}

	float percentage = ((float)sum / total);

	return percentage >= 0.90;

}

//int findHorizontalLine() {
//
//	int line = 0;
//
//	int height = size.height;
//	int * check = (int*)malloc(sizeof(int)*height);
//	int c = 0;
//
//	for (int i = 0; i < height; i++) {
//		check[i] = 0;
//	}
//
//	FILE *f;
//	f = fopen("b.txt", "w");
//
//	int threshold = MAX(30, (realSize_x2 - realSize_x1)*0.7);
//	//int threshold = 30;
//	//printf("threshold : %d\n", threshold);
//
//	for (int y = 0; y < size.height; y++) {
//		int sum = 0;
//		int min_x = size.width, max_x = 0;
//
//		bool isIn = false;
//		for (int x = 0; x < size.width; x++) {
//
//			if (arr[y][x] == 1) {
//				isIn = true;
//				if (x < min_x) {
//					min_x = x;
//				}
//
//				if (x > max_x) {
//					max_x = x;
//				}
//			}
//			/*if (arr[y][x] == 1 && arr[y][x + 1] == 1) {
//			sum += 1;
//			}*/
//
//		}
//
//		if (!isIn) {
//			check[c] = 0;
//			c += 1;
//			continue;
//		}
//
//		if (max_x - min_x < threshold) {
//
//			min_x = 0;
//			max_x = size.width;
//
//		}
//
//		bool chk = false;
//		for (int x = min_x; x < max_x; x++) {
//
//			if (chk == false && arr[y][x] == 1) {
//				chk = true;
//			}
//			else if (chk == true && arr[y][x] == 0) {
//				chk = false;
//				break;
//			}
//
//			/*if (arr[y][x] == 0) {
//			chk = false;
//			break;
//			}*/
//
//		}
//
//		if (chk) {
//			check[c] = 1;
//		}
//		else {
//			check[c] = 0;
//		}
//		c += 1;
//	}
//
//	int sum = 0;
//	for (int i = 0; i < height - 1; i++) {
//		//printf("%d\n", check[i]);
//		fprintf(f, "%d\n", check[i]);
//		if (check[i] == 1 && check[i + 1] == 1) {
//			sum += 1;
//		}
//		else {
//			if (sum > 4) {
//				line += 1;
//				if (i < height / 2) {
//					horizontalLocation = 1;
//					//printf("상\n");
//					return line;
//				}
//				else {
//					horizontalLocation = 2;
//					//printf("하\n");
//					return line;
//				}
//			}
//			sum = 0;
//		}
//	}
//
//	if (sum > 10) {
//		line += 1;
//		horizontalLocation = 2;
//		//printf("하\n");
//		return line;
//	}
//	sum = 0;
//
//	fclose(f);
//
//	return line;
//
//}

void findTopHorizontalLine() {

	int cx = size.width / 2;
	int y = 0;

	int threshold = MAX(30, (realSize_x2 - realSize_x1)*0.7);

	bool check = false;

	while (y < size.height - 1) {

		if (check == false && arr[y][cx] == 1) {
			check = true;
		}

		if (check) {

			y += 2;

			int x1 = cx;
			int x2 = cx;

			while (arr[y][x1] == 1 && x1 >= 0) {
				x1 -= 1;
			}
			while (arr[y][x2] == 1 && x2 < size.width) {
				x2 += 1;
			}

			if (x2 - x1 >= threshold) {
				horizontalLocation = 1;
				isHaveHorizontalLine = true;
			}

			return;

		}

		y += 1;
	}

}

void findBottomHorizontalLine() {

	int cx = size.width / 2;
	int y = size.height - 1;

	int threshold = MAX(30, (realSize_x2 - realSize_x1)*0.7);

	bool check = false;

	while (y > 0) {

		if (check == false && arr[y][cx] == 1) {
			check = true;
		}

		if (check) {

			y -= 2;

			int x1 = cx;
			int x2 = cx;

			while (arr[y][x1] == 1 && x1 >= 0) {
				x1 -= 1;
			}
			while (arr[y][x2] == 1 && x2 < size.width) {
				x2 += 1;
			}

			if (x2 - x1 >= threshold) {
				horizontalLocation = 2;
				isHaveHorizontalLine = true;
			}

			return;

		}

		y -= 1;
	}

}

bool isBlocked(int _x, int _y) {

	bool isBlock = false;

	for (int x = _x; x < size.width; x++) {

		if (arr[_y][x] == 1) {
			isBlock = true;
		}
	}

	if (!isBlock) {
		return isBlock;
	}

	isBlock = false;

	for (int x = _x; x >= 0; x--) {
		if (arr[_y][x] == 1) {
			isBlock = true;
		}
	}

	if (!isBlock) {
		return isBlock;
	}

	return true;

}

bool findBlockField() {

	int count = 0;
	bool isBlock = true;
	int cx = size.width / 2;
	int y = 0;

	bool check = false;
	bool start = false;

	while (y < size.height - 1) {

		if (start == false && check == false && arr[y][cx] == 1) {
			check = true;
			y += 2; // 한컴백제 6때문에 임의로 2칸 전진
		}

		if (start == false && check == true && arr[y][cx] == 0) {
			check = false;
			start = true;
			count += 1;
		}

		if (start) {

			if (arr[y + 1][cx] == 0 && isBlocked(cx, y)) {
				isBlock = true;
			}
			else if (arr[y + 1][cx] == 1 && isBlock) {
				if (count <= 1) {
					blockLocation = 1;
				}
				else {
					blockLocation = 2;
				}
				return true;
			}
			else {
				start = false;
				isBlock = false;
			}

		}

		y += 1;
	}





	return isBlock;

}

int findCenterCount() {

	int count = 0;
	bool isBlock = true;
	int cx = size.width / 2;
	int y = 0;

	bool check = false;
	bool start = false;

	while (y < size.height - 1) {

		if (start == false && check == false && arr[y][cx] == 1) {
			check = true;
		}

		if (start == false && check == true && arr[y][cx] == 0) {
			check = false;
			start = true;
			count += 1;
		}

		if (start == true && arr[y + 1][cx] == 1) {

			start = false;

		}

		y += 1;
	}

	return count;

}

void findRealSize() {

	int x1, x2, y1, y2;
	x1 = size.width;
	x2 = 0;
	y1 = size.height;
	y2 = 0;

	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {

			if (arr[y][x] == 1) {

				if (x < x1) {
					x1 = x;
				}

				if (x > x2) {
					x2 = x;
				}

				if (y < y1) {
					y1 = y;
				}

				if (y > y2) {
					y2 = y;
				}

			}

		}

	}

	realSize_x1 = x1;
	realSize_x2 = x2;
	realSize_y1 = y1;
	realSize_y2 = y2;

}

void init() {

	src = NULL;
	arr = NULL;

	realSize_x1 = 0;
	realSize_x2 = 0;
	realSize_y1 = 0;
	realSize_y2 = 0;

	isHorizontalSym = false;
	isVerticalSym = false;
	isHaveHorizontalLine = false;
	horizontalLocation = 0;
	isHaveBlockField = false;
	blockLocation = 0;
	centerLineNumber = 0;

}

void printfCurrentNumber() {
	FILE *f;
	f = fopen("a.txt", "w");

	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {

			fprintf(f, "%d", arr[y][x]);

		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void checkNumber() {

	/*
	bool isHorizontalSym;
	bool isVerticalSym;
	bool isHaveHorizontalLine;
	int horizontalLocation;
	bool isHaveBlockField;
	int blockLocation;
	int centerLineNumber;
	*/

	if (centerLineNumber == 1) {
		printf("예상 숫자 : 1\n");
		return;
	}

	if (isHorizontalSym == false && isVerticalSym == false && isHaveHorizontalLine == true && horizontalLocation == 2 && isHaveBlockField == false && blockLocation == 0 && centerLineNumber == 3) {
		printf("예상 숫자 : 2\n");
		return;
	}

	if (isHaveHorizontalLine == false && horizontalLocation == 0 && isHaveBlockField == false && blockLocation == 0 && centerLineNumber == 3) {
		printf("예상 숫자 : 3\n");
		return;
	}

	if (isHorizontalSym == false && isVerticalSym == false && isHaveHorizontalLine == true && horizontalLocation == 2 && isHaveBlockField == true && blockLocation == 1 && centerLineNumber == 2) {
		printf("예상 숫자 : 4\n");
		return;
	}

	if (isHorizontalSym == false && isVerticalSym == false && isHaveHorizontalLine == true && horizontalLocation == 1 && isHaveBlockField == false && blockLocation == 0 && centerLineNumber == 3) {
		printf("예상 숫자 : 5\n");
		return;
	}

	if (isHaveBlockField == true && blockLocation == 2) {
		printf("예상 숫자 : 6\n");
		return;
	}

	if (isHorizontalSym == false && isVerticalSym == false && isHaveHorizontalLine == true && horizontalLocation == 1 && isHaveBlockField == false && blockLocation == 0 && centerLineNumber == 2) {
		printf("예상 숫자 : 7\n");
		return;
	}

	if (isVerticalSym == false && isHorizontalSym == true) {
		printf("예상 숫자 : 8\n");
		return;
	}

	if (isHorizontalSym == false && isVerticalSym == false && isHaveBlockField == true && blockLocation == 1 && centerLineNumber == 3) {
		printf("예상 숫자 : 9\n");
		return;
	}

	if (isVerticalSym == true && isHorizontalSym == true) {
		printf("예상 숫자 : 0\n");
		return;
	}

	printf("찾지 못함\n");
}

void loadImage(char * fileName) {

	src = cvLoadImage(fileName);
	size = cvGetSize(src);

	printf("input : %s\n", fileName);

	arr = (int**)malloc(sizeof(int*)*size.height);
	for (int i = 0; i < size.height; i++) {
		arr[i] = (int*)malloc(sizeof(int)*size.width);
	}

	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {

			CvScalar color = cvGet2D(src, y, x);

			if (color.val[0] == 255 && color.val[1] == 255 && color.val[2] == 255) {
				arr[y][x] = 0;
			}
			else {
				arr[y][x] = 1;
			}

		}
	}

	findRealSize();

	isHorizontalSym = isHorizontalSymmetry();
	isVerticalSym = isVerticalSymmetry();
	findTopHorizontalLine();
	findBottomHorizontalLine();
	isHaveBlockField = findBlockField();
	centerLineNumber = findCenterCount();

	checkNumber();

}

int main()
{

	while (true) {
		int mode;
		printf("\n\n");
		printf("***********************************\n");
		printf("*           Select mode           *\n");
		printf("*        1. input directory       *\n");
		printf("*             2. 굴림             *\n");
		printf("*            3. 견고딕            *\n");
		printf("*           4. 한컴백제           *\n");
		printf("*             5. quit             *\n");
		printf("***********************************\n");
		printf("input : ");
		scanf("%d", &mode);

		char fileName[15];
		FILE * input;

		if (mode == 1) {

			printf("input directory : ");
			scanf("%s", fileName);

			IplImage * temp = cvLoadImage(fileName);
			if (temp == NULL) {
				printf("There is no image.\n");
				continue;
			}

			loadImage(fileName);

		}
		else if (mode == 2) {
			input = fopen("굴림\\input.txt", "r");
			int count = 0;
			fscanf(input, "%d", &count);

			for (int k = 0; k < count; k++) {
				init();
				printf("==================================\n");

				fscanf(input, "%s", fileName);

				loadImage(fileName);

				// printfCurrentNumber();
			}


			fclose(input);
		}
		else if (mode == 3) {
			input = fopen("견고딕\\input.txt", "r");
			int count = 0;
			fscanf(input, "%d", &count);

			for (int k = 0; k < count; k++) {
				init();
				printf("==================================\n");

				fscanf(input, "%s", fileName);

				loadImage(fileName);

				// printfCurrentNumber();
			}


			fclose(input);
		}
		else if (mode == 4) {
			input = fopen("한컴백제\\input.txt", "r");
			int count = 0;
			fscanf(input, "%d", &count);

			for (int k = 0; k < count; k++) {
				init();
				printf("==================================\n");

				fscanf(input, "%s", fileName);

				loadImage(fileName);

				// printfCurrentNumber();
			}


			fclose(input);
		}
		else if (mode == 5) {
			break;
		}
		else {
			continue;
		}



	}

}