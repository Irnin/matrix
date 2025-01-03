#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class matrix {
private:
    char name;
    int nrRow;
    int nrColumn;

    vector<vector<float> > macierz ;

    int ilosc_cyfr(float number)
    {
        stringstream ss (stringstream::in | stringstream::out);
        ss << number;
        string test = ss.str();
        return test.length();
    }

public:
    matrix(short nrMatrix, int m_nrRow, int m_nrCol)
    {
        name=65+nrMatrix;
        nrRow=m_nrRow;
        nrColumn=m_nrCol;

        vector<float> tab ;
        for(int j=0;j<nrColumn;j++)
            tab.push_back(0);

        for (int i = 0 ; i < nrRow ; i++)
            macierz.push_back(tab) ;
    }

    void writeMatrix()
    {
        float tmp;

        for(int i=0;i<nrRow;i++)
        {
            for(int j=0; j<nrColumn; j++)
            {
                cout << "[" << i << "x" << j << "]: ";
                cin >> tmp;
                macierz[i][j]=tmp;
            }
        }
        cout << endl << " < macierz utworzono >" << endl << endl;
    }

    void inputValues(int m_nrRow, int m_nrCol, float value)
    {macierz[m_nrRow][m_nrCol]=value;}


    void print()
    {
        cout << " maciez " << name << ":" << endl;
        short dlugosc_liczby[nrColumn];
        for(int i=0; i<nrColumn; i++)
            dlugosc_liczby[i]=0;

        for(int i=0;i<nrRow;i++)
        {
            for(int j=0; j<nrColumn; j++)
            {
                if(dlugosc_liczby[j]<ilosc_cyfr(macierz[i][j]))
                    dlugosc_liczby[j]=ilosc_cyfr(macierz[i][j]);
            }
        }

        for(int i=0;i<nrRow;i++)
        {
            cout << " ";
            if(nrRow==1) cout << "[ ";
            else
            {
                if(i==0) cout << char(218) << " ";
                else if(i==nrRow-1) cout << char(192) << " ";
                else cout << char(179) << " ";
            }

            for(int j=0; j<nrColumn; j++)
            {
                for(int k=0; k<(dlugosc_liczby[j]-ilosc_cyfr(macierz[i][j]));k++)
                    cout << " ";
                cout << macierz[i][j] << " ";
            }

            if(nrRow==1) cout << "]";
            else
            {
                if(i==0) cout << char(191);
                else if(i==nrRow-1) cout << char(217);
                else cout << char(179);
            }
            cout << endl;
        }
    }

    string displayDimension()
    {
        stringstream tmp;
        tmp << '[' << nrRow << 'x' << nrColumn << ']';
        string tmp2 = tmp.str();
        return tmp2;
    }

    int matrixSize(char sign)
    {
        if(sign=='r') return nrRow;
        else if(sign=='c') return nrColumn;
    }

    float matrixElent(int m_nrRow, int m_nrCol)
    { return macierz[m_nrRow][m_nrCol];}

    char martixName()
    { return name; }

};

int main()
{
    short nrRow;
    short nrColumn;

    short choice;

    float value_1;
    float value_2;
    float tmp;

    char choice2;
    char choice3;

    vector<matrix> matrixList;

    for(;;)
    {
        cout << "=======================================" << endl;
        cout << "           Matrix Calculator" << endl << endl;
        cout << " Prsze dokonac wyboru:" << endl;
        cout << "   1) Dodaj nowa macierz" << endl;
        cout << "   2) Wyswietl liste macierzy" << endl;
        cout << "   3) Usuwanie macierzy z pamieci" << endl;
        cout << "   4) Wypisz zawartosc macierzy" << endl;
        cout << "   5) Dodaj macierze" << endl;
        cout << "   6) Przemnuz macierze" << endl;
        cout << "   7) Zakoncz prace" << endl;

        cout << " > ";

        cin >> choice;

        cout << "======================================" << endl;
        cout << endl << endl;

        switch(choice)
        {
        case 1:
            cout << "Tworzenie macierzy:" << endl;
            cout << "Prosze podac ilosc wierszy: "; cin >> nrRow;
            cout << "Prosze podac ilosc kolumn: "; cin >> nrColumn;

            if(nrRow>0 && nrColumn>0)
            {
                cout << "Prosze wpisac wartosci do macierzy: " << endl;

                matrixList.push_back(matrix(matrixList.size(),nrRow,nrColumn));
                matrixList[matrixList.size()-1].writeMatrix();
            }
            else
                cout << " < nie mozna utworzyc takiej macierzy >" << endl << endl;

            break;

        case 2:
            if(matrixList.size()>0)
            {
                cout << " W pamieci znajduja sie nastepujace macierze: " << endl << endl;

                for(short i=0; i<matrixList.size();i++)
                    cout << " " << matrixList[i].martixName() << " " << matrixList[i].displayDimension() << endl;
                cout << endl;
            }
            else cout << " < Nie istnieja macierze do wyswietlenia >" << endl << endl;

            break;

        case 3:
            if(matrixList.size()>0)
            {
                for(short i=matrixList.size()-1; i>=0 ;i--)
                    matrixList.pop_back();
            }
            else cout << " < Nie ma macierzy w pamieci >" << endl << endl;

            break;

        case 4:
            cout << " Ktora macierz wyswietlic? " << endl;
            cout << " [A-Z] > ";
            cin >> choice2;

            if(int(choice2)-65<matrixList.size())
                matrixList[int(choice2)-65].print();
            else
                cout << endl << " < Podana macierz nie istnieje > " << endl << endl;
            break;

        case 5:
            cout << " Ktore macierze dodac? " << endl;
            cout << " macierz pierwsza: [A-Z] > "; cin >> choice2;
            cout << " macierz pierwsza: [A-Z] > "; cin >> choice3;

            if(matrixList[int(choice2)-65].displayDimension()==matrixList[int(choice3)-65].displayDimension())
            {
                nrRow=matrixList[int(choice2)-65].matrixSize('r');
                nrColumn=matrixList[int(choice2)-65].matrixSize('c');

                matrixList.push_back(matrix(matrixList.size(),nrRow,nrColumn));

                for(int i=0;i<nrRow;i++)
                {
                    for(int j=0; j<nrColumn; j++)
                    {
                        value_1 = matrixList[int(choice2)-65].matrixElent(i,j);
                        value_2 = matrixList[int(choice3)-65].matrixElent(i,j);

                        matrixList[matrixList.size()-1].inputValues(i,j,value_1+value_2);
                    }
                }
            }
            else
                cout << "  < Podanych macierzy nie mozna dodac >" << endl;
            break;

            case 6:
            cout << " Ktore macierze przemnozyc? " << endl;
            cout << " macierz pierwsza: [A-Z] > "; cin >> choice2;
            cout << " macierz pierwsza: [A-Z] > "; cin >> choice3;

            if(matrixList[int(choice2)-65].matrixSize('c')==matrixList[int(choice3)-65].matrixSize('r'))
            {
                nrRow=matrixList[int(choice2)-65].matrixSize('r');
                nrColumn=matrixList[int(choice3)-65].matrixSize('c');

                matrixList.push_back(matrix(matrixList.size(),nrRow,nrColumn));

                for(int i=0;i<nrRow;i++)
                {
                    for(int j=0; j<nrColumn; j++)
                    {
                        tmp=0;
                        for(int k=0; k<matrixList[int(choice2)-65].matrixSize('c'); k++)
                        {
                            tmp+=matrixList[int(choice2)-65].matrixElent(i,k)*matrixList[int(choice3)-65].matrixElent(k,j);
                        }
                        matrixList[matrixList.size()-1].inputValues(i,j,tmp);
                    }
                }

                cout << "  < macierze zostaly przemnozone >" << endl;
            }
            else
                cout << "  < Podanych macierzy nie mozna przemnozyc >" << endl;
            break;

            case 7:
                return 0;
                break;
            default:
                cout << "  < Nie isnieje operacja o podanym indeksie >" << endl << endl;
        }
    }

    return 0;
}
