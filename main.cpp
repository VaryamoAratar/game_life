#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<Windows.h>



int main() {
	std::string vvod;
	std::ifstream fin("in.txt");


	if (fin.is_open()) {
		bool exit = 1;
		int rows = 0;
		int cols = 0;
		short generation = 1;

		fin >> vvod;
		rows = stoi(vvod);
		fin >> vvod;
		cols = stoi(vvod);

		// �������� ���� 
		char** pole = new char* [rows];
		char** poleTmp = new char* [rows];
		for (int i = 0; i < rows; i++)
		{
			pole[i] = new char[cols];
			poleTmp[i] = new char[cols];
		}
		// ���������� ���� ������� ��������
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) {
				pole[i][j] = '-';
				poleTmp[i][j] = '-';
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
				break;
			}
		}
		// ������� ���� � ��������� �������
		fin.close();

		// ������� ����, ������� ����� ���������, ������� � ������� ���������� ����� ������ � ������ ���
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
			std::cout << "Generation: " << generation << ' ' << "Alive cells: " << count << std::endl;
		}


		// ���������� ����� ������� �����


		// ���������� �������� � ��������� ����
				// ���� ���� �������
		while (exit)
		{
			if (generation > 1 && generation < 99)
			{
				exit = 0;
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						if (pole[i][j] != poleTmp[i][j])
							exit = 1;
					}
				}
			}
			else if (generation == 99)  exit = 0;
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
				// ���� ����� ������ ���, �� ����� ����
				if (count == 0)
				{
					generation++;
					std::cout << "Generation number: " << generation << ' ' << "Alive cells: " << count << std::endl;
					std::cout << "All cells are dead. Game Over";
					// ������� ������ �� ��� ��������
					for (int i = 0; i < rows; i++)
					{
						delete[] pole[i];
						delete[] poleTmp[i];
					}
					delete[] pole;
					delete[] poleTmp;
					return 0;
				}
				else
				{
					generation++;
					std::cout << "Generation: " << generation << ' ' << "Alive cells: " << count << std::endl;
				}
			}
		}

		//����� ���� ��� ���������

		//������� ������ ����� ������� ��������
		Sleep(500);
		system("cls");

		//������� ���� � ������� ���������� ����� ������
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
			generation++;
			std::cout << "Generation: " << generation << ' ' << "Alive cells: " << count << std::endl;
			std::cout << "The world has stagnated. Game Over";
		}
		// ������� ������ �� ��� ��������
		for (int i = 0; i < rows; i++)
		{
			delete[] pole[i];
			delete[] poleTmp[i];
		}
		delete[] pole;
		delete[] poleTmp;
	}
	else std::cout << "file_not_open!";
	return 0;
}