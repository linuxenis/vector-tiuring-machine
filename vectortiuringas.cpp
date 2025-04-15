#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <locale>
#include <cmath>
#include <vector>
#include <map>
#include <windows.h>
#include <conio.h>

using namespace std;

//                         \/be argumentu
const string failas = "6.txt";

struct bus
{
    vector<char> esamas1, esamas2, naujas1, naujas2;
    vector<int> judejimas1, judejimas2;
    vector<string> naujabusena;
};



int main(/*string failas*/) //pagal mano logika turetu veikt, bet as nemoku per cmd paleist programos kad patestuot
{
    ifstream fin(failas);

    ///////////////////////////////////////////////juostos

    int kiekjuostu;
    fin >> kiekjuostu;

    string temp;
    fin >> temp; //jeigu juostoje yra tarpai, tai neveiks, bet tiesiog speju kad nera

    vector<char> juosta1, juosta2;

    for (int i = 0; i < temp.size(); i++)
    {
        juosta1.push_back(temp[i]);
    }

    int pos1, pos2;

    if (kiekjuostu == 2) //jeigu yra antra juosta, tai ivedu
    {
        fin >> temp;

        for (int i = 0; i < temp.size(); i++)
        {
            juosta2.push_back(temp[i]);
        }


        fin >> pos1 >> pos2;
        pos1--;
        pos2--;
    }
    else
    {
        fin >> pos1;
        pos1--;
    }
    ///////////////////////////////////////////////busenu ivedimas
    map<string, bus> busena;
    while (fin.good()) // !eof() kazkodel neveikia
    {

        string a;
        fin >> a;

        char b;

        fin >> b;
        busena[a].esamas1.push_back(b);

        if (kiekjuostu == 2)
        {
            fin >> b;
            busena[a].esamas2.push_back(b);
        }

        fin >> b;
        busena[a].naujas1.push_back(b);

        if (kiekjuostu == 2)
        {
            fin >> b;
            busena[a].naujas2.push_back(b);
        }

        fin >> b;
        int c;
        if (b == 'L')
        {
            c = -1;
        }
        else if (b == 'R')
        {
            c = 1;
        }
        else
        {
            c = 0;
        }
        busena[a].judejimas1.push_back(c);

        if (kiekjuostu == 2)
        {
            fin >> b;
            if (b == 'L')
            {
                c = -1;
            }
            else if (b == 'R')
            {
                c = 1;
            }
            else
            {
                c = 0;
            }
            busena[a].judejimas2.push_back(c);
        }

        char tarpas;
        fin.get(tarpas);//praleidziu tarpa kad netikrintu jo

        string d;
        fin >> d;
        busena[a].naujabusena.push_back(d);


    }
    ///////////////////////////////////////////////rodykliu sukurimas
    vector<char> rodykle1, rodykle2;
    for (int i = 0; i < juosta1.size(); i++)
    {
        rodykle1.push_back(' ');
    }
    rodykle1[pos1] = '^';

    if (kiekjuostu == 2)//antros juostos rodykle
    {
        for (int i = 0; i < juosta2.size(); i++)
        {
            rodykle2.push_back(' ');
        }
        rodykle2[pos2] = '^';
    }
    ///////////////////////////////////////////////veikimas
    string esamabusena1 = "0", esamabusena2 = "0";

    bool arrado1 = false, arrado2 = false;

    while (!_kbhit()) // <conio.h> biblioteka, jeigu kazkas ant klaviaturos paspausta, tai ciklas baigiasi
    {

        system("cls"); //istrina konsole

        for (int i = 0; i < juosta1.size(); i++)//isvedu juosta
        {
            cout << juosta1[i];

        }
        cout << endl;

        for (int i = 0; i < rodykle1.size(); i++)//isvedu rodykle
        {
            cout << rodykle1[i];
        }
        cout << endl;
        rodykle1[pos1] = ' '; //istrinu rodykle, veliau vel idedu nauja

        cout << "T1 busena: " << esamabusena1 << endl;


        arrado1 = false;
        for (int i = 0; i < busena[esamabusena1].esamas1.size(); i++)//pirmos tiuringo masinos veikimas
        {

            if (juosta1[pos1] == busena[esamabusena1].esamas1[i])
            {

                juosta1[pos1] = busena[esamabusena1].naujas1[i];

                pos1 = pos1 + busena[esamabusena1].judejimas1[i];

                if (pos1 == -1) //juostos begalinis pletimas i kaire ir desine
                {
                    juosta1.insert(juosta1.begin(), '*');  //nezinau kaip pratest juosta, tai tiesiog zvaigzdutes dedu
                }
                else if (pos1 == juosta1.size())
                {
                    juosta1.push_back('*');
                }

                string tempbusena = esamabusena1;
                esamabusena1 = busena[tempbusena].naujabusena[i];
                arrado1 = true;
                break;
            }
        }


        rodykle1[pos1] = '^';

        if (kiekjuostu == 2) //antra juosta :skull:
        {
            for (int i = 0; i < juosta2.size(); i++)//isvedu juosta
            {
                cout << juosta2[i];
            }
            cout << endl;

            for (int i = 0; i < rodykle2.size(); i++)//isvedu rodykle
            {
                cout << rodykle2[i];
            }
            cout << endl;
            rodykle2[pos2] = ' '; //istrinu rodykle, veliau vel idedu nauja

            cout << "T2 busena: " << esamabusena2 << endl;


            arrado2 = false;
            for (int i = 0; i < busena[esamabusena2].esamas2.size(); i++)//antros tiuringo masinos veikimas
            {

                if (juosta2[pos2] == busena[esamabusena2].esamas2[i])
                {

                    juosta2[pos2] = busena[esamabusena2].naujas2[i];

                    pos2 = pos2 + busena[esamabusena2].judejimas2[i];

                    if (pos2 == -1) //juostos begalinis pletimas i kaire ir desine
                    {
                        juosta2.insert(juosta2.begin(), '*');
                    }
                    else if (pos2 == juosta2.size())
                    {
                        juosta2.push_back('*');
                    }

                    string tempbusena = esamabusena2;
                    esamabusena2 = busena[tempbusena].naujabusena[i];
                    arrado2 = true;
                    break;
                }
            }
            rodykle2[pos2] = '^';

        }
        if (arrado1 == false)//jeigu nezinoma ka daryt su tokiu simboliu dabartineje busenoje, darbas nutraukiamas
        {
            cout << "T1: esama busena nezino ka daryti su tokiu simboliu." << endl;
        }
        else if (busena[esamabusena1].esamas1.size() == 0) //jeigu tuscia busena, tai tiesiog baigta
        {
            cout << "T1: baigta, galutine  busena: " << esamabusena1 << endl;
        }

        if (kiekjuostu == 2)
        {
            if (arrado2 == false)//jeigu nezinoma ka daryt su tokiu simboliu dabartineje busenoje, darbas nutraukiamas
            {
                cout << "T2: esama busena nezino ka daryti su tokiu simboliu." << endl;
            }
            else if (busena[esamabusena2].esamas2.size() == 0) //jeigu tuscia busena, tai tiesiog baigta
            {
                cout << "T2: baigta, galutine busena: " << esamabusena2 << endl;
            }
        }

        if ((arrado1 == false || busena[esamabusena1].esamas1.size() == 0) && (arrado2 == false || busena[esamabusena2].esamas2.size() == 0)) //jeigu abi masinos nebedirba, stabdau visa programa
        {
            return 0;
        }

        cout << endl << "paspauskite bet koki klaviaturos mygtuka kad baigtumet darba(del nesibaigiancio ciklo ar dar ko)" << endl; //as nieko "praktiskiau" nesugalvojau

        Sleep(50); //windows.h biblioteka, padaro delay. kuo mazesnis delay, tuo prastesnis juostos matomumas
    }
    return 0;
}
