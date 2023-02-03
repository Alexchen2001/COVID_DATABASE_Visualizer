// Alexander Chen
// SUID: 4186272
// Assignment 4 Covid DataBase




#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string str, char del){
    vector<string> result;
    // declaring temp string to store the curr "word" upto del
    string temp = "";
    for(int i=0; i<(int)str.size(); i++){
        // If current char is not ',', then append it to the "word", otherwise you
         //have completed the word, and start the next word
        if(str[i] != del){
            temp += str[i];
        }else{
            result.push_back(temp);
            temp = "";
        }
    }
    // push the last substring after the last ',' to the result
    result.push_back(temp);
    return result;
}

class cvsdata {
    // Place to store variable/info
    string date;
    string country;
    int covidCases;
    int covidDeaths;
public:
    // setting the data: date, country name, covid cases, and death cases
    cvsdata(string date, string country, int cases, int deaths) {
        this->date = date;
        this->country = country;
        this->covidCases = cases;
        this->covidDeaths = deaths;
    }

    //Date getter
    string getDate() {
        return date;
    }
    
    // Country name getter
    string getCountry() {
        return country;
    }

    //Covid cases getter
    int getCases() {
        return covidCases;
    }

    //Death cases getter
    int getDeaths() {
        return covidDeaths;
    }
};

class DataEntry{
        private:
            // place to store variable that is private
            string date;
            string country;
            int cases;
            int deaths;

        public:

            //Constructor
            DataEntry(){}

            // date getter
            string getDate() {
                return date;
            }

            // country name getter
            string getCountry() {
                return country;
            }

            // covid case getter
            int getCases() {
                return cases;
            }

            //death cases getter
            int getDeaths() {
                return deaths;
            }

            // date setter
            void setDate(string date) {
                this->date = date;
            }

            // country name setter
            void setCountry(string country) {
                this->country = country;
            }

            // covid cases setter
            void setCases(int casesNum) {
                cases = casesNum;
            }

            // death cases setter
            void setDeaths(int deathsNum) {
                deaths = deathsNum;
            }
};


class CovidDB {
private:
    // default table size (given)
    // Initiating a vector<vector<>> for the database
    int tableSize = 17;
    vector<vector<DataEntry> > dataBase;

public:
    // constructed the table with max size "17"
    CovidDB () {
        dataBase = vector<vector<DataEntry> >(tableSize);
    }

    // hash function to find the right index to store the data
    int hash(string country) {
        int sum = 0;
        for (int i = 0; i < country.length(); i++) {
            sum += (i + 1) * int(country[i]);
        }
        return sum % tableSize;
    }
    
    // Compares the first date and second date and returns true if
    // the first greater than the second date
    bool DCompare(vector<string> firstDate, vector<string> secondDate){
        if (stoi(firstDate[2]) > stoi(secondDate[2])){
            return true;
        } else if (stoi(firstDate[2]) < stoi(secondDate[2])){
            return false;
        } else{
            if (stoi(firstDate[0]) > stoi(secondDate[0])){
                return true;
            } else if (stoi(firstDate[0]) < stoi(secondDate[0])){
                return false;
            } else{
                if (stoi(firstDate[1]) > stoi(secondDate[1])){
                    return true;
                } else{
                    return false;
                }
            }
        }
    }

    // accumulates for total cases and deaths for coutries
    bool add(DataEntry entry){
        int entryHash = hash(entry.getCountry());
        vector<DataEntry> &List = dataBase[entryHash];

        for (int i = 0; i < List.size(); i++){
            if (List[i].getCountry() == entry.getCountry()){
                // Merge the countries
                // Compares Date
                vector<string> entryDate = split(entry.getDate(), '/');
                vector<string> currentDate = split(List[i].getDate(), '/');
                if (DCompare(entryDate, currentDate) == true){
                    List[i].setDate(entry.getDate());
                    List[i].setCases(List[i].getCases() + entry.getCases());
                    List[i].setDeaths(List[i].getDeaths() + entry.getDeaths());
                    return true;
                } else{
                    return false;
                }
            }
        }
        List.push_back(entry);
        return true;
    }

    // searches the inputted country entry
    DataEntry get(string country) {
        int index = hash(country);
        vector<DataEntry> &List = dataBase[index];

        for (int i = 0; i < List.size(); i++){
            if (List[i].getCountry() == country){
                return List[i];
            }
        }
        DataEntry null;
        return null;
    }

    // Revoes the entry from the vector base of country name
    void remove(string country) {
        int index = hash(country);
        vector<DataEntry> &List = dataBase[index];

        for (int i = 0; i < List.size(); i++){
            if (List[i].getCountry() == country){
                List.erase(List.begin() + i);
                return;
            }
        }
        return;
    }

    // helper function to put the data for a country togther 
    // and uses add to store in database.
    void DBInitialize(vector<cvsdata> Initial){
        for (int i = 0; i < Initial.size(); i++){
            DataEntry forAdd;
            forAdd.setCases(Initial[i].getCases());
            forAdd.setCountry(Initial[i].getCountry());
            forAdd.setDate(Initial[i].getDate());
            forAdd.setDeaths(Initial[i].getDeaths());

            add(forAdd);
        }
    }


    void display(){
        cout << endl;
        cout << "\n COVID Database" << endl;
        for (int i = 0; i < dataBase.size(); i++){
            vector<DataEntry> &List = dataBase[i];
            for (int j = 0; j < List.size(); j++){
                cout << List[j].getDate() << " " ;
                cout << List[j].getCountry() << " " ;
                cout << List[j].getCases() << " " ;
                cout << List[j].getDeaths() << endl;
            }
        }
        cout << endl;
    }
};

void userInterface(vector<cvsdata> recordList) {
    CovidDB CDB;
    int decision = 1;
    bool table_initialization = false;

    while (decision != 0) {
        cout << endl;
        cout << " The Covid Tracker" << endl;
        cout << "1. Create the initial hash table" << endl;
        cout << "2. Add a new data entry" << endl;
        cout << "3. Get a data entry" << endl;
        cout << "4. Remove a data entry" << endl;
        cout << "5. Display hash table" << endl;
        cout << "0. Quit the system" << endl;
        cout << "Please choose the operation you want: ";
        cin >> decision;

        if (decision == 1) {					
            // Creates initial hash table
            if (!table_initialization) {
                CDB.DBInitialize(recordList);
                cout << "\n Initial hash table successfully created \n" << endl;
                table_initialization = true;
            } else {
                cout << "\nFailed to create, hash table already exist\n" << endl;
            }

        } else if (decision == 2) {		
            // Adds New Entry 
            if (table_initialization) {
                DataEntry newEntry;
                string date;
                string country;
                int cases;
                int deaths;

                cout << "\n  Enter the date( Follow format(mm/dd/yyyy)): ";
                cin >> date;
                newEntry.setDate(date);
                cout << " Enter the country : ";
                cin >> country;
                newEntry.setCountry(country);
                cout << "Enter number of cases :";
                cin >> cases;
                newEntry.setCases(cases);
                cout << "Enter number of death cases:: ";
                cin >> deaths;
                newEntry.setDeaths(deaths);

                if (CDB.add(newEntry)) {
                    cout << " Entry successfully added \n" << endl;
                } else {
                    cout << "Invalid date, failed to add entry\n" << endl;
                }
            } else {
                cout << "\n Invalid choice, initial table hasn't been created \n" << endl;
            }

        } else if (decision == 3) {		
            // Retrieves Entry Data
            if (table_initialization) {
                string country;
                cout << "\nEnter the country name : ";
                cin >> country;
                DataEntry result = CDB.get(country);

                if (result.getCases() == 0) {
                    cout << "Not found, there is no such entry \n" << endl;
                } else {
                    cout << "Entry found: ";
                    cout << result.getDate() << ", ";
                    cout << result.getCountry() << ", ";
                    cout << result.getCases() << ", ";
                    cout << result.getDeaths() << "\n" << endl;
                }

            } else {
                cout << "\nInvalid choice, initial table hasn't been created\n" << endl;
            }

        } else if (decision == 4) {
            // Removes Entry
            if (table_initialization) {
                string country;
                cout << "\nEnter the country name > ";
                cin >> country;
                CDB.remove(country);
            } else {
                cout << "\nInvalid choice, initial table hasn't been created\n" << endl;
            }

        } else if (decision == 5) {
            // Displays the hash table
            if (table_initialization) {
                CDB.display();
            } else {
                cout << "\nInvalid choice, initial table hasn't been created\n" << endl;
            }

        } else if(decision == 0){
            // Exit section of the program
            cout << "\n Program ended" << endl;
            cout << "Thank you for using it !!!" << endl;
            decision = 0;
            
        }else{
            // A case where a number not in the option is entered
            cout << endl;
            cout << "Please choose value between 0 to 5";
            cout << endl;
            cout << endl;
        }
    }
}


int main() {
    vector<cvsdata> recordList;

    // open the file
    ifstream file("WHO-COVID-Data.csv");

    if(file.is_open()){

        cout << "Open File Success" << endl;

        string line;

        while(getline(file, line)){

            // split the content in each line
            vector<string> result = split(line, ',');

            // wrap up all the data in the string to a cvsdata type and push it to the vector
            cvsdata oneEntry = cvsdata(result[0], result[1],std::stoi(result[2]), std::stoi(result[3]));
            recordList.push_back(oneEntry);
        }
        cout << "There are " << recordList.size() << " records in total." << endl;

    }else{
        cout << "Open file failed" << endl;
    }
    cout << " Note to Instructor and TA: The csv file (WHO-COVID-Data) has an issue"<< endl;
    cout << " Please copy the data of the file and create a new csv file with a different name"<< endl;
    cout << " if you see a (stoi) error"<<endl;
    cout << "The code works when the the data copies into a new csv file ! Thank you !"<< endl;
    userInterface(recordList);
    return 0;
}
