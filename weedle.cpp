#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\x1b[42m"
#define YELLOW "\x1b[43m"
#define RED "\x1b[41m"
#define RESET "\e[0;39m"

class Player
{
private:
    string college;
    string name;
    string height;
    string weight;
    string position;
    string team;
    string num;
    string age;
    string exp;
public:
    Player()
    {
        //cout << "New player created\n";
        college = "";
        name = "";
        height = "";
        weight = "";
        position = "";
        team = "";
        num = "";
        age = "";
        exp = "";
    }
    Player(string in_name, map<string, string> data)
    {
        //cout << "New player created\n";
        name = in_name;
        height = data["height"];
        weight = data["weight"];
        position = data["pos"];
        team = data["team"];
        college = data["college"];
        num = data["num"];
        age = data["age"];
        exp = data["exp"];
    }
    void set_name(string in_name)
    {
        this->name = in_name;
    }
    void set_college(string in_college)
    {
        this->college = in_college;
    }
    void set_height(string in_height)
    {
        this->height = in_height;
    }
    void set_weight(string in_weight)
    {
        this->weight = in_weight;
    }
    void set_position(string in_pos)
    {
        this->position = in_pos;
    }
    void set_team(string in_team)
    {
        this->team = in_team;
    }
    void set_num(string in_num)
    {
        this->num = in_num;
    }
    void set_age(string in_age)
    {
        this->age = in_age;
    }
    void set_exp(string in_exp)
    {
        this->exp = in_exp;
    }
    string get_name()
    {
        return name;
    }
    string get_weight()
    {
        return weight;
    }
    string get_team()
    {
        return team;
    }
    string get_num()
    {
        return num;
    }
    string get_height()
    {
        return height;
    }
    string get_position()
    {
        return position;
    }
    string get_age()
    {
        return age;
    }
    string get_exp()
    {
        return exp;
    }
    string get_college()
    {
        return college;
    }
    void print()
    {
        cout << name << "\n";
        cout << "\t" << num << "\n";
        cout << "\t" << team << "\n";
        cout << "\t" << position << "\n";
        cout << "\t" << age << "\n";
        cout << "\t" << height << "\n";
        cout << "\t" << weight << "\n";
        cout << "\t" << exp << "\n";
        cout << "\t" << college << "\n";
    }
};

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void print_guess(string guess[], int status[])
{
    for (int i = 0; i < 5; i++)
    {
        if (status[i] == EXACT)
        {
            cout << GREEN  << guess[i] << RESET "\t";
        }
        else if (status[i] == CLOSE)
        {
            cout << YELLOW  << guess[i] << RESET "\t";
        }
        else
        {
            cout << RED  << guess[i] << RESET "\t";
        }
    }
    cout << RESET "\n";
    return;
}

map<string, Player*> get_players() 
{
    map<string, Player*> player_map;
    string player_filename = "nfl_players.json";
    ifstream player_list; 
    player_list.open(player_filename);
    if (!player_list)
    {
        cout << "Error opening file " << player_filename << "\n";
        return player_map;
    }
    string key_name = "";
    int player_count = 0;
    if (player_list.is_open())
    {
        int i = 0;
        while (player_list)
        { 
            string in_word;
            getline(player_list, in_word);
            string key;
            string val;
            bool found_key = false;
            bool found_val = false;
            if (in_word == "{" || in_word == "}" || in_word == "    },")
            {
                continue;
            }
            if (hasEnding(in_word, ": {"))
            {
                string name = in_word.substr(5, in_word.size() - 9);
                string name_to_lower = "";
                for (int i = 0; i < name.length(); i++)
                {
                    name_to_lower += tolower(name[i]);
                }
                key_name = name_to_lower;
                player_map[name_to_lower] = new Player();
                player_map[name_to_lower]->set_name(name_to_lower);
                continue;
            }
            
            for(int i = 0; i < in_word.size(); i++)
            {
                if (in_word[i] == '\"')
                {
                    found_key = true;
                }
                if (in_word[i] == ':')
                {
                    found_val = true;
                }
                if (found_key)
                {
                    if (in_word[i] != '\"')
                    {
                        key += in_word[i];
                    }
                    else if (key.size() > 0)
                    {
                        found_key = false;
                    }
                }
                if (found_val)
                {

                    if (in_word[i] != '\"' && in_word[i] != ':' && in_word[i] != ',' && in_word[i] != ' ' && in_word[i] != '\\')
                    {
                        val += in_word[i];
                    }
                }
            }
            //cout << i << ") " << key << " : " << val << "\n";
            if (key == "team")
            {
                player_map[key_name]->set_team(val);
            }
            if (key == "pos")
            {
                player_map[key_name]->set_position(val);
            }
            if (key == "age")
            {
                player_map[key_name]->set_age(val);
            }
            if (key == "height")
            {
                val += "\"";
                player_map[key_name]->set_height(val);
            }
            if (key == "weight")
            {
                player_map[key_name]->set_weight(val);
            }
            if (key == "exp")
            {
                player_map[key_name]->set_exp(val);
            }
            else if (key == "num")
            {
                player_map[key_name]->set_num(val);
            }
            else if (key == "college")
            {
                player_map[key_name]->set_college(val);
                player_count++;
            }
            i++;
        }
    }
        return player_map;
}

string get_guess()
{
    string guess = "";
    cout << "Input a player: ";
    getline(cin, guess);
    return guess;
}

// TODO
int check_player(Player* guess, int status[], Player* choice)
{
    int score = 0;

    //check team
    if (guess->get_team() == choice->get_team())
    {
        status[0] = EXACT;
        score += EXACT;
    }
    else
    {
        //TODO check division
         status[0] = WRONG;
    }
    if (guess->get_num() == choice->get_num())
    {
        status[1] = EXACT;
        score += EXACT;
    }
    else
    {
         status[1] = WRONG;
    }
    if (guess->get_position() == choice->get_position())
    {
        status[2] = EXACT;
        score += EXACT;
    }
    else
    {
         status[2] = WRONG;
    }
    if (guess->get_age() == choice->get_age())
    {
        status[3] = EXACT;
        score += EXACT;
    }
    else
    {
         status[3] = WRONG;
    }
    if (guess->get_height() == choice->get_height())
    {
        status[4] = EXACT;
        score += EXACT;
    }
    else
    {
         status[4] = WRONG;
    }
    return score;
}



int main()
{
    map<string, Player*> players = get_players();
    Player * choice = players["maxx crosby"];

    //srand( static_cast<unsigned int>(time(nullptr)));
    //Player *answer = players[rand() % players.size()];
    //cout << "Answer: " << answer->get_name() << "\n";
    bool won = false;
    int guesses = 8;

    // print greeting, using ANSI color codes to demonstrate
    cout << GREEN "This is WEEDLE" RESET "\n";
    cout << "You have " << guesses << " tries to guess the NFL player I'm thinking of\n";

    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess();
        while (players.count(guess) == 0)
        {
            cout << guess << " not a real player\n";
            guess = get_guess();
        }
        

        // array to hold guess status, initially set to zero
        int status[5];

        // Calculate score for the guess
        int score = check_player(players[guess], status, choice);

        cout << "Guess " << i + 1 << ": \n";
        // Print the guess
        string guess_vec[5];
        guess_vec[0] = players[guess]->get_team();
        guess_vec[1] = players[guess]->get_num();
        guess_vec[2] = players[guess]->get_position();
        guess_vec[3] = players[guess]->get_age();
        guess_vec[4] = players[guess]->get_height();
        
        cout << guess << ": ";
        print_guess(guess_vec, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * 5)
        {
            won = true;
            break;
        }
    }

    if (won)
    {
        cout << "YOU WON!\n";
    }
    else
    {
        cout << "The word was: " << choice->get_name() << "\n";
    }
    return 0;
}