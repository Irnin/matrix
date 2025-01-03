#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;
const double eps = 1e-12;

class matrix {
private:
    char name;
    int nrRow;
    int nrColumn;
    double wyz;

    vector<vector<float> > macierz;
    vector<vector<float> > macierz_kopia;
    vector<vector<float> > macierz_odwrotna;

    void kopia()
    {
        vector<float> tab ;
        for(int j=0;j<nrColumn;j++)
            tab.push_back(0);

        for (int i = 0 ; i < nrRow ; i++)
            macierz_kopia.push_back(tab) ;

        for(int i=0;i<nrRow;i++)
        {
            for(int j=0; j<nrColumn; j++)
            {
                macierz_kopia[i][j]=macierz[i][j];
            }
        }
    }

    void przywruc()
    {
        for(int i=0;i<nrRow;i++)
        {
            for(int j=0; j<nrColumn; j++)
            {
                macierz[i][j]=macierz_kopia[i][j];
            }
        }
    }

    int ilosc_cyfr(float number)
    {
        stringstream ss (stringstream::in | stringstream::out);
        ss << number;
        string test = ss.str();
        return test.length();
    }

    //=============================================================Operacje elementarne
    void zamiana_wierszy(short x, short y)
    {
        for(short i=0; i<nrColumn; i++)
        {
            swap(macierz[x][i],macierz[y][i]);
            swap(macierz_odwrotna[x][i],macierz_odwrotna[y][i]);
        }
    }

    void dodaj_wierszy(short x, short y, double c)
    {
        for(short i=0; i<nrColumn; i++)
        {
            macierz[x][i]+=c*macierz[y][i];
            macierz_odwrotna[x][i]+=c*macierz_odwrotna[y][i];
        }
    }

    void przemnuz_wiersz(short x, double c)
    {
        for(short i=0; i<nrColumn; i++)
        {
            macierz[x][i]*=c;
            macierz_odwrotna[x][i]*=c;
        }
    }

public:
    matrix(short nrMatrix, int m_nrRow, int m_nrCol)
    {
        //tworzenie zerowej macierzy

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
        //Wpisywanie warto�ci do macierzy
        float tmp;

        for(int i=0;i<nrRow;i++)
        {
            for(int j=0; j<nrColumn; j++)
            {
                cout << "   [" << i << "x" << j << "]: ";
                cin >> tmp;
                macierz[i][j]=tmp;
            }
        }
        cout << endl << "   < macierz utworzono >" << endl << endl;
    }

    void inputValues(int m_nrRow, int m_nrCol, float value)
    {macierz[m_nrRow][m_nrCol]=value;}

    //========================================================================Wypisanie
    void print(bool pOdwrotna)
    {
        if(pOdwrotna) cout << endl <<"   maciez odwrotna do " << name << ":" << endl;
        else cout << endl <<"   maciez " << name << ":" << endl;

        short dlugosc_liczby[nrColumn];

        for(int i=0; i<nrColumn; i++)
            dlugosc_liczby[i]=0;

        for(int i=0;i<nrRow;i++)
        {
            for(int j=0; j<nrColumn; j++)
            {
                if(pOdwrotna)
                {
                    if(dlugosc_liczby[j]<ilosc_cyfr(macierz_odwrotna[i][j]))
                        dlugosc_liczby[j]=ilosc_cyfr(macierz_odwrotna[i][j]);
                }
                else
                {
                    if(dlugosc_liczby[j]<ilosc_cyfr(macierz[i][j]))
                        dlugosc_liczby[j]=ilosc_cyfr(macierz[i][j]);
                }

            }
        }

        for(int i=0;i<nrRow;i++)
        {
            cout << "   ";
            if(nrRow==1) cout << "[ ";
            else
            {
                if(i==0) cout << char(218) << " ";
                else if(i==nrRow-1) cout << char(192) << " ";
                else cout << char(179) << " ";
            }

            for(int j=0; j<nrColumn; j++)
            {
                if(pOdwrotna)
                {
                    for(int k=0; k<(dlugosc_liczby[j]-ilosc_cyfr(macierz_odwrotna[i][j]));k++)
                        cout << " ";
                    cout << macierz_odwrotna[i][j] << " ";
                }
                else
                {
                    for(int k=0; k<(dlugosc_liczby[j]-ilosc_cyfr(macierz[i][j]));k++)
                        cout << " ";
                    cout << macierz[i][j] << " ";
                }

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

    //========================================================================Zwrucenia

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

    float InvertibleMatrixElent(int m_nrRow, int m_nrCol)
    { return macierz_odwrotna[m_nrRow][m_nrCol];}

    char martixName()
    { return name; }

    float wypisz_wyznacznik()
    { return wyz; }

    bool czy_kwadratowa()
    {
        if(nrRow==nrColumn) return true;
        else return false;
    }

    //=================================================================Macierz odwrotna
    void odwrotna()
    {
        vector<float> tab ;
        for(int j=0;j<nrColumn;j++)
            tab.push_back(0);

        for (int i = 0 ; i < nrRow ; i++)
            macierz_odwrotna.push_back(tab);

        for(int i=0;i<nrRow;i++)
            for(int j=0; j<nrColumn; j++)
                macierz_odwrotna[i][j]=0;

        for(int i=0, j=0; i<nrRow; i++, j++)
            macierz_odwrotna[i][j]=1;
    }

    void wyznacz_odwrotna(bool wypisac)
    {
        if(nrRow==nrColumn)
        {
            odwrotna();
            kopia();

            int row=0;
            int col=0;

            while(row < nrRow && col < nrColumn)
            {
                int j = 0;
                while(j+row<nrRow && macierz[j+row][col]==0)
                    j++;

                if(j+row==nrRow) col++;
                else
                {
                    if(j!=0) zamiana_wierszy(row, j+row);

                    if(macierz[row][col]!=1) przemnuz_wiersz(row, 1/macierz[row][col]);

                    for(j=0; j<nrRow; j++)
                        if(j!=row && macierz[j][col]!=0)
                            dodaj_wierszy(j, row, -macierz[j][col]);
                    row++;
                    col++;
                }
            }

            przywruc();

            if(wypisac==true) print(true);
        }
        else
            cout << "   < Nie mozna obliczyc maciezy odwrotnej > " << endl << endl;

    }

    //=======================================================================Wyznacznik
    bool lu()
    {
        wyz=0;
        for(int k=0; k<nrColumn-1; k++)
        {
            if(fabs(macierz[k][k])<eps)
                return false;

            for(int i=k+1; i<nrColumn; i++)
                macierz[i][k]/=macierz[k][k];

            for(int i=k+1; i<nrColumn; i++)
                for(int j=k+1; j<nrColumn; j++)
                    macierz[i][j]-=macierz[i][k]*macierz[k][j];
      }
      return true;
    }

    void wyznacznik()
    {
        kopia();

        if(nrColumn==nrRow)
        {
            if(lu())
            {
                wyz = macierz[0][0];
                for(int i = 1; i < nrColumn; i++)
                    wyz *= macierz[i][i];
            }
        }
        przywruc();
    }
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
    char choice4;

    vector <matrix> matrixList;

    for(;;)
    {
        cout << "===================================================================" << endl;
        cout << "                       Matrix Calculator                           " << endl << endl;

        cout << "   Prsze dokonac wyboru:                                           " << endl;
        cout << "   1) Dodaj nowa macierz            6) Przemnuz macierze           " << endl;
        cout << "   2) Wyswietl liste macierzy       7) Oblicz wyznacznik           " << endl;
        cout << "   3) Usuwanie macierzy z pamieci   8) Oblicz macierz odwrotna     " << endl;
        cout << "   4) Wypisz zawartosc macierzy     9) Oblicz rownanie  AX + B = C " << endl;
        cout << "   5) Dodaj macierze                10) Zakoncz prace              " << endl;
        cout << endl;

        cout << "   > ";
        cin >> choice;

        cout << "===================================================================" << endl;
        cout << endl;

        switch(choice)
        {
        case 1:
            cout << "   Tworzenie macierzy:" << endl;
            cout << "   Prosze podac ilosc wierszy: "; cin >> nrRow;
            cout << "   Prosze podac ilosc kolumn: "; cin >> nrColumn;
            cout << endl;

            if(nrRow>0 && nrColumn>0)
            {
                cout << "   Prosze wpisac wartosci do macierzy: " << endl;

                matrixList.push_back(matrix(matrixList.size(),nrRow,nrColumn));
                matrixList[matrixList.size()-1].writeMatrix();
            }
            else
                cout << "   < nie mozna utworzyc takiej macierzy >" << endl << endl;

            break;

        case 2:
            if(matrixList.size()>0)
            {
                cout << "   W pamieci znajduja sie nastepujace macierze: " << endl << endl;

                for(short i=0; i<matrixList.size();i++)
                    cout << "   " << matrixList[i].martixName() << " " << matrixList[i].displayDimension() << endl;
                cout << endl;
            }
            else cout << "   < Nie istnieja macierze do wyswietlenia >" << endl << endl;

            break;

        case 3:
            if(matrixList.size()>0)
            {
                for(short i=matrixList.size()-1; i>=0 ;i--)
                    matrixList.pop_back();
            }
            else cout << "   < Nie ma macierzy w pamieci >" << endl << endl;

            break;

        case 4:
            cout << "   Ktora macierz wyswietlic? " << endl;
            cout << "   macierz [A-Z] > ";
            cin >> choice2;

            if(int(choice2)-65<matrixList.size())
                matrixList[int(choice2)-65].print(false);
            else
                cout << endl << "   < Podana macierz nie istnieje > " << endl << endl;
            break;

        case 5:
            cout << "   Ktore macierze dodac? " << endl;
            cout << "   macierz pierwsza: [A-Z] > "; cin >> choice2;
            cout << "   macierz druga:    [A-Z] > "; cin >> choice3;

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

                matrixList[matrixList.size()-1].print(false);
            }
            else
                cout << "   < Podanych macierzy nie mozna dodac >" << endl;
            break;

            case 6:
            cout << "   Ktore macierze przemnozyc? " << endl;
            cout << "   macierz pierwsza: [A-Z] > "; cin >> choice2;
            cout << "   macierz pierwsza: [A-Z] > "; cin >> choice3;

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

                matrixList[matrixList.size()-1].print(false);
            }
            else
                cout << "   < Podanych macierzy nie mozna przemnozyc >" << endl;
                break;

            case 7:
                cout << "   Wyznacznik macierzy: " << endl;
                cout << "   macierz: [A-Z] > "; cin >> choice2;

                if(matrixList[int(choice2)-65].czy_kwadratowa())
                {
                    matrixList[int(choice2)-65].wyznacznik();
                    cout << " Wyznacznik: " << matrixList[int(choice2)-65].wypisz_wyznacznik() << endl << endl;
                }
                else cout << "   < Nie mozna obliczyc wyznacznika macierzy >" << endl;

                break;

            case 8:
                cout << "   Odwracanie macierzy: " << endl;
                cout << "   macierz: [A-Z] > "; cin >> choice2;

                matrixList[int(choice2)-65].wyznacz_odwrotna(1);


                break;
            case 9:

                cout << "   Ktore macierze Podstawic pod rownanie AX + B = C? " << endl;
                cout << "   A: [A-Z] > "; cin >> choice2;
                cout << "   B: [A-Z] > "; cin >> choice3;
                cout << "   C: [A-Z] > "; cin >> choice4;

                if(matrixList[int(choice2)-65].matrixSize('c')==matrixList[int(choice3)-65].matrixSize('r')&&(matrixList[int(choice3)-65].displayDimension()==matrixList[int(choice4)-65].displayDimension()))
                {

                    //--------------------------------------------------------------Dodawanie
                    nrRow=matrixList[int(choice3)-65].matrixSize('r');
                    nrColumn=matrixList[int(choice3)-65].matrixSize('c');

                    matrixList.push_back(matrix(matrixList.size(),nrRow,nrColumn));

                    for(int i=0;i<nrRow;i++)
                    {
                        for(int j=0; j<nrColumn; j++)
                        {
                            value_1 = matrixList[int(choice4)-65].matrixElent(i,j);
                            value_2 = matrixList[int(choice3)-65].matrixElent(i,j);

                            matrixList[matrixList.size()-1].inputValues(i,j,value_1-value_2);
                        }
                    }

                    //-------------------------------------------------------------Odwracanie
                    matrixList[int(choice2)-65].wyznacz_odwrotna(0);

                    //---------------------------------------------------------------Mnozenie
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
                                tmp+=matrixList[int(choice2)-65].InvertibleMatrixElent(i,k)*matrixList[int(choice3)-65].matrixElent(k,j);
                            }
                            matrixList[matrixList.size()-1].inputValues(i,j,tmp);
                        }
                    }
                    //------------------------------------------------------------Wypisywanie
                    matrixList[matrixList.size()-1].print(false);
                }
                else
                    cout << "   < Nie mozna wykonac operacji na podanych macierzach >" << endl;

                break;
            case 10:
                cout << "   < Wychodzenie z programu >" << endl;
                return 0;
                break;

            default:
                cout << "   < Nie isnieje operacja o podanym indeksie >" << endl << endl;
        }
    }

    return 0;
}
