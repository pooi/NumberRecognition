#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<stdio.h>

#define PI 3.141592
#define MIN(a, b) (a<b)? a:b
#define MAX(a, b) (a>b)? a:b

IplImage * src; // 입력 이미지
CvSize size; // 이미지 크기
int **arr; // 이미지를 2진화한 2차원 배열

// 이미지의 실제크기(여백을 제외한 실제 크기)
int realSize_x1 = 0;
int realSize_x2 = 0;
int realSize_y1 = 0;
int realSize_y2 = 0;

bool isHorizontalSym; // 좌우대칭인지
bool isVerticalSym; // 상하대칭인지
bool isHaveHorizontalLine; // 수평선이 존재하는지
int horizontalLocation; // 수평선의 위치 (0: 없음, 1: 상단, 2: 하단)
bool isHaveBlockField; // 막힌 곳이 있는지
int blockLocation; // 막힌 곳의 위치 (0: 없음, 1: 상단, 2: 하단)
int centerLineNumber; // 중심선과 겹치는 부분의 개수

// 좌우 대칭을 판별하는 함수
bool isHorizontalSymmetry() {

	int total = 0; // 비교한 면적
	int sum = 0; // 일치한 면적
	for (int y = realSize_y1; y <= realSize_y2; y++) {
		for (int x = realSize_x1; x <= (realSize_x1 + realSize_x2) / 2; x++) { // 가장 왼쪽부터 중심까지만 비교

			int _x = realSize_x2 - (x - realSize_x1); // 비교할 x좌표값을 구함

			if (arr[y][x] == arr[y][_x]) { // 좌측과 우측을 비교해 같으면 진입
				sum += 1; // 일치한 면적의 값을 1증가
			}

			total += 1; // 비교한 면적의 값을 1증가

		}
	}

	float percentage = ((float)sum / total); // 비교한 면적대비 일치한 면적의 비율을 구함(일치율)

	return percentage >= 0.90; // 일치율이 90% 이상이면 ture 아니면 false

}

// 상하 대칭을 판별하는 함수
bool isVerticalSymmetry() {

	int total = 0; // 비교한 면적
	int sum = 0; // 일치한 면적

	for (int x = realSize_x1; x <= realSize_x2; x++) { 
		for (int y = realSize_y1; y <= (realSize_y1 + realSize_y2) / 2; y++) { // 가장 위쪽부터 중심까지만 비교

			int _y = realSize_y2 - (y - realSize_y1); // 비교할 y좌표값을 구함

			if (arr[y][x] == arr[_y][x]) { // 상단과 하단을 비교해 같으면 진입
				sum += 1; // 일치한 면적의 값을 1증가
			}

			total += 1; // 비교한 면적의 값을 1증가

		}
	}

	float percentage = ((float)sum / total); // 비교한 면적대비 일치한 면적의 비율을 구함(일치율)

	return percentage >= 0.90; // 일치율이 90% 이상이면 true 아니면 false

}

// 상단에 수평선이 있는지 판별
void findTopHorizontalLine() {

	int cx = (realSize_x2 + realSize_x1) / 2;
	int y = 0;

	int threshold = MAX(30, (realSize_x2 - realSize_x1)*0.7); // 임계값을 정함(좌우로 이동해야하는 최소값)(숫자 1때문에 최소값을 30으로 설정)

	bool check = false; // 최초로 등장하는 검은부분(1)을 찾기위한 임시 변수

	while (y < size.height - 1) { // 가장 위쪽부터 계산

		if (check == false && arr[y][cx] == 1) { // 검은부분을 만난적이 없고, 현재 좌표가 검은부분(1)일 경우 진입
			check = true; // 최초로 검은 부분이 등장했다고 표시
		}

		if (check) {

			y += 2; // 정확성을 위해 임의로 2칸 진입

			int x1 = cx; // 중심으로부터 좌측으로 나아갈 변수
			int x2 = cx; // 중심으로부터 우측으로 나아갈 벼눗

			// 가장 왼쪽의 흰색과 검은색의 경계점을 구할 수 있음
			while (arr[y][x1] == 1 && x1 >= 0) {
				x1 -= 1;
			}
			// 가장 오른쪽의 경계점을 구할 수 있음
			while (arr[y][x2] == 1 && x2 < size.width) {
				x2 += 1;
			}

			if (x2 - x1 >= threshold) { // 가장 좌측 경계점과 우측 경계점의 길이가 임계값보다 크다면 진입
				horizontalLocation = 1; // 수평선의 위치가 상단임을 표시
				isHaveHorizontalLine = true; // 수평선이 있음을 표시
			}

			return; // 상단의 수평선만 확인하면 되므로 반환

		}

		y += 1;
	}

}

// 하단에 수평선이 있는지 판별
// 상단 수평선 판별과 비슷하나 y값이 하단부터 시작
void findBottomHorizontalLine() {

	int cx = (realSize_x2 + realSize_x1) / 2;
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
	int cx = (realSize_x2 + realSize_x1) / 2; // size.width / 2;
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
	int cx = (realSize_x2 + realSize_x1) / 2;
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

// 숫자의 실제 영역을 찾음
void findRealSize() {

	int x1, x2, y1, y2;
	x1 = size.width;
	x2 = 0;
	y1 = size.height;
	y2 = 0;

	// 상하좌우 최소 최대값을 추출
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {

			if (arr[y][x] == 1) {

				if (x < x1)
					x1 = x;
				if (x > x2)
					x2 = x;
				if (y < y1)
					y1 = y;
				if (y > y2)
					y2 = y;

			}
		}
	}

	realSize_x1 = x1;
	realSize_x2 = x2;
	realSize_y1 = y1;
	realSize_y2 = y2;

}

// 계산에 필요한 값 초기화
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

double toRadians(int angle) {
	return (double)angle * PI / 180.0;
}
int calculateHorizontalOffset(int angle, int radius) {
	return (int)round(cos(toRadians(angle)) * radius);
}
int calculateVerticalOffset(int angle, int radius) {
	return (int)round(sin(toRadians(angle)) * radius);
}
double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void usingTrigonometric(char * fileName) {

	int cx = (realSize_x2 + realSize_x1) / 2;//size.width / 2;
	int cy = (realSize_y2 + realSize_y1) / 2;//size.height / 2;

	FILE * f = fopen("graph.txt", "w");

	int range = MIN((size.height - 1) / 2, (size.width - 1) / 2);

	for (int i = 0; i <= 360; i++) {
		double d = 0;
		int x = 0;
		int y = 0;

		for (int r = 0; r <range; r++) {

			int offsetX = calculateHorizontalOffset(i, r);
			int offsetY = calculateVerticalOffset(i, r);

			int x2 = cx + offsetX;
			int y2 = cy + offsetY;

			if (x2 > 0 && x2 < size.width-1 && y2 > 0 && y2 <size.height-1 && arr[y2][x2] == 1) {
				x = x2;
				y = y2;
			}

		}

		d = distance(cx, cy, x, y);
		fprintf(f, "%f\n", d);

	}

	fclose(f);

	f = fopen("graph.txt", "r");

	IplImage * graph = cvCreateImage(cvSize(361, 300), 8, 3);

	CvScalar black = cvScalar(0, 0, 0);

	for (int x = 0; x <= 360; x++) {

		float d;
		fscanf(f, "%f", &d);

		for (int y = 0; y < d; y++) {
			cvSet2D(graph, 300-y-1, x, black);
		}

	}

	cvShowImage(fileName, graph);
	cvWaitKey(100);

}

void checkNumber() {

	/* 계산한 조건
	bool isHorizontalSym; // 좌우대칭
	bool isVerticalSym; // 상하대칭
	bool isHaveHorizontalLine; // 수평선이 있는지
	int horizontalLocation; // 수평선의 위치 0: 없음, 1: 상단, 2: 하단
	bool isHaveBlockField; // 막힌 곳이 있는지
	int blockLocation; // 막힌 곳의 위치 0: 없음, 1: 상단, 2: 하단
	int centerLineNumber; // 중심선과 만나는 지점의 개수
	*/

	if (isHaveBlockField) { // 막힌 곳이 있는지

		if (blockLocation == 2) { // 막힌 곳의 위치가 하단인지
			printf("에상 숫자 : 6\n");
			return;
		}
		else {

			if (isHaveHorizontalLine) { // 수평선이 있는지
				printf("예상 숫자 : 4\n");
				return;
			}
			else {
				if (!isHorizontalSym) { // 좌우대칭이 아닌지
					printf("예상 숫자 : 9\n");
					return;
				}
				else {

					if (isVerticalSym) { // 상하대칭인지
						printf("예상 숫자 : 0\n");
						return;
					}
					else {
						printf("예상 숫자 : 8\n");
						return;
					}

				}
			}

		}

	}
	else {

		if (centerLineNumber == 1) { // 중신선과 1번 만나는지
			printf("예상 숫자 : 1\n");
			return;
		}
		else {

			if (!isHaveHorizontalLine) { // 수평선이 없는지
				printf("예상 숫자 : 3\n");
				return;
			}
			else {
				if (horizontalLocation == 2) { // 수평선의 위치가 하단인지
					printf("예상 숫자 : 2\n");
					return;
				}
				else {
					if (centerLineNumber == 3) { // 중심선과 3번 만나는지
						printf("예상 숫자 : 5\n");
						return;
					}
					else {
						printf("예상 숫자 : 7\n");
						return;
					}
				}
			}

		}

	}

	printf("찾지 못함\n");
}

void loadImage(char * fileName) {

	src = cvLoadImage(fileName); // 그림을 입력받음
	size = cvGetSize(src); // 그림의 크기를 구함

	printf("input : %s\n", fileName);

	// 그림 사이즈와 동일한 크기의 2차원 동적배열 선언(그림을 '2진화'하기 위해)
	arr = (int**)malloc(sizeof(int*)*size.height);
	for (int i = 0; i < size.height; i++) {
		arr[i] = (int*)malloc(sizeof(int)*size.width);
	}

	// 그림 전체를 반복
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {

			CvScalar color = cvGet2D(src, y, x); // 해당 픽셀의 색

			if (color.val[0] == 255 && color.val[1] == 255 && color.val[2] == 255) {
				arr[y][x] = 0; // 흰색일 경우 0으로 표시
			}
			else {
				arr[y][x] = 1; // 흰색이 아닐 경우(옅은회색, 검은색 등) 일괄 1로 표시
			}

		}
	}

	findRealSize(); // 여백을 제외한 실제 크기를 찾음

	isHorizontalSym = isHorizontalSymmetry(); // 좌우대칭 판변
	isVerticalSym = isVerticalSymmetry(); // 상하대칭 판별
	findTopHorizontalLine(); // 상단 수평선이 있는지 판별
	findBottomHorizontalLine(); // 하단 수평선이 있는지 판별
	isHaveBlockField = findBlockField(); // 막힌 부분이 있는지 판별
	centerLineNumber = findCenterCount(); // 중심선에 걸치는 부분이 몇개인지 판별

	checkNumber(); // 계산한 값을 토대로 숫자인식

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
		printf("*           5. Test Set           *\n");
		printf("*             6. quit             *\n");
		printf("***********************************\n");
		printf("mode : ");
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
			//usingTrigonometric(fileName);

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
				//usingTrigonometric(fileName);

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
				//usingTrigonometric(fileName);

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
				//usingTrigonometric(fileName);

				// printfCurrentNumber();
			}


			fclose(input);
		}
		else if (mode == 5) {
			input = fopen("test\\input.txt", "r");
			int count = 0;
			fscanf(input, "%d", &count);

			for (int k = 0; k < count; k++) {
				init();
				printf("==================================\n");

				fscanf(input, "%s", fileName);

				loadImage(fileName);
				//usingTrigonometric(fileName);

				// printfCurrentNumber();
			}


			fclose(input);
		}
		else if (mode == 6) {
			break;
		}
		else {
			continue;
		}



	}

}