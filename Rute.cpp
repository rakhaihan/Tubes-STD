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

void buildGraph(graph &G) {

}



void findAllRoutes(graph &G, string gudangAsal, string gudangTujuan, string allRoutes[][MAX_RUTE_LENGTH], int &ruteCount, int jarak[]) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju)
    //F.S Semua rute dari gudangAsal ke gudangTujuan disimpan di allRoutes, dan jarak tempuh disimpan di jarak

}

void cariRuteTerpendek(graph G, string gudangAsal, string gudangTujuan) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju)
    //F.S memberikan rute terpendek dari gudangAsal ke gudangTujuan
    //catatan : mencari nilai minimum dari array jarak

}

void hindariMacet(graph &G, string gudangAsal, string gudangTujuan, string ruteMacet) {
    //I.S terdefinisi graph G, GudangAsal (posisi saat ini), gudangTujuan (gudang yang dituju), dan ruteMacet (rute yang terdapat kemacetan)
    //F.S memberikan rute terpendek dari gudangAal ke gudangTujuan dengan menghindari ruteMacet
}

void lewatJalanTol(graph &G, string gudangAsal, string gudangTujuan, int jarakTol, bool tolTersedia) {
    //I.S Graf G telah diinisialisasi, dan mungkin sudah memiliki vertex (gudang) serta edge (rute)
    //F.S Jika opsi "tol tersedia" dipilih, rute baru akan ditambahkan dari gudang asal ke tujuan dengan informasi jalur tol (nama rute dan jarak)
}
