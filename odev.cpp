#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// الصف الأساسي: اللاعب
class Player {
protected:
    string name;
    int score;

public:
    Player(const string& n) : name(n), score(0) {}

    virtual void move() {
        cout << name << " is moving to find a treasure..." << endl;
    }

    void addScore(int points) {
        score += points;
        cout << name << " found a treasure and earned " << points << " points!" << endl;
    }

    int getScore() const {
        return score;
    }

    string getName() const {
        return name;
    }

    void displayStatus() const {
        cout << name << " | Score: " << score << endl;
    }
};

// صف الباحث عن الكنز
class TreasureHunter : public Player {
private:
    int luck;

public:
    TreasureHunter(const string& n, int l) : Player(n), luck(l) {}

    void move() override {
        cout << name << " (Treasure Hunter) is moving carefully with luck level " << luck << "..." << endl;
    }

    int searchTreasure() {
        int points = rand() % (10 + luck); // النقاط تعتمد على مستوى الحظ
        return points;
    }
};

// صف المستكشف
class Explorer : public Player {
private:
    int explorationSkill;

public:
    Explorer(const string& n, int es) : Player(n), explorationSkill(es) {}

    void move() override {
        cout << name << " (Explorer) is exploring the area with skill level " << explorationSkill << "..." << endl;
    }

    int searchTreasure() {
        int points = rand() % (15 + explorationSkill); // النقاط تعتمد على مهارة الاستكشاف
        return points;
    }
};

// منطق اللعبة
void game() {
    // إعداد العشوائية
    srand(static_cast<unsigned int>(time(0)));

    // إنشاء اللاعبين
    TreasureHunter hunter("Hunter", 5); // الحظ = 5
    Explorer explorer("Explorer", 3);  // مهارة الاستكشاف = 3

    // عدد الجولات
    const int rounds = 5;

    cout << "Game Start! Treasure Hunt Begins!" << endl;

    for (int i = 1; i <= rounds; ++i) {
        cout << "\n--- Round " << i << " ---" << endl;

        // حركة اللاعبين
        hunter.move();
        explorer.move();

        // كل لاعب يبحث عن الكنز
        int hunterPoints = hunter.searchTreasure();
        int explorerPoints = explorer.searchTreasure();

        // تحديد الفائز بالجولة بشكل عشوائي
        if (rand() % 2 == 0) { // اختيار فائز عشوائي (0 للصياد، 1 للمستكشف)
            hunter.addScore(hunterPoints);
            cout << hunter.getName() << " wins this round!" << endl;
        } else {
            explorer.addScore(explorerPoints);
            cout << explorer.getName() << " wins this round!" << endl;
        }

        // عرض الحالة بعد الجولة
        hunter.displayStatus();
        explorer.displayStatus();
    }

    // إعلان النتيجة النهائية
    cout << "\n--- Final Scores ---" << endl;
    hunter.displayStatus();
    explorer.displayStatus();
    cout << "\n--- Game Over ---" << endl;
    if (hunter.getScore() > explorer.getScore()) {
        cout << "Hunter is the overall winner with " << hunter.getScore() << " points!" << endl;
    } else if (explorer.getScore() > hunter.getScore()) {
        cout << "Explorer is the overall winner with " << explorer.getScore() << " points!" << endl;
    } else {
        cout << "It's a tie! Both players scored " << hunter.getScore() << " points!" << endl;
    }
}

// الدالة الرئيسية
int main() {
    game();
    return 0;
}
