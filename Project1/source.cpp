#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "russian");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    const double e = 2.71828182845904523536;

    int day = 1;
    double maxBananaCost = 11.0;
    double minBananaCost = 1.1;
    int choiseM = 1;
    int choiseB = 1;
    double bLoos = 0.0;
    double rotChance = 1.5;

    double m = 5000.0;
    double b = 5.0;

    // Инициализация начальных значений
    uniform_real_distribution<> bp_dis(1.0, 4.0);
    double bp = round(bp_dis(gen) * 100) / 100;  // Округление до 2 знаков

    uniform_real_distribution<> l_dis(0.0, 1.0);
    double l = round(l_dis(gen) * 10) / 10;  // Округление до 1 знака

    int playercount;
    cout << "введите количество игроков" << endl;
    cin >> playercount;

    int* dayp = new int[playercount];
    for (int i = 0; i < playercount; i++) {
        dayp[i] = day;
        cout << dayp[i] << endl;
    }


    int* m1 = new int[playercount];
    for (int i = 0; i < playercount; ++i) {
        m1[i] = m;
        cout << m1[i] << endl;
    }

    int* b1 = new int[playercount];
    for (int i = 0; i < playercount; ++i) {
        b1[i] = b;
        cout << b1[i] << endl;
    }

    //uniform_real_distribution<> l_dis(0.0, 1.0);
    double* l1 = new double[playercount];
    for (int i = 0; i < playercount; i++) {
        l1[i]= round(l_dis(gen) * 10) / 10; // Округление до 1 знака
        cout << l1[i] << endl;
    }

    double* bp1 = new double[playercount];
    for (int i = 0; i < playercount; i++) {
        bp1[i] = round(bp_dis(gen) * 100) / 100;
        cout << bp1[i];
    }

    double robincrease = 0.5 / (1 + pow(e, -((m / 200) * (bp / 200))));

    double* robChance1 = new double[playercount];
    for (int i = 0; i < playercount; i++) {
        robChance1[i] = 0;
    }

    double* maxrobChance1 = new double[playercount];
    for (int i = 0; i < playercount; i++) {
        maxrobChance1[i] = 0;
    }
    
    for (int i = 0; i < playercount; i++) {
        while (m > 0) {
            cout << fixed << setprecision(2);
            cout << "Доброе утро сэр. Сегодня ваш " << dayp[i]
                << " день в торговле бананами. У вас " << m1[i]
                << " денег и " << b1[i] << " бананов. Цены на бирже бананов сегодня "
                << bp << " Цена за аренду сегодня: " << l << ".\n";

            cout << "Выберите что мы сегодня будем делать: Продавать бананы(1), Покупать бананы(2), Ничего не делать(3): ";
            string choise = 0;
            cin >> choise;

            if (choise == "1") {
                cout << "Продавать бананы\n";
                cout << "Сэр сколько бананов вы хотите продать? ";
                cin >> choiseB;

                if (choiseB > b) {
                    cout << "Сэр мне придется выпотрошить вас :(((\n";
                    break;
                }
                m = m - l + bp * choiseB;
                b -= choiseB;
            }
            else if (choise == "2") {
                cout << "Покупать бананы\n";
                cout << "Сэр сколько бананов вы хотите купить? ";
                cin >> choiseM;

                if (choiseM > m) {
                    cout << "Сэр мне придется выпотрошить вас :(((\n";
                    break;
                }
                b += choiseM;
                m = m - l - bp * choiseM;
            }
            else if (choise == "3") {
                cout << "Ничего не делать\n";
                cout << "Cэр можете отправиться в джакузи 3 раз за день до следующего дня\n";
                m -= l;
            }
            else {
                cout << "Сэр мне придется выпотрошить вас :(((\n";
                break;
            }
    }

    

        // Расчет шанса ограбления
        maxrobChance += 100 + dis(gen) * 0.033 - 0.015;
        maxrobChance += robincrease;
        uniform_real_distribution<> rob_dis(0.01, maxrobChance);
        robChance = rob_dis(gen);

        cout << "шанс грабежа: " << robChance << " макс шанс грабежа: " << maxrobChance << "\n";
        cout << "прирост грабежа: " << robincrease << "\n";

        uniform_real_distribution<> chance_dis(0.0, 100.0);
        if (robChance > chance_dis(gen)) {
            double loss = round(((m / 4) + bp + l / 10) * 100) / 100;
            cout << "ВАС ОГРАБИЛИ НА " << loss << " ДЕНЕГ!!!\n";
            m = round((m - loss) * 100) / 100;
            maxrobChance /= 1.8;
        }

        // Механика гниения
        if (rotChance > chance_dis(gen)) {
            uniform_real_distribution<> rot_dis(2.0, 10.0);
            bLoos = round(b / rot_dis(gen));
            b -= bLoos;
            cout << bLoos << " ВАШИХ БАНАНОВ СГНИЛО!!!\n";
            rotChance /= 2;
        }
        
        // Обновление экономики
        maxBananaCost += 0.013;
        minBananaCost += 0.0131;

        // Обновление цен
        uniform_real_distribution<> new_bp_dis(minBananaCost + 0.01, maxBananaCost);
        bp = round(new_bp_dis(gen) * 100) / 100;

        double l_max = bp + day / 4.0 + choiseM / (bp - minBananaCost + 1) + choiseB / (bp - minBananaCost + 1);
        uniform_real_distribution<> new_l_dis(0.0, l_max);
        l = round(new_l_dis(gen) * 10) / 10;

        day++;

    return 0;
}