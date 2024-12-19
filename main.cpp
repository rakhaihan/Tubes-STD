#include "Rute.h"

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

    int choice;
    string gudangAsal, gudangTujuan;

    do {
        cout << "Menu:\n";
        cout << "1. Lakukan Pengiriman\n";
        cout << "2. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Masukkan lokasi awal: ";
                cin >> gudangAsal;
                cout << "Masukkan lokasi tujuan: ";
                cin >> gudangTujuan;

                cariRuteTerpendek(G, gudangAsal, gudangTujuan);

                string macet;
                cout << "Apakah ada kemacetan (y/n)? ";
                cin >> macet;
                if (macet == "y" || macet == "Y") {
                    string lokasiMacet;
                    cout << "Masukkan lokasi kemacetan: ";
                    cin >> lokasiMacet;
                    hindariMacet(G, gudangAsal, gudangTujuan, lokasiMacet);
                }

                string tol;
                cout << "Apakah ingin lewat tol (y/n)? ";
                cin >> tol;
                if (tol == "y" || tol == "Y") {
                    int jarakTol;
                    cout << "Masukkan jarak tol: ";
                    cin >> jarakTol;
                    lewatJalanTol(G, gudangAsal, gudangTujuan, jarakTol, true);
                } else {
                    lewatJalanTol(G, gudangAsal, gudangTujuan, 0, false);
                }

                int biaya = hitungBiayaPerjalanan(G, gudangAsal, gudangTujuan);
                if (biaya != -1) {
                    cout << "Biaya perjalanan: " << biaya << " Berries" << endl; // Using "Berries" as currency for fun
                }

                break;
            }
            case 2:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (choice != 2);

    return 0;
}
