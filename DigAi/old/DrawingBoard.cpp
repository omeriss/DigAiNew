#include "DrawingBoard.h"

DrawingBoard::DrawingBoard()
{
	if(UploadFile == "0")
		network = new NeuralNetwork();
	else
		network = new NeuralNetwork(UploadFile);

	srand((unsigned)time(NULL));
	pixel.setSize(sf::Vector2f(PIXELSIZE, PIXELSIZE));
	for (int i = 0; i < PIXELLEN; i++) {
		for (int j = 0; j < PIXELLEN; j++) {
			board[i][j] = 0;
		}
	}

	font.loadFromFile("arial.ttf");

	text.setPosition(SCREENSIZE / 2, SCREENSIZE / 15);
	text.setFont(font);
	text.setScale(SCREENSIZE / 300, SCREENSIZE / 300);
	text.setString("0");
	text.setOrigin(text.getLocalBounds().width / 2, 0);
	text.setFillColor(sf::Color::Red);
}

void DrawingBoard::DrawBoard(sf::RenderWindow& window)
{
	for (int i = 0; i < PIXELLEN; i++) {
		for (int j = 0; j < PIXELLEN; j++) {
			pixel.setFillColor(sf::Color(board[i][j] * 255, board[i][j] * 255, board[i][j] * 255));
			pixel.setPosition(sf::Vector2f(j * PIXELSIZE, i * PIXELSIZE));
			window.draw(pixel);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		GetNum();
		window.draw(text);
	}
}

void DrawingBoard::SetCell(int x, int y)
{
	if (x != lastX || y != lastY) {
		int m = x / PIXELSIZE;
		int n = y / PIXELSIZE;
		for (int i = n - 1; i <= n + 1; i++) {
			for (int j = m - 1; j <= m + 1; j++) {
				if (i >= 0 && i < PIXELLEN && j >= 0 && j < PIXELLEN) {
					float xtemp = j * PIXELSIZE + PIXELLEN / 2;
					float ytemp = i * PIXELSIZE + PIXELLEN / 2;
					board[i][j] += 1 - std::min(1.0, (sqrt(pow(x - xtemp, 2) +
						pow(y - ytemp, 2))) / ((3.0 / 4.0) * (2 * sqrt(2 * PIXELSIZE * PIXELSIZE))));
					board[i][j] = std::min(1.0f, board[i][j]);
				}
			}
		}
		lastX = x;
		lastY = y;
		if (m >= 0 && m < PIXELLEN && n >= 0 && n < PIXELLEN) {
			board[n][m] = 1;
		}
	}
}

void DrawingBoard::ClearBoard()
{
	for (int i = 0; i < PIXELLEN; i++) {
		for (int j = 0; j < PIXELLEN; j++) {
			board[i][j] = 0;
		}
	}
}

void OpenFile(FILE*& file, const char* fileName) {
	file = fopen(fileName, "rb");
	if (!file) {
		std::cout << "cant open file" << std::endl;
		return;
	}
}

void DrawingBoard::InsertInput(const char* dataName, const char* labelName, int mode)
{
	unsigned int fileLen = 0;
	FILE* fData = NULL, *fLabel = NULL;
	vector<double*> inputV;
	vector<int> labelV;
	// open data file
	OpenFile(fData, dataName);
	// open label file
	OpenFile(fLabel, labelName);

	// skip the Mnum
	fseek(fData, 4, SEEK_SET);
	// read the len
	fread(&fileLen, 4, 1, fData);
	// swap from little endian to big endian
	fileLen = (fileLen >> 24) |
		((fileLen << 8) & 0x00ff0000) |
		((fileLen >> 8) & 0x0000ff00) |
		(fileLen << 24);
	std::cout << fileLen << std::endl;
	// skip to start of data and labels
	fseek(fData, 16, SEEK_SET);
	fseek(fLabel, 8, SEEK_SET);

	// go over the data
	for (int i = 0; i < fileLen; i++) {
		double* temp = new double[28 * 28];
		for (int j = 0; j < 28 * 28; j++) {
			// read pixel
			bool n; // use bool for the byte
			fread(&n, 1, 1, fData);
			temp[j] = (double)n / 255;
		}
		inputV.push_back(temp);
		// read label
		bool n;
		fread(&n, 1, 1, fLabel);
		labelV.push_back((int)n);
	}

	fclose(fData);
	fclose(fLabel);


	if (mode) {
		network->Learn(inputV, labelV, LEARNRATE);
		if (SaveFile != "0")
			network->SaveToFile(SaveFile);
	}
	else
		network->Test(inputV, labelV);

	for (int i = 0; i < fileLen; i++) {
		delete inputV[i];
	}
}




int DrawingBoard::GetNum()
{
	double* nnInput = new double[28 * 28];
	for (int i = 0; i < PIXELLEN; i++) {
		for (int j = 0; j < PIXELLEN; j++) {
			nnInput[i * PIXELLEN + j] = board[i][j];
		}
	}
	int ans = network->Calc(nnInput);
	text.setString(to_string(ans));
	delete [] nnInput;
	return ans;
}
