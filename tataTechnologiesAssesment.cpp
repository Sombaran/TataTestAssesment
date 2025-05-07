/*
Sombaran_Coding test_C++ Middleware
*/


#include <iostream>
#include <vector>

using namespace std;

class BowlingGame {
private:
    vector<int> rolls;

public:
    void roll(int pins) {
        rolls.push_back(pins);
    }

    int score() {
        int totalScore = 0;
        int rollIndex = 0;

        // Calculate score for first 9 frames with bonuses
        for (int frame = 0; frame < 9; frame++) {
            if (isStrike(rollIndex)) { // Strike
                totalScore += 10 + strikeBonus(rollIndex);
                rollIndex += 1;
            } else if (isSpare(rollIndex)) { // Spare
                totalScore += 10 + spareBonus(rollIndex);
                rollIndex += 2;
            } else { // Open frame
                totalScore += frameScore(rollIndex);
                rollIndex += 2;
            }
        }

        // 10th frame scoring: no bonuses for strike or spare, just sum pins
        totalScore += tenthFrameScore(rollIndex);

        return totalScore;
    }

private:
    bool isStrike(int rollIndex) {
        return rolls[rollIndex] == 10;
    }

    bool isSpare(int rollIndex) {
        return rolls[rollIndex] + rolls[rollIndex + 1] == 10;
    }

    int strikeBonus(int rollIndex) {
        return rolls[rollIndex + 1] + rolls[rollIndex + 2];
    }

    int spareBonus(int rollIndex) {
        return rolls[rollIndex + 2];
    }

    int frameScore(int rollIndex) {
        return rolls[rollIndex] + rolls[rollIndex + 1];
    }

    int tenthFrameScore(int rollIndex) {
        int sum = 0;
        // The 10th frame can have 2 or 3 rolls
        // Just sum them, no bonus points for strike or spare
        for (size_t i = rollIndex; i < rolls.size(); i++) {
            sum += rolls[i];
        }
        return sum;
    }
};

int main() {
    BowlingGame game;
    vector<int> rolls;
    int pins;

    cout << "Enter rolls for each frame (10 frames):\n";

    for (int frame = 1; frame <= 10; frame++) {
        if (frame < 10) {
            // Frame 1 to 9
            cout << "Frame " << frame << ", Roll 1: ";
            while (!(cin >> pins) || pins < 0 || pins > 10) {
                cout << "Invalid input. Enter pins (0-10): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            rolls.push_back(pins);

            if (pins == 10) {
                // Strike, no second roll in this frame
                continue;
            }

            int maxPins = 10 - pins;
            cout << "Frame " << frame << ", Roll 2: ";
            while (!(cin >> pins) || pins < 0 || pins > maxPins) {
                cout << "Invalid input. Enter pins (0-" << maxPins << "): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            rolls.push_back(pins);
        } else {
            // 10th frame
            cout << "Frame 10, Roll 1: ";
            while (!(cin >> pins) || pins < 0 || pins > 10) {
                cout << "Invalid input. Enter pins (0-10): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            rolls.push_back(pins);

            cout << "Frame 10, Roll 2: ";
            int maxPins = (pins == 10) ? 10 : 10 - pins; // pins reset if strike
            while (!(cin >> pins) || pins < 0 || pins > maxPins) {
                cout << "Invalid input. Enter pins (0-" << maxPins << "): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            rolls.push_back(pins);

            // Check if a third roll is allowed (strike or spare in 10th frame)
            bool thirdRollAllowed = false;
            int firstRoll = rolls[rolls.size() - 2];
            int secondRoll = rolls[rolls.size() - 1];
            if (firstRoll == 10 || firstRoll + secondRoll == 10) {
                thirdRollAllowed = true;
            }

            if (thirdRollAllowed) {
                cout << "Frame 10, Roll 3: ";
                while (!(cin >> pins) || pins < 0 || pins > 10) {
                    cout << "Invalid input. Enter pins (0-10): ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                rolls.push_back(pins);
            }
        }
    }

    // Feed all rolls to the game
    for (int r : rolls) {
        game.roll(r);
    }

    cout << "Total score: " << game.score() << endl;

    return 0;
}

/*
Test output
Enter rolls for each frame (10 frames):
Frame 1, Roll 1: 10
Frame 2, Roll 1: 7
Frame 2, Roll 2: 3
Frame 3, Roll 1: 9
Frame 3, Roll 2: 0
Frame 4, Roll 1: 10
Frame 5, Roll 1: 0
Frame 5, Roll 2: 8
Frame 6, Roll 1: 8
Frame 6, Roll 2: 2
Frame 7, Roll 1: 0
Frame 7, Roll 2: 6
Frame 8, Roll 1: 10
Frame 9, Roll 1: 10
Frame 10, Roll 1: 10
Frame 10, Roll 2: 10
Frame 10, Roll 3: 10
Total score: 193
*/