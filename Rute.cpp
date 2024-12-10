#include "Rute.h"

void createVertex(string namaGudang, adrVertex &v) {
    v = new gudang;
    namaGudang(v) = namaGudang;
    nextVertex(v) = NULL;
    firstEdge(v) = NULL;
}

void initGraph(graph &G) {
    firstVertex(G) = NULL;
}

void addVertex(graph &G, string namaGudang) {
    adrVertex v;
    createVertex(namaGudang, v);
    nextVertex(v) = firstVertex(G);
    firstVertex(G) = v;
}

void addEdge(graph &G, string gudangAsal, string gudangTujuan, int jarakTempuh) {
    adrVertex v = firstVertex(G);
    while (v != NULL && namaGudang(v) != gudangAsal) {
        v = nextVertex(v);
    }
    if (v != NULL) {
        adrEdge e = new rute;
        namaRute(e) = gudangTujuan;
        jarakTempuh(e) = jarakTempuh;
        nextEdge(e) = firstEdge(v);
        firstEdge(v) = e;
    }
}

void findAllRoutesUtil(graph &G, string posisiSekarang, string posisiTujuan, string rutePerjalanan[], int &indexRute, string allRoutes[][MAX_RUTE_LENGTH], int &ruteCount, JarakRute jarak[], int &jarakTempuh) {
    adrVertex v;
    adrEdge e;
    bool visited;

    rutePerjalanan[indexRute++] = posisiSekarang;

    if (posisiSekarang == posisiTujuan) {
        for (int i = 0; i < indexRute; i++) {
            allRoutes[ruteCount][i] = rutePerjalanan[i];
        }
        jarak[ruteCount].totalJarak = jarakTempuh;
        jarak[ruteCount].indexRute = ruteCount;
        ruteCount++;
    } else {
        v = findVertex(G, posisiSekarang);
        if (v != NULL) {
            e = firstEdge(v);
            while (e != NULL) {
                visited = false;
                for (int i = 0; i < indexRute; i++) {
                    if (rutePerjalanan[i] == namaRute(e)) {
                        visited = true;
                        break;
                    }
                }
                if (!visited) {
                    jarakTempuh += jarakTempuh(e);
                    findAllRoutesUtil(G, namaRute(e), posisiTujuan, rutePerjalanan, indexRute, allRoutes, ruteCount, jarak, jarakTempuh);
                    jarakTempuh -= jarakTempuh(e);
                }
                e = nextEdge(e);
            }
        }
    }
    
}

void findAllRoutes(graph &G, string gudangAsal, string gudangTujuan, string allRoutes[][], int &ruteCount, int jarak[]) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju)
    //F.S Semua rute dari gudangAsal ke gudangTujuan disimpan di allRoutes, dan jarak tempuh disimpan di jarak
    string rutePerjalanan[MAX_RUTE_LENGTH];
    int indexRute = 0;
    int jarakTempuh = 0;
    findAllRoutesUtil(G, gudangAsal, gudangTujuan, rutePerjalanan, indexRute, allRoutes, ruteCount, jarak, jarakTempuh);
}

void cariRuteTerpendek(graph G, string gudangAsal, string gudangTujuan) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju)
    //F.S memberikan rute terpendek dari gudangAsal ke gudangTujuan 
    //catatan : mencari nilai minimum dari array
    string allRoutes[][];
    JarakRute jarak[];
    int ruteCount = 0;

    findAllRoutes(G, gudangAsal, gudangTujuan, allRoutes, ruteCount, jarak);

    if (ruteCount > 0) {
        // Temukan indeks rute dengan jarak minimum (pencarian nilai ekstrim)
        int minIndex = 0;
        for (int i = 1; i < ruteCount; i++) {
            if (jarak[i].totalJarak < jarak[minIndex].totalJarak) {
                minIndex = i;
            }
        }

        // Cetak rute terpendek
        cout << "Rute terpendek: ";
        for (int i = 0; !allRoutes[jarak[minIndex].indexRute][i].empty(); i++) {
            cout << allRoutes[jarak[minIndex].indexRute][i] << " ";
        }
        cout << endl;
        cout << "Jarak tempuh: " << jarak[minIndex].totalJarak << endl;
    } else {
        cout << "Tidak ada rute yang ditemukan." << endl;
    
}

void hindariMacet(graph &G, string gudangAsal, string gudangTujuan, string ruteMacet) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju), dan ruteMacet (rute yang terdapat kemacetan)
    //F.S memberikan rute terpendek dari gudangAal ke gudangTujuan dengan menghindari ruteMacet
}

void lewatJalanTol(graph &G, string gudangAsal, string gudangTujuan, int jarakTol, bool tolTersedia) {
    //I.S Graf G telah diinisialisasi, dan mungkin sudah memiliki vertex (gudang) serta edge (rute)
    //F.S Jika opsi "tol tersedia" dipilih, rute baru akan ditambahkan dari gudang asal ke tujuan dengan informasi jalur tol (nama rute dan jarak)
}

int hitungBiayaPerjalanan(graph &G, string gudangAsal, string gudangTujuan){
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju)
    //I.S memberikan hasil perhitungan biaya perjalanan
    //catatan : biaya = jarakTempuh * ongkirPerKilo

    int ongkirPerKilo = 10000;
    string allRoutes[][];
    JarakRute jarak[];
    int ruteCount = 0;

    findAllRoutes(G, gudangAsal, gudangTujuan, allRoutes, ruteCount, jarak);

    if (ruteCount > 0) {
        // Temukan indeks rute dengan jarak minimum
        int minIndex = 0;
        for (int i = 1; i < ruteCount; i++) {
            if (jarak[i].totalJarak < jarak[minIndex].totalJarak) {
                minIndex = i;
            }
        }

        int totalJarak = jarak[minIndex].totalJarak;
        int biaya = totalJarak * ongkirPerKilo;
        return biaya;
    } else {
        cout << "Tidak ada rute yang ditemukan." << endl;
        return 0;
    
}
