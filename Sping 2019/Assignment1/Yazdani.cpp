
/**
 *                      WHATS THE ALGORITHM?
 * This program uses Hashmap combined with linked list
 * File structure of each table is like below :
 *           _________________________
 *          |        Metadata         |
 *          |=========================|
 *          | Record with keyhash : 0 |                              ----
 *          | Record with keyhash : 1 |                                 |---> This section is named hashtable
 *          | ....................... |                                 |
 *          | Record with keyhash : n | which n is HASHTABLE_SIZE    ----
 *          |=========================|
 *          |   unstructered Nodes    | 
 *           _________________________
 * 
 * As the records have same size, It's really easy to find record by keyhash
 * 
 * It's really easy to explain the mechanism by an example:
 *                  ```` SET command ````
 *     1 - User wants to set testkey => testvalue
 *     2 - Hash the key, it will be forexample 3
 *     3 - Save the testkey => testvalue as record with keyhash 3, leave other records empty (filled by zero)
 *     4 - User wants to set testkey1 => testvalue
 *     5 - Hashcode of testkey1 is also 3 :-(
 *     4 - The testkey1 => testvalue will be inserted in unstructered Nodes section (It's position will be pos1 for example)
 *         And will be linked to record with hash 3
 *     5 - User wants to set testkey2 => testvalue
 *     6 - Hashcode of testkey2 is also 3
 *     7 - The testkey2 => testvalue will be saved in unstructered node, and it's position will be linked to `pos1` (Previous node created at level 4)
 *   
 * 
 *                  ```` GET command ```` 
 *     1 - User wants to receive testkey value
 *     2 - Hashcode of testkey is 3
 *     3 - Program looks for record with hash 3
 *     4 - If key equals testkey, then the value will be returned
 *     5 - User wants to receive testkey1 value, The hashcode is 3
 *     6 - Program looks for record with hash 3
 *     7 - It's key isn't equal to testkey1
 *     8 - There is another node linked to that record (in unstructered nodes section), program will read that node
 *     9 - It's key equals testkey1, Program returns the value
 *
 *                   ```` DELETE command ````
 *     1 - User wants to delete testkey1, hashcode is 3
 *     2 - Program looks for record with hash 3
 *     3 - After traversing and finding node, the record will be flagged by delete
 *     4 - For next `SET` commands, this deleted record will be overwritten
 * 
 *  @NOTICE In this program, the table files won't get smaller after deletes, recommended for people who will gift whole their hard to this program
 *  For more details you can read the code
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <iomanip>

#define KEY_SIZE 4 // Max key size
#define VALUE_SIZE 32 // Max value size
#define HASHTABLE_SIZE 100000 // Hashtable size
#define MAX_INPUT_SIZE 1000 // Maximum size of string taken from input (Only while getting value in `SET` command)

// Get input from user in special size, calls `errorFunc` if any error happens. input should be in this format : `(%s)`
// @TODO It's not safe to do such this works, just replace it with functions
#define GET_PARAM(input, errorFunc, size) { \
                                        input = inputFormatted(errorFunc, size); \
                                        if (input.empty() || strlen(input.c_str()) > size) { \
                                            ignoreInput(); \
                                            continue; \
                                        } \
                                    } 

using namespace std;

// Shows the name of currently using table + ">"
void showCommandInput();

// Shows error bad key
void errBadKey();

// Shows error bad value
void errBadValue();

// Trim a string, returns a trimmed string Ex: trim(" test ") -> "test"
string trim(const string);

// Open a table and use it, if table doesnt exists, it will create a file filled with zeros
void useTable(string);

// Parse a string in this format : `(%s)` and returns `%s`
string parseFormatted(string);

// Input a string in this format : `(%s)`
string inputFormatted(void (), size_t);


// Input a string (supports spaces)
string inputStr(size_t);

// Deletes a key from table, returns `0` if key was founded and deleted and `1` if key wasn't founded
int deleteKey(string);

// Add a node (key, value) to deleted nodes section. This method set node->deleted flag to true (1) and link the deleted node to other deleted nodes
void addNodeToDeleted(streampos, struct Node, bool);

// Returns a position for node to be written in according to the key
streampos findNodePositionByKeyForSet(string);

// Link a node to another node
void linkCurrentToPrevious(streampos, struct Node, streampos);


// Set a value = key
void set(string key, string value);

// Hash a string and returns hash code in bound 0 to size (second arg)
unsigned int hash_func(const char*, const unsigned int);

// Shows errors to user if no table was used
void errUseTable();


// Ignores input until '\n' character, used to stop unhandled characters from being part of next command
// Ex : if user enters ` GET (test) something really bad `
//      this function will reject everything after ')' character until '\n'
void ignoreInput();

// Get a value from key, return value
string get(string key);


// Empties a block of file, from pos1 (arg 1) to pos2 (arg 2)
void emptyBlock(streampos, streampos);

void gen_random(char*, size_t);


// Constains name of current using table
string currentTable = "";

// Current using table file stream
fstream table;


// Metadata, first block of file that constains first and last deleted node position
struct Metadata {
    streampos firstDeletedPos = 0;
    streampos lastDeletedPos = 0;
};

// Node, a simple linked key value struct
struct Node {
    char key[KEY_SIZE + 1];
    char value[VALUE_SIZE + 1];

    // Is deleted? `1` for yes and `0` for no
    int deleted : 4;

    // Position of next element, `0` if there wasn't next element
    streampos next;
};

int main() {
    string commandName, // Entered command name (SET, GET, DELETE, USE, EXIST)
                key, // Entered key (For commands : SET, GET, DELETE, EXIST)
                value; // Entered value (For command : SET)
    // for (unsigned int i = 0; i < 100000; i++) {
    //     char randomKey[5];
    //     gen_random(randomKey, 4);
    //     randomKey[4] = '\0';
    //     if (hash_func(randomKey, HASHTABLE_SIZE) == 105) {
    //         cout << randomKey << endl;
    //     }
    // }
    while (1) {

        // Show the beginning of input line, may be `>` or `tablename>`
        showCommandInput();
        cin >> commandName; // Get command from user
        commandName = trim(commandName); // Trim it

        if (commandName == "EXIT") {

            // Exit the program
            return 0;

        } else if (commandName == "SET") {

            GET_PARAM(key, errBadKey, 4); // Get key from user, key shouldn't be more that 4 byte
            value = trim(parseFormatted(trim(inputStr(MAX_INPUT_SIZE)))); // Get value from user, trim and parse it
            if (value.size() > 32 || value == "") {  // Validate the value
                errBadValue();
                continue;
            }
            
            if (!table.is_open()) { // If table wasn't open show error
                errUseTable();
                continue;   // App should continue ....
            }

            // Set a key => value
            set(key, value);

        } else if (commandName == "GET") {

            GET_PARAM(key, errBadKey, 4);
            if (!table.is_open()) {
                ignoreInput();
                errUseTable();
                continue;
            }

            // Get a key and returns value
            string value = get(key);

            if (value == "") value = "\033[0;31m(" + key + ")" + " was not found.\033[0m"; // Key wasn't found
            cout << value << endl; // Show value

        } else if (commandName == "EXIST") {

            GET_PARAM(key, errBadKey, 4);
            if (!table.is_open()) {
                ignoreInput();
                errUseTable();
                continue;
            }
            string value = get(key);
            if (value == "") {
                cout << "0" << endl; // Key doesn't exist
            } else {
                cout << "1" << endl; // Key exists
            }

        } else if (commandName == "USE") {

            cin >> currentTable; // Table name cannot constain spaces
            useTable(trim(currentTable));

        } else if (commandName == "DELETE") {

            GET_PARAM(key, errBadKey, 4);
            deleteKey(key);

        } else if (commandName == "HELP") {

            cout << "List of commands : " << endl;
            cout << "   " << left << setw(20) << "SET (key) (value)" << right << setw(30) << "Set a key => value" << endl;
            cout << "   " << left << setw(20) << "GET (key)" << right << setw(30) << "Get key's value" << endl;
            cout << "   " << left << setw(20) << "DELETE (key)" << right << setw(30) << " Delete a key => value" << endl;
            cout << "   " << left << setw(20) << "EXIST (key)" << right << setw(30) << "Check if a key exists" << endl;
            cout << "   " << left << setw(20) << "USE tablename" << right << setw(30) << "Use a table" << endl;
            cout << "   " << left << setw(20) << "EXIT" << right << setw(30) << "Close the program" << endl;
        }

        if (commandName != "SET") { // Don't ignore unhandled chars for `SET` command, It's already handled :-)
            ignoreInput(); 
        }
    }

    // Close the table :-(
    if (table.is_open()) {
        table.close();
    }
}


streampos findNodePositionByKeyForSet(string key) {
    unsigned int keyHash = hash_func(key.c_str(), HASHTABLE_SIZE); // Get hash code of key
    
    // Because the data structure used in this app, is `HashMap`, keys are located according to their hash code, by default 
    // And this is how the position is calculated
    // @NOTICE metadata is at the beginning of file.
    streampos position = keyHash * sizeof(struct Node) + sizeof(struct Metadata);
    struct Node node;
    table.seekg(position);
    table.read(reinterpret_cast<char*>(&node), sizeof(struct Node)); // Read the node in key position
    if (strlen(node.key) == 0) { // Node doesn't exists, so currently entered node should be written here
        return position;
    }
    streampos prevNodePosition = position;
    struct Node prevNode;

     // If node exists in key position, it may be linked with other nodes with same key hash code let's traverse them until getting desired Node
    while (node.next != 0) { // Until there was a next Node
        table.seekg(node.next);
        prevNodePosition = node.next;
        prevNode = node;
        table.read(reinterpret_cast<char*>(&node), sizeof(struct Node)); // Read the next Node
        if (strcmp(node.key, key.c_str()) == 0) { // Is this Node what we were looking for?
            return node.next; // So return its position, it will be overwritten
        }
    }

    // Read metadata to find first deleted node, Deleted nodes will be overwritten with new Node! we don't resize file, we use empty sections. Feeling like memory
    struct Metadata metadata;
    table.seekg(0);
    table.read(reinterpret_cast<char*>(&metadata), sizeof(struct Metadata));
    if (metadata.firstDeletedPos != 0) {

        // Find the next deleted node if exists
        if (metadata.firstDeletedPos == metadata.lastDeletedPos) { // There is only one removed Node

            position = metadata.lastDeletedPos;
            // Empty metadata 
            metadata.firstDeletedPos = 0;
            metadata.lastDeletedPos = 0;
            table.seekp(0);
            table.write(reinterpret_cast<char*>(&metadata), sizeof(struct Metadata)); // Update metadata
            return position; // Overwrite that single poor delted node :-(

        } else { // There is more than one deleted node
            
            // Find (n - 1)th deleted node (Not a efficient work, But I'm running out of time now), We want to remove it's link to the nth node
            // @TODO link every node with it's next and previous element, not only next element
            table.seekg(metadata.firstDeletedPos);
            table.read(reinterpret_cast<char*>(&node), sizeof(struct Node));
            struct Node prevNode;
            while (node.next == metadata.lastDeletedPos) { // We need (n-1)th node, not the nth node
                position = node.next;
                prevNode = node;
                table.seekg(node.next);
                table.read(reinterpret_cast<char*>(&node), sizeof(struct Node));
            }
            // Update (n - 1)th node
            table.seekp(position);
            prevNode.next = 0; // Because the next Node will be overwritten soon
            table.write(reinterpret_cast<char*>(&node), sizeof(struct Node));

            // Update metadata, The last deleted Node is changed
            metadata.lastDeletedPos = position;
            table.seekp(0);
            table.write(reinterpret_cast<char*>(&metadata), sizeof(struct Metadata));
            return metadata.lastDeletedPos;
        }

    }

    table.seekg (0, ios::end); // Append currently requested Node to end of file :-(
    position = table.tellg();
    linkCurrentToPrevious(position, prevNode, prevNodePosition);
    return position;
}



string get(string key) {
    unsigned int keyHash = hash_func(key.c_str(), HASHTABLE_SIZE);
    streampos position = keyHash * sizeof(struct Node) + sizeof(struct Metadata);
    struct Node node;
    table.seekg(position);
    table.read(reinterpret_cast<char*>(&node), sizeof(struct Node));
    if (strlen(node.key) == 0) { // Key doesn't exists
        return "";
    } else if (strcmp(node.key, key.c_str()) == 0) { // Key exists
        if (node.deleted == 0) {
            return node.value; // So return value
        } else {
            return "";
        }
    }

    // There are next elemetns to traverse
    while (node.next != 0) {
        table.seekg(node.next);
        table.read(reinterpret_cast<char*>(&node), sizeof(struct Node));
        if (strcmp(node.key, key.c_str()) == 0) {
            if (node.deleted == 0) { // If it wasn't deleted
                return node.value;
            } else {
                return "";
            }
        }
    }
    return "";
}


void addNodeToDeleted(streampos pos, struct Node node, bool shouldChangeMetadata) {
    // Set node flag to deleted
    node.deleted = 1;
    table.seekp(pos);
    table.write(reinterpret_cast<char*>(&node), sizeof(struct Node));

    if (!shouldChangeMetadata) return;

    // Parse metadata
    struct Metadata metadata;
    table.seekg(0);
    table.read(reinterpret_cast<char*>(&metadata), sizeof(struct Metadata));

    if (metadata.firstDeletedPos == 0) {

        // Metadata is empty, So currently deleted node, is the first deleted node
        metadata.firstDeletedPos = pos;
        metadata.lastDeletedPos = pos;
        table.seekp(0);
        table.write(reinterpret_cast<char*>(&metadata), sizeof(struct Metadata));

    } else {

        // Change last deleted node, and link deleted nodes
        struct Node lastNode;
        table.seekg(metadata.lastDeletedPos);
        table.read(reinterpret_cast<char*>(&lastNode), sizeof(struct Node));
        lastNode.next = pos; // (n - 1)th Node will be linked to nth node
        table.seekp(metadata.lastDeletedPos);
        table.write(reinterpret_cast<char*>(&lastNode), sizeof(struct Node));

        metadata.lastDeletedPos = pos; // Last deleted node in metadata is changed
        table.seekp(0);
        table.write(reinterpret_cast<char*>(&metadata), sizeof(struct Metadata));

    }
}

int deleteKey(string key) {

    // First find node
    unsigned int keyHash = hash_func(key.c_str(), HASHTABLE_SIZE);
    streampos position = keyHash * sizeof(struct Node) + sizeof(struct Metadata);
    struct Node node;
    table.seekg(position);
    table.read(reinterpret_cast<char*>(&node), sizeof(struct Node));
    if (strlen(node.key) == 0) {
        return 1; // Node with desired key doesn't found
    } else if (strcmp(node.key, key.c_str()) == 0) {
        addNodeToDeleted(position, node, false);         // Node founded, Add node to deleted nodes section, Don't change metadata for Hashtable records
        return 0;
    }

    struct Node prevNode;
    streampos prevPos;

    // Traverse all linked nodes to get to desired node
    while (node.next != 0) {

        prevNode = node;
        prevPos = position;
        table.seekg(node.next);
        position = node.next;
        table.read(reinterpret_cast<char*>(&node), sizeof(struct Node));

        if (strcmp(node.key, key.c_str()) == 0) {
            // Node founded
            addNodeToDeleted(position, node, true);
            prevNode.next = node.next; // Link previous node and next node of deleted node together
            table.seekp(prevPos);
            table.write(reinterpret_cast<char*>(&prevNode), sizeof(struct Node));
            return 0;
        }

    }

    return 1; // Key wasn't found
}


void linkCurrentToPrevious(streampos currentPosition, struct Node prevNode, streampos prevPosition) {
    prevNode.next = currentPosition;
    table.seekp(prevPosition);
    table.write(reinterpret_cast<char*>(&prevNode), sizeof(struct Node));
}

string parseFormatted(string formatted) {
    formatted = trim(formatted);
    if (formatted.at(0) != '(') { // Check input starts with `(`
        return "";
    }
    char lastChar = formatted.at(strlen(formatted.c_str()) - 1);
    if (lastChar != ')') { // Check if input ends with `)`
        return "";
    }
    return trim(formatted.substr(1, formatted.size() - 2)); // Remove last and first char (parantheses)
}

void errBadKey() {
    cout << "\033[0;31mEnter a correct key, try HELP for more information\033[0m" << endl;
}

void errBadValue() {
    cout << "\033[0;31mEnter a correct value, try HELP for more information\033[0m" << endl;
}

string trim(const string str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void showCommandInput() {
    cout << currentTable << ">";
}

void useTable(string tableName) {
    // Check if folder exists
    struct stat info;
    if(stat("storage", &info ) != 0) {
        const int dir_err = mkdir("storage", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (dir_err == -1) {
            cout << "\033[0;31mError while opening directory : \033[0m" << strerror(errno) << endl; // Show file openning error
            currentTable = "";
        }
    }
    if (table.is_open()) {
        table.close();
    }
    string tableFile = "storage/" + tableName;
    ifstream f(tableFile);
    if (!f.good()) { // File doesn't exist?
        ofstream out(tableFile);
        for (int i = 0; i < (HASHTABLE_SIZE * sizeof(struct Node) + sizeof(struct Metadata)); i++) out.write("\0", 1); // Create empty file
        out.close();
    }
    f.close();
    table.open(tableFile,  fstream::out | fstream::in); // Open already created file
    if (!table) {
        cout << "\033[0;31mError while opening file : \033[0m" << strerror(errno) << endl; // Show file openning error
        currentTable = "";
    }
}

void errUseTable() {
    cout << "\033[0;31mSelect a table first, try HELP for more informations\033[0m" << endl;
}

unsigned int hash_func(const char *key, const unsigned int table_size)
{
	unsigned int h = 0;
	unsigned int o = 31415;
	const unsigned int t = 27183;
	while (*key)
	{
		h = (o * h + *key++) % table_size;
		o = o * t % (table_size - 1);
	}
	return h;
}

void set(string key, string value) {
    streampos nodePosition = findNodePositionByKeyForSet(key);
    struct Node node;
    strncpy(node.key, key.c_str(), KEY_SIZE + 1);
    strncpy(node.value, value.c_str(), VALUE_SIZE + 1);
    node.next = 0;
    table.seekp(nodePosition);
    table.write(reinterpret_cast<char*>(&node), sizeof(struct Node));
}


string inputFormatted(void errFunc(), size_t size) {
    string input;
    cin >> input;
    input = parseFormatted(input);
    if (input == "" || input.size() > size) (*errFunc)();
    return input;
}


string inputStr(size_t size){
    char *str = (char*) malloc(1 * sizeof(char));
    int len = 0;
    char ch;
    while ((ch = getchar()) != EOF && ch != '\n' && len < size) {
        *(str + len) = ch;
        len++;
        str = (char*) realloc(str, len + 1);
    }
    *(str + len) = '\0';
    string input = string(str);
    free(str);
    return input;
}

void ignoreInput() {
    cin.ignore(1000, '\n');
}


void emptyBlock(streampos from, streampos size) {
    if (table.is_open()) {
        table.seekp(from);
        for (int i = 0; i < size; i++) {
            table.write("\0", 1); // Fill by zero
        }
    }
}


void gen_random(char *s, size_t len) {
     for (size_t i = 0; i < len; ++i) {
         int randomChar = rand()%(26+26+10);
         if (randomChar < 26)
             s[i] = 'a' + randomChar;
         else if (randomChar < 26+26)
             s[i] = 'A' + randomChar - 26;
         else
             s[i] = '0' + randomChar - 26 - 26;
     }
     s[len] = 0;
 }