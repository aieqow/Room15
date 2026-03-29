#include <iostream>
using namespace std;


//базовый абстрактный класс
class Room
{
protected:
    int Number; //номер комнаты 
    int Count; //количество мест в комнате 
    double Price; //цена
    int CountOccupied; //количество занятых мест

public:
    //конструктор по умолчанию
    Room()
    {
        Number = 0;
        Count = 1;
        Price = 0;
        CountOccupied = 0;
    }


    //конструктор с параметрами 
    Room(int m_Number, int m_Count, double m_Price, int m_CountOccupied)
    {
        Number = m_Number;
        if (m_Count > 0)
            Count = m_Count;
        else
            Count = 1;

        if (m_Price >= 0)
            Price = m_Price;
        else
            Price = 0;

        if (m_CountOccupied >= 0 && m_CountOccupied <= Count)
            CountOccupied = m_CountOccupied;
        else
            CountOccupied = 0;
    }


    //виртуальный деструктор
    virtual ~Room()
    {
        cout << "Комната " << Number << " удалена" << endl;
    }


    //вирутальный метод вывода информации 
    virtual void printInfo()
    {
        cout << "Номер комнаты: " << Number << endl;
        cout << "Количество мест: " << Count << endl;
        cout << "Занято мест: " << CountOccupied << endl;
        cout << "Свободно мест: " << Count - CountOccupied << endl;
        cout << "Цена за ночь: " << Price << endl;
    }

    // геттеры
    int getNumber() const
    {
        return Number;
    }
    int getCount() const
    {
        return Count;
    }
    double getPrice() const
    {
        return Price;
    }
    int getCountOccupied() const
    {
        return CountOccupied;
    }

    // сеттеры
    void setPrice(double new_Price)
    {
        if (new_Price >= 0)
            Price = new_Price;
        else
            cout << "Цена не может быть отрицательной" << endl;
    }

    void setCount(int new_Count)
    {
        if (new_Count > 0)
            Count = new_Count;
        else
            cout << "Количество мест должно быть > 0" << endl;
    }


    //виртуальные методы подсчета стоимости и описания
    virtual void calcNightCost(int guests, int nights) = 0;
    virtual void getRoomDescription() = 0;
};


//класс общего номера 
class DormRoom : public Room
{
private:
    int twoLevelBeds; //количество двухъярусных кроватей
    bool Lockers; //количество шкафчиков

public:
    DormRoom(int m_Number, int m_Count, double m_Price, int m_CountOccupied,
        int m_twoLevelBeds, bool m_Lockers) : Room(m_Number, m_Count, m_Price, m_CountOccupied)
    {
        twoLevelBeds = m_twoLevelBeds;
        Lockers = m_Lockers;
    }

    void calcNightCost(int guests, int nights)
    {
        if (guests <= 0 || nights <= 0)
        {
            cout << "Некорректные данные" << endl;
            cout << "----------------" << endl;
            return;
        }

        if (guests > Count - CountOccupied)
        {
            cout << "Недостаточно свободных мест" << endl;
            cout << "----------------" << endl;
            return;
        }

        cout << "Количество гостей: " << guests << endl;
        cout << "Количество ночей: " << nights << endl;

        double result = Price * guests * nights;

        if (guests > 3)
        {
            double discount = 0.8;
            result = result * discount;
            cout << "Скидка для группы: 20%" << endl;
        }

        cout << "Стоимость: " << result << endl;
        cout << "----------------" << endl;
    }

    void getRoomDescription()
    {
        cout << "Общий номер с двухъярусными кроватями" << endl;
    }

    void printInfo()
    {
        Room::printInfo();
        cout << "Двухъярусных кроватей: " << twoLevelBeds << endl;
        cout << "Шкафчики: " << Lockers << endl;
    }
};


//класс приватной комнаты 
class PrivateRoom : public Room
{
private:
    bool Bathroom;
    bool TV;

public:
    PrivateRoom(int m_Number, int m_Count, double m_Price, int m_CountOccupied,
        bool m_Bathroom, bool m_TV) : Room(m_Number, m_Count, m_Price, m_CountOccupied)
    {
        Bathroom = m_Bathroom;
        TV = m_TV;
    }

    void calcNightCost(int guests, int nights)
    {
        if (guests <= 0 || nights <= 0)
        {
            cout << "Некорректные данные" << endl;
            cout << "----------------" << endl;
            return;
        }

        cout << "Количество гостей: " << guests << endl;
        cout << "Количество ночей: " << nights << endl;

        double result = Price * guests * nights;

        if (Bathroom)
            result = result + 300;

        if (TV)
            result = result + 600;

        cout << "Стоимость: " << result << endl;
        cout << "----------------" << endl;
    }

    void getRoomDescription()
    {
        cout << "Приватная комната" << endl;
    }

    void printInfo()
    {
        Room::printInfo();
        cout << "Санузел: " << Bathroom << endl;
        cout << "Телевизор: " << TV << endl;
    }
};



//дополнительные функции выбора 
int safeReadInt()
{
    int value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода. Введите число: ";
        }
        else
        {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}


//метод показа информации о всех комнатах
void showRooms(Room* rooms[], int count)
{
    if (count == 0)
    {
        cout << "Список пока что без записей.\n";
        return;
    }
    for (int i = 0; i < count; i++)
    {
        cout << "\nКомната с номером: " << i + 1 << endl;
        rooms[i]->getRoomDescription();
        rooms[i]->printInfo();
    }
}


//метод добавления комнат 
void addRoom(Room* rooms[], int& count)
{
    cout << "1 - Общая комната\n2 - Приватная комната\nВыбор: ";
    int type = safeReadInt();

    cout << "Номер комнаты: ";
    int num = safeReadInt();

    cout << "Количество мест: ";
    int places = safeReadInt();

    cout << "Цена: ";
    double price;
    cin >> price;

    if (type == 1)
    {
        rooms[count] = new DormRoom(num, places, price, 0, 2, true);
        count++;
    }
    else if (type == 2)
    {
        rooms[count] = new PrivateRoom(num, places, price, 0, true, true);
        count++;
    }
    else
    {
        cout << "Ошибка выбора\n";
    }
}


//метод удаления комнат
void deleteRoom(Room* rooms[], int& count)
{
    if (count == 0)
    {
        cout << "Нет комнат\n";
        return;
    }

    cout << "Введите номер (1-" << count << "): ";
    int index = safeReadInt();

    if (index < 1 || index > count)
    {
        cout << "Ошибка\n";
        return;
    }

    delete rooms[index - 1];

    for (int i = index - 1; i < count - 1; i++)
    {
        rooms[i] = rooms[i + 1];
    }

    count--;
}



int main()
{
    setlocale(LC_ALL, "RU");

    const int maximum = 100;
    Room* rooms[maximum];
    int count = 0;

    bool running = true;

    while (running)
    {
        cout << "\n     МЕНЮ     \n";
        cout << "1. Добавить комнату\n";
        cout << "2. Показать все\n";
        cout << "3. Удалить комнату\n";
        cout << "4. Рассчитать стоимость\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";

        int choice = safeReadInt();

        switch (choice)
        {
        case 1:
            addRoom(rooms, count);
            break;
        case 2:
            showRooms(rooms, count);
            break;
        case 3:
            deleteRoom(rooms, count);
            break;
        case 4:
        {
            if (count == 0)
            {
                cout << "Нет комнат\n";
                break;
            }

            cout << "Выберите комнату (от 1 до " << count << "): ";
            int i = safeReadInt();
            cout << "Количество гостей: ";
            int g = safeReadInt();
            cout << "Количество ночей: ";
            int n = safeReadInt();
            rooms[i - 1]->calcNightCost(g, n);
            break;
        }
        case 0:
            running = false;
            break;
        default:
            cout << "Ошибка\n";
        }
    }
    return 0;
}