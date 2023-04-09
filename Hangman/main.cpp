#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;
string wordState = "";	//For the current word state
string defaultWords[12] = {"Programming", "Language", "C Plus Plus", "Recursion", "UML", "Class Inheritance", 
						"Asymptotic Notation", "Space Complexity", "Exchange Sort", "Quick Sort", "Templates", "Operator Overloading"};
vector<char> lettersUsed;	//To keep track of letters used
vector<string> wordsUsed;	//FOR HARD MODE ONLY!!
int SIZE;

//Display the current stick figure state:
void displayCurFigure(int max, int guessNum){
	switch(max){
		case 12:	//EASY
			if(guessNum == 10 || guessNum == 9){
				cout << "\t O "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 8 || guessNum == 7){
				cout << "\t O "<< endl;
				cout << "\t | "<< endl;
				cout << "\t | "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 6 || guessNum == 5){
				cout << "\t O "<< endl;
				cout << "\t\\| "<< endl;
				cout << "\t | "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 4|| guessNum == 3){
				cout << "\t O "<< endl;
				cout << "\t\\|/"<< endl;
				cout << "\t | "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 2 || guessNum == 1){
				cout << "\t O "<< endl;
				cout << "\t\\|/"<< endl;
				cout << "\t | "<< endl;
				cout << "\t/  "<< endl;
			}
			else if(guessNum == 0){
				cout << "\t O "<< endl;
				cout << "\t\\|/"<< endl;
				cout << "\t | "<< endl;
				cout << "\t/ \\"<< endl;
			}
			else{
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
			}
			break;
		case 6:		//NORMAL and HARD
			if(guessNum == 5){
				cout << "\t O "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 4){
				cout << "\t O "<< endl;
				cout << "\t | "<< endl;
				cout << "\t | "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 3){
				cout << "\t O "<< endl;
				cout << "\t\\| "<< endl;
				cout << "\t | "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 2){
				cout << "\t O "<< endl;
				cout << "\t\\|/"<< endl;
				cout << "\t | "<< endl;
				cout << "\t   "<< endl;
			}
			else if(guessNum == 1){
				cout << "\t O "<< endl;
				cout << "\t\\|/"<< endl;
				cout << "\t | "<< endl;
				cout << "\t/  "<< endl;
			}
			else if(guessNum == 0){
				cout << "\t O "<< endl;
				cout << "\t\\|/"<< endl;
				cout << "\t | "<< endl;
				cout << "\t/ \\"<< endl;
			}
			else{
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
				cout << "\t   "<< endl;
			}
			break;
	}
}

//Set words list:
void setWordsList(vector<string> & list, string file){
	string line;
	ifstream readline;
	readline.open(file);
	while(true){
		if(getline(readline, line)){
			list.push_back(line);
		}
		else{
			SIZE = list.size();
			readline.close();
			break;
		}
	}

	int k;	//Used as an index
	//Check for any characters that are not letters:
	for(int i = 0; i < list.size(); i++){
		k = list[i].find_first_of("1234567890-=`~!@#$%^&*)(}{][|\\:\";\'><.,?/_+");
		while(k != string::npos){
			list[i].erase(list[i].begin() + k);
			k = list[i].find_first_of("1234567890-=`~!@#$%^&*)(}{][|\\:\";\'><.,?/_+");
		}
	}

}

//Create the starting wordState
void createWordState(string word){
	for(int i = 0; i < word.length(); i++){
		if(word[i] == ' '){
			wordState.append(" ");
		}
		else{
			wordState.append("_");
		}
	}
}

//Check if word is complete and correct
bool finishedWord(string word){
	return (wordState == word);
}

//Creating a temporary copy of the original word
string createTemp(string origWord){
	string temp = origWord;
	
	for(int i = 0; i < temp.length(); i++){
		temp[i] = tolower(temp[i]);
	}

	return temp;
}

//Display current state of 'wordState'
void displayWordState(){
	int wordCount = 0;
	for(int i = 0; i < wordState.length(); i++){
		if(wordState[i] == ' '){
			++wordCount;
			if(wordCount > 4){
				cout << endl;
				wordCount = 0;
			}
		}
		cout << wordState[i] << " ";
	}
	cout << endl;
}

//Check if letter exists in the original word
bool letterExists(char letter, string tempWord){
	return (tempWord.find_first_of(letter) != string::npos);
}

//IF THE LETTER EXISTS, add it to 'wordState'
void changeWordState(char letter, string wordTemp, string word){
	for(int i = 0; i < wordState.length(); i++){
		if(wordTemp[i] == letter){
			wordState[i] = word[i];
		}
	}
}

//Add the letters the user already input
void addLettersUsed(char letter){
	char capLetter = toupper(letter);
	if(lettersUsed.size() == 0){
		lettersUsed.push_back(capLetter);
	}
	else{
		bool letterExists = false;
		for(int i = 0; i < lettersUsed.size(); i++){
			if(lettersUsed[i] == capLetter){
				letterExists = true;
				break;
			}
		}
	
		if(!letterExists){
			lettersUsed.push_back(capLetter);
		}
	}

}



//Display the letters the user already input
void displayLettersUsed(){
	if(lettersUsed.size() == 0){
		cout << endl;
	}
	else{
		for(int i = 0; i < lettersUsed.size(); i++){
			if(i % 5 == 0 && i != 0){
				cout << "\n" << endl;
			}
			cout << "\t" << lettersUsed[i];
		}
		cout << "\n" << endl;
	}
}

//HARD MODE ONLY:
//Check if any of the letters previously entered are in the new word
void checkLettersUsed_HARD(string tempWord, string origWord){
	char tempLetter;
	for(int i = 0; i < lettersUsed.size(); i++){
		tempLetter = tolower(lettersUsed[i]);
		if(letterExists(tempLetter, tempWord)){
			changeWordState(tempLetter, tempWord, origWord);
		}
	}
}

void addWordsUsed(string word){
	wordsUsed.push_back(word);
}

void displayWordsUsed(){
	int j;
	for(int i = 0; i < wordsUsed.size(); i++){
		j = i + 1;
		cout << j << ". " << wordsUsed[i] << endl;
	}
	cout << endl;
}

/**********EASY/NORMAL MODE**********/
void startGame_EASY_NORMAL(string word, int MAX_GUESSES){
	int curGuessNum = MAX_GUESSES;
	string inputGuess;
	char letterGuess;
	string tempWord = createTemp(word);
	char tempLetter;
	int won = 1;	//1 means WIN; 0 means LOSE; 3 means quitting
	createWordState(word);

	while(true){
		if(curGuessNum == 0){
			displayCurFigure(MAX_GUESSES, curGuessNum);
			won = 0;
			break;
		}
		else if(finishedWord(word)){
			break;
		}

		displayCurFigure(MAX_GUESSES, curGuessNum);
		displayWordState();
		cout << "\nNumber of guesses left: " << curGuessNum << endl;
		cout << "Letters that you have guessed:\n";
		displayLettersUsed();
		cout << "Enter a letter (0 to exit): ";
		cin >> inputGuess;
		letterGuess = inputGuess[0];
		system("cls");
		
		//USER QUITS:
		if(letterGuess == '0'){
			won = 3;
			break;
		}
		////////////

		tempLetter = tolower(letterGuess);
		addLettersUsed(tempLetter);

		if(!letterExists(tempLetter, tempWord)){
			--curGuessNum;
		}
		else{
			changeWordState(tempLetter, tempWord, word);
		}
	}
	
	lettersUsed.clear();
	wordState = "";

	if(won == 1){
		cout << "YOU WON! CONGRATULATIONS!" << endl;
		cout << "Your word: " << word << endl;
	}
	else if(won == 0){
		cout << "You lose!!!" << endl;
		cout << "The word was \"" << word << "\"" << endl;
	}
	else{
		cout << "Exiting!!" << endl;
	}
	
}
/********************************************/

/**********HARD MODE**********/
void startGame_HARD(vector<string> list, int MAX_GUESSES){
	string word = list[rand() % list.size()];
	int curGuessNum = MAX_GUESSES;
	string inputGuess;
	char letterGuess;
	string tempWord;
	char tempLetter;
	int won = 1;	//1 means WIN; 0 means LOSE; 3 means quitting
	createWordState(word);

	while(true){
		if(curGuessNum == 0){
			displayCurFigure(MAX_GUESSES, curGuessNum);
			won = 0;
			break;
		}
		else if(finishedWord(word)){
			break;
		}

		displayCurFigure(MAX_GUESSES, curGuessNum);
		displayWordState();
		cout << "\nNumber of guesses left: " << curGuessNum << endl;
		cout << "Letters that you have guessed:\n";
		displayLettersUsed();
		cout << "Enter a letter (0 to exit): ";
		cin >> inputGuess;
		letterGuess = inputGuess[0];
		system("cls");

		//USER QUITS:
		if(letterGuess == '0'){
			won = 3;
			break;
		}
		////////////

		tempLetter = tolower(letterGuess);
		addLettersUsed(tempLetter);
		tempWord = createTemp(word);

		if(!letterExists(tempLetter, tempWord)){
			--curGuessNum;
			wordState = "";
			word = list[rand() % list.size()];
			addWordsUsed(word);
			createWordState(word);
			tempWord = createTemp(word);
			checkLettersUsed_HARD(tempWord, word);
		}
		else{
			changeWordState(tempLetter, tempWord, word);
		}
	}
	
	lettersUsed.clear();
	wordState = "";

	if(won == 1){
		cout << "YOU WON! CONGRATULATIONS!" << endl;
		cout << "Winning word: " << word << "\n" << endl;
		cout << "Words used: " << endl;
		displayWordsUsed();
		wordsUsed.clear();
	}
	else if(won == 0){
		cout << "You lose!!!" << endl;
		cout << "Words used: " << endl;
		displayWordsUsed();
		wordsUsed.clear();
	}
	else{
		cout << "Exiting!!" << endl;
	}

}
/********************************************/

/*********MAIN*********/
int main(){
	string word;
	string fileName;
	vector<string> wordsList;
	srand(time(0));
	string playGame;
	string difficulty;
	ifstream fin;

	while(true){
		cout << "Welcome to JSP's Hangman Game!" << endl;
		cout << "MAIN MENU" << endl;
		cout << "1) Start Game" << endl;
		cout << "2) Load File" << endl;
		cout << "3) Exit" << endl;
		cout << ">> ";
		fileName = "";
		cin >> playGame;
		

		if(playGame == "1" || playGame == "2"){
			if(playGame == "1"){	//IF user selected Start Game
				system("cls");
				wordsList.assign(defaultWords, defaultWords + 12);
				word = wordsList[rand() % 12];
			}
			else if(playGame == "2"){
				cin.ignore();
				system("cls");
				cout << "**IMPORTANT**\nFile(s) must contain words that are separated by a new line. If a word contains characters that are NOT letters, those characters will be deleted.\n" << endl;
				cout << "Please enter a file name to import your own words list: ";
				getline(cin, fileName);


				fin.open(fileName);
				if(fin.fail()){
					system("cls");
					cout << "\"" + fileName + "\" doesn't exist!\n" << endl;
					fin.close();
					continue;
				}
				else{
					setWordsList(wordsList, fileName);
					fin.close();
					if(SIZE == 0){
						system("cls");
						cout << "File is empty!\n" << endl;
						continue;
					}
					else{
						system("cls");
						word = wordsList[rand() % SIZE];
						cout << "Successfully read the file contents!\n" << endl;
					}
				}
			}
			
			
			while(true){
				cout << "CHOOSE A DIFFICULTY: " << endl;
				cout << "1) EASY" <<endl;
				cout << "2) NORMAL" << endl;
				cout << "3) HARD" << endl;
				cout << "4) Difficulty description" << endl;
				cout << "0 to return to main menu" << endl;
				cout << ">> ";
				cin >> difficulty;

				if(difficulty == "0"){
					system("cls");
					break;
				}
				else if(difficulty == "1"){	//EASY
					system("cls");
					cout << "Starting Easy Mode!" << endl;
					startGame_EASY_NORMAL(word, 12);
					wordState.clear();
					wordsList.clear();
					cout << endl;
					break;
				}
				else if(difficulty == "2"){	//NORMAL
					system("cls");
					cout << "Starting Normal Mode!" << endl;
					startGame_EASY_NORMAL(word, 6);
					wordState.clear();
					wordsList.clear();
					cout << endl;
					break;
				}
				else if(difficulty == "3"){	//HARD
					system("cls");
					cout << "Starting Hard Mode!" << endl;
					startGame_HARD(wordsList, 6);
					wordState.clear();
					wordsList.clear();
					cout << endl;
					break;
				}
				else if(difficulty == "4"){
					system("cls");
					cout << "EASY\t - 12 chances to guess the correct letters" << endl;
					cout << "NORMAL\t - 6 chances to guess the correct letters" << endl;
					cout << "HARD\t - 6 chance to guess the correct letters and \n\t every wrong guess will change the word!\n" << endl;
				}
				else{
					system("cls");
					cout << "Invalid option!\n" << endl;
				}
			}
		}
		else if(playGame == "3"){
			cout << "Thanks for playing!" << endl;
			break;
		}
		else{
			system("cls");
			cout << "Invalid option!\n" << endl;
			cin.ignore();
		}
	}

	return 0;
}