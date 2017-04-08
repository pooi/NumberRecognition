#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<stdio.h>

#define PI 3.141592
#define MIN(a, b) (a<b)? a:b
#define MAX(a, b) (a>b)? a:b

IplImage * src; // �Է� �̹���
CvSize size; // �̹��� ũ��
int **arr; // �̹����� 2��ȭ�� 2���� �迭

// �̹����� ����ũ��(������ ������ ���� ũ��)
int realSize_x1 = 0;
int realSize_x2 = 0;
int realSize_y1 = 0;
int realSize_y2 = 0;

bool isHorizontalSym; // �¿��Ī����
bool isVerticalSym; // ���ϴ�Ī����
bool isHaveHorizontalLine; // ������ �����ϴ���
int horizontalLocation; // ������ ��ġ (0: ����, 1: ���, 2: �ϴ�)
bool isHaveBlockField; // ���� ���� �ִ���
int blockLocation; // ���� ���� ��ġ (0: ����, 1: ���, 2: �ϴ�)
int centerLineNumber; // �߽ɼ��� ��ġ�� �κ��� ����

// �¿� ��Ī�� �Ǻ��ϴ� �Լ�
bool isHorizontalSymmetry() {

	int total = 0; // ���� ����
	int sum = 0; // ��ġ�� ����
	for (int y = realSize_y1; y <= realSize_y2; y++) {
		for (int x = realSize_x1; x <= (realSize_x1 + realSize_x2) / 2; x++) { // ���� ���ʺ��� �߽ɱ����� ��

			int _x = realSize_x2 - (x - realSize_x1); // ���� x��ǥ���� ����

			if (arr[y][x] == arr[y][_x]) { // ������ ������ ���� ������ ����
				sum += 1; // ��ġ�� ������ ���� 1����
			}

			total += 1; // ���� ������ ���� 1����

		}
	}

	float percentage = ((float)sum / total); // ���� ������� ��ġ�� ������ ������ ����(��ġ��)

	return percentage >= 0.90; // ��ġ���� 90% �̻��̸� ture �ƴϸ� false

}

// ���� ��Ī�� �Ǻ��ϴ� �Լ�
bool isVerticalSymmetry() {

	int total = 0; // ���� ����
	int sum = 0; // ��ġ�� ����

	for (int x = realSize_x1; x <= realSize_x2; x++) { 
		for (int y = realSize_y1; y <= (realSize_y1 + realSize_y2) / 2; y++) { // ���� ���ʺ��� �߽ɱ����� ��

			int _y = realSize_y2 - (y - realSize_y1); // ���� y��ǥ���� ����

			if (arr[y][x] == arr[_y][x]) { // ��ܰ� �ϴ��� ���� ������ ����
				sum += 1; // ��ġ�� ������ ���� 1����
			}

			total += 1; // ���� ������ ���� 1����

		}
	}

	float percentage = ((float)sum / total); // ���� ������� ��ġ�� ������ ������ ����(��ġ��)

	return percentage >= 0.90; // ��ġ���� 90% �̻��̸� true �ƴϸ� false

}

// ��ܿ� ������ �ִ��� �Ǻ�
void findTopHorizontalLine() {

	int cx = (realSize_x2 + realSize_x1) / 2;
	int y = 0;

	int threshold = MAX(30, (realSize_x2 - realSize_x1)*0.7); // �Ӱ谪�� ����(�¿�� �̵��ؾ��ϴ� �ּҰ�)(���� 1������ �ּҰ��� 30���� ����)

	bool check = false; // ���ʷ� �����ϴ� �����κ�(1)�� ã������ �ӽ� ����

	while (y < size.height - 1) { // ���� ���ʺ��� ���

		if (check == false && arr[y][cx] == 1) { // �����κ��� �������� ����, ���� ��ǥ�� �����κ�(1)�� ��� ����
			check = true; // ���ʷ� ���� �κ��� �����ߴٰ� ǥ��
		}

		if (check) {

			y += 2; // ��Ȯ���� ���� ���Ƿ� 2ĭ ����

			int x1 = cx; // �߽����κ��� �������� ���ư� ����
			int x2 = cx; // �߽����κ��� �������� ���ư� ����

			// ���� ������ ����� �������� ������� ���� �� ����
			while (arr[y][x1] == 1 && x1 >= 0) {
				x1 -= 1;
			}
			// ���� �������� ������� ���� �� ����
			while (arr[y][x2] == 1 && x2 < size.width) {
				x2 += 1;
			}

			if (x2 - x1 >= threshold) { // ���� ���� ������� ���� ������� ���̰� �Ӱ谪���� ũ�ٸ� ����
				horizontalLocation = 1; // ������ ��ġ�� ������� ǥ��
				isHaveHorizontalLine = true; // ������ ������ ǥ��
			}

			return; // ����� ���򼱸� Ȯ���ϸ� �ǹǷ� ��ȯ

		}

		y += 1;
	}

}

// �ϴܿ� ������ �ִ��� �Ǻ�
// ��� ���� �Ǻ��� ����ϳ� y���� �ϴܺ��� ����
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
			y += 2; // ���Ĺ��� 6������ ���Ƿ� 2ĭ ����
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

// ������ ���� ������ ã��
void findRealSize() {

	int x1, x2, y1, y2;
	x1 = size.width;
	x2 = 0;
	y1 = size.height;
	y2 = 0;

	// �����¿� �ּ� �ִ밪�� ����
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

// ��꿡 �ʿ��� �� �ʱ�ȭ
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

	/* ����� ����
	bool isHorizontalSym; // �¿��Ī
	bool isVerticalSym; // ���ϴ�Ī
	bool isHaveHorizontalLine; // ������ �ִ���
	int horizontalLocation; // ������ ��ġ 0: ����, 1: ���, 2: �ϴ�
	bool isHaveBlockField; // ���� ���� �ִ���
	int blockLocation; // ���� ���� ��ġ 0: ����, 1: ���, 2: �ϴ�
	int centerLineNumber; // �߽ɼ��� ������ ������ ����
	*/

	if (isHaveBlockField) { // ���� ���� �ִ���

		if (blockLocation == 2) { // ���� ���� ��ġ�� �ϴ�����
			printf("���� ���� : 6\n");
			return;
		}
		else {

			if (isHaveHorizontalLine) { // ������ �ִ���
				printf("���� ���� : 4\n");
				return;
			}
			else {
				if (!isHorizontalSym) { // �¿��Ī�� �ƴ���
					printf("���� ���� : 9\n");
					return;
				}
				else {

					if (isVerticalSym) { // ���ϴ�Ī����
						printf("���� ���� : 0\n");
						return;
					}
					else {
						printf("���� ���� : 8\n");
						return;
					}

				}
			}

		}

	}
	else {

		if (centerLineNumber == 1) { // �߽ż��� 1�� ��������
			printf("���� ���� : 1\n");
			return;
		}
		else {

			if (!isHaveHorizontalLine) { // ������ ������
				printf("���� ���� : 3\n");
				return;
			}
			else {
				if (horizontalLocation == 2) { // ������ ��ġ�� �ϴ�����
					printf("���� ���� : 2\n");
					return;
				}
				else {
					if (centerLineNumber == 3) { // �߽ɼ��� 3�� ��������
						printf("���� ���� : 5\n");
						return;
					}
					else {
						printf("���� ���� : 7\n");
						return;
					}
				}
			}

		}

	}

	printf("ã�� ����\n");
}

void loadImage(char * fileName) {

	src = cvLoadImage(fileName); // �׸��� �Է¹���
	size = cvGetSize(src); // �׸��� ũ�⸦ ����

	printf("input : %s\n", fileName);

	// �׸� ������� ������ ũ���� 2���� �����迭 ����(�׸��� '2��ȭ'�ϱ� ����)
	arr = (int**)malloc(sizeof(int*)*size.height);
	for (int i = 0; i < size.height; i++) {
		arr[i] = (int*)malloc(sizeof(int)*size.width);
	}

	// �׸� ��ü�� �ݺ�
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {

			CvScalar color = cvGet2D(src, y, x); // �ش� �ȼ��� ��

			if (color.val[0] == 255 && color.val[1] == 255 && color.val[2] == 255) {
				arr[y][x] = 0; // ����� ��� 0���� ǥ��
			}
			else {
				arr[y][x] = 1; // ����� �ƴ� ���(����ȸ��, ������ ��) �ϰ� 1�� ǥ��
			}

		}
	}

	findRealSize(); // ������ ������ ���� ũ�⸦ ã��

	isHorizontalSym = isHorizontalSymmetry(); // �¿��Ī �Ǻ�
	isVerticalSym = isVerticalSymmetry(); // ���ϴ�Ī �Ǻ�
	findTopHorizontalLine(); // ��� ������ �ִ��� �Ǻ�
	findBottomHorizontalLine(); // �ϴ� ������ �ִ��� �Ǻ�
	isHaveBlockField = findBlockField(); // ���� �κ��� �ִ��� �Ǻ�
	centerLineNumber = findCenterCount(); // �߽ɼ��� ��ġ�� �κ��� ����� �Ǻ�

	checkNumber(); // ����� ���� ���� �����ν�

}

int main()
{

	while (true) {
		int mode;
		printf("\n\n");
		printf("***********************************\n");
		printf("*           Select mode           *\n");
		printf("*        1. input directory       *\n");
		printf("*             2. ����             *\n");
		printf("*            3. �߰��            *\n");
		printf("*           4. ���Ĺ���           *\n");
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
			//usingTrigonometric(fileName);

		}
		else if (mode == 2) {
			input = fopen("����\\input.txt", "r");
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
			input = fopen("�߰��\\input.txt", "r");
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
			input = fopen("���Ĺ���\\input.txt", "r");
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
			break;
		}
		else {
			continue;
		}



	}

}