#include<iostream> 

#include<vector> 

#include<string> 

using namespace std;

class Game
{
public:
    void create() 
    {
        cout << "Create game Krestiki-noliki " << endl;
    }

    void open(string file) {
        cout << "Open game from " << file << endl;
    }

    void save(string file) 
    {
        cout << "Save game in " << file << endl;
    }

    void make_move(string move) 
    {
        cout << "Make move " << move << endl;
    }

};
string win[9];
int z = 0;
void winner()
{
    // 00 01 02
    // 10 11 12
    // 20 21 22
    
    
}


int getPlayerInput(string prompt) 
{

    int input1,input2;
    
    cout << prompt;
    cin >> input1;
    if (z % 2 == 0)
    {
        win[input1] = "+";
        cout << "First player win!";
        exit(0);
    }
    else
    {
        win[input1] = "-";
       
    }
    z++;
    return input1;

}



// Базовый класс 

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
protected:
    Command(Game* p) : pgame(p) {}
    Game* pgame;
};



class CreateGameCommand : public Command
{
public:
    CreateGameCommand(Game* p) : Command(p) {}
    void execute() {
        pgame->create();
    }

};



class OpenGameCommand : public Command

{
public:
    OpenGameCommand(Game* p) : Command(p) {}
    void execute() {
        string file_name;
        file_name = getPlayerInput("Enter file name:");
        pgame->open(file_name);

    }

};



class SaveGameCommand : public Command

{

public:
    SaveGameCommand(Game* p) : Command(p) {}
    void execute() {

        string file_name;

        file_name = getPlayerInput("Enter file name:");

        pgame->save(file_name);

    }

};



class MakeMoveCommand : public Command

{
public:
    MakeMoveCommand(Game* p) : Command(p) {}
    void execute() { 
        string move;
        move = getPlayerInput("Enter your move:");
        pgame->make_move(move);

    }

};



class UndoCommand : public Command
{
public:
    UndoCommand(Game* p) : Command(p) {}
    void execute() {
        // Восстановим игру из временного файла 
        pgame->open("TEMP_FILE");
    }

};
void gamemap()
{
    
    for (int i = 1; i < 11; i++)
    {
        cout << win[i-1] << "\t";
        if (i%3==0)
        cout << endl;
    }
}




int main()

{
    Game game;
    // Имитация действий игрока 

    vector<Command*> v;
    for (int i = 0; i < 9; i++)
        win[i] = "0";
    
    // Создаем новую игру  
    v.push_back(new CreateGameCommand(&game));
    
    for (int i = 0; i < 9; i++)
    {
        v.push_back(new MakeMoveCommand(&game));
        

    }
    v.push_back(new SaveGameCommand(&game));

    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i]->execute();
        gamemap();
    }
    

    for (size_t i = 0; i < v.size(); ++i)

        delete v[i];



    return 0;

}