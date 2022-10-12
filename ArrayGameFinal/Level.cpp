#include "Level.h"
#include <iostream>
#include <fstream>
using namespace std;


constexpr char WAL = (char)219;
constexpr char KEY = (char)232;
constexpr char DOR = (char)179;
constexpr char GOL = (char)36;

Level::Level()
    : m_pLevelData(nullptr)
    , m_height(0)
    , m_width(0)
{
}
Level::~Level()
{
    if (m_pLevelData != nullptr)
    {
        delete[] m_pLevelData;
        m_pLevelData = nullptr;
    }
}
// loads file into array for game
bool Level::Load(string LevelName, int* playerX, int* playerY)
{
    // requires ifstream library
    LevelName.insert(0, "../");
    ifstream LevelFile;
    LevelFile.open(LevelName);
    if (!LevelFile)
    {
        cout << "Couldn't open level file" << endl;
        return false;
    }
    else
    {
        constexpr int tempSize = 100;
        char temp[tempSize];

        // gives us the first line
        LevelFile.getline(temp, tempSize, '\n');
        // convets temp array into a interger
        m_width = atoi(temp);

        LevelFile.getline(temp, tempSize, '\n');
        // convets temp array into a interger
        m_height = atoi(temp);

        m_pLevelData = new char[static_cast<__int64>(m_width) * m_height];
        LevelFile.read(m_pLevelData, (long long)m_width * (long long)m_height);


        bool anyWarnings = Convert(playerX,playerY);
        if (anyWarnings)
        {
            
            cout << "There were some warnings int the level data, seee above" << endl;
            system("pause");
        }
        return true;
   }
}

void Level::Draw(int x, int y)
{
    int index = GetIndexFromCordinates(x, y);
    cout << m_pLevelData[index];

}
bool Level::isSpace(int x, int y)
{
    return m_pLevelData[GetIndexFromCordinates(x, y)] == ' ';
}
bool Level::isDoor(int x, int y)
{
    return m_pLevelData[GetIndexFromCordinates(x, y)] == DOR;

}
bool Level::isKey(int x, int y)
{
    return m_pLevelData[GetIndexFromCordinates(x, y)] == KEY;

}
bool Level::isGoal(int x, int y)
{
    return m_pLevelData[GetIndexFromCordinates(x, y)] == GOL;
}
void Level::PickUpKey(int x, int y)
{
    m_pLevelData[GetIndexFromCordinates(x, y)] = ' ';
}
void Level::OpenDoor(int x, int y)
{
    m_pLevelData[GetIndexFromCordinates(x, y)] = 'O';
}

bool Level::Convert(int* playerX, int* playerY)
{   
    bool anyWarnings = false;
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int index = GetIndexFromCordinates(x, y);

            switch (m_pLevelData[index])
            {
            case '+':
            case '_':
            case '-':
            case '|':
                m_pLevelData[index] = WAL;
                break;
            case '*':
                m_pLevelData[index] = KEY;
                break;
            case 'D':
            case 'd':
                m_pLevelData[index] = DOR;
            case 'X':
            case 'x':
                m_pLevelData[index] = GOL;
            case '@':
                m_pLevelData[index] = ' ';
                if (playerX != nullptr && playerY != nullptr)
                {
                    *playerX = x;
                    *playerY = y;
                }
                break;
            case ' ':
                break;
            default:
                cout << "invalid char in level file:" << m_pLevelData[index] << endl;
                anyWarnings = true;
                break;
            }
        }
        
    }return anyWarnings;
}

int Level::GetIndexFromCordinates(int x, int y)
{
    return x + (y * m_width);
}
