#include "Rute.h"

int main() {
    graph G;
    initGraph(G);

    // Adding One Piece locations and edges (distances are just for example)
    addVertex(G, "Alabasta");
    addVertex(G, "Dressrosa");
    addVertex(G, "Skypiea");
    addVertex(G, "Water7");
    addVertex(G, "Zou");
    addVertex(G, "Wano");
    addVertex(G, "Loguetown");
    addVertex(G, "ImpelDown");

    addEdge(G, "Alabasta", "Dressrosa", 300);
    addEdge(G, "Dressrosa", "Skypiea", 200);
    addEdge(G, "Skypiea", "Water7", 250);
    addEdge(G, "Water7", "Zou", 150);
    addEdge(G, "Zou", "Wano", 100);
    addEdge(G, "Wano", "Loguetown", 400);
    addEdge(G, "Loguetown", "ImpelDown", 500);
    addEdge(G, "ImpelDown", "Alabasta", 600);
    addEdge(G, "Loguetown", "Alabasta", 450);

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
