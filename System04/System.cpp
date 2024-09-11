#include <iostream>
#include <string>
#include <fstream> // 添加fstream库用于文件操作
using namespace std;
#define MAX 1000

class Person {
private:
    string name;
    string number;

public:
    Person() : name(""), number("") {}
    Person(string n, string num) : name(n), number(num) {}

    void setName(string n) { name = n; }
    void setNumber(string num) { number = num; }
    string getName() { return name; }
    string getNumber() { return number; }

    void display() {
        cout << "名前：" << name << " 電話番号：" << number << endl;
    }

    string formatData() {
        return name + " " + number + "\n"; // 将联系人信息格式化为字符串
    }
};

void showMenu() {
    cout << "**********************" << endl;
    cout << "******１・新　規******" << endl;
    cout << "******２・一　覧******" << endl;
    cout << "******３・削　除******" << endl;
    cout << "******４・検　索******" << endl;
    cout << "******５・編　集******" << endl;
    cout << "******６・クリア******" << endl;
    cout << "******０・終　了******" << endl;
    cout << "**********************" << endl;
}

// 新規作成時にファイルに書き込む関数
void writeToFile(Person& p) {
    ofstream outFile("person_data.txt", ios::app); // 追記モードでファイルを開く
    if (outFile.is_open()) {
        outFile << p.formatData(); // データを書き込む
        outFile.close();
        cout << "ファイルに保存しました。" << endl;
    }
    else {
        cout << "ファイルを開くことができませんでした。" << endl;
    }
}

void createPerson(Person per[], int& j) {
    string name, number;
    cout << "名前を入力してください: ";
    cin >> name;
    cout << "電話番号を入力してください: ";
    cin >> number;
    per[j] = Person(name, number);
    writeToFile(per[j]); // ファイルに書き込む
    j++;
    cout << "新規登録しました" << endl;
}

void printPersons(Person per[], int j) {
    if (j != 0) {
        for (int i = 0; i < j; i++) {
            per[i].display();
        }
    }
    else {
        cout << "データがありません" << endl;
    }
}

void deletePerson(Person per[], int& j) {
    string name;
    cout << "削除したい名前を入力してください: ";
    cin >> name;
    int i;
    for (i = 0; i < j; i++) {
        if (per[i].getName() == name) {
            break;
        }
    }
    if (i < j) {
        for (; i < j - 1; i++) {
            per[i] = per[i + 1];
        }
        j--;
        cout << "削除しました" << endl;
    }
    else {
        cout << "この名前は存在しません" << endl;
    }
}

void findPerson(Person per[], int j) {
    string name;
    cout << "検索したい名前を入力してください: ";
    cin >> name;
    bool found = false;
    for (int i = 0; i < j; i++) {
        if (per[i].getName() == name) {
            per[i].display();
            found = true;
        }
    }
    if (!found) {
        cout << "この名前は存在しません" << endl;
    }
}

void modifyPerson(Person per[], int j) {
    string name;
    cout << "編集したい名前を入力してください: ";
    cin >> name;
    for (int i = 0; i < j; i++) {
        if (per[i].getName() == name) {
            string newName, newNumber;
            cout << "新しい名前を入力してください: ";
            cin >> newName;
            cout << "新しい電話番号を入力してください: ";
            cin >> newNumber;
            per[i].setName(newName);
            per[i].setNumber(newNumber);
            cout << "更新しました。";
            per[i].display();
            return;
        }
    }
    cout << "この名前は存在しません" << endl;
}

void clearPersons(Person per[], int& j) {
    j = 0;
    cout << "すべてのデータが消去されました" << endl;
}

int main() {
    int j = 0, a;
    Person per[MAX];
    while (true) {
        showMenu();
        cout << "操作を選んでください: ";
        cin >> a;
        switch (a) {
        case 0:
            cout << "ご利用いただきありがとうございました" << endl;
            return 0;
        case 1:
            if (j < MAX) {
                createPerson(per, j);
            }
            else {
                cout << "人数が上限に達しました" << endl;
            }
            break;
        case 2:
            printPersons(per, j);
            break;
        case 3:
            deletePerson(per, j);
            break;
        case 4:
            findPerson(per, j);
            break;
        case 5:
            modifyPerson(per, j);
            break;
        case 6:
            clearPersons(per, j);
            break;
        default:
            cout << "無効な操作です。再度選択してください。" << endl;
            break;
        }
    }
}
