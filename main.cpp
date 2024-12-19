#include "Rute.h"
#include <iostream>

using namespace std;

int main() {
    graph G;
    initGraph(G);

    addVertex(G, "Alabasta");
    addVertex(G, "Dressrosa");
    addVertex(G, "Skypiea");
    addVertex(G, "Water7");
    addVertex(G, "Zou");
    addVertex(G, "Wano");
    addVertex(G, "Loguetown");
    addVertex(G, "Elbaph");

    addEdge(G, "Skypiea", "Loguetown", 250);
    addEdge(G, "Loguetown", "Elbaph", 1100);
    addEdge(G, "Loguetown", "Alabasta", 150);
    addEdge(G, "Loguetown", "Water7", 200);
    addEdge(G, "Water7", "Dressrosa", 350);
    addEdge(G, "Dressrosa", "Wano", 210);
    addEdge(G, "Alabasta", "Wano", 800);
    addEdge(G, "Wano", "Zou", 450);
    addEdge(G, "Elbaph", "Zou", 200);

    printAllGudang(G);
    cout << "\n";

    string choice;
    string gudangAsal, gudangTujuan;

    do {
        cout << "Menu:\n";
        cout << "1. Lakukan Pengiriman\n";
        cout << "2. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        if (choice == "1") {
            cout << "Masukkan lokasi awal: ";
            cin >> gudangAsal;
            cout << "Masukkan lokasi tujuan: ";
            cin >> gudangTujuan;

            if (!isValidCity(G, gudangAsal)) {
                cout << "Lokasi awal tidak valid. Silakan coba lagi.\n";
            } else if (!isValidCity(G, gudangTujuan)) {
                cout << "Lokasi tujuan tidak valid. Silakan coba lagi.\n";
            } else {
                cariRuteTerpendek(G, gudangAsal, gudangTujuan);

                string macet;
                cout << "Apakah ada kemacetan (y/n)? ";
                cin >> macet;
                if (macet == "y") {
                    string lokasiMacet;
                    cout << "Masukkan lokasi kemacetan: ";
                    cin >> lokasiMacet;
                    if (!isValidCity(G, lokasiMacet)) {
                        cout << "Lokasi kemacetan tidak valid. Silakan coba lagi.\n";
                    } else {
                        hindariMacet(G, gudangAsal, gudangTujuan, lokasiMacet);
                    }
                }

                string tol;
                cout << "Apakah ingin lewat tol (y/n)? ";
                cin >> tol;
                if (tol == "y") {
                    int jarakTol;
                    cout << "Masukkan jarak tol: ";
                    cin >> jarakTol;
                    if (jarakTol >= 0) {
                        lewatJalanTol(G, gudangAsal, gudangTujuan, jarakTol, true);
                    } else {
                        cout << "Masukkan nilai jarak tol yang valid.\n";
                    }
                } else if (tol == "n") {
                    lewatJalanTol(G, gudangAsal, gudangTujuan, 0, false);
                } else {
                    cout << "Pilihan tidak valid untuk lewat tol. Silakan coba lagi.\n";
                }

                int biaya = hitungBiayaPerjalanan(G, gudangAsal, gudangTujuan);
                if (biaya != -1) {
                    cout << "Biaya perjalanan: " << biaya << " Berries" << endl; // Using "Berries" as currency for fun
                }
            }
        } else if (choice == "2") {
            cout << "Keluar dari program.\n";
        } else {
            cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != "2");

    return 0;
}
