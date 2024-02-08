#include <iostream>
#include <vector>
#include <cstdlib> 
#include <limits> 

int knapSack(int W, std::vector<int> &berat, std::vector<int> &nilai, int n)
{
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int w = 1; w <= W; ++w)
        {
            if (berat[i - 1] <= w)
                dp[i][w] = std::max(nilai[i - 1] + dp[i - 1][w - berat[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

void clearScreenWindows()
{
    system("cls");
}

void clearScreenUnix()
{
    system("clear");
}

void clearScreen()
{
    #ifdef _WIN32 
        clearScreenWindows();
    #else
        clearScreenUnix();
    #endif
}

void clearCin()
{
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

bool inputInt(int &value, std::string prompt)
{
    std::cout << prompt;
    while (!(std::cin >> value))
    {
        clearCin();
        std::cout << "Input tidak valid, masukkan angka. Coba lagi.\n" << prompt;
    }
    return true;
}

void displayCenteredTitle(std::string title)
{
    int titleLength = title.length();
    int tableWidth = 31; 

    int padding = (tableWidth - titleLength) / 2;

    std::cout << "+-------------------------------+\n";
    std::cout << "|";
    std::cout << std::string(padding, ' ');
    std::cout << title;
    std::cout << std::string(padding + (tableWidth - titleLength) % 2, ' ');
    std::cout << "|\n";
    std::cout << "+-------------------------------+\n";
}

void displayMenu()
{
    clearScreen();
    displayCenteredTitle("MENU UTAMA");
    std::cout << "| 1. Input Data Knapsack        |\n";
    std::cout << "| 2. Keluar Program             |\n";
    std::cout << "+-------------------------------+\n";
    std::cout << "Pilih opsi (1-2): ";
}

void inputAndCalculate()
{
    int n, W;
    bool validInput = false;

    do {
        clearScreen();
        displayCenteredTitle("INPUT DATA KNAPSACK");

        inputInt(n, "Masukkan jumlah item: ");
        std::vector<int> berat(n), nilai(n);

        for (int i = 0; i < n; ++i)
        {
            std::cout << "Item " << i + 1 << ":\n";
            std::cout << "   Berat: ";
            while (!(std::cin >> berat[i]))
            {
                clearCin();
                std::cout << "Input tidak valid, masukkan angka. Coba lagi.\n";
                std::cout << "   Berat: ";
            }

            std::cout << "   Nilai: ";
            while (!(std::cin >> nilai[i]))
            {
                clearCin();
                std::cout << "Input tidak valid, masukkan angka. Coba lagi.\n";
                std::cout << "   Nilai: ";
            }
        }

        std::cout << "Masukkan kapasitas knapsack: ";
        validInput = inputInt(W, "");

        if (validInput) {
            int result = knapSack(W, berat, nilai, n);
            clearScreen();
            displayCenteredTitle("HASIL KEUNTUNGAN MAKSIMUM");
            std::cout << "| Keuntungan maksimum: " << result << std::endl;
            std::cout << "+-------------------------------+\n";
            std::cout << "Tekan Enter untuk kembali ke menu...";
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "Input kapasitas knapsack tidak valid. Coba lagi.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Tekan Enter untuk kembali ke menu...";
            std::cin.get();
        }
    } while (!validInput);
}

int main()
{
    int choice;
    while (true)
    {
        displayMenu();
        if (!inputInt(choice, "")) continue;

        switch (choice)
        {
        case 1:
            inputAndCalculate();
            break;
        case 2:
            std::cout << "Keluar dari program...\n";
            return 0;
        default:
            std::cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    }
    return 0;
}
