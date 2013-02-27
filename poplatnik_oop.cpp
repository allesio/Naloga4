/* 
 * File:   poplatnik_oop.cpp
 * Author: Matej
 *
 * Created on Ponedeljek, 25 februar 2013, 19:19
 */

#include "stdafx.h" // za vs
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

void izpis_txt(string ibeseda,short ii)
/*izpisujem besedilo in smernico endl
smernico endl izpi�em, �e je ii parameter enak 1
INPUT: besedilo, ki g aiuzpi�em in navodilo za ispis endl
OUTPUT:
LOKALNO:
*/
{
 cout<<ibeseda;
 if (ii==1) cout<<endl;
}

string citaj_txt ()
/*izpi�em navodil in �itam �tevilo v obliki niza znakov, ker je to edini tip
podatkov v katerega lahko shranim karkoli ho�em in PC ne javlja napak
INPUT:

OOUTPUT:
beseda, ki bi naj bila �tevilo
LOKALNO:
sbeseda- za �itanje podanega podatka
*/
{ 
  string dbeseda;
  getline(cin, dbeseda);
  return(dbeseda); 
}

bool preveri_txt (string pbeseda)
/*
DELOVANJE:
preverim, �e so vsi znaki v �tevilu dovoljeni. V celem �tevilu so dovoljeni 
znaki za cifre '0', ..., '9' in znak '-' na prem mestu
Preverim vse znake od za�etka do konca �e so znaki dovoljeni vrnem true, druga�e false
�e je prvi znak minus, ga presko�im.
S preverjanjem kon�am, ko naletim na prvi znak, ki ni dovoljen. Uporabim 
spremenljivko  pprav, ki jo pred za�etkom preverjanje pravilnosti besede nastavim 
na true kar mi pomeni, da so predvidevam, da bodo vsi znaki dovoljeni. V zanki 
preverim, �e temu res tako in po potrebi nasatvi, pprav na fals, kar pomeni, da sem
na�el znak, ki ni dovoljen.
INPUT:
pbeseda-beseda, ki jo preverjam
LOKALNO:
pi- �tevilski, kazalec na trenutni znak v podani besedi
OUTPUT:
pprav-logi�ni tip, �e je tru pomeni, da so vsi znaki dobvoljeni, druga�e,
sem na�el znak, ki ni dovoljen
*/
{
  short pi;//kazalec na trenutni znak v pbesedi
  bool pprav;//spremenljivka, v kateri hranim napako 

  //minus presko�im, minus je lahkona prvem mestu in nikjer drugje
  if((pbeseda[0]=='-') || (pbeseda[0]=='+')) pi=1;
  else pi=0;
  //preverjanje, �e so vsi znaki dovoljeni v podani besedi
  pprav=true; 
  while((pbeseda[pi]!='\0')&&(pprav))
  {
   if((pbeseda[pi]<'0')||(pbeseda[pi]>'9')) pprav=false;
   pi=pi+1;//naslednji znak
  }
  return(pprav);
}

short pretvori_txt_st (string rbeseda)
/*podano besedo, ki predstavlja �tevilo pretvorim v �tevilo
minus presko�im, preostale zanke pretvorim v �tevilo, nato doam morebitni minus
v obliki mno�enja z -1, 
Za vse znake opravim postopek vzami znak, pretvori znak v cifro, dodaj cifro k �tevilu
INPUT: rbeseda-�tevilo v obliki niza znakov
OUTPUT: rstevilo - pretvorjeno celo �tevilo 
LOKALNO:
ri, cifra,znak, rstevilo(opisani zraven deklaracije prostorov)
*/

{
  short ri;//kazalec na trenuntni znak
  short cifra;//cifra iz �tevila
  char znak;//znak iz besedila
  short rstevilo; //v ta prostor bom dodajal cifre
  rstevilo=0;
  //minus presko�im, minus je lahkona prvem mestu in nikjer drugje
  if((rbeseda[0]=='-') ||(rbeseda[0]=='+')) ri=1;
  else ri=0;
  while(rbeseda[ri]!='\0')
  {
    znak=rbeseda[ri];//vzami znak
    cifra=((long)znak)-48;//pretvori znak v cifro ASCII tabela
    rstevilo=rstevilo*10+cifra;//dodaj cifro k �tevilu
    ri=ri+1;//naslednji znak
  }
  //minus dodam, tako, da mno�im �tevilo z -1
  if(rbeseda[0]=='-') rstevilo=-1*rstevilo;
  return(rstevilo);  
}

void izpisinterval(short izi)
/* izpi�e, napako, ker �tevilo ni v podanem intervalu
INPUT: izi, ki vsebuje informacijo o legi �tevila glede na interval
�e je izi 1->preveliko, druga�e premajhno
OUTPUT: ustrezno besedilo o napaki �tevila
LOKALNO:

*/
{
 if(izi==1)izpis_txt("Podano stevilo je preveliko. ",1); // 
 else izpis_txt("Podano stevilo je premajhno. ",1);
}

bool preveriinterval(short pist, short pimin, short pimax)
/*Preverim interval �tevila in javim napako, �e ni v intervalu
LOKALNO:
INPUT:
pist-�tevilo, ki ga preverjam, �e je v intervalu pimin<pist<pimax
OUTPUT:
  true-�tevilo je v intervalu, meje ne �tejejo
  false-�tevilo izven intervala -Y javim napako
*/
{ 
  if ((pist<pimin)||(pist>pimax))
  {
   if (pist < pimin)izpisinterval(0);
   else izpisinterval(1);
   return(false);
  }else return (true);
}

void vnos(string hm, int sp_meja, int zg_meja,int &vst, int nv)
/*
 INPUT: 
 hm-besedilo, ki se izpi�e na ekran
 vst-prostor preko katerega bom vrnil �tevilo
 sp_meja-spodanja meja intervala, kejr mora biti �tevilo, meja je traven
 zg_meja- zgornaj meja intervala, kjer mora biti �tevilo, meje ja zraven
 nv-�e je 1, se pomaknemo v novo vrstico, ce je 0 pa ne 
 OUTPUT: vst je definiran referen�no, kar pomeni, da se sprememba vrednosti 
 tega prostora ohrani in prenese v spremenljivko od koder smo klicali ta podprogram
 LOKALNO:
  �tevilo �itam kot niz znakov(vbeseda), preverim, �e so v nizi vsi znaki dovoljeni 
  �e se vsi znaki dovoljeni, niz pretvorim v �tevilo (vstevilo)
  �e v nizu kateri znak ni dovoljen, javim napako in uporabnik mora ponoviti vnos
  vvseok-logi�ni tip, ki ga uporabim dvakrat za krmiljenje dveh do while zank
          prvi� za zanko, ki preverja uporabljene znake in
          drugi� za zanko, ki preverja, �e je �tevilo v intervalu
          Velja:
            true-vsi znaki dovoljeni (�tevilo je v intervalu)
            false- vsaj en znak ni dovoljen (�tevilo ni v intervalu)
*/
{ 
   string vbeseda;//�tevilo �itam v obliki niza znakov 
   short vstevilo;//
   bool vvseok;
   do{  
      do{
         izpis_txt(hm,1); //izpisem besedilo na zaslon, nato v novo vrstico
         vbeseda=citaj_txt(); // �itam tekst s tipkovnice in ga shranim v vbeseda
         vvseok=preveri_txt(vbeseda);//ce vbeseda vsebuje cifre, dobim tru, drugace false
         if(!vvseok)izpis_txt("Podani znaki niso stevilo.",1);//napako javi, to ni �tevilo
      }while(!vvseok);//ponavljaj, dokler ne dobi� pravilnega �tevila  
      vstevilo=pretvori_txt_st(vbeseda);  //sedaj pretvorim tekst v �tevilo long tipa
      vvseok=preveriinterval(vstevilo, sp_meja, zg_meja);//preverim interval �tevila
      if(!vvseok) izpis_txt("Podano stevilo ni v intervalu.",1);//napako javi, ker nisi v intervalu
   }while(!vvseok);//�e ni v intervalu, pridobi novo �tevilo
   vst=vstevilo;//�tevilo vrnem tja od koder sem klical ta podprogram(referenca)
}

void meni1()
/*
 * INPUT: -
 * DELOVANJE: na zaslon izpisem opcije
 * OUTPUT: izpis opcij na zaslon
 */ {
    cout << "Za urejanje podatkov prosimo vnesite ustrezen znak:" << endl << endl;
    cout << "--------------------------------" << endl;
    cout << "|    a:) Podatki o pohistvu    |" << endl;
    cout << "|    b:) Podatki o kupcu       |" << endl;
    cout << "|    c:) Izhod iz programa     |" << endl;
    cout << "--------------------------------" << endl << endl;
}

void meni2()
/*
 * INPUT: -
 * DELOVANJE: na zaslon izpisem opcije
 * OUTPUT: izpis opcij na zaslon
 */ {
    cout << "Izberite ustrezno opcijo: " << endl;
    cout << "---------------------------------------" << endl;
    cout << "|    a:) Shrani podatke v datoteko    |" << endl;
    cout << "|    b:) Citaj podatke iz datoteke    |" << endl;
    cout << "|    c:) Sortiraj po postni stevilki  |" << endl;
    cout << "|    d:) Sortiraj po vrsti pohistva   |" << endl;
    cout << "|    e:) Dodaj elemente               |" << endl;
    cout << "|    f:) Isci elemente po vrsti       |" << endl;
    cout << "|    g:) Brisi elemente               |" << endl;
    cout << "|    h:) Izpisi vse elemente          |" << endl;
    cout << "|    i:) Vrni se v glavni meni        |" << endl;
    cout << "---------------------------------------" << endl << endl;
}

struct Naslov // vrinjena struktura s tremi lastnostmi
{
public:
    string ulica[30];
    string naslov_poste[30];
    short postna_st;
};

class Pohistvo // osnovni razred za vodenje evidence pohistva
{
private:
    Naslov proizvajalec; // latnosti so privat, naslov proizvajalca
    bool zaloga; // zaloga pohistva
    string vrsta_pohistva[30]; // vrsta pohistva (bukev, hrast,...)
public:
    Pohistvo();
    ~Pohistvo();
    void pohistvo();
    void pridobi(Pohistvo aa[], int &ii);
    void citaj();
    void vpis_v_dat(Pohistvo a[], int i);
    void citaj_iz_dat(Pohistvo cz[], int &ck, int cn);
    void sortiranje1(Pohistvo bz[], int zb);
    void sortiranje2(Pohistvo bz[], int zb);
    void dodaj_element(Pohistvo cz[], int &ck, int cn);
    void isci_txt(Pohistvo iz[], int &ik);
    void izpis_en(Pohistvo iz, int ij);
    void brisi_txt(Pohistvo bz[], int &bk);
    void izpis_vse(Pohistvo iz[], short ik);
};

void Pohistvo::pridobi(Pohistvo d[], int &ii)
/*
 * INPUT: -
 * DELOVANJE: podprogram odpre tekstovno datoteko
 *            v datoteko izpise ustrezne podatke
 *            s pomocjo random funkcije vnese izbrane podatke
 *            podprogram zapre tekstovno datoteko
 * OUTPUT: shranijo se vrednosti spremenljivk
 */ {
    ii = 0;
    vrsta_pohistva[0] = "Bukev            ";
    vrsta_pohistva[1] = "Gaber            ";
    vrsta_pohistva[2] = "Hrast            ";
    vrsta_pohistva[3] = "Jelka            ";
    vrsta_pohistva[4] = "Hrast            ";
    vrsta_pohistva[5] = "Breza            ";
    vrsta_pohistva[6] = "Macesen          ";
    vrsta_pohistva[7] = "Bor              ";
    vrsta_pohistva[8] = "Smreka           ";
    vrsta_pohistva[9] = "Hrast            ";
    vrsta_pohistva[10] = "Bukev            ";
    vrsta_pohistva[11] = "Češnja           ";
    vrsta_pohistva[12] = "Lipa             ";
    vrsta_pohistva[13] = "Hrast            ";
    vrsta_pohistva[14] = "Oreh             ";
    vrsta_pohistva[15] = "Sekvoja          ";
    vrsta_pohistva[16] = "Macesen          ";
    vrsta_pohistva[17] = "Bukev            ";
    vrsta_pohistva[18] = "Kostanj          ";
    vrsta_pohistva[19] = "Bor              ";
    vrsta_pohistva[20] = "Akacija          ";
    vrsta_pohistva[21] = "Brest            ";
    vrsta_pohistva[22] = "Javor            ";
    vrsta_pohistva[23] = "Lipa             ";
    vrsta_pohistva[24] = "Oreh             ";
    vrsta_pohistva[25] = "Vrba             ";
    vrsta_pohistva[26] = "Kostanj          ";
    vrsta_pohistva[27] = "Češnja           ";
    vrsta_pohistva[28] = "Hrast            ";
    vrsta_pohistva[29] = "Bukev            ";

    proizvajalec.ulica[0] = "Volkmerjeva ul. ";
    proizvajalec.ulica[1] = "Kajuhova ul.    ";
    proizvajalec.ulica[2] = "Tovarniška c.   ";
    proizvajalec.ulica[3] = "Titova c.       ";
    proizvajalec.ulica[4] = "Prešernova ul.  ";
    proizvajalec.ulica[5] = "Sodna ul.       ";
    proizvajalec.ulica[6] = "Naberšnikova c. ";
    proizvajalec.ulica[7] = "Volkmerjeva c.  ";
    proizvajalec.ulica[8] = "Radomlje        ";
    proizvajalec.ulica[9] = "Lovrenc         ";
    proizvajalec.ulica[10] = "Markovci        ";
    proizvajalec.ulica[11] = "Stoperce        ";
    proizvajalec.ulica[12] = "Skoke           ";
    proizvajalec.ulica[13] = "Ljubno          ";
    proizvajalec.ulica[14] = "Planica         ";
    proizvajalec.ulica[15] = "Cirkovce        ";
    proizvajalec.ulica[16] = "Mihovce         ";
    proizvajalec.ulica[17] = "Njiverce        ";
    proizvajalec.ulica[18] = "Kungota         ";
    proizvajalec.ulica[19] = "Apače           ";
    proizvajalec.ulica[20] = "Tezno           ";
    proizvajalec.ulica[21] = "Kog             ";
    proizvajalec.ulica[22] = "Kobarid         ";
    proizvajalec.ulica[23] = "Velenje         ";
    proizvajalec.ulica[24] = "Celje           ";
    proizvajalec.ulica[25] = "Sobetinci       ";
    proizvajalec.ulica[26] = "Borl            ";
    proizvajalec.ulica[27] = "Cirkulane       ";
    proizvajalec.ulica[28] = "Mihovci         ";
    proizvajalec.ulica[29] = "Gaj             ";

    proizvajalec.naslov_poste[0] = "Ptuj        ";
    proizvajalec.naslov_poste[1] = "Kiričevo    ";
    proizvajalec.naslov_poste[2] = "Majšperk    ";
    proizvajalec.naslov_poste[3] = "Zavrč       ";
    proizvajalec.naslov_poste[4] = "Gorišnica   ";
    proizvajalec.naslov_poste[5] = "Ljutomer    ";
    proizvajalec.naslov_poste[6] = "Lendava     ";
    proizvajalec.naslov_poste[7] = "Koper       ";
    proizvajalec.naslov_poste[8] = "Ptuj        ";
    proizvajalec.naslov_poste[9] = "Maribor     ";
    proizvajalec.naslov_poste[10] = "Lenart      ";
    proizvajalec.naslov_poste[11] = "Krško       ";
    proizvajalec.naslov_poste[12] = "Nova Gorica ";
    proizvajalec.naslov_poste[13] = "Litija      ";
    proizvajalec.naslov_poste[14] = "Idrija      ";
    proizvajalec.naslov_poste[15] = "Apače       ";
    proizvajalec.naslov_poste[16] = "Zavrč       ";
    proizvajalec.naslov_poste[17] = "Jesenice    ";
    proizvajalec.naslov_poste[18] = "Ljubljana   ";
    proizvajalec.naslov_poste[19] = "Domžale     ";
    proizvajalec.naslov_poste[20] = "Ig          ";
    proizvajalec.naslov_poste[21] = "Koper       ";
    proizvajalec.naslov_poste[22] = "Piran       ";
    proizvajalec.naslov_poste[23] = "Izola       ";
    proizvajalec.naslov_poste[24] = "Cerknica    ";
    proizvajalec.naslov_poste[25] = "Kirdičevo   ";
    proizvajalec.naslov_poste[26] = "Ptuj        ";
    proizvajalec.naslov_poste[27] = "Ormož       ";
    proizvajalec.naslov_poste[28] = "Radenci     ";
    proizvajalec.naslov_poste[29] = "Lendava     ";

    for (; ii < 30; ii++) {
        proizvajalec.ulica[ii];
        proizvajalec.naslov_poste[ii];
        proizvajalec.postna_st = (rand() % 8999) + 1000;
        vrsta_pohistva[ii];
        zaloga = rand() % 2;
    }
}

void Pohistvo::vpis_v_dat(Pohistvo a[], int i)
/*
 * INPUT: i, ki nam pove koliko vrednosti lahko vnesemo
 * DELOVANJE: odprem tekstovno datoteko
 *            v datoteko vnsem prej ustvarjene vrednosti spremenljivk
 * OUTPUT: vrednosti spremenljivk vpišem v tekstovno datoteko
 *         na zaslon izpišem, kaj se je pravkar zgodilo
 */ {
    ofstream cigel;
    cigel.open("podatki.txt", ios::in);
    cigel << " --------------------------------------------------------------------------" << endl;
    cigel << "|           naslov proizvajalca:              |                            |" << endl;
    cigel << "|---------------------------------------------|                            |" << endl;
    cigel << "|   kraj/ulica:   |   pošta:    | poštna št.: |  vrsta pohistva: | zaloga: |" << endl;
    cigel << "|--------------------------------------------------------------------------|" << endl;
    int j = 0;
    for (; j < i; j++)//vpis podatkov v datoteko
    {
        proizvajalec.postna_st = (rand() % 8999) + 1000;
        zaloga = rand() % 2;
        cigel << "| " << proizvajalec.ulica[j];
        cigel << "| " << proizvajalec.naslov_poste[j];
        cigel << "| " << proizvajalec.postna_st << "        ";
        cigel << "| " << vrsta_pohistva[j];
        cigel << "| " << zaloga << "       |";
        if (j < i) cigel << endl; //zadnja vrstica zadnjega podatka
    }
    cigel << " --------------------------------------------------------------------------" << endl;
    cout << endl << "Vpisanih je 30 podatkov v datoteki" << endl << endl;
}

short pretvori_v_st(string a) {
    short st = 0;
    for (short i = 0; i < a.length(); i = i + 1)//vse znake pretvorim v �tevilo
    {
        st = st * 10 + (((short) a[i]) - 48); // znak v cifro in dodam k �tevilu
    }
    //cout<<"st="<<st<<endl;//kontrolni izpis
    return st; //vrnem stevilo short, ki sem ga dobil iz string
}

void Pohistvo::citaj_iz_dat(Pohistvo cz[], int &ck, int cn)
/*
 * INPUT: ck je števec, ki je referenčnega tipa
 *        cz je polje, v katerem se nahajajo vsi podatki
 * DELOVANJE: odprem tekstovno datoteko
 *            iz datoteke citam podatke
 *            zaprem tekstovno datoteko
 * OUTPUT: izpis rezultatov, ki so se v podprogramu zgodili
 */ {
    string podatki;
    ifstream cigel; //simbolično ime datoteke
    cigel.open("podatki.txt", ios::in); //odprem za čitanje
    ck = 0;
    if (cigel.is_open()) {
        while (!cigel.eof() && ck < cn) {
            getline(cigel, podatki);
            cz[ck].proizvajalec.ulica[ck] = podatki;
            getline(cigel, podatki);
            cz[ck].proizvajalec.naslov_poste[ck] = podatki;
            getline(cigel, podatki);
            cz[ck].proizvajalec.postna_st = pretvori_v_st(podatki);
            getline(cigel, podatki);
            cz[ck].vrsta_pohistva[ck] = podatki;
            getline(cigel, podatki);
            cz[ck].zaloga = pretvori_v_st(podatki);
            ck++;
        }
        cout << endl << "Uspesno vcitanje" << endl << endl;
        if (ck >= cn && !cigel.eof())cout << "OPOZORILO polje je polno, so res vsi podatki preneseni? Preveri!!" << endl;
        cigel.close();
    } else {
        cout << "Prislo je do napake" << endl;
    }
}

void menjaj(Pohistvo & prvi, Pohistvo & drugi)
/*
 * INPUT: parametra podprograma sta referenčno definirana
 * DELOVANJE: menjam elementa s pomočjo pomožnega elementa
 * OUTPUT: -
 */ {
    Pohistvo vmes; //pomožni element
    vmes = prvi; //prvega si zapomnim
    prvi = drugi; //drugi na mesto prvega
    drugi = vmes; //prvi na mesto drugega
}

void Pohistvo::sortiranje1(Pohistvo bz[], int zb)
/*
 * INPUT: bz je polje spremenljivk, v katerem so vsi podatki
 * DELOVANJE: zamenjava spremenljivk če je druga večja od prve
 *            sortiranje je po številkah
 * OUTPUT: podprogram vrne izpis na zaslon
 */ {
    zaloga = rand() % 2;
    short i, j; //števca zank, zunanja(i) in notranja(j) zanka
    for (i = 0; i < zb - 1; i = i + 1)//izberem mesto za katerega poiščem najustreznejši element
    {
        for (j = i + 1; j < zb; j = j + 1)//iščem najustreznejši element
        {
            if (bz[i].proizvajalec.postna_st > bz[j].proizvajalec.postna_st) //po potrebi menjam
            {
                menjaj(bz[i], bz[j]); //menjaj elementa
            }
        }
    }
    cout << endl << "Podatki so uspesno sortirani" << endl;
}

void Pohistvo::sortiranje2(Pohistvo bz[], int zb)
/*
 * INPUT: bz je polje spremenljivk, v katerem so vsi podatki
 * DELOVANJE: zamenjava spremenljivk če je druga večja od prve
 *            sortiranje je po znakih
 * OUTPUT: podprogram vrne izpis na zaslon
 */ {
    short i, j; //števca zank, zunanja(i) in notranja(j) zanka
    for (i = 0; i < zb - 1; i = i + 1)//izberem mesto za katerega poiščem najustreznejši element
    {
        for (j = i + 1; j < zb; j = j + 1)//iščem najustreznejši element
        {
            if (bz[i].vrsta_pohistva[i] > bz[j].vrsta_pohistva[j]) //po potrebi menjam
            {
                menjaj(bz[i], bz[j]); //menjaj elementa
            }
        }
    }
    cout << endl << "Podatki so uspesno sortirani" << endl;
}

void Pohistvo::dodaj_element(Pohistvo cz[], int& ck, int cn) {
    izpis_txt("Podaj elemente:", 1);
    cz[ck].proizvajalec.ulica[ck] = citaj_txt();
    //vnos("Podaj kraj/ulico proizvajalca: ", cz[ck].proizvajalec.ulica, 1);
    //(string hm, int sp_meja, int zg_meja,int &vst, int nv)
    string naslov_poste = citaj_txt();
    // kaj posto si lahko zmisli oz naslov al mora bit isti ko v kakem polji, to ke mam gori vnešene, so samo za to, ker 
    
    vnos("Podaj posto proizvajalca:  ",1000,9999, cz[ck].proizvajalec.naslov_poste, 1);//
    vnos("Podaj postno stevilko: ", 1000, 9999, cz[ck].proizvajalec.postna_st, 1);
    vnos("Podaj vrsto pohistva: ", cz[ck].vrsta_pohistva[ck], 1);
    vnos("vnesi, ce je izdelek na zalogi (1) ali ce ni(0):  ", 0, 1, cz[ck].zaloga, 1);
    ck = ck + 1; //dodali smo element
}

void Pohistvo::izpis_en(Pohistvo iz, int ij) {
    cout << "Podatki " << ij + 1 << ". elementa so:" << endl << "kraj: " << iz.proizvajalec.ulica << endl << "datum merjenja: ";
    cout << iz.proizvajalec.naslov_poste << "." << iz.proizvajalec.postna_st << ".";
    cout << iz.vrsta_pohistva << endl << "vreme: " << zaloga << endl;
}

string formatiranje(string beseda) {
    if (beseda[0] >= 'a' && beseda[0] <= 'z')//prva �rka je velika
    {
        beseda[0] = (char) (((short) beseda[0]) - 32);
    }
    for (short jj = 1; jj < beseda.length(); jj = jj + 1)//vse znake obdelati
    {
        if (beseda[jj] >= 'A' && beseda[jj] <= 'Z') {
            beseda[jj] = (char) (((short) beseda[jj]) + 32); //pretvorba v malo �rko
        }
    }
    return beseda;
}

void Pohistvo::isci_txt(Pohistvo iz[], int &ik) {
    string vmes; //iskalni podatek
    cout << "Iskanje po tekstu" << endl;
    cout << "Podaj vrsto pohistva:" << endl;
    getline(cin, vmes);
    //cout<<"Vmes je prej:"<<vmes<<endl; //kontrolni izpis
    vmes = formatiranje(vmes); //pretvorim v ustrezno obliko, kotje opisano zgoraj
    //cout<<"Vmes je kasneje:"<<vmes<<endl;//kontrolni izpis
    for (short j = 0; j < ik; j = j + 1)//od elementa do elementa-linearno iskanjhe
    {
        if (vmes == iz[j].vrsta_pohistva[j]) izpis_en(iz[j], j); //izpis na zaslon
    }
    system("pause");
}

void Pohistvo::brisi_txt(Pohistvo bz[], int &bk) {
    string vmes; //iskalni podatek
    string odl; //odlocitev za brisanje
    cout << "Brisanje prvega elementa, ki ustreza:" << endl;
    cout << "Podaj vreme, po katerem zelis brisati:" << endl;
    getline(cin, vmes);
    //cout<<"Vmes je prej:"<<vmes<<endl; //kontrolni izpis
    vmes = formatiranje(vmes); //pretvorim v ustrezno obliko, kot je opisano zgoraj
    //cout<<"Vmes je kasneje:"<<vmes<<endl;//kontrolni izpis
    for (short j = 0; j < bk; j = j + 1)//od elementa do elementa-linearno iskanje
    {
        if (vmes == bz[j].vrsta_pohistva[j]) {
            izpis_en(bz[j], j); //izpis na zaslon
            cout << "Zelis, da podani element zbrisem?(d ali D= brisi element) " << endl;
            getline(cin, odl);
            if ((odl.length() == 1)&& (odl == "D" || odl == "d")) {
                bz[j] = bz[bk - 1]; //zadnjega prenesem na mesto brisanega=brisanje enega elementa   
                bk = bk - 1; //�tevilo elementov se je zmanj�alo
                j = j - 1; //prenesenega moram �e enkrat preveriti, mogo�e ustreza za brisanje
            }
        }
    }
}

void Pohistvo::izpis_vse(Pohistvo iz[], short ik) {
    for (short i = 0; i < ik; i = i + 1) {
        cout << "Podatki " << i + 1 << ". elementa so:" << endl << "kraj: " << iz[i].proizvajalec.ulica << endl << "Naslov poste: ";
        cout << iz[i].proizvajalec.naslov_poste << "." << iz[i].proizvajalec.postna_st << ".";
        cout << iz[i].vrsta_pohistva << endl << "Zaloga: " << zaloga << endl;
    }

}
/*
void Zrak::meni_zr(Zrak a[], int & ak, int an) {
    int k; //toliko podatkov dejansko imam
    int n = 100; //toliko podatkov predvidevam
    int kk;
    int nn=100;

    Zrak podatki[n];
    podatki[0].pridobi(podatki, k);
    Zrak podatkii[nn];

    string zac = "1", kon = "9";
    string izb; //izbira uporabnika
    do {//izhod iz glavnega menija
        do {//preverim izbiro, ce ni ok, ponovi vnos
            izpis_opcij2();
            getline(cin, izb);
            if (izb.length() != 1 || (izb < zac || izb > kon))cout << "Napacen vnos, ponovi ga." << endl;
        } while (izb < zac || izb > kon);
        if (izb == "1") podatki[0].vpis_v_dat(podatki, k);
        if (izb == "2") podatki[0].citaj_iz_dat(podatkii, kk, nn);
        if (izb == "3") podatki[0].sort1(podatki,n);
        if (izb == "4") podatki[0].sort2(podatki,n);
        if (izb == "5") podatki[0].dodaj_element(podatki,k, n);
        if (izb == "6") podatki[0].isci_txt(podatki,k);
        if (izb == "7") podatki[0].brisi_txt(podatki,k);
        if (izb == "8") podatki[0].izpis_vse(podatki,k);

    } while (izb != kon);
}
*/
void meni_glavni()
/*
 * INPUT: -
 * DELOVANJE: na zaslon izpisemo opcije
 *            citam, preverim izbiro uporabnika
 *            izvedem izbiro uporabnika
 * OUTPUT: klic metode, ki jo izbere uporabnik
 */ {
    int n = 50;
    Pohistvo podatki[n];

    char bes;
    string bess;
    //dve zanki, ena je v drugi
    //zunanja prepreci izhod, ce ni izbral izhoda
    do {
        //notranja preverja vnos in ne spusti dalje, ce vnos ni v intervalu
        do {
            meni1();
            getline(cin, bess);
            if (bess.length() == 1)bes = bess[0];
            else bes = 'z';
            //if stavek ob napacnem vnosu podatkov
            if (!((bes >= 'a')&&(bes <= 'c'))) cout << "Vnesen podatek ni veljaven. Prosim poskusite ponovno" << endl;
        } while (!((bes >= 'a')&&(bes <= 'c')));
        //if stavka za izvedbo izbrane akcije
        if (bes == 'a')podatki[0].pohistvo();
        if (bes == 'b')cout << "Izbrali ste akcijo B, sama zadeva pa se ne deluje." << endl;
    } while (!((bes == 'c')));
    cout << "Izbrali ste opcijo izhod." << endl;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    meni_glavni();
    
    return 0;
}