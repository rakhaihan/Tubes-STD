#include "Rute.h"

void createVertex(string namaGudang, adrVertex &v) {
    //I.S Nama gudang (namaGudang) diberikan, pointer v belum diinisialisasi
    //F.S Pointer v mengarah ke simpul baru yang merepresentasikan gudang dengan atribut namaGudang, serta atribut lainnya (nextVertex, firstEdge) diinisialisasi ke nilai awal (NULL)
    v = new gudang;
    namaGudang(v) = namaGudang;
    nextVertex(v) = NULL;
    firstEdge(v) = NULL;
}

void initGraph(graph &G) {
    //I.S Struktur data graph G dideklarasikan tetapi belum diinisialisasi
    //F.S Struktur data graph G diinisialisasi, di mana firstVertex bernilai NULL
    firstVertex(G) = NULL;
}

void addVertex(graph &G, string namaGudang) {
    //I.S Graph G dan nama gudang (namaGudang) diberikan. Vertex mungkin belum ada di dalam graph
    //F.S Vertex baru dengan nama gudang tersebut ditambahkan ke graph G di posisi awal (menjadi firstVertex)
    adrVertex v;
    createVertex(namaGudang, v);
    nextVertex(v) = firstVertex(G);
    firstVertex(G) = v;
}

void addEdge(graph &G, string gudangAsal, string gudangTujuan, int jarakTempuh) {
    //I.S Graph G diberikan, beserta gudang asal (gudangAsal), gudang tujuan (gudangTujuan), dan jarak tempuh (jarakTempuh). Edge mungkin belum ada
    //F.S Edge baru ditambahkan dari vertex yang sesuai dengan gudangAsal ke gudangTujuan dengan jarak tempuh yang diberikan
    adrVertex vAsal = findVertex(G, gudangAsal);
    if (vAsal != NULL) {
        adrEdge e = new rute;
        namaRute(e) = gudangTujuan;
        jarakTempuh(e) = jarakTempuh;
        nextEdge(e) = firstEdge(vAsal);
        firstEdge(vAsal) = e;
    }


    adrVertex vTujuan = findVertex(G, gudangTujuan);
    if (vTujuan != NULL) {
        adrEdge e = new rute;
        namaRute(e) = gudangAsal;
        jarakTempuh(e) = jarakTempuh;
        nextEdge(e) = firstEdge(vTujuan);
        firstEdge(vTujuan) = e;
    }
}

adrVertex findVertex(graph &G, string vertexName) {
    //I.S Graph G dan nama vertex (vertexName) diberikan
    //F.S Mengembalikan pointer ke vertex dengan nama sesuai (vertexName) jika ditemukan, atau NULL jika tidak ditemukan
    adrVertex v = firstVertex(G);
    while (v != NULL) {
        if (namaGudang(v) == vertexName) {
            return v;
        }
        v = nextVertex(v);
    }
    return NULL;
}

void printAllGudang(graph &G) {
    adrVertex currentVertex = firstVertex(G);
    while (currentVertex != NULL) {
        cout << namaGudang(currentVertex) << endl;
        currentVertex = nextVertex(currentVertex);
    }
}

bool isValidCity(graph &G, string &namaGudang) {
    adrVertex v = findVertex(G, namaGudang);
    return v != NULL;
}

void findAllRoutesUtil(graph &G, string posisiSekarang, string posisiTujuan, string rutePerjalanan[], int &indexRute, string allRoutes[][MAX_RUTE_LENGTH], int &ruteCount, JarakRute jarak[], int &jarakTempuh) {
    //I.S Graph G, posisi sekarang, posisi tujuan, array rute perjalanan, dan variabel pembantu lainnya (index, jarak tempuh) diberikan
    //F.S Semua rute dari posisiSekarang ke posisiTujuan ditemukan dan disimpan di allRoutes, dengan jarak tempuh masing-masing disimpan di jarak

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
        // cari jarak minimum (nilai ekstrim)
        int minIndex = 0;
        for (int i = 1; i < ruteCount; i++) {
            if (jarak[i].totalJarak < jarak[minIndex].totalJarak) {
                minIndex = i;
            }
        }


        cout << "Rute terpendek: ";
        int i = 0;
        while (!allRoutes[jarak[minIndex].indexRute][i].empty()) {
            cout << allRoutes[jarak[minIndex].indexRute][i] << " ";
            i++;
        }
        cout << endl;
        cout << "Jarak tempuh: " << jarak[minIndex].totalJarak << endl;
    } else {
        cout << "Tidak ada rute yang ditemukan." << endl;
    }
}


void hindariMacet(graph &G, string gudangAsal, string gudangTujuan, string ruteMacet) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju), dan ruteMacet (rute yang terdapat kemacetan)
    //F.S memberikan rute terpendek dari gudangAsal ke gudangTujuan dengan menghindari ruteMacet
    string allRoutes[MAX_RUTE_LENGTH][MAX_RUTE_LENGTH];
    JarakRute jarak[MAX_RUTE_LENGTH];
    bool lewatRuteMacet;
    int ruteCount = 0;

    findAllRoutes(G, gudangAsal, gudangTujuan, allRoutes, ruteCount, jarak);

    int filteredRuteCount = 0;
    string filteredRoutes[MAX_RUTE_LENGTH][MAX_RUTE_LENGTH];
    JarakRute filteredJarak[MAX_RUTE_LENGTH];

    for (int i = 0; i < ruteCount; i++) {
        bool lewatRuteMacet = false;
        int j = 0;
        while (!allRoutes[i][j].empty()) {
            if (allRoutes[i][j] == ruteMacet) {
                lewatRuteMacet = true;
                break;
            }
            j++;
        }
        if (!lewatRuteMacet) {
            int k = 0;
            while (!allRoutes[i][k].empty()) {
                filteredRoutes[filteredRuteCount][k] = allRoutes[i][k];
                k++;
            }
            filteredJarak[filteredRuteCount] = jarak[i];
            filteredRuteCount++;
        }
    }

    if (filteredRuteCount > 0) {
        //cari jarak minimum
        int minIndex = 0;
        for (int i = 1; i < filteredRuteCount; i++) {
            if (filteredJarak[i].totalJarak < filteredJarak[minIndex].totalJarak) {
                minIndex = i;
            }
        }

        cout << "Rute terpendek menghindari kemacetan: ";
        int i = 0;
        while (!filteredRoutes[filteredJarak[minIndex].indexRute][i].empty()) {
            cout << filteredRoutes[filteredJarak[minIndex].indexRute][i] << " ";
            i++;
        }
        cout << endl;
        cout << "Jarak tempuh: " << filteredJarak[minIndex].totalJarak << endl;
    } else {
        cout << "Tidak ada rute yang ditemukan yang menghindari kemacetan." << endl;
    }
}



void lewatJalanTol(graph &G, string gudangAsal, string gudangTujuan, int jarakTol, bool tolTersedia) {
    //I.S Graph G, gudang asal, gudang tujuan, jarak tol, dan status tol tersedia (tolTersedia) diberikan
    //F.S Jika tolTersedia bernilai true, edge dengan jarak tol ditambahkan dari gudangAsal ke gudangTujuan. Jika tidak, pesan ditampilkan bahwa rute tol tidak tersedia
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
