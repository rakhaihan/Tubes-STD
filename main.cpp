#include "Rute.h"

void tampilkanMenu() {
    cout << "===== MENU =====" << endl;
    cout << "1. Cari Rute Terpendek" << endl;
    cout << "2. Lewat Jalan Tol" << endl;
    cout << "3. Hitung Biaya Perjalanan" << endl;
    cout << "4. Keluar" << endl;
    cout << "================" << endl;
    cout << "Pilih menu: ";
}

int main() {
    graph G;
    initGraph(G);

    // Tambahkan vertex dan edge sebagai contoh
    addVertex(G, "GudangA");
    addVertex(G, "GudangB");
    addVertex(G, "GudangC");
    addVertex(G, "GudangD");

    addEdge(G, "GudangA", "GudangB", 10);
    addEdge(G, "GudangA", "GudangC", 15);
    addEdge(G, "GudangB", "GudangD", 20);
    addEdge(G, "GudangC", "GudangD", 30);

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;

        }if (pilihan == 1) {
            string gudangAsal, gudangTujuan, ruteMacet;
            char macet, lewatTol;
            int jarakTol;

            // Input asal dan tujuan
            cout << "Masukkan nama gudang asal: ";
            cin >> gudangAsal;
            cout << "Masukkan nama gudang tujuan: ";
            cin >> gudangTujuan;

            // Cari rute terpendek
            cariRuteTerpendek(G, gudangAsal, gudangTujuan);

            // Pilihan: macet atau tidak
            cout << "Apakah ada kemacetan? (y/n): ";
            cin >> macet;
            if (macet == 'y' || macet == 'Y') {
                cout << "Masukkan nama rute yang macet: ";
                cin >> ruteMacet;
                hindariMacet(G, gudangAsal, gudangTujuan, ruteMacet);
            }

            // Pilihan: lewat tol atau tidak
            cout << "Apakah ingin lewat jalan tol? (y/n): ";
            cin >> lewatTol;
            if (lewatTol == 'y' || lewatTol == 'Y') {
                cout << "Masukkan jarak tol (km): ";
                cin >> jarakTol;
                lewatJalanTol(G, gudangAsal, gudangTujuan, jarakTol, true);
            }

        } else if (pilihan == 2) {
            string gudangAsal, gudangTujuan;
            int jarakTol;
            cout << "Masukkan nama gudang asal: ";
            cin >> gudangAsal;
            cout << "Masukkan nama gudang tujuan: ";
            cin >> gudangTujuan;
            cout << "Masukkan jarak tol (km): ";
            cin >> jarakTol;
            lewatJalanTol(G, gudangAsal, gudangTujuan, jarakTol, true);

        } else if (pilihan == 3) {
            string gudangAsal, gudangTujuan;
            cout << "Masukkan nama gudang asal: ";
            cin >> gudangAsal;
            cout << "Masukkan nama gudang tujuan: ";
            cin >> gudangTujuan;
            int biaya = hitungBiayaPerjalanan(G, gudangAsal, gudangTujuan);
            if (biaya > 0) {
                cout << "Biaya perjalanan dari " << gudangAsal << " ke " << gudangTujuan
                     << " adalah Rp " << biaya << endl;
            }

        } else if (pilihan == 4) {
            cout << "Keluar dari program. Terima kasih!" << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        cout << endl;
    } while (pilihan != 4);

    return 0;
}
