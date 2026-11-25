#ifndef TUBESMLL_H_INCLUDED
#define TUBESMLL_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

// Infotype Parent (Coach)
struct Coach {
    string idCoach;
    string namaCoach;
    string spesialisasiCabor; // Contoh: Futsal, Badminton, Renang
    string lisensi;           // Contoh: AFC Pro, Nasional
};

// Infotype Child (Atlet)
struct Atlet {
    string idAtlet;
    string namaAtlet;
    string cabor;
    string kategoriUmur;      // Contoh: U-19, Senior
    int poinTurnamen;
};

struct elmCoach;
struct elmAtlet;

typedef elmCoach* adrCoach;
typedef elmAtlet* adrAtlet;

// Elemen Child (Atlet) - disimpan di dalam sub-list milik Coach
struct elmAtlet {
    Atlet info;
    adrAtlet next;
};

// Elemen Parent (Coach) - memiliki pointer ke sub-list Atlet
struct elmCoach {
    Coach info;
    adrCoach next;
    adrAtlet firstAtlet;
};

// List Utama (Hanya List Parent sesuai MLL N-M Versi 2)
struct ListCoach {
    adrCoach first;
};

// --- PROTOTIPE FUNGSI & PROSEDUR ---
void createListCoach(ListCoach &L);
bool isEmptyCoach(ListCoach L);
bool isEmptyAtlet(adrCoach P);

adrCoach createElemenCoach(Coach data);
adrAtlet createElemenAtlet(Atlet data);

// Insert Coach
void insertFirstCoach(ListCoach &L, adrCoach P);
void insertLastCoach(ListCoach &L, adrCoach P);
void insertAfterCoach(adrCoach prec, adrCoach P);

// Insert Atlet (Relasi ke Coach)
void insertFirstAtlet(adrCoach P, adrAtlet Q);
void insertLastAtlet(adrCoach P, adrAtlet Q);
void insertAfterAtlet(adrAtlet prec, adrAtlet Q);
bool addAtletToCoach(ListCoach &L, string idCoach, Atlet dataAtlet);

// Search
adrCoach searchCoach(ListCoach L, string idCoach);
adrAtlet searchAtletInCoach(adrCoach P, string idAtlet);
void searchCoachByAtlet(ListCoach L, string idAtlet);

// Delete Atlet (Hapus Relasi pada 1 Coach & Hapus Global)
void deleteFirstAtlet(adrCoach P, adrAtlet &Q);
void deleteLastAtlet(adrCoach P, adrAtlet &Q);
void deleteAfterAtlet(adrAtlet prec, adrAtlet &Q);
bool deleteAtletFromCoach(ListCoach &L, string idCoach, string idAtlet);
int deleteAtletGlobal(ListCoach &L, string idAtlet);

// Delete Coach (Hapus Parent beserta seluruh Child-nya)
void emptyListAtlet(adrCoach P);
void deleteFirstCoach(ListCoach &L, adrCoach &P);
void deleteLastCoach(ListCoach &L, adrCoach &P);
void deleteAfterCoach(adrCoach prec, adrCoach &P);
bool deleteCoach(ListCoach &L, string idCoach);

// Show Data Coach & Atlet
void showAllData(ListCoach L);
void showAtletByCoach(ListCoach L, string idCoach);

// Count Total Coach & Atlet
int countAtletOfCoach(adrCoach P);
int countCoachOfAtlet(ListCoach L, string idAtlet);

#endif // TUBESMLL_H_INCLUDED
