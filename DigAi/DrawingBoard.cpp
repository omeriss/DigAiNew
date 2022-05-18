#include "DrawingBoard.h"

DrawingBoard::DrawingBoard()
{
	network2 = new Network({
	new FullyConnectedLayer(2025, 40),
	new Sigmoid(40),
	new FullyConnectedLayer(40, 40),
	new Sigmoid(40),
	new FullyConnectedLayer(40, 40),
	new Sigmoid(40),
	new FullyConnectedLayer(40, 14),
	new Sigmoid(14),
		}, 2025, 14, "cool.dat");
	if (UploadFile == "0")
		network = new NeuralNetwork();
	else {
		network = new NeuralNetwork(UploadFile);
	}

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
		//for (int i = n - 1; i <= n + 1; i++) {
		//	for (int j = m - 1; j <= m + 1; j++) {
		//		printf("%d %d\n", i, j);
		//		if (i >= 0 && i < PIXELLEN && j >= 0 && j < PIXELLEN) {
		//			float xx = j * PIXELSIZE + PIXELSIZE / 2.0;
		//			float yy = i * PIXELSIZE + PIXELSIZE / 2.0;
		//			this->board[i][j] += 1 - std::min((double)1, (sqrt(pow(x - xx, 2) + pow(y - yy, 2))) / ((3.0 / 4.0) * (2 * sqrt(2 * PIXELSIZE * PIXELSIZE))));
		//			if (board[i][j] > 1)
		//				board[i][j] = 1;
		//		}
		//	}
		//}
		if (x > 0 && x <= SCREENSIZE && y > 0 && y <= SCREENSIZE)
			board[(int)(y / PIXELSIZE)][(int)(x / PIXELSIZE)] = 1.0;
		lastX = x;
		lastY = y;
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

using std::string;
void DrawingBoard::InsertInput2(string path)
{
	vector<double*> inputV;
	vector<int> labelV;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9000; j++) {
			sf::Image img;
			img.loadFromFile(path + "\\" + std::to_string(i) + "\\" + std::to_string(j) + ".jpg");
			double* temp = new double[45 * 45];
			for (int k = 0; k < 45 * 45; k++) {
				int n = 255 - (img.getPixel(k / 45, k % 45).r + img.getPixel(k / 45, k % 45).g + img.getPixel(k / 45, k % 45).b)/3;
				temp[k] = (double)n / 255;
			}
			cout<<i<<" " << j << endl;
			inputV.push_back(temp);
			labelV.push_back(i);
		}
	}

	network->Learn(inputV, labelV, LEARNRATE);
	if (SaveFile != "0")
		network->SaveToFile(SaveFile);

	int count = 0;
	for (int i = 0; i < inputV.size(); i++) {
		auto output = network->Calc(inputV[i]);
		int maxn = 0;
		for (int i = 1; i < output.size(); i++) {
			if (output[i] > output[maxn])
				maxn = i;
		}
		if (maxn == labelV[i])
			count++;
	}
	std::cout << count * 1.0 / inputV.size();
}

void DrawingBoard::InsertInput3(string path)
{
	vector<double*> inputV;
	vector<int> labelV;
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 9000; j++) {
			sf::Image img;
			img.loadFromFile(path + "\\" + std::to_string(i) + "\\" + std::to_string(j) + ".jpg");
			double* temp = new double[45 * 45];
			for (int k = 0; k < 45 * 45; k++) {
				int n = 255 - (img.getPixel(k / 45, k % 45).r + img.getPixel(k / 45, k % 45).g + img.getPixel(k / 45, k % 45).b) / 3;
				temp[k] = (double)n / 255;
			}
			cout << i << " " << j << endl;
			inputV.push_back(temp);
			labelV.push_back(i);
		}
	}

	network2->Learn(inputV, labelV,disCostDerivative, 10, 0.5, SetSize, "coolnn.dat");
	//if (SaveFile != "0")
	//network2->SaveToFile(SaveFile);
	//network->Test(inputV, labelV);

	int count = 0;
	for (int i = 0; i < inputV.size(); i++) {
		auto output = network2->FeedForword(inputV[i]);
		int maxn = 0;
		for (int i = 1; i < output.size(); i++) {
			if (output[i] > output[maxn])
				maxn = i;
		}
		if (maxn == labelV[i])
			count++;
	}
	std::cout << count * 1.0 / inputV.size();
}


int DrawingBoard::GetNum()
{
	double* nnInput = new double[PIXELLEN*PIXELLEN];
	for (int i = 0; i < PIXELLEN; i++) {
		for (int j = 0; j < PIXELLEN; j++) {
			nnInput[i + j * PIXELLEN] = board[i][j];
		}
	}

	auto output = network2->FeedForword(nnInput);
	int maxn = 0;
	for (int i = 1; i < output.size(); i++) {
		if (output[i] > output[maxn])
			maxn = i;
	}
	int ans = maxn;
	text.setString(to_string(ans));
	delete [] nnInput;
	return ans;
}
