#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<Windows.h>


void fClean(char** pole, char** poleTmp, char** poleTmpC, int rows) // ������� ������
{
	for (int i = 0; i < rows; i++)
	{
		delete[] pole[i];
		delete[] poleTmp[i];
		delete[] poleTmpC[i];
	}
	delete[] pole;
	delete[] poleTmp;
	delete[] poleTmpC;
}
int printPole(char** pole, char** poleTmp, char** poleTmpC, int rows, int cols, short& generation) //����� ���� �� �������
{
	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << pole[i][j] << ' ';
			if (pole[i][j] == '*') count++;
		}
		std::cout << std::endl;
	}
	if (count == 0)
	{
		generation++;
		std::cout << "Generation number: " << generation << ' ' << "Alive cells: " << count << std::endl;
		std::cout << "All cells are dead. Game Over";
		fClean(pole, poleTmp, poleTmpC, rows);
		return 0;
	}
	else
	{
		generation++;
		std::cout << "Generation: " << generation << ' ' << "Alive cells: " << count << std::endl;
	}
	return count;
}

int main()
{
	std::string vvod;
	std::ifstream fin("in.txt");


	if (fin.is_open())
	{
		int count = 0;

		bool exit = 1;
		int rows = 0;
		int cols = 0;
		short generation = 0;

		fin >> vvod;
		rows = stoi(vvod);
		fin >> vvod;
		cols = stoi(vvod);

		// �������� ���� 
		char** pole = new char* [rows];
		char** poleTmp = new char* [rows];
		char** poleTmpC = new char* [rows];
		for (int i = 0; i < rows; i++)
		{
			pole[i] = new char[cols];
			poleTmp[i] = new char[cols];
			poleTmpC[i] = new char[cols];
		}
		// ���������� ���� ������� ��������
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) {
				pole[i][j] = '-';
				poleTmp[i][j] = '-';
				poleTmpC[i][j] = '-';
			}
		}
		// ���������� ���� ������ ��������
		while (fin >> vvod)
		{
			int i = stoi(vvod);
			while (fin >> vvod)
			{
				int j = stoi(vvod);
				pole[i][j] = '*';
				poleTmp[i][j] = '*';
				poleTmpC[i][j] = '-';
				break;
			}
		}
		// ������� ���� � ��������� �������
		fin.close();

		// ������� ����, ������� ����� ���������, ������� � ������� ���������� ����� ������ � ������ ���
		printPole(pole, poleTmp, poleTmpC, rows, cols, generation);

		// ���������� ����� ������� �����


		// ���������� �������� � ��������� ����
				// ���� ���� �������
		while (exit)
		{
			if (generation > 1 && generation < 999)
			{
				exit = 0;
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{

						if (pole[i][j] != poleTmp[i][j])
						{
							exit = 1;
						}
					}
				}
			}
			// ���� ������� ����� ��������
			else if (generation == 999)
				//������� ������ ����� ������� �������� ��������
			{
				Sleep(500);
				system("cls");
				//������� ��������� ����, ��������� � ������� ���������� ����� ������

				count = printPole(pole, poleTmp, poleTmpC, rows, cols, generation);
				if (count == 0)
				{
					fClean(pole, poleTmp, poleTmpC, rows);
					return 0;
				}
				else
				{
					std::cout << "the end of the world. Game Over";
					fClean(pole, poleTmp, poleTmpC, rows);
					return 0;
				}
			}
			// ���� �������������, ����� ���������� � ���������� ����������

			if (!generation % 2)
			{
				int cicle = 0;
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						if (pole[i][j] == poleTmpC[i][j])
						{
							cicle++;
						}
					}
				}
				if (cicle == (rows * cols))
				{
					//������� ������ ����� ������� �������� ��������
					Sleep(500);
					system("cls");
					count = printPole(pole, poleTmp, poleTmpC, rows, cols, generation);
					if (count == 0)
					{
						fClean(pole, poleTmp, poleTmpC, rows);
						return 0;
					}
					else
					{
						std::cout << "the world is looped. Game Over";
						fClean(pole, poleTmp, poleTmpC, rows);
						return 0;
					}
				}
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						if (pole[i][j] != poleTmpC[i][j])
						{
							poleTmpC[i][j] = pole[i][j];
						}
					}
				}
			}




			// ���������� ������� ��������� 
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					poleTmp[i][j] = pole[i][j];
				}
			}
			// ��������� ��������� ������
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					// ���� ������ �����, �� ��������, �� ����� �� ���. �������: ������ ������ ������ 2� ��� ������ 3� ����� ������
					if (poleTmp[i][j] == '*')
					{
						// ������� ����� ����
						if (i == 0 && j == 0)
						{
							int count = 0;
							for (int k = i; k < i + 2; k++)
							{
								for (int h = j; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ������� ������ ����
						else if (i == 0 && j == cols - 1)
						{
							int count = 0;
							for (int k = i; k < i + 2; k++) {
								for (int h = j - 2; h < j; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ������ ����� ����
						else if (i == rows - 1 && j == 0)
						{
							int count = 0;
							for (int k = i - 2; k < i; k++)
							{
								for (int h = j; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ������ ������ ����
						else if (i == rows - 1 && j == cols - 1)
						{
							int count = 0;
							for (int k = i - 2; k < i; k++)
							{
								for (int h = j - 2; h < j; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ������� ������
						else if (i == 0 && j > 0 && j < cols - 1)
						{
							int count = 0;
							for (int k = i; k < i + 2; k++)
							{
								for (int h = j - 1; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ������ ������
						else if (i == rows - 1 && j > 0 && j < cols - 1)
						{
							int count = 0;
							for (int k = i - 2; k < i; k++)
							{
								for (int h = j - 1; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ����� �������
						else if (i > 0 && i < rows - 1 && j == 0)
						{
							int count = 0;
							for (int k = i - 1; k < i + 2; k++)
							{
								for (int h = j; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ������ �������
						else if (i > 0 && i < rows - 1 && j == cols - 1)
						{
							int count = 0;
							for (int k = i - 1; k < i + 2; k++)
							{
								for (int h = j - 2; h < j; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
						// ��������� ����
						else
						{
							int count = 0;
							for (int k = i - 1; k < i + 2; k++)
							{
								for (int h = j - 1; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count < 3 || count > 4) pole[i][j] = '-';
						}
					}
					// ���� ������ ������, ��������, ��������� �� �����. �������: ������ ������ ������ ����� 3 ����� �����
					else
					{
						// ������� ����� ����
						if (i == 0 && j == 0)
						{
							int count = 0;
							for (int k = i; k < i + 2; k++)
							{
								for (int h = j; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ������� ������ ����
						else if (i == 0 && j == cols - 1)
						{
							int count = 0;
							for (int k = i; k < i + 2; k++)
							{
								for (int h = j - 2; h < j; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ������ ����� ����
						else if (i == rows - 1 && j == 0)
						{
							int count = 0;
							for (int k = i - 2; k < i; k++)
							{
								for (int h = j; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ������ ������ ����
						else if (i == rows - 1 && j == cols - 1)
						{
							int count = 0;
							for (int k = i - 2; k < i; k++)
							{
								for (int h = j - 2; h < j; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ������� ������
						else if (i == 0 && j > 0 && j < cols - 1)
						{
							int count = 0;
							for (int k = i; k < i + 2; k++)
							{
								for (int h = j - 1; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ������ ������
						else if (i == rows - 1 && j > 0 && j < cols - 1)
						{
							int count = 0;
							for (int k = i - 2; k < i; k++)
							{
								for (int h = j - 1; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ����� �������
						else if (i > 0 && i < rows - 1 && j == 0)
						{
							int count = 0;
							for (int k = i - 1; k < i + 2; k++)
							{
								for (int h = j; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ������ �������
						else if (i > 0 && i < rows - 1 && j == cols - 1)
						{
							int count = 0;
							for (int k = i - 1; k < i + 2; k++)
							{
								for (int h = j - 2; h < j; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
						// ��������� ����
						else
						{
							int count = 0;
							for (int k = i - 1; k < i + 2; k++)
							{
								for (int h = j - 1; h < j + 2; h++)
									if (poleTmp[k][h] == '*') count++;
							}
							if (count == 3) pole[i][j] = '*';
						}
					}
				}
			}

			//������� ������ ����� ������� �������� ��������
			Sleep(500);
			system("cls");

			//������� ��������� ����, ��������� � ������� ���������� ����� ������
			{
				count = printPole(pole, poleTmp, poleTmpC, rows, cols, generation);
				if (count == 0)
				{
					fClean(pole, poleTmp, poleTmpC, rows);
					return 0;
				}
			}
		}

		//����� ���� ��� ���������

		//������� ������ ����� ������� ��������
		Sleep(500);
		system("cls");

		//������� ���� � ������� ���������� ����� ������
		{
			count = printPole(pole, poleTmp, poleTmpC, rows, cols, generation);
			std::cout << "The world has stagnated. Game Over";
		}
		fClean(pole, poleTmp, poleTmpC, rows);
	}
	else std::cout << "file_not_open!";
	return 0;
}