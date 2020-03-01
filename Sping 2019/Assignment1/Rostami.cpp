//This code has written for create a simple database that can set value get value Delete value and extra
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
fstream DataBase ;
//person struct definition 
struct person {
	string Key;
	string Value;
};
typedef struct person Person;
//Use function definiton
void Use ( string DataBaseName ) {
    DataBaseName = DataBaseName + ".txt" ;
    DataBase.open( DataBaseName , ios::out | ios::app  );
    DataBase.close();
}
//Set function definiton
void Set ( Person p , string DataBaseName ) {
    DataBaseName = DataBaseName + ".txt" ;
    DataBase.open( DataBaseName , ios::in | ios::out | ios::app ) ;
    Person search ;
    DataBase << p.Key << " ";
    DataBase << p.Value << endl ; 
    DataBase.close();
}
//Get function definiton
void Get ( Person p , string DataBaseName ) {
    DataBaseName = DataBaseName + ".txt" ;
    DataBase.open( DataBaseName , ios::in | ios::app );
    Person search ;
    string temp = "NOTHING" ;
    bool flag = false ; 
    bool not_found = false ;
    while( !DataBase.eof() ){
        DataBase >> search.Key ;      
        if( search.Key == p.Key ) {
        DataBase >> search.Value ;
        flag = true ;
        not_found = true ;
        temp = search.Value ; 
        }
        else DataBase >> search.Value ; 
    }
    if ( temp == "NOTHING" ) flag = false ; 
    if ( not_found != false && flag == true ) cout << temp << endl ; 
    else cout << "not found" << endl ; 
    DataBase.clear();
    DataBase.close();
}
//Delete function definiton
void Delete ( Person p , string DataBaseName ) {
    Person pass = { p.Key , "NOTHING"} ; 
    Set ( pass , DataBaseName ) ;
}
//Exist function definiton
void Exist ( Person p , string DataBaseName ) {
    DataBaseName = DataBaseName + ".txt" ;
    DataBase.open( DataBaseName , ios::in | ios::app );
    Person search ;
    string temp = "NOTHING" ;
    bool flag = false ; 
    while( !DataBase.eof() ){
        DataBase >> search.Key ;      
        if( search.Key == p.Key ) {
        DataBase >> search.Value ;
        flag = true ;
        temp = search.Value ; 
        }
        else DataBase >> search.Value ; 
    }
    if ( temp == "NOTHING" ) flag = false ; 
    if ( flag == true ) cout << "1" << endl ;
    else cout << "0" << endl ; 
    DataBase.clear();
    DataBase.close();
}
//main function
int main()
{
    //determin variable in main scope
    string Line;
    string DataBaseName ;
    Person p;
        cout << "> ";
	    getline( cin , Line );
        string Command = Line.substr( 0 , Line.find_first_of(' ')) ;
        //Check value of command that user enter
    while(Command != "USE") { 
        cout << "please choose a database first" << endl ;
        cout << "> ";
	    getline( cin , Line );
        Command = Line.substr( 0 , Line.find_first_of(' ')) ;
    }
    //define commands operation
    while( Command != "EXIT" ){
        
        if( Command == "USE" ){
            //assigning database name and pass to Use function
            DataBaseName = Line.substr( Line.find_first_of(' ') + 1 , Line.length() ) ;
            Use ( DataBaseName );
        }
        else if ( Command == "SET" ){
            //assigning Key and Value var to SET
            p.Key = Line.substr( Line.find_first_of("(") + 1 , Line.find_first_of(")") - Line.find_first_of("(") - 1 );
            Line = Line.substr( Line.find_first_of(")") + 1 , Line.length()  ) ;
            p.Value = Line.substr( Line.find_first_of("(") + 1 , Line.find_first_of(")") - Line.find_first_of("(") - 1 ) ;
            //pass by value to function SET
            Set ( p , DataBaseName ) ;
        }
        else if ( Command == "GET" ){
            //assigning Key var to GET
            p.Key = Line.substr( Line.find_first_of("(") + 1 , Line.find_first_of(")") - Line.find_first_of("(") - 1 );
            //pass by value to function GET
            Get ( p , DataBaseName ) ; 
        }
        else if ( Command == "DELETE" ){
            //assigning Key var to DELETE
            p.Key = Line.substr( Line.find_first_of("(") + 1 , Line.find_first_of(")") - Line.find_first_of("(") - 1 );
            //pass by value to function DELETE
            Delete ( p , DataBaseName ) ; 
        }
        else if ( Command == "EXIST" ){
            //assigning Key var to EXIST
            p.Key = Line.substr( Line.find_first_of("(") + 1 , Line.find_first_of(")") - Line.find_first_of("(") - 1 );
            //pass by value to function EXIST
            Exist ( p , DataBaseName ) ; 
        }
        //initialize Key and Value
        cout << DataBaseName << "> " ;
        getline( cin , Line );
        Command = Line.substr( 0 , Line.find_first_of(' ')) ;
    }
    return 0;
}


