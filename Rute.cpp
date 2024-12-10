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

adrVertex findVertex(graph &G, string vertexName) {
    adrVertex v = firstVertex(G);
    while (v != NULL) {
        if (namaGudang(v) == vertexName) {
            return v;
        }
        v = nextVertex(v);
    }
    return NULL;
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

void findAllRoutes(graph &G, string gudangAsal, string gudangTujuan, string allRoutes[][MAX_RUTE_LENGTH], int &ruteCount, JarakRute jarak[]) {
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
    string allRoutes[MAX_RUTE_LENGTH][MAX_RUTE_LENGTH];
    JarakRute jarak[MAX_RUTE_LENGTH];
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
}

void hindariMacet(graph &G, string gudangAsal, string gudangTujuan, string ruteMacet) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju), dan ruteMacet (rute yang terdapat kemacetan)
    //F.S memberikan rute terpendek dari gudangAal ke gudangTujuan dengan menghindari ruteMacet
    string allRoutes[MAX_RUTE_LENGTH][MAX_RUTE_LENGTH];
    JarakRute jarak[MAX_RUTE_LENGTH];
    bool lewatRuteMacet;
    int ruteCount = 0;

    findAllRoutes(G, gudangAsal, gudangTujuan, allRoutes, ruteCount, jarak);

    // Filter out routes that use the congested route
    int filteredRuteCount = 0;
    string filteredRoutes[MAX_RUTE_LENGTH][MAX_RUTE_LENGTH];
    JarakRute filteredJarak[MAX_RUTE_LENGTH];

    for (int i = 0; i < ruteCount; i++) {
        bool lewatRuteMacet = false;
        for (int j = 0; !allRoutes[i][j].empty(); j++) {
            if (allRoutes[i][j] == ruteMacet) {
                lewatRuteMacet = true;
                break;
            }
        }
        if (!lewatRuteMacet) {
            for (int j = 0; !allRoutes[i][j].empty(); j++) {
                filteredRoutes[filteredRuteCount][j] = allRoutes[i][j];
            }
            filteredJarak[filteredRuteCount] = jarak[i];
            filteredRuteCount++;
        }
    }

    if (filteredRuteCount > 0) {
        // Temukan indeks rute dengan jarak minimum
        int minIndex = 0;
        for (int i = 1; i < filteredRuteCount; i++) {
            if (filteredJarak[i].totalJarak < filteredJarak[minIndex].totalJarak) {
                minIndex = i;
            }
        }

        cout << "Rute terpendek menghindari kemacetan: ";
        for (int i = 0; !filteredRoutes[filteredJarak[minIndex].indexRute][i].empty(); i++) {
            cout << filteredRoutes[filteredJarak[minIndex].indexRute][i] << " ";
        }
        cout << endl;
        cout << "Jarak tempuh: " << filteredJarak[minIndex].totalJarak << endl;
    } else {
        cout << "Tidak ada rute yang ditemukan yang menghindari kemacetan." << endl;
    }
}

void lewatJalanTol(graph &G, string gudangAsal, string gudangTujuan, int jarakTol, bool tolTersedia) {
    if (!tolTersedia) {
        cout << "Rute tol dari " << gudangAsal << " ke " << gudangTujuan << " tidak tersedia." << endl;
        return;
    }

    adrVertex vAsal = firstVertex(G);
    adrVertex vTujuan = firstVertex(G);
    bool foundAsal = false, foundTujuan = false;

    while (vAsal != nullptr) {
        if (namaGudang(vAsal) == gudangAsal) {
            foundAsal = true;
        }
        if (namaGudang(vTujuan) == gudangTujuan) {
            foundTujuan = true;
        }
        if (foundAsal && foundTujuan) {
            break;
        }
        if (!foundTujuan) {
            vTujuan = nextVertex(vTujuan);
        }
        if (!foundAsal) {
            vAsal = nextVertex(vAsal);
        }
    }

    if (!foundAsal) {
        addVertex(G, gudangAsal);
        vAsal = firstVertex(G);
        while (vAsal != nullptr && namaGudang(vAsal) != gudangAsal) {
            vAsal = nextVertex(vAsal);
        }
    }

    if (!foundTujuan) {
        addVertex(G, gudangTujuan);
        vTujuan = firstVertex(G);
        while (vTujuan != nullptr && namaGudang(vTujuan) != gudangTujuan) {
            vTujuan = nextVertex(vTujuan);
        }
    }

    if (vAsal != nullptr && vTujuan != nullptr) {
        addEdge(G, gudangAsal, gudangTujuan, jarakTol);
        cout << "Rute tol dari " << gudangAsal << " ke " << gudangTujuan << " dengan jarak " << jarakTol
             << " km berhasil ditambahkan." << endl;
    } else {
        cout << "Gagal menambahkan rute tol. Pastikan gudang asal dan tujuan valid." << endl;
    }
}

int hitungBiayaPerjalanan(graph &G, string gudangAsal, string gudangTujuan){
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju)
    //I.S memberikan hasil perhitungan biaya perjalanan
    //catatan : biaya = jarakTempuh * ongkirPerKilo

    int ongkirPerKilo = 10000;
    string allRoutes[MAX_RUTE_LENGTH][MAX_RUTE_LENGTH];
    JarakRute jarak[MAX_RUTE_LENGTH];
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
}
