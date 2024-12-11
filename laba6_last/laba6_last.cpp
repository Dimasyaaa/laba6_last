#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Student { // студики
public:
    int id;
    string name;

    Student(int id, const string& name) : id(id), name(name) {} // конструктор

    int getID() const { return id; } // геттеры
    void display() const { // инфа о студенте
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

class Professor { // профессионалы 
public:
    int id;
    string name;

    Professor(int id, const string& name) : id(id), name(name) {} // конструктор

    int getID() const { return id; } // геттер
    void display() const { // инфа о преподе
        cout << "ID: " << id << ", Name: " << name << endl;
    }

    void editProfessor() { // редактирование препода
        cout << "Редактирование профессора (ID: " << id << "). Введите новое имя: ";
        cin >> name;
    }
};

class Schedule { // расписание
public:
    vector<pair<string, string>> classes;  // вектор, содержащий пары (день, занятие)

    void addClass(const string& day, const string& className) { // метод для добавления в расписание по дню и названию занятия
        classes.push_back({ day, className });
    }

    void display() const { // инфа о расписании
        if (classes.empty()) {
            cout << "Расписание пусто.\n";
            return;
        }
        for (const auto& cls : classes) {
            cout << "День: " << cls.first << ", Занятие: " << cls.second << endl;
        }
    }
};

bool idExists(const vector<Student>& students, int id) { // ф-ия для проверки существования студента
    return any_of(students.begin(), students.end(), [id](const Student& s) { return s.getID() == id; }); // ф-ия any_of, чтобы проверить наличие студента с данным id
}

bool idExists(const vector<Professor>& professors, int id) { // ф-ия для проверки существования препода
    return any_of(professors.begin(), professors.end(), [id](const Professor& p) { return p.getID() == id; }); // ф-ия any_of, чтобы проверить наличие препода с данным id 
}

int main() {

    setlocale(LC_ALL, "rus");

    vector<Student> students;
    vector<Professor> professors;
    Schedule schedule;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить студента\n";
        cout << "2. Удалить студента\n";
        cout << "3. Добавить профессора\n";
        cout << "4. Удалить профессора\n";
        cout << "5. Редактировать профессора\n";
        cout << "6. Показать студентов\n";
        cout << "7. Показать профессоров\n";
        cout << "8. Добавить занятие в расписание\n";
        cout << "9. Показать расписание\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1: {
            int id;
            string name;
            cout << "Введите ID студента: ";
            cin >> id;
            cin.ignore();

            if (idExists(students, id)) {
                cout << "Ошибка: Студент с ID " << id << " уже существует.\n";
                break;
            }

            cout << "Введите имя студента: ";
            getline(cin, name);
            students.emplace_back(id, name);
            break;
        }
        case 2: {
            int id;
            cout << "Введите ID студента для удаления: ";
            cin >> id;
            students.erase(remove_if(students.begin(), students.end(),
                [id](const Student& s) { return s.getID() == id; }),
                students.end());
            break;
        }
        case 3: {
            int id;
            string name;
            cout << "Введите ID профессора: ";
            cin >> id;
            cin.ignore();

            if (idExists(professors, id)) {
                cout << "Ошибка: Профессор с ID " << id << " уже существует.\n";
                break;
            }

            cout << "Введите имя профессора: ";
            getline(cin, name);
            professors.emplace_back(id, name);
            break;
        }
        case 4: {
            int id;
            cout << "Введите ID препода для удаления: ";
            cin >> id;
            professors.erase(remove_if(professors.begin(), professors.end(),
                [id](const Professor& p) { return p.getID() == id; }),
                professors.end());
            break;
        }
        case 5: {
            int id;
            cout << "Введите ID препода для редактирования: ";
            cin >> id;
            bool found = false;
            for (auto& professor : professors) {
                if (professor.getID() == id) {
                    professor.editProfessor();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Препод с ID " << id << " не найден.\n";
            }
            break;
        }
        case 6: {
            if (students.empty()) {
                cout << "Список студентов пуст.\n";
            }
            else {
                for (const auto& student : students) {
                    student.display();
                }
            }
            break;
        }
        case 7: {
            if (professors.empty()) {
                cout << "Список преподов пуст.\n";
            }
            else {
                for (const auto& professor : professors) {
                    professor.display();
                }
            }
            break;
        }
        case 8: {
            string day, className;
            cout << "Введите день недели: ";
            getline(cin, day);
            cout << "Введите название занятия: ";
            getline(cin, className);

            if (day.empty() || className.empty()) {
                cout << "День недели и название занятия не могут быть пустыми.\n";
            }
            else {
                schedule.addClass(day, className);
                cout << "Занятие добавлено в расписание.\n";
            }
            break;
        }
        case 9: {
            schedule.display();
            break;
        }
        case 0:
            cout << "Выход из программы.\n";
            return 0; 
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
            break;
        }
    }

    return 0; 
}
