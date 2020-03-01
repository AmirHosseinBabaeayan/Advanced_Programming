#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <math.h>

using namespace std;
typedef short int pixel;
typedef size_t counter;

pixel *** createEmptyMatrix ( short int height , short int width ){
    pixel *** const emptyMatrix = new pixel ** [height];
    for ( counter i=0 ; i<height ; i++ ){
        *(emptyMatrix + i) = new pixel * [width];
        for ( counter j=0 ; j<width ; j++ ){
        *(*(emptyMatrix + i) + j) = new pixel [3];
            for ( counter k=0 ; k<3 ; k++ ){
                *(*(*(emptyMatrix + i) + j ) + k) = 0 ;
            }
        }
    }
    return emptyMatrix;
}

short int *** createImage ( short int height , short int width ){
    srand( static_cast < unsigned int > ( time(0) ) ) ;
    static unsigned int seed = rand();
    srand(seed) ;
    pixel *** const matrixPic = new pixel ** [height];
    for ( counter i=0 ; i<height ; i++ ){
        *(matrixPic + i) = new pixel * [width];
        for ( counter j=0 ; j<width ; j++ ){
        *(*(matrixPic + i) + j) = new pixel [3];
            for ( counter k=0 ; k<3 ; k++ ){
                *(*(*(matrixPic + i) + j ) + k) = rand() % 256;
            }
        }
    }
    seed ++ ;
    return matrixPic;
}

void display( short int const * const * const * const matrixPic , short int height , short int width ){
    for ( counter i=0 ; i<height ; i++ ){
        for ( counter j=0 ; j<width ; j++ ){
            cout << "[" ;
            for ( counter k=0 ; k<3 ; k++ ){
                cout << setw(4) << *(*(*(matrixPic + i) + j ) + k ) ;
            }
            cout << "]" << " " ;
        }
        cout << endl ;
    }
}

short int*** addImage(short int const * const * const * const matrixPic1, short int const * const * const * const matrixPic2 , short int height , short int width ){
    pixel *** emptyMatrix = createEmptyMatrix ( height , width ) ;
    for ( counter i=0 ; i<height ; i++ ){
        for ( counter j=0 ; j<width ; j++ ){
            for( counter k=0 ; k<3 ; k++ ){
                pixel sum = *(*(*(matrixPic1 + i ) + j ) + k ) + *(*(*(matrixPic2 + i ) + j ) + k ) ;
                if ( sum > 255 ) *(*(*( emptyMatrix + i ) + j ) + k ) = 255 ;
                else *(*(*( emptyMatrix + i ) + j ) + k ) = sum ;
            }
        }
    }
    return emptyMatrix ;
}

short int*** diffImage( short int const * const * const * const matrixPic1 , short int const * const * const * const matrixPic2 , short int height , short int width ){
    pixel *** emptyMatrix = createEmptyMatrix ( height , width ) ;
    for ( counter i=0 ; i<height ; i++ ){
        for ( counter j=0 ; j<width ; j++ ){
            for( counter k=0 ; k<3 ; k++ ){
                pixel sub = abs( *(*(*(matrixPic1 + i ) + j ) + k ) - *(*(*(matrixPic2 + i ) + j ) + k ) ) ;
                *(*(*( emptyMatrix + i ) + j ) + k ) = sub ;
            }
        }
    }
    return emptyMatrix ;
}

void rotateImage( const short int*** matrixPic , short int height , short int width ){
    pixel *** tempMatrix = createEmptyMatrix( width , height ) ;
    for ( counter j = 0 ; j < width ; j++ ){
        for ( counter i=0 ; i < height ; i++ ){
                *(*(tempMatrix + j ) + i ) = *(*(const_cast < pixel *** > ( matrixPic ) + i ) + (width - (j+1)) ) ;
            }
        }
    matrixPic = const_cast < const short int *** > ( tempMatrix ) ;
    for ( counter i = 0 ; i < width ; i++ ){
        for ( counter j=0 ; j < height ; j++ ){
            cout << "[" ;
            for ( counter k=0 ; k<3 ; k++){
                cout << setw(4) << *(*(*(matrixPic + i ) + j ) + k ) ;
            }
            cout << "]" << " " ;
        }
        cout << endl ;
    }
}

short int**** createVideo(short int n, short int height , short int width){
    srand( static_cast < unsigned int > ( time(0) ) ) ;
    static unsigned int seed = rand();
    srand(seed) ;
    pixel **** const matrixVideo = new pixel *** [n] ;
    for ( counter i=0 ; i<n ; i++ ){
        *(matrixVideo + i) = new pixel ** [height] ;
        for ( counter j=0 ; j<height ; j++ ){
            *(*(matrixVideo+i)+j) = new pixel * [width] ;
            for ( counter k=0 ; k<width ; k++ ){
                *(*(*(matrixVideo + i ) + j ) + k ) = new pixel [3] ;
                for ( counter l=0 ; l<3 ; l++ ){
                    *(*(*(*(matrixVideo + i ) + j ) + k ) + l ) = rand()%256 ;
                }
            }
        }
    }
    seed ++ ;
    return matrixVideo ;
}

void display(short int const * const * const * const * const matrixVideo , short int n, short int width, short int height){
    for ( counter i=0 ; i<n ; i++ ){
        cout << "Frame" << " " << i+1 << endl ;
        for ( counter j=0 ; j<height ; j++ ){
            for ( counter k=0 ; k<width ; k++ ){
                cout << "[" ;
                for ( counter l=0 ; l<3 ; l++ ){
                    cout << setw(4) << *(*(*(*(matrixVideo + i ) + j ) + k ) + l );
                }
                cout << "]" << " ";
            }
            cout << endl ;
        }
    }
}

void swapFrames(short int const * const * const * * const matrixVideo , short int f1, short int f2){
    f1 = f1 - 1 ;
    f2 = f2 - 1 ;
    pixel const * const * const * temp = *( matrixVideo + f1 ) ;
    *( matrixVideo + f1 ) = *( matrixVideo + f2 ) ;
    *( matrixVideo + f2 ) = temp ;
}

void freeMemory(short int **** matrixVideo , short int n, short int height, short int width){
    for ( counter i=0 ; i<n ; i++ ){
        for ( counter j=0 ; j<height ; j++ ){
            for ( counter k=0 ; k<width ; k++ ){
                    delete ( *(*(*(matrixVideo + i ) + j ) + k ) ) ;
            }
        }
    }
    for ( counter i=0 ; i<n ; i++ ){
        for ( counter j=0 ; j<height ; j++ ){
                    delete ( *(*(matrixVideo + i ) + j ) ) ;
        }
    }
    for ( counter i=0 ; i<n ; i++ ){
                    delete ( *(matrixVideo + i ) ) ;
    }
    delete ( matrixVideo ) ;
}

void freeMemory(short int *** matrixPic , short int width, short int height){
    for ( counter i=0 ; i<height ; i++ ){
        for ( counter j=0 ; j<width ; j++ ){
                delete ( *(*(matrixPic + i ) + j ) ) ;
        }
    }
    for ( counter i=0 ; i<height ; i++ ){
                delete ( *(matrixPic + i) ) ;
    }
    delete ( matrixPic ) ;
}

int main()
{
    string command ;
    cout << "valid commands : " << endl ;
    cout << "1.exit" << endl ;
    cout << "2.displayPic" << endl ;
    cout << "3.addImage" << endl ;
    cout << "4.diffImage" << endl ;
    cout << "5.rotateImage" << endl ;
    cout << "6.displayVideo" << endl ;
    cout << "7.swapFrames" << endl ;
    cin >> command ;
    while( command != "1" ){
        if ( command == "2" ){
            short int height , width ;
                cout << "Enter height and width respectively " << endl ;
                cin >> height >> width ;
                pixel *** matrixPic = createImage( height , width );
                display( const_cast < short int const * const * const * const > ( matrixPic ) , height , width ) ;
                freeMemory( matrixPic , width , height ) ;
        }
        else if ( command == "3" ){
            short int height , width ;
            cout << "Enter first and second height and width respectively" << endl ;
            cin >> height >> width ;
            pixel *** matrixPic1 = createImage ( height , width ) ;
            pixel *** matrixPic2 = createImage ( height , width ) ;
            pixel *** matrixPicResult = addImage ( const_cast < short int const * const * const * const > ( matrixPic1 ) , const_cast < short int const * const * const * const > ( matrixPic2 ) , height , width ) ;
            cout << "First Picture : " << endl ;
            display( const_cast < short int const * const * const * const > ( matrixPic1 ) , height , width ) ;
            cout << "Second Picture : " << endl ;
            display( const_cast < short int const * const * const * const > ( matrixPic2 ) , height ,width ) ;
            cout << "addition Result :" << endl ;
            display ( const_cast < short int const * const * const * const > ( matrixPicResult ) , height , width ) ;
            cout << endl ;
            freeMemory( matrixPic1 , width , height ) ;
            freeMemory( matrixPic2 , width , height ) ;
            freeMemory( matrixPicResult , width , height ) ;
        }
        else if ( command == "4" ){
            short int height , width ;
            cout << "Enter first and second height and width respectively" << endl ;
            cin >> height >> width ;
            pixel *** matrixPic1 = createImage ( height , width ) ;
            pixel *** matrixPic2 = createImage ( height , width ) ;
            pixel *** matrixPicResult = diffImage ( matrixPic1 , matrixPic2 , height , width ) ;
            cout << "First Picture : " << endl ;
            display( const_cast < short int const * const * const * const > ( matrixPic1 ) , height , width ) ;
            cout << "Second Picture : " << endl ;
            display( const_cast < short int const * const * const * const > ( matrixPic2 ) , height ,width ) ;
            cout << "subtraction Result :" << endl ;
            display ( const_cast < short int const * const * const * const > ( matrixPicResult ) , height , width ) ;
            cout << endl ;
            freeMemory( matrixPic1 , width , height ) ;
            freeMemory( matrixPic2 , width , height ) ;
            freeMemory( matrixPicResult , width , height ) ;
        }
        else if ( command == "5") {
            short int height , width ;
            cout << "Enter height and width respectively" << endl ;
            cin >> height >> width ;
            pixel *** matrixPic = createImage( height , width ) ;
            display ( const_cast < short int const * const * const * const > ( matrixPic ) , height , width ) ;
            cout << endl ;
            rotateImage ( const_cast < const pixel *** > ( matrixPic ) , height , width ) ;
            freeMemory( matrixPic , width , height ) ;
        }
        else if ( command == "6" ){
            cout << "Enter n frame you want to create and height and width respectively " << endl ;
            short int n , height , width ;
            cin >> n >> height >> width ;
            pixel **** matrixVideo = createVideo ( n , height , width ) ;
            display( const_cast < short int const * const * const * const * const > ( matrixVideo ) , n , width , height ) ;
            freeMemory( matrixVideo , n , height , width ) ;
        }
        else if ( command == "7" ){
            cout << "Enter n frame you want to create and height and width respectively " << endl ;
            short int n , height , width ;
            cin >> n >> height >> width ;
            pixel **** matrixVideo = createVideo ( n , height , width ) ;
            display( const_cast < short int const * const * const * const * const > ( matrixVideo ) , n , width , height ) ;
            cout << "Enter first and second number of frames you want to swap " << endl ;
            short int f1 , f2 ;
            cin >> f1 >> f2 ;
            if ( f1 <= n || f2 <= n ){
                swapFrames( const_cast < short int const * const * const * * const > ( matrixVideo ) , f1 , f2 ) ;
                display( const_cast < short int const * const * const * const * const > ( matrixVideo ) , n , width , height ) ;
            }
            else cout << "not valid"  << endl ;
            freeMemory( matrixVideo , n ,height ,width ) ;
        }
        else cout << "invalid command " << endl ;

    cout << endl << "valid commands : " << endl ;
    cout << "1.exit" << endl ;
    cout << "2.displayPic" << endl ;
    cout << "3.addImage" << endl ;
    cout << "4.diffImage" << endl ;
    cout << "5.rotateImage" << endl ;
    cout << "6.displayVideo" << endl ;
    cout << "7.swapFrames" << endl ;
    cin >> command ;
    }
    return 0;
}
