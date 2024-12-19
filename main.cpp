#include "Rute.h"

int main() {
    graph G;
    initGraph(G);

    addVertex(G, "Jakarta");
    addVertex(G, "Bandung");
    addVertex(G, "Surabaya");
    addVertex(G, "Yogyakarta");
    addVertex(G, "Semarang");
    addVertex(G, "Bali");
    addVertex(G, "Medan");
    addVertex(G, "Makassar");

    addEdge(G, "Jakarta", "Bandung", 150);
    addEdge(G, "Jakarta", "Yogyakarta", 560);
    addEdge(G, "Bandung", "Surabaya", 790);
    addEdge(G, "Yogyakarta", "Surabaya", 330);
    addEdge(G, "Jakarta", "Semarang", 450);
    addEdge(G, "Semarang", "Yogyakarta", 130);
    addEdge(G, "Surabaya", "Bali", 300);
    addEdge(G, "Medan", "Jakarta", 1435);
    addEdge(G, "Makassar", "Surabaya", 1100);
    addEdge(G, "Medan", "Makassar", 2480);

    printAllGudang(G);
    cout << "\n";

    int choice;
    string gudangAsal, gudangTujuan;

    do {
        cout << "Menu:\n";
        cout << "1. Lakukan pengiriman\n";
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
                    cout << "Biaya perjalanan: " << biaya << " Rupiah" << endl;
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
