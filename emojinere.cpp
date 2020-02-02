#include <iostream>
#include <vector>
using namespace std;

/* 
    Returns position of a letter in english alphabet, if alphabet is different returns -1
    @params
        1. alphabet - usign which data is encrypted or decrypted
        2. letter  - piece of the information
*/ 
int get_index(vector<char>& alph, char letter);  // for english letters
int get_index(vector<string> & alph, string letter); // for emoji

/* 
    Encodes data using emojinere cipher 
    @params 
        1. raw data
        2. key
*/
string encrypt(string r_d, string key);

/*
    Decrypts data using emojinere cipher
    @params
        1. encrypted data 
        2. key
*/

string decrypt(string enc_data, string key);

/*
    Prints unicode emoji string
    @params
        1. data - string, which should be printed
*/
void print_data(string data)
{
    for (int i = 0; i < data.length(); i+=4)
    {
        cout << data.substr(i, 4) << ' ';
    }
    cout << endl;
}
int main()
{
    int option = 0;

    cout << "Choose the operation, you want to confirm:\n\t1) encrypt data\n\t2) decrypt data:\n";
    cin >> option;

    if (option == 1)
    {
        string key = "";
        string raw_data = "";
        string encrypted_data = "";

        cout << "Enter the key: ";
        cin >> key;

        cout << "Enter the data: ";
        cin >> raw_data;
        
        encryption_fail: 
            encrypted_data = encrypt(raw_data, key);
            
            // cheks whether the entered data is english letter or not
            while (encrypted_data == "1" || encrypted_data == "2" )
            {
                if(encrypted_data == "1") 
                {
                    cout << "Wrong input!\nEnter the key again: ";
                    cin >> key;
                    goto encryption_fail;   
                }
                else if (encrypted_data == "2")
                {
                    cout << "Wrong input!\nEnter the data again: ";
                    cin >> raw_data;
                    goto encryption_fail;           
                }

            }

        
       print_data(encrypted_data);
    }
    else if (option == 2)
    {
        string key = "";
        string encrypted_data = "";
        string decrypted_data = "";

        cout << "Enter encrypted data: ";
        cin >> encrypted_data;

        cout << "Enter the key: ";
        cin >> key;

        decryption_fail:
            decrypted_data = decrypt(encrypted_data, key);

            // cheks whether the entered data is english letter or correct emoji 
            while (decrypted_data == "1" || decrypted_data == "2" )
            {
                if(decrypted_data == "1") 
                {
                    cout << "Wrong input!\nEnter the key again: ";
                    cin >> key;
                    goto decryption_fail;   
                }
                else if (decrypted_data == "2")
                {
                    cout << "Wrong input!\nEnter the data again: ";
                    cin >> encrypted_data;
                    goto decryption_fail;           
                }

            }
            cout << decrypted_data << endl;
    }
    else
    {
        cout << "Enter correct option\n";
    }
    
    
    return 0;
}

    
string encrypt(string r_d, string key)
{
    vector<char> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    vector<string> emoji = { "😀", "😁", "😂", "🤣", "😃", "😄","😅", "😆", "😉", "😊", "😋", "😎", "😍", "😘", "🥰", "😗", "😙", "😚", "🙂", "🤗", "🤩", "🤔", "🤨", "😐", "😑", "😶" };
    cout << alphabet.size() << ' ' << emoji.size() << endl;

    string encoded = "";
    string check = "";
    string extended_key = "";
    
    // makes the length of the key not less than the lenght of the data
    while (extended_key.length() < r_d.length())
        extended_key += key;


    for (int i = 0; i < r_d.length() ; ++i )
    {
        // get the position of letter in alphabet 
        int number_of_iterations = get_index(alphabet, extended_key[i]);
        if (number_of_iterations == -1)
        {
            return "1";
        }
        // get the position of letter in alphabet
        int value_for_shift = get_index(alphabet, r_d[i]);
        if (value_for_shift == -1)
        {
            return "2";
        }

        
        int index_of_emoji= (value_for_shift + number_of_iterations) % 26;
        
        encoded += emoji[index_of_emoji];       
        check += alphabet[index_of_emoji];

    }
    //uncomment the line below, to check whether algorithm converts to the correct vigenere or not
    //cout << check << endl;
    
    return encoded;

}


string decrypt(string enc_data, string key)
{
    vector<char> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    vector<string> emoji = { "😀", "😁", "😂", "🤣", "😃", "😄","😅", "😆", "😉", "😊", "😋", "😎", "😍", "😘", "🥰", "😗", "😙", "😚", "🙂", "🤗", "🤩", "🤔", "🤨", "😐", "😑", "😶" };
    
    string decoded = "";
    string extended_key = "";
    
    // makes data and the key same lenght
    while (extended_key.length() < enc_data.length())
    {
        extended_key += key;
    }
    
    // iterates over the encoded data and converts each 4 character to the one english letter 
    for (int i = 0, j = 0; i < enc_data.length(); i+=4, j++)
    {
        //gets the position of the letter of key in the english alphabet
        int number_of_shifts = get_index(alphabet, extended_key[j]);
        if (number_of_shifts== -1)
        {
            return "1";
        }
        string emoji_letter = enc_data.substr(i , 4);

        //gets the position of the emoji in the emoji alphabet
        int index_of_emoji = get_index(emoji, emoji_letter);

        if(index_of_emoji == -1)
        {
            return "2";
        }

        //finds the position of the decoded letter in the english alphabet
        int index_of_english_letter = index_of_emoji - number_of_shifts;
        
        //checks the margins
        if (index_of_english_letter < 0)
            index_of_english_letter = 26 + index_of_english_letter;
        
    
        decoded += alphabet[index_of_english_letter];
    }
    return decoded; 
}

int get_index(vector<string>& alph, string letter)
{
    for (int i = 0; i < alph.size(); ++i)
    {
        if (alph[i] == letter)
        {
            return i;
        }
    }

    return -1;
}


int get_index(vector<char>&alph, char letter)
{
    for (int i = 0; i < alph.size(); ++i)
    {
        if (alph[i] == letter)
        return i;
    }
    
    return -1;

}

