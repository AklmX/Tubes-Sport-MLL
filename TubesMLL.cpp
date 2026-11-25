#include <iostream>
#include "TubesMLL.h"
using namespace std;

void createListCoach(ListCoach &L){
    L.first == nullptr;
    L.last == nullptr;
}

bool isEmptyCoach(ListCoach L){
    return L.first == nullptr;
}

bool isEmptyAtlet(adrCoach L){
    return P->firstAtlet == nullptr;
}

//buat elemen
adrCoach createElemenCoach(Coach data) {
    adrCoach P = new elmCoach;
    P->info = data;
    P->next = nullptr;
    P->firstAtlet = nullptr;
    return P;
}

adrAtlet createElemenAtlet(Atlet data) {
    adrAtlet Q = new elmAtlet;
    Q->info = data;
    Q->next = nullptr;
    return Q;
}
 // Insert coach
void insertFirstCoach(ListCoach &L, adrCoach P) {
    if (isEmptyCoach(L)) {
        L.first = P;
    } else {
        P->next = L.first;
        L.first = P;
    }
}

void insertLastCoach(ListCoach &L, adrCoach P) {
    if (isEmptyCoach(L)) {
        L.first = P;
    } else {
        adrCoach Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertAfterCoach(adrCoach prec, adrCoach P) {
    if (prec != nullptr && P != nullptr) {
        P->next = prec->next;
        prec->next = P;
    }
}

//insert atlet
void insertFirstAtlet(adrCoach P, adrAtlet Q) {
    if (P != nullptr && Q != nullptr) {
        if (isEmptyAtlet(P)) {
            P->firstAtlet = Q;
        } else {
            Q->next = P->firstAtlet;
            P->firstAtlet = Q;
        }
    }
}

void insertLastAtlet(adrCoach P, adrAtlet Q) {
    if (P != nullptr && Q != nullptr) {
        if (isEmptyAtlet(P)) {
            P->firstAtlet = Q;
        } else {
            adrAtlet R = P->firstAtlet;
            while (R->next != nullptr) {
                R = R->next;
            }
            R->next = Q;
        }
    }
}

void insertAfterAtlet(adrAtlet prec, adrAtlet Q) {
    if (prec != nullptr && Q != nullptr) {
        Q->next = prec->next;
        prec->next = Q;
    }
}
//Prosedur utama menambahkan relasi Atlet ke Coach
bool addAtletToCoach(ListCoach &L, string idCoach, Atlet dataAtlet) {
    adrCoach P = searchCoach(L, idCoach);
    if (P == nullptr) {
        cout << "[Gagal] Coach dengan ID " << idCoach << " tidak ditemukan." << endl;
        return false;
    }

    // Mencegah atlet yang sama didaftarkan dua kali ke coach yang sama
    if (searchAtletInCoach(P, dataAtlet.idAtlet) != nullptr) {
        cout << "[Gagal] Atlet " << dataAtlet.namaAtlet << " sudah terdaftar di bawah Coach " << P->info.namaCoach << "." << endl;
        return false;
    }

    adrAtlet Q = createElemenAtlet(dataAtlet);
    insertLastAtlet(P, Q);
    return true;
}

adrCoach searchCoach(ListCoach L, string idCoach) {
    adrCoach P = L.first;
    while (P != nullptr) {
        if (P->info.idCoach == idCoach) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

adrAtlet searchAtletInCoach(adrCoach P, string idAtlet) {
    if (P == nullptr) return nullptr;

    adrAtlet Q = P->firstAtlet;
    while (Q != nullptr) {
        if (Q->info.idAtlet == idAtlet) {
            return Q;
        }
        Q = Q->next;
    }
    return nullptr;
}

// Mencari semua Coach yang melatih seorang Atlet tertentu (Relasi N-M)
void searchCoachByAtlet(ListCoach L, string idAtlet) {
    adrCoach P = L.first;
    bool ditemukan = false;

    cout << "Daftar Coach untuk Atlet ID [" << idAtlet << "]:" << endl;
    while (P != nullptr) {
        adrAtlet Q = searchAtletInCoach(P, idAtlet);
        if (Q != nullptr) {
            cout << "- " << P->info.namaCoach << " (ID: " << P->info.idCoach
                 << " | Spesialisasi: " << P->info.spesialisasiCabor << ")" << endl;
            ditemukan = true;
        }
        P = P->next;
    }

    if (!ditemukan) {
        cout << "Tidak ada Coach yang melatih atlet dengan ID tersebut." << endl;
    }
}

void deleteFirstAtlet(adrCoach P, adrAtlet &Q) {
    Q = nullptr;
    if (P != nullptr && !isEmptyAtlet(P)) {
        Q = P->firstAtlet;
        P->firstAtlet = Q->next;
        Q->next = nullptr;
    }
}

void deleteLastAtlet(adrCoach P, adrAtlet &Q) {
    Q = nullptr;
    if (P != nullptr && !isEmptyAtlet(P)) {
        if (P->firstAtlet->next == nullptr) {
            Q = P->firstAtlet;
            P->firstAtlet = nullptr;
        } else {
            adrAtlet prev = P->firstAtlet;
            while (prev->next->next != nullptr) {
                prev = prev->next;
            }
            Q = prev->next;
            prev->next = nullptr;
        }
    }
}

void deleteAfterAtlet(adrAtlet prec, adrAtlet &Q) {
    Q = nullptr;
    if (prec != nullptr && prec->next != nullptr) {
        Q = prec->next;
        prec->next = Q->next;
        Q->next = nullptr;
    }
}

bool deleteAtletFromCoach(ListCoach &L, string idCoach, string idAtlet) {
    adrCoach P = searchCoach(L, idCoach);
    if (P == nullptr || isEmptyAtlet(P)) {
        return false;
    }

    adrAtlet curr = P->firstAtlet;
    adrAtlet prec = nullptr;

    while (curr != nullptr && curr->info.idAtlet != idAtlet) {
        prec = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false; // Atlet tidak ditemukan pada Coach ini
    }

    adrAtlet delNode = nullptr;
    if (curr == P->firstAtlet) {
        deleteFirstAtlet(P, delNode);
    } else if (curr->next == nullptr) {
        deleteLastAtlet(P, delNode);
    } else {
        deleteAfterAtlet(prec, delNode);
    }

    delete delNode;
    return true;
}

// Menghapus seorang Atlet dari SEMUA Coach yang melatihnya
int deleteAtletGlobal(ListCoach &L, string idAtlet) {
    int jumlahTerhapus = 0;
    adrCoach P = L.first;

    while (P != nullptr) {
        if (deleteAtletFromCoach(L, P->info.idCoach, idAtlet)) {
            jumlahTerhapus++;
        }
        P = P->next;
    }
    return jumlahTerhapus;
}

bool deleteAtletFromCoach(ListCoach &L, string idCoach, string idAtlet) {
    adrCoach P = searchCoach(L, idCoach);
    if (P == nullptr || isEmptyAtlet(P)) {
        return false;
    }

    adrAtlet curr = P->firstAtlet;
    adrAtlet prec = nullptr;

    while (curr != nullptr && curr->info.idAtlet != idAtlet) {
        prec = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false; // Atlet tidak ditemukan pada Coach ini
    }

    adrAtlet delNode = nullptr;
    if (curr == P->firstAtlet) {
        deleteFirstAtlet(P, delNode);
    } else if (curr->next == nullptr) {
        deleteLastAtlet(P, delNode);
    } else {
        deleteAfterAtlet(prec, delNode);
    }

    delete delNode;
    return true;
}

// Menghapus seorang Atlet dari SEMUA Coach yang melatihnya
int deleteAtletGlobal(ListCoach &L, string idAtlet) {
    int jumlahTerhapus = 0;
    adrCoach P = L.first;

    while (P != nullptr) {
        if (deleteAtletFromCoach(L, P->info.idCoach, idAtlet)) {
            jumlahTerhapus++;
        }
        P = P->next;
    }
    return jumlahTerhapus;
}

// Mengosongkan seluruh node Atlet milik seorang Coach sebelum Coach dihapus
void emptyListAtlet(adrCoach P) {
    if (P == nullptr) return;

    adrAtlet Q = nullptr;
    while (!isEmptyAtlet(P)) {
        deleteFirstAtlet(P, Q);
        delete Q;
    }
}

void deleteFirstCoach(ListCoach &L, adrCoach &P) {
    P = nullptr;
    if (!isEmptyCoach(L)) {
        P = L.first;
        L.first = P->next;
        P->next = nullptr;
    }
}

void deleteLastCoach(ListCoach &L, adrCoach &P) {
    P = nullptr;
    if (!isEmptyCoach(L)) {
        if (L.first->next == nullptr) {
            P = L.first;
            L.first = nullptr;
        } else {
            adrCoach prev = L.first;
            while (prev->next->next != nullptr) {
                prev = prev->next;
            }
            P = prev->next;
            prev->next = nullptr;
        }
    }
}

void deleteAfterCoach(adrCoach prec, adrCoach &P) {
    P = nullptr;
    if (prec != nullptr && prec->next != nullptr) {
        P = prec->next;
        prec->next = P->next;
        P->next = nullptr;
    }
}

// Menghapus Coach beserta seluruh sub-list Atletnya
bool deleteCoach(ListCoach &L, string idCoach) {
    if (isEmptyCoach(L)) return false;

    adrCoach curr = L.first;
    adrCoach prec = nullptr;

    while (curr != nullptr && curr->info.idCoach != idCoach) {
        prec = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false; // Coach tidak ditemukan
    }

    // 1. Wajib kosongkan semua child atlet milik coach ini terlebih dahulu
    emptyListAtlet(curr);

    // 2. Lepaskan node coach dari ListCoach
    adrCoach delCoach = nullptr;
    if (curr == L.first) {
        deleteFirstCoach(L, delCoach);
    } else if (curr->next == nullptr) {
        deleteLastCoach(L, delCoach);
    } else {
        deleteAfterCoach(prec, delCoach);
    }

    // 3. Dealokasi memori node coach
    delete delCoach;
    return true;
}

// Show Data Atlet & Coach
void showAllData(ListCoach L) {
    if (isEmptyCoach(L)) {
        cout << "Data Coach masih kosong." << endl;
        return;
    }

    adrCoach P = L.first;
    while (P != nullptr) {
        cout << "==========================================" << endl;
        cout << "Coach ID     : " << P->info.idCoach << endl;
        cout << "Nama Coach   : " << P->info.namaCoach << endl;
        cout << "Spesialisasi : " << P->info.spesialisasiCabor
             << " (Lisensi: " << P->info.lisensi << ")" << endl;
        cout << "Daftar Atlet Binaan (" << countAtletOfCoach(P) << " orang):" << endl;

        if (isEmptyAtlet(P)) {
            cout << "   (Belum ada atlet yang dilatih)" << endl;
        } else {
            adrAtlet Q = P->firstAtlet;
            int no = 1;
            while (Q != nullptr) {
                cout << "   " << no << ". [" << Q->info.idAtlet << "] " << Q->info.namaAtlet
                     << " | Cabor: " << Q->info.cabor
                     << " | Kategori: " << Q->info.kategoriUmur
                     << " | Poin: " << Q->info.poinTurnamen << endl;
                Q = Q->next;
                no++;
            }
        }
        P = P->next;
    }
    cout << "==========================================" << endl;
}

void showAtletByCoach(ListCoach L, string idCoach) {
    adrCoach P = searchCoach(L, idCoach);
    if (P == nullptr) {
        cout << "Coach dengan ID " << idCoach << " tidak ditemukan." << endl;
        return;
    }

    cout << "Atlet binaan Coach " << P->info.namaCoach << ":" << endl;
    if (isEmptyAtlet(P)) {
        cout << "- Tidak ada atlet." << endl;
    } else {
        adrAtlet Q = P->firstAtlet;
        while (Q != nullptr) {
            cout << "- [" << Q->info.idAtlet << "] " << Q->info.namaAtlet
                 << " (" << Q->info.kategoriUmur << ", Poin: " << Q->info.poinTurnamen << ")" << endl;
            Q = Q->next;
        }
    }
}

// Count Atlet & Coach
int countAtletOfCoach(adrCoach P) {
    if (P == nullptr) return 0;

    int count = 0;
    adrAtlet Q = P->firstAtlet;
    while (Q != nullptr) {
        count++;
        Q = Q->next;
    }
    return count;
}

int countCoachOfAtlet(ListCoach L, string idAtlet) {
    int count = 0;
    adrCoach P = L.first;
    while (P != nullptr) {
        if (searchAtletInCoach(P, idAtlet) != nullptr) {
            count++;
        }
        P = P->next;
    }
    return count;
}
